import React, { Fragment } from 'react'
import { Router, Route, Switch } from 'react-router-dom'
import { history } from './history'
import Scoreboard from './scoreboard'
import Problems from './problems'
import ViewProblem from './view-problem'
import Submissions from './submissions'
import Login from './login'

export default class App extends React.Component {
  render () {
    return (
      <Fragment>
        <Router history={history}>
          <Switch>
            <Route exact path={'/'} component={Scoreboard}/>
            <Route exact path='/scoreboard' component={Scoreboard}/>
            <Route exact path='/problems' component={Problems}/>
            <Route exact path='/problems/:id' component={ViewProblem}/>
            <Route exact path='/submissions' component={Submissions}/>
            <Route exact path='/login' component={Login}/>
          </Switch>
        </Router>
      </Fragment>

    )
  }
}

