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
    padding: .125rem .55rem;
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

`

const Logo = styled.div`
  color: #FFF;
  font-weight: bold;
  flex-grow: 1;
  
`

const Menu = styled.div`
    display: flex;
    flex-direction: row;
    align-items: center;
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

let ws

let queue = []

class App extends Component {

  state = {
    error: null,
    submissions: [],
    problems: [],
    scoreboard: [],
    page: 'scoreboard',
    user: service.user,
  }

  loadData = () => {

    this.reloadScoreBoard()

    service.get('api/my-submissions').then((res) => {
      this.setState({
        submissions: res.data,
      })
    }).catch((e) => {

      if (e.response && e.response.status && e.response.status === 401) {
        service.logout();
        this.setState({
          page: 'login',
          error: 'An error loading submissions'
        })
      } else {
        this.setState({
          error: 'An error loading submissions'
        })
      }

    })

  }

  componentDidMount () {

    this.connect()

    if (this.state.user) {
      this.loadData()
    } else {

      this.setState({
        page: 'login'
      })
    }

  }

  reloadScoreBoard () {

    service.get('api').then((res) => {
      this.setState({
        ...this.state,
        scoreboard: res.data.scoreboard,
        problems: res.data.problems,
      })
    }).catch((e) => {

      if (e.response && e.response.status && e.response.status === 401) {
        this.setState({
          page: 'login',
          error: 'An error loading data'
        })
      } else {
        this.setState({
          error: 'An error loading data'
        }, () => {
          service.logout()
        })
      }

    })

  }

  connect () {
    ws = new WebSocket(`${window.Ued.ws}`)
    ws.onopen = () => {

      // check queue and send
      if (service.user) {
        ws.send(JSON.stringify({
          action: 'auth',
          payload: service.user.token,
        }))
      }
      queue.forEach((p) => {
        ws.send(JSON.stringify(p))
      })

      queue = []
    }
    ws.onmessage = (event) => {

      const data = event.data

      try {

        const message = JSON.parse(data)
        switch (message.action) {
          case 'reload':
            this.reloadScoreBoard()
            break

          case 'submission':

            let submissions = this.state.submissions

            const sIndex = submissions.findIndex((s) => s.id === message.payload.id)
            if (sIndex !== -1) {
              submissions[sIndex] = message.payload

            } else {
              submissions.push(message.payload)
            }

            this.setState({
              ...this.state,
              submissions: submissions,
            })

            break

          default:

            break
        }

      } catch (e) {
        console.log('an error parser message', e)
      }

    }
    ws.onclose = () => {
      this.connect()
    }
    ws.onerror = () => {
      this.connect()
    }
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

              const data = {
                action: 'auth',
                payload: user.token,
              }

              if (ws.readyState === 1) {
                ws.send(JSON.stringify(data))
              } else {
                queue.push(data)
              }

              this.loadData()
              this.setState({
                error: null,
                user: user,
                page: 'scoreboard',
              })
            }).catch((e) => {
              let msg = 'Login error'

              if (e.response && e.response.data && e.response.data.message) {
                msg = e.response.data.message
              }
              this.setState({
                error: msg,
              }, () => service.logout())
            })
          }}/>
        )

      case 'viewProblem':

        return <ViewProblem onSubmit={(data) => {

          service.solveProblem(data.problem, data.code).then((data) => {

            const submissions = [data].concat(this.state.submissions)

            this.setState({
              page: 'submissions',
              submission: submissions,
            })

          }).catch((e) => {
            if (e.response && e.response.status && e.response.status === 401) {
              this.setState({
                page: 'login',
                error: 'Your submission could not be saved.'
              })

            } else {
              this.setState({
                error: 'Your submission could not be saved.'
              })
            }

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
            Programming contests platform
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
            <MenuItem
              active={this.state.page === 'login'}
              onClick={() => {
                if (!user) {
                  this.setState({
                    page: 'login'
                  })
                }

              }}
              className={this.state.user ? 'no-link' : 'has-link'}>{this.state.user ? this.state.user.name : 'Login'}</MenuItem>
            {this.state.user ? <MenuItem>
              <button onClick={() => {

                this.setState({
                  page: 'login',
                  user: null,
                }, () => {
                  service.logout()
                })

              }}>Sign Out
              </button>
            </MenuItem> : null}
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
