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
			dialog.text = "話したくねえ。";
			link.l1 = "ふむ、なるほど。";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "zpq_sld2":
			dialog.text = "ちょっと待て、旦那、あんたは "+GetFullName(pchar)+"?";
			link.l1 = "はい…どうされましたか？";
			link.l1.go = "zpq_sld2_1";
		break;
		case "zpq_sld2_1":
			dialog.text = "俺たちにはお前が必要だ。いや、正確にはお前の金が必要なんだ。\nそれに、意地を張るんじゃねえぞ。今日は機嫌が悪いんだ。怒るかもしれねえからな。";
			link.l1 = "おいおい、何の金の話だよ？まさか俺が宝を持ち歩いてるとでも思ってるのか？";
			link.l1.go = "zpq_sld2_2";
		break;
		case "zpq_sld2_2":
			dialog.text = "俺を騙そうなんて思うな。ただ金を渡せ―― "+FindRussianMoneyString(sti(pchar.questTemp.zpq.sum))+" お前は好きに行っていいぜ。\nさもなくば、力ずくで奪い取るまでだ。";
			if (pchar.questTemp.zpq == "failed")
			{
				link.l1 = "あの砦のネズミの手下じゃねえのか？だったらいい知らせがあるぜ、俺がそいつを地獄に送ってやったんだ。";
				link.l1.go = "zpq_sld2_3_1";
			}
			else
			{
				link.l1 = "あの砦のネズミの手下じゃねえのか？そいつに伝えろ、金は信頼できる奴の手に渡ったから、もう諦めろってな。";
			link.l1.go = "zpq_sld2_3";
			}
			if(makeint(Pchar.money) >= sti(pchar.questTemp.zpq.sum))
			{
				link.l2 = "いいだろう、汚い金を持っていけ、この野郎！";
				link.l2.go = "zpq_sld2_6";
			}
			else
			{
				link.l2 = "俺は持ってねえんだ……";
				link.l2.go = "zpq_sld2_3";
			}
		break;
		case "zpq_sld2_3":
			dialog.text = "それが貴様の運命だな――強欲のせいで若くして死ぬんだ。生かしておくには危険すぎる。";
			link.l1 = "ずいぶん自信満々だな。";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_3_1":
			dialog.text = "へっ、欲深さのせいで死ぬのが運命ってわけだな。\n俺たちには都合がいい、分け合う気なんてねえからな。";
			link.l1 = "お前を殺すのは自分の強欲さだ……";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_4":
			dialog.text = "おい、野郎ども！そいつの頭に袋をかぶせろ！";
			link.l1 = "まあ、お前の選択だったんだぜ……";
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
			dialog.text = "いいだろう。それを渡して、とっとと消えな、船長！";
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
