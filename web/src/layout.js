import React, { Component } from 'react'
import styled from 'styled-components'
import Header from './header'
import { bindActionCreators } from 'redux'
import { connect } from 'react-redux'

const Content = styled.div`
  padding: 15px;
  box-sizing: border-box;
  table{  
    text-align: left;
    width: 100%;
    margin-bottom: 1rem;
    background-color: transparent;
    border-collapse: collapse;
    th tr{
      vertical-align: bottom;
      border-bottom: 2px solid #dee2e6;
    }
    td{
      padding: .75rem;
      vertical-align: top;
      border-top: 1px solid #dee2e6;
    }
    th{
      padding: .75rem;
      border-top: 1px solid #dee2e6;
    }
  }
  table tbody tr:hover {
    background-color: rgba(0,0,0,.05);
  }
  .form-item{
    margin-bottom: 10px;
    label{
      display: inline-block;
      margin-bottom: .5rem;
      
    }
    .form-text, .form-password{
      box-sizing: border-box;
      display: block;
      width: 100%;
      height: calc(2.25rem + 2px);
      padding: .375rem .75rem;
      font-size: 1rem;
      line-height: 1.5;
      color: #495057;
      background-color: #fff;
      background-clip: padding-box;
      border: 1px solid #ced4da;
      border-radius: .25rem;
      transition: border-color .15s ease-in-out,box-shadow .15s ease-in-out;
    }
    .form-textarea{
      box-sizing: border-box;
      display: block;
      width: 100%;
      padding: .375rem .75rem;
      font-size: 1rem;
      line-height: 1.5;
      color: #495057;
      background-color: #fff;
      background-clip: padding-box;
      border: 1px solid #ced4da;
      border-radius: .25rem;
      transition: border-color .15s ease-in-out,box-shadow .15s ease-in-out;
    }
  }
  button{
    display: inline-block;
    font-weight: 400;
    text-align: center;
    white-space: nowrap;
    vertical-align: middle;
    -webkit-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    border: 1px solid transparent;
    border-top-color: transparent;
    border-right-color: transparent;
    border-bottom-color: transparent;
    border-left-color: transparent;
    padding: .375rem .75rem;
    font-size: 1rem;
    line-height: 1.5;
    border-radius: .25rem;
    transition: color .15s ease-in-out,background-color .15s ease-in-out,border-color .15s ease-in-out,box-shadow .15s ease-in-out;
    &.primary-btn{
      color: #fff;
      background-color: #0069d9;
      border-color: #0062cc;
    }
  }
  
  .login-form{
    max-width: 300px;
    margin: 0 auto;
  }
  .alert{
    position: relative;
    padding: .75rem 1.25rem;
    margin-bottom: 1rem;
    border: 1px solid transparent;
    border-top-color: transparent;
    border-right-color: transparent;
    border-bottom-color: transparent;
    border-left-color: transparent;
    border-radius: .25rem;
  }
  .error{
    color: #721c24;
    background-color: #f8d7da;
    border-color: #f5c6cb;
  }
`

class Layout extends Component {

  render () {
    const {message} = this.props

    return (
      <div>
        <Header/>
        <Content>
          {message && (
            <div className={`alert ${message.type}`}>
              {message.body}
            </div>)}
          {this.props.children}
        </Content>
      </div>
    )
  }
}

const mapStateToProps = (state, props) => ({
  message: state.message,
})

const mapDispatchToProps = (dispatch) => bindActionCreators({}, dispatch)

export default connect(mapStateToProps, mapDispatchToProps)(Layout)