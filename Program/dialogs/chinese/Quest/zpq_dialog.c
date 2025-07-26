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
			dialog.text = "我不想说话。 ";
			link.l1 = "嗯, 我明白了。 ";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "zpq_sld2":
			dialog.text = "等一下, 先生, 你是" + GetFullName (pchar) +"吗? ";
			link.l1 = "是的.. 我能帮你什么? ? ";
			link.l1.go = "zpq_sld2_1";
		break;
		case "zpq_sld2_1":
			dialog.text = "我们需要你。 更确切地说, 需要你的钱。 别装糊涂, 我今天心情不太好, 很容易发火。 ";
			link.l1 = "哦, 拜托, 你在说什么钱? 你真以为我会随身带着财宝吗? ";
			link.l1.go = "zpq_sld2_2";
		break;
		case "zpq_sld2_2":
			dialog.text = "别想骗我。 把钱交出来 - " + FindRussianMoneyString(sti(pchar.questTemp.zpq.sum)) + " 然后你就可以走了。 否则我们就强取。 ";
			if (pchar.questTemp.zpq == "failed")
			{
				link.l1 = "你不是为那个堡垒里的老鼠工作吗? 那我有个好消息要告诉你, 我把他送进地狱了。 ";
				link.l1.go = "zpq_sld2_3_1";
			}
			else
			{
				link.l1 = "你不是为那个堡垒里的老鼠工作吗? 告诉他钱已经交给可靠的人了, 让他别再惦记了。 ";
			link.l1.go = "zpq_sld2_3";
			}
			if(makeint(Pchar.money) >= sti(pchar.questTemp.zpq.sum))
			{
				link.l2 = "好吧, 拿上你这脏钱, 混蛋! ";
				link.l2.go = "zpq_sld2_6";
			}
			else
			{
				link.l2 = "我没有那么多钱... ";
				link.l2.go = "zpq_sld2_3";
			}
		break;
		case "zpq_sld2_3":
			dialog.text = "那这就是你的命运 - 因为贪婪而英年早逝。 让你活着太危险了。 ";
			link.l1 = "太自信了。 ";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_3_1":
			dialog.text = "呵呵, 那你的命运就是因为贪婪而死。 这对我们来说正好, 我们不想分享。 ";
			link.l1 = "是你的贪婪会要了你的命... ";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_4":
			dialog.text = "嘿, 伙计们! 给他头上套个袋子! ";
			link.l1 = "好吧, 这是你们的选择... ";
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
			dialog.text = "很好。 把钱交出来然后滚, 船长! ";
			link.l1 = "... ";
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