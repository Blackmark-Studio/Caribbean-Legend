void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "Exit_Fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar); 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			
			if(pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}			
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");			
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}	
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();	
			AddDialogExitQuest("OpenTheDoors");			
		break;
		
		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
//			Diag.TempNode = "OnceAgain";
			if(pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = LinkRandPhrase("네 길을 가라, "+GetSexPhrase("동료","아가씨")+". 결국에는 그녀가 우리에게 감사할 거야, 알지.","꺼져! 신사분들께서 즐기시게 내버려 둬.","이건 네 알 바 아니야, "+GetSexPhrase("이방인","아가씨")+". 그냥 재미 좀 보고 끝내자!");
				link.l1 = LinkRandPhrase("이건 절대로 허락할 수 없어!","지금 당장 그 사악한 계획을 포기해라!","나는 어떤 폭력도 용납하지 않겠다!");
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple("알겠어, 나 간다. 방해해서 미안해.","다시는 감히 폐를 끼치지 않겠습니다. 신경 써 드려 죄송합니다.");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if(pchar.GenQuest.EncGirl == "Begin_2")
			{
				if(sti(pchar.rank) < 10)
				{
					dialog.text = LinkRandPhrase("네 길을 가라, "+GetSexPhrase("동료","아가씨")+". 결국엔 그녀가 우리에게 감사할 거야, 알지.","꺼져! 나리들께서 즐기시게 내버려 둬.","이건 네 알 바 아니야, "+GetSexPhrase("이방인","아가씨")+". 그냥 좀 즐기기만 할 거야, 그게 다야!!");
					link.l1 = LinkRandPhrase("이건 절대로 허락하지 않겠다!","지금 당장 그 사악한 계획을 포기해라!","나는 어떤 폭력도 용납하지 않겠다!");
					link.l1.go = "Node_Fight";
					link.l2 = RandPhraseSimple("알겠어, 나 간다. 방해해서 미안해.","다시는 감히 폐를 끼치지 않겠습니다. 신경 쓰이게 해서 죄송합니다.");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = RandPhraseSimple("이봐, "+GetSexPhrase("이방인","아가씨")+", 왜 시비를 거는 거야? 이 아가씨는 우리 정착지에서 '유명한' 인물이야. 우리는 이미 돈을 지불했는데, 네가 나타나자 그녀가 우리 돈을 들고 도망치기로 한 거지.","이봐, "+GetSexPhrase("동료","아가씨")+", 네 일이나 하고 우리 일에 끼어들지 마라. 저 아가씨는 주사위 게임에서 우리가 이겼는데, 너무 재빠르게 도망쳐서 한 시간째 이 정글에서 쫓고 있던 참이다.");
					link.l1 = "난 상관없어, 그녀를 해치게 두지 않을 거야!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("아, 그렇군! 나도 그녀 말을 거의 믿을 뻔했지! 저런 계집이라니...","아, 그래, 그건 또 다른 이야기지. 자, 신나게 놀아라, 이 녀석들아!");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}	
			}
			if(pchar.GenQuest.EncGirl == "Begin_3")
			{
				if(sti(pchar.rank) < 20)
				{	
					dialog.text = "네 갈 길을 가라, "+GetSexPhrase("좋은 사람","아가씨")+". 너 없이도 우리가 알아서 할 거야.";
					link.l1 = "나는 어떤 폭력도 용납하지 않겠다!";
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = RandPhraseSimple("이봐, "+GetSexPhrase("이방인","아가씨")+", 왜 괜히 문제를 일으키는 거야? 이 아가씨는 우리 정착지에서 '잘 알려진' 인물이야. 우리는 이미 돈을 지불했는데, 네가 나타나자 그녀가 우리 돈을 들고 도망치기로 한 거지.","이봐, "+GetSexPhrase("동료","아가씨")+", 네 갈 길이나 가고 우리 일에 참견하지 마라. 이 아가씨는 주사위 게임에서 우리가 이겼는데, 너무 재빨리 도망쳐서 한 시간째 쫓고 있었다.");
					link.l1 = "신경 안 써 - 그녀를 해치게 두지 않을 거야!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("아, 그렇군! 나 그 여자 말을 거의 믿을 뻔했잖아! 저런 계집이라니...","아, 그렇다면 또 다른 이야기군. 자, 신나게 놀아라, 이 녀석들아!");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}			
		break;
		
		case "Node_Fight":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("그래, 산책하기엔 정말 딱 좋은 때를 골랐군...","그래서, 영웅이 되기로 한 거야?")+" 그놈을 처리해"+GetSexPhrase("im","er")+", 얘들아!","You "+GetSexPhrase("점액","오물")+"! 우리 길을 막으려 들어?! 베어버려라"+GetSexPhrase("임","er")+"!");
			link.l1 = "나는 더 위협적인 사람들도 봤어!";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			dialog.text = "그녀 때문에 우리 꽤나 돈 썼다는 걸 알아둬! 그렇게 고귀하다면, 네가 그녀를 데려가도 돼\n "+sti(pchar.GenQuest.EncGirl.price)+" 페소입니다."+GetSexPhrase(" 그 여자랑 재미있게 놀 거야, 헤헤...","")+"";
			if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = RandPhraseSimple("여기 돈이다. 나는 그녀를 데려가겠다.","이 악물지 마라. 그 아가씨는 내가 데려간다. 여기 네 돈이다.");
				link.l1.go = "Node_4";
			}	
			link.l2 = LinkRandPhrase("그래, 돈이 필요한 거냐? 아니면 차가운 칼날이 더 좋겠어?","그게 웃기다는 거냐, 이 바보야, 저 여자애 좀 봐! 겁먹었잖아!","누구를 속이려는 거냐, 이 타락한 놈아!");
			link.l2.go = "Node_Fight";
		break;
		
		case "Node_4": // бандюки уходят, девица остаётся - ГГ ее выкупил у бандюков
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price))); 
			ChangeCharacterComplexReputation(pchar,"nobility", 7);
			//pchar.quest.LandEnc_RapersBadExit.over = "yes";
			sGlobalTemp = "Saved_CangGirl";
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_5":
			dialog.text = "애초에 왜 그녀 말을 믿는 거지? 무슨 폭력? 걔가 집에서 도망친 거고, 우리는 우리 두목이 시켜서 걔를 찾으러 온 거야.";
			link.l1 = RandPhraseSimple("그렇다면 이야기가 다르지. 가서 네 도망자를 쫓아라.","아, 그렇군. 그럼 계속 그녀를 쫓아가 봐... 나는 처리할 일이 좀 있거든.");
			link.l1.go = "Exit_NoFight";
			link.l2 = RandPhraseSimple("그런 허튼소리는 네 손자들에게나 해라, 오래 살아서 손자라도 보게 된다면 말이지!","누구를 속이려는 거야, 이 자식아?!");
			link.l2.go = "Node_6";
			link.l3 = "내가 직접 그녀를 집에 데려다주겠소, 괜한 문제를 피하려고. 그녀 부모가 누구요?";
			link.l3.go = "Node_7";
		break;
		
		case "Node_6":
			dialog.text = "죽고 싶어? 그건 네 선택이지...";
			link.l1 = "누가 할 소린지 모르겠군.";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_7":
			sGlobalTemp = "Saved_CangGirl";
			if(pchar.GenQuest.EncGirl.city == "Panama") i = hrand(2);
			else	i = hrand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = "is a store owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a store owner";
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = "serves in the port office";
					pchar.GenQuest.EncGirl.FatherGen = "who serves in the port office";
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = "serves as the prison's commandant";
					pchar.GenQuest.EncGirl.FatherGen = "of a prison's commandant";
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = "is a shipyard owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a shipyard owner";
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;				
			}
			dialog.text = "그녀의 아버지 "+pchar.GenQuest.EncGirl.FatherNom+", "+XI_ConvertString("settlement")+"에서 "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+". 하지만 제발, 우리를 실망시키지 마시오, 그는 만만한 사람이 아니니 우리 모두를 산 채로 가죽을 벗길 수도 있소...";
			link.l1 = "걱정 마. 내가 그녀를 그에게 데려다줄게.";
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;
		
		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_8":
			dialog.text = "또 다시 만났군. 네 동료는 어디 있지? 뭐, 사실 네가 여기 있다면 그 여자는 필요 없어.";
			link.l1 = "신사 여러분, 내 생각엔 이미 충분히 돈을 받았으니 그 아가씨는 이제 그만 놔주는 게 좋겠소.";
			link.l1.go = "Node_9";
		break;
		
		case "Node_9":
			if(hrand(1) == 0)
			{	
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;	
			}	
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);	
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;	
			}	
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch(hrand(4))
			{
				case 0:
					sTemp = "a leg";
				break;
				case 1:
					sTemp = "an arm";
				break;
				case 2:
					sTemp = "an ear";
				break;
				case 3:
					sTemp = "a nose";
				break;
				case 4:
					sTemp = "an eye";
				break;
			}
			dialog.text = "네 돈이 무슨 대수냐, 그 보물에 비하면 "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_GEN)+"? "+"그자는 너무 욕심이 많아서 자기 딸을 시집보내는 것조차 추가 지출이 싫어서 꺼렸지...\n그런데 우리 몫은 자기 금고에 꼭꼭 숨겨두고 있단 말이야! "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.PirateName2,NAME_NOM)+" 승선 전투에서 패배함 "+sTemp+"! 그리고 대신 뭘 가지고 있지? "+"한심한 은화 몇 닢이냐? "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_NOM)+" 항상 전리품을 전부 자기 은닉처로 가져갔지. 하지만 이제는 포기하지 않을 거야! 그의 상자가 어디 있는지 보여 줘!";
			link.l1 = "음, 난 분명히 네 선장의 보물을 지키려고 온 건 아니지만, 그 장소를 보여줄 수는 없어... 왜냐하면 나도 어디 있는지 모르거든.";
			link.l1.go = "Node_10";
		break;
		
		case "Node_10":
			dialog.text = "거짓말하지 마!!! 이 동굴에서 금 냄새가 나는 걸 내가 맡았어! 죽기 싫으면 어서 그곳을 보여 줘!";
			link.l1 = "내 말로는 설득이 안 되는 모양이군. 내 칼이 더 설득력 있을지도 모르지?";
			link.l1.go = "Node_11";
		break;
		
		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = "You "+GetSexPhrase("똥개","오물")+"! 비켜!";
			link.l1 = "아르그!";
			link.l1.go = "exit_fight";
		break;
		
		case "EncGirl_Berglar":
			dialog.text = "안녕, 좋아 "+GetSexPhrase("남자","아가씨")+". 당신에 대한 불만이 접수되었습니다.";
			link.l1 = "누가 불평한다고? 그 창녀가?";
			link.l1.go = "EncGirl_Berglar1";
		break;
		
		case "EncGirl_Berglar1":
			dialog.text = "입 조심해, 알겠어? 내 여동생을 모욕하는 건 절대 용납 못 해! 처음엔 정글에서 그녀를 공격하더니, 이제 여기까지 데려왔잖아\n "+GetSexPhrase("더한 추태를 위해\n","그리고 나를 털어갔어")+".";
			link.l1 = "이봐, 친구, 내가 그 얘기 전부 다 들어야 해?";
			link.l1.go = "EncGirl_Berglar2";
		break;
		
		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money)/5) + 5000;
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dialog.text = "아니. 단지 소박한 금액인 "+sti(pchar.GenQuest.EncGirl.BerglarSum)+" 페소만 있으면 모든 곤란에서 벗어날 수 있지.";
				if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = "음, 고귀한 행동이 요즘은 좀 값이 나가긴 하지. 좋아, 가져가라...";
					link.l1.go = "EncGirl_Berglar3";
				}	
				link.l2 = "네 뱃속에 구멍을 뚫어버리는 게 출구로 가는 길을 막지 않게 하는 데 더 싸게 먹힐 것 같은데.";
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = "아니. 하지만 너도 주머니 다 뒤집어! 안 그러면 찔러버릴 거야!";
				link.l1 = "알겠어, 가져가라 이 악당아! 하지만 그냥 넘어가진 않을 거야...";
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = "네 배에 구멍을 뚫어버리는 게 내가 나가는 길을 막지 않게 하는 더 쉬운 방법일 것 같은데.";
				link.l2.go = "EncGirl_Berglar4";				
			}			
		break;
		
		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = "아주 좋아. 잘 됐군.";
			link.l1 = "행운을 빌어.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");			
		break;
		
		case "EncGirl_Berglar3_1":
			dialog.text = "물론 안 하지, 물론이지... 자, 그럼 잘 가라, "+GetSexPhrase("동료","아가씨")+"."+GetSexPhrase(" 그리고 명심해, 네가 그렇게 잘생긴 것도 아니라서 아무 여자나 널 보자마자 반할 정도는 아니야. 이게 내가 너한테 주는 교훈이야.","")+"";
			link.l1 = ""+GetSexPhrase("그건 확실하지!..","꺼져 버려라!")+"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");			
		break;
		
		case "EncGirl_Berglar4":
			dialog.text = "너는 ~처럼 보여 "+GetSexPhrase("그렇게 고귀한 분","이렇게 교양 있는 숙녀")+", 왜 그렇게 입이 험해?";
			link.l1 = "그게 나한테 제일 잘 맞지...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;
		
		case "Node_2":
			dialog.text = "자, 네가 원한 거잖아! 간질여 줄까\n"+GetSexPhrase("임","er")+" 칼로 할래, 얘들아?";
			Link.l1 = "죽기 전에 기도나 해라!";
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = "그래서, 합류할 거야, 말 거야? "+GetSexPhrase("꺼져, 우리 모두 먹을 만큼 충분하지 않아","꺼져라, 우리한텐 아가씨 한 명이면 충분하니까\n")+"!";
			Link.l1 = "그렇다면 더 이상 방해하지 않겠소.";
			Link.l1.go = "Exit_NoFight";
			Link.l2 = "나는 어떤 폭력도 용납하지 않겠다!";
			Link.l2.go = "Node_2";
		break;				
	}
}
