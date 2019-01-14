import React from 'react'

export default class Login extends React.Component{

  state = {
    id: "",
    password: "",
    error: null,
  }

  onChange = (e) => {
    const name = e.target.name
    const value = e.target.value

    this.setState({
      ...this.state,
      [name] : value,
    })
  }

  onSubmit = (e) => {

    e.preventDefault();

    if(this.state.id && this.state.password){

      if(this.props.onSubmit){
        this.props.onSubmit({
          id: this.state.id,
          password: this.state.password
        })
      }
    }


    if(!this.state.id){
      this.setState({
        ...this.state,
        error: "Id is required."
      })
    }


    if(!this.state.password){
      this.setState({
        ...this.state,
        error: "Password is required."
      })

    }



  }
  render () {

    return (
      <form
        onSubmit={this.onSubmit}
        className={'login-form'}>

        {this.state.error ? <div className={'alert error'}>{this.state.error}</div> : null}
        <div className={'form-item'}>
          <label>Your ID</label>
          <input autoCapitalize={'None'} autoCorrect={'None'} autoComplete={'None'} onChange={this.onChange} value={this.state.id} className={'form-text'} name={'id'}/>
        </div>
        <div className={'form-item'}>
          <label>Password</label>
          <input type={'password'} value={this.state.password} onChange={this.onChange} className={'form-text form-password'} name={'password'}/>
        </div>
        <button className={'primary-btn'} type={'submit'}>Login</button>
      </form>
    )
  }
}