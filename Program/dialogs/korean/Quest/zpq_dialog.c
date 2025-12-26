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
			dialog.text = "나 말하기 싫어.";
			link.l1 = "흠, 알겠군.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "zpq_sld2":
			dialog.text = "잠깐만, 나리, 당신이 "+GetFullName(pchar)+"?";
			link.l1 = "그래... 무엇을 도와줄까?";
			link.l1.go = "zpq_sld2_1";
		break;
		case "zpq_sld2_1":
			dialog.text = "우린 네가 필요해. 아니, 네 돈이 필요하지. 괜히 고집부리지 마라, 오늘 내 기분이 별로거든. 화낼 수도 있으니까.";
			link.l1 = "아, 제발요, 무슨 돈 얘기하는 거야? 내가 보물을 몸에 지니고 다닐 거라고 진짜 생각하는 거야?";
			link.l1.go = "zpq_sld2_2";
		break;
		case "zpq_sld2_2":
			dialog.text = "날 속이려고 하지 마. 그냥 돈이나 내놔 - "+FindRussianMoneyString(sti(pchar.questTemp.zpq.sum))+" 그리고 네 갈 길을 가도 된다. 아니면 우리가 힘으로 빼앗을 수도 있지.";
			if (pchar.questTemp.zpq == "failed")
			{
				link.l1 = "그 요새 쥐새끼 밑에서 일하는 거 아니야? 그럼 좋은 소식 하나 알려주지. 내가 그놈을 지옥으로 보내버렸거든.";
				link.l1.go = "zpq_sld2_3_1";
			}
			else
			{
				link.l1 = "그 요새 쥐새끼 밑에서 일하는 거 아니냐? 돈은 믿을 만한 손에 넘겼으니 이제 잊으라고 전해라.";
			link.l1.go = "zpq_sld2_3";
			}
			if(makeint(Pchar.money) >= sti(pchar.questTemp.zpq.sum))
			{
				link.l2 = "좋아, 이 더러운 돈이나 가져가, 이 자식아!";
				link.l2.go = "zpq_sld2_6";
			}
			else
			{
				link.l2 = "나는 그걸 가지고 있지 않아...";
				link.l2.go = "zpq_sld2_3";
			}
		break;
		case "zpq_sld2_3":
			dialog.text = "그게 네 운명이군 - 욕심 때문에 젊어서 죽게 되는 거지. 널 살려두기엔 너무 위험해.";
			link.l1 = "참 자신감이군.";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_3_1":
			dialog.text = "헤, 네놈의 운명은 결국 탐욕 때문에 죽는 거다. 우리한텐 잘된 일이야, 나눠주고 싶지도 않거든.";
			link.l1 = "너의 탐욕이 너를 죽일 거다...";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_4":
			dialog.text = "이봐, 녀석들! 저 자식 머리에 자루 씌워!";
			link.l1 = "글쎄, 그건 네 선택이었지...";
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
			dialog.text = "좋아. 그것들 내놓고 꺼져, 선장!";
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
