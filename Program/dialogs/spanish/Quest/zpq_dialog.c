void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "No quiero hablar.";
			link.l1 = "Mm, ya veo.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "zpq_sld2":
			dialog.text = "Un momento, señor, ¿es usted "+GetFullName(pchar)+"?";
			link.l1 = "Sí.. ¿Cómo puedo ayudarte??";
			link.l1.go = "zpq_sld2_1";
		break;
		case "zpq_sld2_1":
			dialog.text = "Te necesitamos. Tu dinero, para ser más específicos. Y no intentes hacerte el terco porque no estoy de buen humor hoy, puedo enfadarme.";
			link.l1 = "Oh, por favor, ¿de qué dinero estás hablando? ¿De verdad piensas que llevaré el tesoro conmigo?";
			link.l1.go = "zpq_sld2_2";
		break;
		case "zpq_sld2_2":
			dialog.text = "No intentes engañarme. Solo dame el dinero, "+FindRussianMoneyString(sti(pchar.questTemp.zpq.sum))+"y podréis marcharos. O lo tomaremos por la fuerza.";
			if (pchar.questTemp.zpq == "failed")
			{
				link.l1 = "¿No trabajas para esa rata del fuerte? Tengo buenas noticias para ti entonces, lo envié al infierno.";
				link.l1.go = "zpq_sld2_3_1";
			}
			else
			{
				link.l1 = "¿No trabajas para este rata de fuerte? Dile que el dinero fue entregado a manos confiables, así que puede olvidarse de ellos.";
			link.l1.go = "zpq_sld2_3";
			}
			if(makeint(Pchar.money) >= sti(pchar.questTemp.zpq.sum))
			{
				link.l2 = "Está bien, ¡toma tu sucio dinero, bastardo!";
				link.l2.go = "zpq_sld2_6";
			}
			else
			{
				link.l2 = "No  los tengo...";
				link.l2.go = "zpq_sld2_3";
			}
		break;
		case "zpq_sld2_3":
			dialog.text = "Ese es tu destino entonces: morir joven por tu avaricia. Es demasiado peligroso dejarte con vida.";
			link.l1 = "Qué confianza en sí mismo.";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_3_1":
			dialog.text = "He-he, tu destino es morir por tu avaricia entonces. Nos conviene, no queremos compartir.";
			link.l1 = "Es tu avaricia la que te matará...";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_4":
			dialog.text = "¡Eh, muchachos!! ¡Ponedle una bolsa en la cabeza!";
			link.l1 = "Bueno, fue tu elección...";
			link.l1.go = "zpq_sld2_5";
		break;
		case "zpq_sld2_5":
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(PChar, true);

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("zpq", "7");

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = "Cumana";
			pchar.quest.zpq_seaBattle.function = "zpq_seaBattle";
		break;
		case "zpq_sld2_6":
			dialog.text = "Bien. ¡Dáselos y piérdete, capitán!";
			link.l1 = "...";
			link.l1.go = "zpq_sld2_7";
			AddMoneyToCharacter(Pchar, -makeint(pchar.questTemp.zpq.sum));
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("zpq", "8");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
		break;
		case "zpq_sld2_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for(int i = 1; i <= 3; i++)

			{

				sld = CharacterFromID("qp2_" +i);
				LAi_SetImmortal(sld, true);
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 6.0);
			}
		break;
	}
}
