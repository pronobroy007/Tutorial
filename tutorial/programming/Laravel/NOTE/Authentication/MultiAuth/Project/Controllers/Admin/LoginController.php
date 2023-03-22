<?php

namespace App\Http\Controllers\Admin;

use Illuminate\Http\Request;
use App\Http\Controllers\Controller;
use Auth;

class LoginController extends Controller
{ 
    public function __construct()
    {
        $this->middleware('guest:admin')->except('logout');
    }

    public function showLoginForm()
    {
        return view('admin\admin-login');
    }

    public function login(Request $req)
    {
        $this->validate($req, [
            'email' => 'required|email',
            'password' => 'required|min:6'
        ]);
        
        if(Auth::guard('admin')->attempt(['email' => $req->email, 'password' => $req->password],  $req->remember))
        {
            return redirect()->intended(route('admin.home'));
        }

        return ridirect()->back()->withInput($req->only('email', 'remember'));
    }

}
