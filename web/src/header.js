import React, { Fragment } from 'react'
import styled from 'styled-components'
import { bindActionCreators } from 'redux'
import { connect } from 'react-redux'
import { logout } from './redux/actions'
import { Link } from 'react-router-dom'
import { history } from './history'

const Container = styled.div`
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
    a{
      text-decoration: none;
      font-size: 1rem;
      font-weight: 400;
      line-height: 1.5;
      color: #cbbde2;
      padding: 5px 10px;
      cursor: pointer;
      &.no-link{
        cursor: default;
        color: rgba(255,255,255,.75);
      }
    }
`

class Header extends React.Component {

  render () {

    const {user} = this.props

    return (
      <Container>
        <Logo>
          Programming contests platform
        </Logo>
        <Menu>
          {
            user && (
              <Fragment>
                <Link to={'/'}>Scoreboard</Link>
                <Link to={'/problems'}>Problems</Link>
                <Link to={'/submissions'}>Submissions</Link>
              </Fragment>
            )
          }
          {user ? <Link to={'/'}>{user.name}</Link> : <Link to={'/login'}>Login</Link>}
          {
            user && <button onClick={() => {
              this.props.logout()
              history.push('/login')
            }}>Sign Out
            </button>
          }

        </Menu>
      </Container>
    )
  }
}

const mapStateToProps = (state, props) => ({
  user: state.app.user,
})

const mapDispatchToProps = (dispatch) => bindActionCreators({
  logout,
}, dispatch)

export default connect(mapStateToProps, mapDispatchToProps)(Header)