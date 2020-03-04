using RDR2;
using RDR2.Native;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TieYourLasso
{
    public class LassoHandler
    {
        public Entity LassoTarget { get; private set; }

        public LassoHandler()
        {
            this.LassoTarget = null;
        }

        public bool IsLassoEquiped
        {
            get
            {
                var player = Game.Player.Character;
                return (player.Weapons.Current != null) && (player.Weapons.Current.Hash == WeaponHash.Lasso);
            }
        }

        public bool IsTargetPed
        {
            get
            {
                return (LassoTarget != null) && LassoTarget.Model.IsPed;
            }
        }

        public bool DidJustLassoed { get; private set; }

        public void Update()
        {
            DidJustLassoed = false;
            var player = Game.Player.Character;

            if (!IsLassoEquiped)
            {
                LassoTarget = null;
            }

            if (player.IsShooting)
            {
                var targetOutputArg = new OutputArgument();
                if (Function.Call<bool>(Hash.GET_ENTITY_PLAYER_IS_FREE_AIMING_AT, Game.Player, targetOutputArg))
                {
                    var target = targetOutputArg.GetResult<Entity>();
                    if (target != null)
                    {
                        LassoTarget = target;
                        DidJustLassoed = true;
                        Script.Wait(500);
                    }
                }
            }
        }
    }
}
