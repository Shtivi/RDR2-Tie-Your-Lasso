using System;
using System.Windows.Forms;
using RDR2;
using RDR2.UI;
using RDR2.Native;
using RDR2.Math;
using System.IO;
using RDR2.NaturalMotion;
using TieYourLasso.Scenarios;
using System.Collections.Generic;

namespace TieYourLasso
{
    public class Main : Script
    {
        private LassoHandler lassoHandler { get; set; }
        private SpawnedPropsManager propsManager { get; set; }
        private RaycastHelper raycastHelper { get; set; }
        private RopesFactory ropesFactory { get; set; }

        private List<IScenario> activeScenarios { get; set; }

        public Main()
        {
            Interval = 1;

            KeyDown += OnKeyDown;
            KeyUp += OnKeyUp;
            Tick += OnTick;

            Logger.SetPath(this.BaseDirectory + "/TieYourLasso.txt");
            log("started");

            this.activeScenarios = new List<IScenario>();
            this.lassoHandler = new LassoHandler();
            this.raycastHelper = new RaycastHelper();
            this.propsManager = new SpawnedPropsManager();
            this.ropesFactory = new RopesFactory(propsManager);
        }

        private void OnTick(object sender, EventArgs e)
        {
            try
            {
                lassoHandler.Update();
                activeScenarios.ForEach(scenario => scenario.Update());
                activeScenarios.RemoveAll(scenario => scenario.IsFinished);

                if (lassoHandler.IsTargetPed && !Game.Player.Character.IsOnMount)
                {
                    RDR2.UI.Screen.ShowSubtitle("~INPUT_RELOAD~ Attach to ground");
                }
            }
            catch(Exception ex)
            {
                log(ex.ToString());
            }
        }

        private void OnKeyUp(object sender, KeyEventArgs e)
        {
            try
            {
                if (e.KeyCode == Keys.R)
                {
                    if (lassoHandler.IsTargetPed && !Game.Player.Character.IsOnMount)
                    {
                        var scenario = new AttachToGroundScenario(ropesFactory, propsManager, lassoHandler.LassoTarget as Ped);
                        scenario.Start();
                        activeScenarios.Add(scenario);
                    }
                }
            } 
            catch(Exception ex)
            {
                log(ex.ToString());
            }
        }

        private void OnKeyDown(object sender, KeyEventArgs e)
        {

        }

        private void log(string msg)
        {
            Logger.Log(msg);
        }
    }
}
