// Якоб ван Берг - злодей и пират, капитан Миража
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
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "아으! 헉... 너 대체 누구야? 그 빌어먹을 중국인은 어디 갔어? 내가 너한테 말하고 있는데, 귀라도 먹었냐? 헉!";
				link.l1 = "잘 들리니까 소리 지르지 마. 중국인은 안 올 거야. 그 대신 내가 왔다.";
				link.l1.go = "HollJacob_inRoom";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "버그다. 개발자들에게 알려라.";
			link.l1 = "그렇게 말씀하신다면...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "HollJacob_inRoom":
			dialog.text = "뭐야? 너 누구야? 도대체 여기서 뭐 하는 거야? 질문했잖아, 이 쓰레기야!";
			link.l1 = "그건 알 필요 없어. 네 배가 필요해.";
			link.l1.go = "HollJacob_inRoom_1";			
		break;
		
		case "HollJacob_inRoom_1":
			dialog.text = "아으... 뭐라고?! 씨발... 잠깐! 너 영국 개새끼잖아! 젠장! 결국 날 찾아냈군... 이제 끝이다! 난 절대 항복 안 해!";
			link.l1 = "글쎄, 네가 항복할 필요는 없어...";
			link.l1.go = "HollJacob_inRoom_fight";			
		break;
		
		case "HollJacob_inRoom_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern_upstairs")], false);
			pchar.quest.JacobOnMainOver.over = "yes";//снять таймер
			chrDisableReloadToLocation = true;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "HollJacob_dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "JacobBerg_abordage":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "아악! 젠장! 이게 무슨 난장판이야! 너 상인이 아니지?";
				link.l1 = "참 영리한 녀석이군. 내 부하들은 하나같이 엄선된 영국 해병들이라, 애초에 네 운명은 정해져 있었지. 리처드 플리트우드와 내가 상인의 이야기를 꾸며냈고, 그래서 네가 여기까지 온 거다. 네 모험은 이제 끝났어, 이 잡놈아!";
				link.l1.go = "JacobBerg_abordage_1";
			}
			else
			{
				dialog.text = "마침내 우리가 만났군, 선장. 자네 제법 똑똑한 친구로군... 이렇게 진지한 상대는 정말 오랜만이야.";
				link.l1 = "그리고 내가 너의 마지막 상대다, Jacob. 넌 여기서 살아나가지 못할 거다.";
				link.l1.go = "JacobBerg_abordage_3";
			}
		break;
		
		case "JacobBerg_abordage_1":
			dialog.text = "그런 것 같군. 네 선원들이 내 배를 점령했으니, 내가 살려달라고 기대할 이유도 없지. 하지만 놈들이 널 도우러 오기 전에, 내가 널 지옥으로 보내주겠다! 반 베르크는 쉽게 목숨을 내주지 않을 거다!\n";
			link.l1 = "그건 네 생각일 뿐이지. 내 생각엔 네 목숨은 한 푼 값어치도 안 돼. 말은 그만하고, 각오해라!";
			link.l1.go = "JacobBerg_abordage_2";			
		break;
		
		case "JacobBerg_abordage_2":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "JacobBerg_abordage_3":
			dialog.text = "정말인가? 네가 도망치지 못하게 내가 조치를 해두었지. 화약고에 도화선을 붙였으니, 곧 우리 배들이 산산조각 날 거다.";
			link.l1 = "네 놈이랑 네 낡은 배만 터질 것 같군. 나는 네 놈을 배 갈라 죽이고, 내 배를 되찾아서, 내가 떠날 때 불꽃놀이를 구경할 거다.";
			link.l1.go = "JacobBerg_abordage_4";			
		break;
		
		case "JacobBerg_abordage_4":
			dialog.text = "내가 먼저 널 죽이고, 창문 밖으로 뛰어내려서, 헤엄쳐서 해안까지 가서 불꽃놀이를 직접 구경한다면 그땐 아니겠지!";
			link.l1 = "내기?";
			link.l1.go = "JacobBerg_abordage_5";			
		break;
		
		case "JacobBerg_abordage_5":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
}
}
