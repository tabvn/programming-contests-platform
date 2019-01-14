import React, { Component } from 'react'
import styled from 'styled-components'
import Scoreboard from './scoreboard'
import service from './service'
import Login from './login'
import Problems from './problems'
import Submissions from './submissions'
import ViewProblem from './view-problem'

const Header = styled.div`
  min-height: 4rem;
  background-color: #563d7c;
  box-shadow: 0 .5rem 1rem rgba(0,0,0,.05),inset 0 -1px 0 rgba(0,0,0,.1);
  display: flex;
  flex-direction: row;
  align-items: center;
  padding: 0 20px;

`

const Logo = styled.div`
  color: #FFF;
  font-weight: bold;
  flex-grow: 1;
  
`

const Menu = styled.div`
    display: flex;
    flex-direction: row;
`

const MenuItem = styled.div`
  font-size: 1rem;
  font-weight: 400;
  line-height: 1.5;
  color: ${props => props.active ? '#FFF' : '#cbbde2'};
  padding: 5px 10px;
  cursor: pointer;
  &.no-link{
    cursor: default;
    color: rgba(255,255,255,.75);
  }
`

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

class App extends Component {

  state = {
    error: null,
    submissions: [
      {
        userId: 201,
        problem: 'A',
        code: 'abc',
        status: 0,
        error: null,
        score: 0,
        accepted: 0,
      },
      {
        userId: 201,
        problem: 'A',
        code: 'abc',
        status: 2,
        error: 'Time limit execution',
        accepted: 0,
      },
      {
        userId: 201,
        problem: 'A',
        code: 'abc',
        status: 2,
        score: 30,
        error: null,
        accepted: 1.
      }
    ],
    problems: [
      {name: 'A', description: '', maxScore: 30},
      {name: 'B', description: '', maxScore: 30}
    ],
    scoreboard: [
      {
        id: 201,
        name: 'Nguyen Dinh Toan',
        problems: [
          {
            name: 'B',
            score: -1,
          },
          {
            name: 'A',
            score: 10,
          }
        ],
        total: 10,

      },
    ],
    page: 'scoreboard',
    user: service.user,
  }

  componentDidMount () {
    service.get('api').then((res) => {
      this.setState({
        ...this.state,
        scoreboard: res.data.scoreboard,
        problems: res.data.problems,
        submissions: res.data.submissions,
      })
    }).catch((e) => {

      this.setState({
        ...this.state,
        error: 'An error loading data'
      })
    })
  }

  renderPage = () => {

    switch (this.state.page) {

      case 'scoreboard':

        return <Scoreboard problems={this.state.problems} data={this.state.scoreboard}/>

      case 'problems':

        return <Problems onSelect={(p) => {
          this.setState({
            selectedProblem: p,
            page: 'viewProblem',

          })
        }} problems={this.state.problems}/>

      case 'login':

        return (
          <Login onSubmit={(data) => {
            service.auth(data.id, data.password).then((user) => {
              this.setState({
                ...this.state,
                user: user
              })
            })
          }}/>
        )

      case 'viewProblem':

        return <ViewProblem onSubmit={(data) => {

          service.solveProblem(data.problem, data.code).then((data) => {

            this.setState({
              ...this.state,
              submission: [...this.state.submissions, data]
            })

          }).catch((e) => {
            this.setState({
              error: 'Your submission could not be saved.'
            })
          })

        }} problem={this.state.selectedProblem}/>

      case 'submissions':
        return <Submissions submissions={this.state.submissions}/>

      default:

        break
    }

    return null
  }

  render () {
    const {user} = this.state
    return (
      <div>
        <Header>
          <Logo>
            Logo Name
          </Logo>
          <Menu>
            <MenuItem active={this.state.page === 'scoreboard'} onClick={() => {
              this.setState({
                page: 'scoreboard'
              })
            }}>Scoreboard</MenuItem>
            <MenuItem active={this.state.page === 'problems'} onClick={() => {
              this.setState({
                page: 'problems',
                selectedProblem: null
              })
            }}>Problems</MenuItem>

            <MenuItem active={this.state.page === 'submissions'} onClick={() => {
              this.setState({
                page: 'submissions'
              })

            }}>Submissions</MenuItem>
            <MenuItem active={this.state.page === 'login'} onClick={() => {
              if (!user) {
                this.setState({
                  page: 'login'
                })
              }

            }} className={'no-link'}>{this.state.user ? this.state.user.name : 'Login'}</MenuItem>
          </Menu>
        </Header>

        <Content>
          {this.state.error ? <div className={'alert error'}>
            {this.state.error}
          </div> : null}

          {this.renderPage()}
        </Content>
      </div>
    )
  }
}

export default App
