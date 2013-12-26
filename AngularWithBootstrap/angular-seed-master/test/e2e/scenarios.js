'use strict';

/* http://docs.angularjs.org/guide/dev_guide.e2e-testing */

describe('my app', function() {

  beforeEach(function() {
    browser().navigateTo('../../app/index.html');
  });
  
  afterEach(function() {
    pause();
  });


  it('should automatically redirect to /login when location hash/fragment is empty', function() {
    expect(browser().location().url()).toBe("/login");
  });


  describe('login', function() {

    beforeEach(function() {
      browser().navigateTo('#/login');
    });


    it('should render login when user navigates to /login', function() {
      expect(element('[ng-view] label:first').text()).
        toMatch(/Login/);
    });

  });


  describe('register', function() {

    beforeEach(function() {
      browser().navigateTo('#/register');
    });


    it('should render register when user navigates to /register', function() {
      expect(element('[ng-view] label:first').text()).
        toMatch(/Register/);
    });

  });
});
