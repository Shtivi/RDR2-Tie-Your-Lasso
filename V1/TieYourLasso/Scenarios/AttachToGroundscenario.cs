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
    public class AttachToGroundScenario : IScenario
    {
        public bool IsFinished { get; private set; }

        private RopesFactory ropesFactory { get; set; }
        private SpawnedPropsManager propsManager { get; set; }
        private AttachedRope rope { get; set; }
        private Ped ped { get; set; }
        private Vector3 groundPosition { get; set; }

        private bool IsHanging { get; set; }

        public AttachToGroundScenario(RopesFactory ropesFactory, SpawnedPropsManager propsManager, Ped ped)
        {
            this.ropesFactory = ropesFactory;
            this.propsManager = propsManager;
            this.ped = ped;
            this.groundPosition = groundPosition;
            IsFinished = false;
        }

        public void Start()
        {
            var player = Game.Player.Character;
            var groundPosition = new Vector3(player.Position.X, player.Position.Y, World.GetGroundHeight(player.Position));
            var neckCoords = Function.Call<Vector3>(Hash.GET_PED_BONE_COORDS, ped.Handle, 14284);
            float ropeLength = neckCoords.DistanceTo(groundPosition);

            if (ped.IsInAir)
            {
                ropeLength -= 0.1f;
            }

            rope = ropesFactory.AttachEntityToMapPosition(groundPosition, ped, ropeLength, "SKEL_NECK0");
        }

        public void Update()
        {
            if (!ped.IsAlive)
            {
                IsFinished = true;
                return;
            }

            if (IsHanging && !ShouldHang)
            {
                Script.Wait(1000);
                if (!ShouldHang)
                {
                    IsHanging = false;
                }
            }

            if (ShouldHang && !IsHanging)
            {
                StartHanging();
            }

            if (IsHanging)
            {
                Function.Call(Hash.SET_PED_TO_RAGDOLL, ped.Handle, 1000, 1000, 0, false, false, false);
                Function.Call(Hash._SET_ENTITY_HEALTH, ped.Handle, Math.Max(ped.Health - 1, 0));
                Script.Wait(80);
            }
        }

        private bool ShouldHang
        {
            get
            {
                return ped.HeightAboveGround > 1.1f;
            }
        }

        private void StartHanging()
        {
            if (ped != null && ped.Exists() && ped.IsHuman)
            {
                IsHanging = true;
            }
        }
    }
}
