using RDR2;
using RDR2.Math;
using RDR2.Native;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TieYourLasso.Scenarios
{
    public class HangPedScenario : IScenario
    {
        private RopesFactory ropesFactory { get; set; }
        private SpawnedPropsManager propsManager { get; set; }
        private AttachedRope rope { get; set; }
        private bool isAnimating { get; set; }
        private Ped hangedPed { get; set; }
        private Vector3 hangingPosition { get; set; }

        public bool IsFinished { get { return true;  } }

        public HangPedScenario(RopesFactory ropesFactory, SpawnedPropsManager propsManager, Ped ped, Vector3 hangingPosition)
        {
            this.ropesFactory = ropesFactory;
            this.propsManager = propsManager;
            this.hangedPed = ped;
            this.hangingPosition = hangingPosition;
        }

        public void Start()
        {
            var player = Game.Player.Character;
            hangedPed.Task.ClearAllImmediately();
            Function.Call(Hash.TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS, hangedPed.Handle, true);
            this.hangedPed.AlwaysKeepTask = true;

            RDR2.UI.Screen.FadeOut(1000);
            Script.Wait(1000);

            var pos = player.Position + Vector3.Zero;
            player.Position = player.Position + player.ForwardVector * 3;

            var groundPos = new Vector3(player.Position.X, player.Position.Y, World.GetGroundHeight(pos));

            var neckCoords = Function.Call<Vector3>(Hash.GET_PED_BONE_COORDS, hangedPed.Handle, 14284);
            float ropeLength = neckCoords.DistanceTo(hangingPosition) - 0.45f;
            rope = ropesFactory.AttachEntityToMapPosition(hangingPosition, hangedPed, ropeLength, "SKEL_NECK0");

            this.hangedPed.Task.PlayAnimation("script_re@public_hanging@female", "struggle_idle_female");

            //var seq = new TaskSequence();
            //seq.AddTask.TurnTo(hangedPed, 200);
            //seq.Close();
            //player.Task.PerformSequence(seq);

            RDR2.UI.Screen.FadeIn(1000);

            Script.Wait(4000);
            Function.Call(Hash._SET_ENTITY_HEALTH, hangedPed.Handle, 0);
        }

        public void Update()
        {
            //if (this.hangedPed == null)
            //{
            //    return;
            //}

            ////RDR2.UI.Screen.ShowSubtitle("above ground: " + hangedPed.HeightAboveGround + " Z: " + hangedPed.Position.Z + " world: " + World.GetGroundHeight(hangedPed.Position));
            //if (hangedPed.HeightAboveGround - 2f >= 0.0f)
            //{
            //    if (!isAnimating)
            //    {
            //        this.hangedPed.Task.PlayAnimation("script_re@public_hanging@female", "struggle_idle_female");
            //        this.isAnimating = true;
            //    }

            //    Script.Wait(60);
            //    Function.Call(Hash._SET_ENTITY_HEALTH, hangedPed.Handle, Math.Max(hangedPed.Health - 1, 0));
            //}
            //else
            //{
            //    isAnimating = false;
            //}
        }
    }
}
