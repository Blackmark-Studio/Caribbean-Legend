void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Captain","Lady")+"! 제발, 자비를 베풀어 주세요! 제발 저를 지켜 주세요, 부탁입니다!","도와줘! "+GetSexPhrase("Stranger","아가씨")+", 살려줘, 제발 부탁이야!");
			link.l1 = LinkRandPhrase("무슨 일이야?","무슨 일이야?",RandPhraseSimple("무슨 일인데?","무슨 일이야?"));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("선장님! 선장님","아가씨! 아가씨")+", 제발 버텨!","잠깐만, "+GetSexPhrase("Captain","아가씨")+"! 제발.");
			link.l1 = LinkRandPhrase("무슨 일이야?","무슨 일이야?",RandPhraseSimple("무슨 문제야?","무슨 일이야?"));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = "오, 맙소사"+GetSexPhrase("ister","iss")+"! 제발, 불쌍한 소녀를 도와주세요, 부탁드려요! 저 사람들이 저한테 끔찍한 짓을 하려고 해요!";
			link.l1 = LinkRandPhrase("무슨 일이야?","무슨 일이야?",RandPhraseSimple("무슨 일이야?","무슨 일이야?"));
			link.l1.go = "Begin_31";
		break;
		
		case "Begin_11":
			dialog.text = RandPhraseSimple("이 악당들이 나를 능욕하려 해! 제발, 아무쪼록 그들이 그러지 못하게 막아 줘!","제발, 신이시여, 저 괴물들로부터 저를 지켜주십시오! 저들이 저를 욕보이려 하고 있어요!");
			link.l1 = "겁먹지 마라"+GetSexPhrase(", 이쁜이","")+". 여기서 무슨 일이 있었지?";
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = RandPhraseSimple("강간범들이 나를 쫓아오고 있어!"+GetSexPhrase(" 숙녀의 명예를 지켜 주시겠습니까?","")+"","선장님, "+GetSexPhrase("사내답게 굴어라","너도 여자잖아")+" 여자를 치욕에서 구하지 않겠소!");
			link.l1 = "당황하지 마라"+GetSexPhrase(", 미인","")+". 여기서 무슨 일이 있었지?";
			link.l1.go = "exit_1";
		break;
		
		case "Begin_31":
			dialog.text = "놈들이 날 쫓아오고 있어! 그 도적들 말이야! 그들에게 나 좀 내버려 두라고 전해 줘!";
			link.l1 = "겁먹지 마라"+GetSexPhrase(", 미인아","")+". 여기서 무슨 일이 있었지?";
			link.l1.go = "exit_1";
		break;
		
		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase("도와줘! 도와줘! 쟤들이 나 쫓아와! 살려줘!","아아악! 도와줘, "+GetSexPhrase("이방인","아가씨")+"! 이 악당들한테서 나 좀 구해 줘!","자비를 베풀어 이 악당들로부터 저를 지켜주십시오! 제발요!");
			Link.l1 = LinkRandPhrase("무슨 일이야?","무슨 일이야?","무슨 일이야?");
			Link.l1.go = "Node_2";			
		break;        

		case "Node_2":
			dialog.text = LinkRandPhrase("그들이... 나를 겁탈하려 해! 제발, 제발 막아 줘! 부탁이야!","이 짐승들... 뭔가 끔찍한 일을 꾸미고 있어... 제발, 저를 저들로부터 지켜주세요!","우리 주님의 이름으로, 이 음탕한 짐승들로부터 저를 구해주소서! 저들을 저를 욕보이려 합니다!");
			Link.l1 = "그럼 모두 정리해 보자.";
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = RandPhraseSimple("감사합니다, "+GetSexPhrase("Captain","아가씨")+". 나는 너무 무서웠어!","구해줘서 고마워! 정말 감사해!");
					link.l1 = "좋아, "+GetSexPhrase("아름다움","친애하는")+", 진정해, 다 지난 일이야.";
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = "오, 고마워, "+GetSexPhrase("귀인 나리! 당신은 진정한 신사이십니다!","아가씨! 저를 구해주셨군요!")+"";
					link.l1 = "달리 할 수 없었소.";
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = "오, 고마워, "+GetSexPhrase("귀인 나리! 당신은 진정한 신사이십니다!","이봐, 낯선이! 네가 날 구해줬어!")+"";
					link.l1 = "달리 할 수 없었소.";
					link.l1.go = "Node_12";	
				}
				else
				{
					dialog.text = "무슨 짓을 한 거야? 왜 그들을 죽였지?! 이제 그놈들이 나를 찾으러 올 거야! 이런, 내가 뭘 잘못했다고 이런 일을 겪는 거지!";
					link.l1 = "이게 바로 고마움의 표시냐!";
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = "무슨 짓을 한 거야, "+GetSexPhrase("선장","아가씨")+"?! 왜 그들을 죽였어? 사실 그들은 우리 아버지가 보낸 사람들이었는데... 이런, 이제 아버지가 분명히 나를 죽일 거야...";
				link.l1 = "이거야말로 소식이네! 그런데 도대체 무슨 생각으로 산적들에게 쫓긴다고 소리쳤던 거야?!";
				link.l1.go = "Node_31";
			}
		break;
		
		case "Node_11":
			Diag.TempNode = "Node_1Next";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank))*25 + frand(2)*500));
			dialog.text = "제가 돈이 좀 있습니다. 부디 감사의 표시로 받아주십시오. 이제 모두에게 알리겠습니다, "+GetSexPhrase("정말 훌륭하고 고귀한 분이시군요","당신은 참으로 훌륭하고 고귀한 여인이로군")+".";
			link.l1 = "물론 그렇게 할 거야. 고마워... 이제 그냥 집에 가.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "Node_12":
			dialog.text = "아직 정신을 못 차리겠어. 혹시 가져다줄 수 있겠나\n "+GetSexPhrase("숙녀","나")+" 정착지로 "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"? 있잖아, 이제는 덤불마다 강간범이 숨어 있는 것 같아 보여.";
			link.l1 = RandPhraseSimple("그렇게 걱정하지 마, 진짜로... 좋아, 가자.","넌 정말 겁쟁이구나, 안 그래? 좋아, 내가 데려다줄게.");
			link.l1.go = "Node_121Next";
			link.l2 = "미안해, 자기야, 하지만 지금은 정말 시간이 없어. 너무 바빠서 그래.";
			link.l2.go = "Node_3End";
		break;
						
		case "Node_22":
			dialog.text = "난 네가 그냥 놈들을 쫓아버릴 줄 알았는데! 이제 나를 그 정착지의 선술집으로 데려가야 하네\n "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", 너 말고는 도와줄 사람이 없어.";
			link.l1 = "아, 젠장! 좋아, 가자. 하지만 뒤처지지 마.";
			link.l1.go = "Node_122Next";
			link.l2 = "아니, 그게 다야, "+GetSexPhrase("아름다움","친애하는")+"! 오늘은 놀랄 일은 충분히 겪었어. 다른 사람한테 가서 도와달라고 해.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_31":
			dialog.text = "그럼 내가 어쩌라고?! 아버지는 나보고 고리대금업자 아들, 그 겁쟁이랑 결혼하래... 그냥 그 아버지가 돈이 많다는 이유로! 하지만 난 다른 남자를 사랑해! 제발, 그 사람에게 데려다줘...";
			link.l1 = "정말 짐이 되는구나! 뭐, 알겠다. 가자. 이제 와서 널 여기 그냥 둘 수도 없지, 안 그래?.. 네가 고른 사람 이름이 뭐지, 어디로 데려가면 되겠어?";
			link.l1.go = "Node_32";
			link.l2 = "아니, 그게 다야, "+GetSexPhrase("아름다움","친애하는")+"! 오늘은 놀랄 일은 이걸로 충분해. 다른 사람한테 부탁해.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "그의 이름은 "+pchar.GenQuest.EncGirl.sLoverId+", 그는 신참이야. 지금은 그 정착지에 머무르고 있어 "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", 거기서 일자리를 구해보려고 했지만, 요즘은 힘든 시기야. 모두가 위기라고들 하지... 이제는 어차피 집으로 돌아갈 수도 없어.";
			link.l1 = "위기라고? 하... 진짜 해적에게 위기란, 지평선에 무역 선단이 보이는데 돛을 채울 바람이 없을 때지...";
			link.l1.go = "Node_12Next";
		break;
		
		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = RandPhraseSimple("있잖아, "+GetSexPhrase("선장","아가씨")+"? 너무 무서워서 아직도 다리가 좀 후들거려.","아, 있잖아요, 정말 무서웠어요. 하나님께서 당신을 제게 보내주셔서 정말 다행이에요.");
			link.l1 = RandPhraseSimple("신께 감사하네, 아직 살아 있어서.","너무 마음에 담아두지 마. 이렇게 된 게 오히려 잘된 거야, 알지?");
			link.l1.go = "exit";
		break;
		
		case "Node_1Next":
			dialog.text = RandPhraseSimple("감사합니다, "+GetSexPhrase("선장","아가씨")+", 다시 한 번. 정말로, 당신에게 큰 신세를 졌소.","정말 감사합니다, "+GetSexPhrase("선장","아가씨")+". 당신의 도움이 없었다면 어찌했을지 모르겠소.");
			link.l1 = RandPhraseSimple("그것이 너에게 교훈이 되었으면 좋겠군. 좋아, 행운을 빌지...","다음엔 좀 더 조심해야 할 거야... 이제 집에 가, 나 할 일이 있으니까.");
			link.l1.go = "Node_1End";
			link.l2 = "어떻게 그렇게 부주의할 수가 있지? 왜 혼자서 정글로 들어간 거야?";
			link.l2.go = "Node_13";
		break;
		
		case "Node_1End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = RandPhraseSimple("마음이 바뀌었나?","선장님, 마음을 바꿔 주시다니 정말 기쁩니다!");
			link.l1 = RandPhraseSimple("아니, 아니, 자기야, 난 사양할게.","헛된 희망은 품지 마라...");
			link.l1.go = "exit";
		break;
		
		case "Node_13":
			if(pchar.GenQuest.EncGirl == "FindCoins") 
			{
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(sti(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = "아마 나를 비웃을지도 모르겠지만... 사랑의 묘약 재료를 모으고 있었어... 한 마녀가 내게 마음의 문제에 도움이 되는 뿌리가 있다고 말했거든.";
						link.l1 = "오, 맙소사! 뭐야 "+GetSexPhrase("이 여자들은 무슨 생각을 하는 거지","생각하고 있었나")+"?! 아무래도 꽤 많이 모았구나, 너를 쫓는 구혼자들이 정말 많았지. 내가 그놈들 다 쫓아내느라 고생 좀 했어. 하하하하... 잘 가라.";
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = "나는 그냥 약초를 좀 채집하고 바람도 쐴 겸 산책을 나갔을 뿐이야. 하필 산책하기에 좋은 때는 아니었던 모양이군.";
						link.l1 = "이런 부주의가! 내가 제때 도착해서 다행이군. 아무튼, 행운을 빌어.";
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = "제 주인님께서 산책하시다가 이 근처 어딘가에서 목걸이의 진주를 떨어뜨리셨어요. 집에 돌아가시자마자 저를 소리치며 내보내시고, 진주들을 다 주워오라고 명령하셨어요. '다 찾기 전에는 얼굴도 들이밀지 마라!'고 하셨죠. 그런데 정확히 어디서 떨어뜨리셨는지도 모르겠고, 게다가 이렇게 풀이 우거진 데서 그걸 어떻게 찾으라는 건지... 진주가 너무 작거든요... 그래서 저는 여기서 그냥 어쩔 줄도 모르고 헤매고만 있어요...";
					link.l1 = "그 목걸이가 어떤 거였지? 정글을 헤매는 것보다 그냥 새로 사는 게 더 쉽지 않을까? 네 주인님이 진주를 몇 개나 잃어버린 거야?";
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = "돌아가신 아버지께서 나에게 지도를 남기셨는데, 그의 동료들이 그 지도를 빼앗으려 했어. 아버지가 살아 계실 때는 모두가 그분 앞에서 벌벌 떨었지만, 내가 장례를 치르자마자 힘든 시기가 시작됐지. 처음에는 그 지도를 돈 주고 사려고 했지만 내가 거절하자, 이번엔 나를 협박하기 시작했어.";
					link.l1 = "그런데 왜 그냥 팔지 않았지? 이 지도에 뭐가 특별하길래 해적 무리들이 찾고 있는 거야?";
					link.l1.go = "Node_132";
				break;
			}	
		break;
		
		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = "그 목걸이는 엄선된 진주로 만들어졌어, 그런 건 싸게 살 수 없는 거야. 있었다 "+sti(pchar.GenQuest.EncGirl.BigCoins)+" 큰 진주와 "+sti(pchar.GenQuest.EncGirl.SmallCoins)+" 작은 진주들이지. 만약 그 진주들을 찾는다면, 저 목걸이처럼 또 하나를 주문할 수 있을 텐데.";
			link.l1 = "분명 이 일은 쉽지 않을 거야... 뭐, 네 주인 아가씨가 명령을 내렸다면 어쩔 수 없지. 진주를 찾아봐. 행운을 빈다.";
			link.l1.go = "Node_131End";
			link.l2 = "소용없어. 이 빽빽한 풀밭에서 진주를 찾는 것보다 건초더미에서 바늘을 찾는 게 더 쉬울 거야. 게다가 진주를 잃어버린 장소조차 네가 모르잖아...";
			link.l2.go = "Node_133";
		break;
		
		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1); 
			dialog.text = "내 아버지가 그 지도에 자기 보물을 숨긴 장소를 표시해 두셨어. 그 유명한 해적에 대해 들어본 적 있나\n "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_VOC)+"?";
			link.l1 = "아니, 그 사람에 대해서는 들어본 적 없어.";
			link.l1.go = "Node_132_1";
		break;
		
		case "Node_132_1":
			dialog.text = "음, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_NOM)+" 내 아버지였지. 모두가 그분을 두려워했고, 감히 한마디도 못 했어. 지금은 물론 뻔뻔해졌지. 내가 지도를 팔지 않겠다고 하자, 자기들도 보물의 몫을 받아야 한다고 우겼어. 나는 지도를 숨기려고 했지만, 결국 놈들이 날 찾아냈지...";
			link.l1 = "애초에 왜 그걸 숨겼겠어? 배를 빌려 타고 가서, 네 보물을 찾아라. 네 아버지가 괜히 그걸 숨겼을 리 없지.";
			link.l1.go = "Node_132_2";
		break;
		
		case "Node_132_2":
			dialog.text = "말처럼 쉽지 않지. 배를 빌릴 돈도 없고... 그리고 두렵기도 해... 그 많은 걸 어떻게 다 파내서 배까지 옮기란 말이야... 그리고 그 보물을 나중에 어디로 가져가야 하지? 가는 길에 누구든 나를 쉽게 노릴 수 있을 텐데...\n";
			link.l1 = "좋은 말이야... 좋아, 그럼 지도를 숨겨도 돼. 하지만 잘 숨겨두는 거 잊지 마라.";
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = "흠... 아마 맞는 말이군. 그러니 더더욱 그걸 팔았어야지.";
				link.l2.go = "Node_132_3";
			}
			link.l3 = "동료를 찾아보았나?";
			link.l3.go = "Node_132_8";	
		break;
		
		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_3":
			dialog.text = "이런 기회를 잃게 되어 정말 아쉽군... 아버지가 거기에 숨겨둔 보물에 대해 말씀해 주셨지. 그만큼 돈을 줄 사람은 아무도 없을 텐데...";
			link.l1 = "글쎄, 너무 헐값에 팔지는 마라. 그리고 아무리 그래도 금이 네 목숨만큼 값지진 않지. 게다가 이게 네게는 가장 쉬운 방법이야. 돈만 챙기고 모든 골칫거리에서 벗어날 수 있으니까...";
			link.l1.go = "Node_132_4";
		break;
		
		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
			dialog.text = "그거 솔깃한데... 그래서 그걸 얼마에 줄 수 있는데?";
			link.l1 = "그게 그 이상 가치 있을 것 같진 않아 "+sti(pchar.GenQuest.EncGirl.mapPrice)+" 페소입니다.";
			link.l1.go = "Node_132_5";
		break;
		
		case "Node_132_5":
			if((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = "헤, 여자로 산다는 게 쉽지 않지... 좋아, 동의해. 드디어 이 악몽도 끝나겠군... 이 지도가 너한테 있는 게 제일 나을지도 몰라,"+GetSexPhrase(" 고귀한 신사","")+", 그 악당들보다는.";
				link.l1 = "좋아. 여기 네 돈이야... 한 번에 다 써버리지만 마라.";
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = "아니, "+GetSexPhrase("선장","아가씨")+". 나는 그것을 팔지 않을 거야. 나는 좋은 남자와 결혼해서, 그다음에 함께 보물을 찾을 거야.";
				link.l1 = "글쎄, 그건 네가 결정할 일이야. 네 종이쪼가리는 어차피 더 이상 아무 가치도 없어.";
				link.l1.go = "Node_132_2End";
			}	
		break;
		
		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice))); 
			ref rMap = ItemsFromID("map_full"); // mitrokosta фикс пустой карты
			FillMapForTreasure(rMap, "");
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_8":
			dialog.text = "그럼 어디서 그들을 찾을 수 있지? 젊은 녀석들은 믿을 수 없고, 보물보다는 딴 것에 더 관심이 많아. 그리고 나이 든 녀석들은 두렵기까지 해, 다들 우리 아버지 친구들을 떠올리게 하거든. 얼마나 교활하고 간사한지, 무슨 짓을 할지 전혀 알 수가 없어.";
			link.l1 = "하하하... 좋아, 그런데 나도 데려가 줄 거야?";
			link.l1.go = "Node_132_9";
		break;
		
		case "Node_132_9":
			dialog.text = "너? 네가 간다고? 하지만 그러면 날 다시 여기, 이 정착지로 데려와야 할 텐데\n "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", 알겠지?";
			link.l1 = "좋아, 약속하지. 길만 알려줘.";
			link.l1.go = "Node_132_10";
		break;
		
		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = "보물은 동굴 안에 숨겨져 있어 "+XI_ConvertString(pchar.GenQuest.EncGirl.islandId+"Acc")+", 우리는 상륙해야 해 "+XI_ConvertString(pchar.GenQuest.EncGirl.shoreId+"Gen")+", 내가 모습을 드러낼 곳이지... 하지만 잊지 마, 절반만 가져갈 거야!";
			link.l1 = "좋아, 너한테 바람 안 피울게, 약속해. 따라와, 뒤처지지 말고.";
			link.l1.go = "Node_132_11";
		break;
		
		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_11_1":
			dialog.text = "선장님, 이제 우리가 동굴을 찾아야 합니다.";
			link.l1 = "좋아, 이제 한번 살펴보자.";
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = "선장님, 우리가 그 동굴을 찾아야 합니다.";
			link.l1 = "좋아, 이제 한번 살펴보자.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_12":
			dialog.text = "여기 있어! 찾았어! 아버지가 말한 그대로야! 엄청난 보물 더미야! 약속대로 절반은 네 거야.";
			link.l1 = "봤지? 별로 어렵지 않았으니 두려워할 것도 없었어.";
			link.l1.go = "Node_132_13";
		break;
		
		case "Node_132_13":
			dialog.text = "하하하! 이제 나 부자야! 네 몫 지금 가져갈래?";
			link.l1 = "그렇겠지.";
			link.l1.go = "Node_132_15";
		break;
		
		case "Node_132_15":
			dialog.text = "그럼 가져가, 그리고 제발 저 짐들 전부 배까지 옮기는 것 좀 도와줘. 아직도 나를 집에 데려다주기로 약속한 거 기억하지?";
			link.l1 = "잊지 않았어! 물론 데려다줄게.";
			link.l1.go = "Node_132_16";
		break;
		
		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.		
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 2+hrand(6));
			TakeNItems(pchar, "jewelry1", 30+hrand(15));
			TakeNItems(pchar, "jewelry2", 30+hrand(15));
			TakeNItems(pchar, "jewelry3", 30+hrand(15));
			TakeNItems(pchar, "jewelry4", 30+hrand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry6", 10+rand(10));
			TakeNItems(pchar, "jewelry42", 20+rand(10));
			TakeNItems(pchar, "jewelry44", 30+rand(10));
			TakeNItems(pchar, "jewelry46", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));		
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			pchar.quest.EncGirl_AddPassenger.win_condition.l1 = "location";// лесник на корабль девицу. 
			pchar.quest.EncGirl_AddPassenger.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.EncGirl_AddPassenger.function = "EncGirl_AddPassenger";
		break;
		
		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = "부자가 되니 정말 멋지군! 이제 완전히 다른 기분이야."; 
			link.l1 = "기쁘게 생각하오.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_18":
			dialog.text = "알겠습니다, 선장님. 이제 제 여정은 끝났습니다. 도와주셔서 감사합니다.";
			link.l1 = "천만에... 그런데, 새로 얻은 부로 뭘 할 생각이오? 노예를 사서 플랜테이션을 살 건가?";
			link.l1.go = "Node_132_19";
		break;
		
		case "Node_132_19":
			dialog.text = "모르겠어, 아직 결정하지 않았어. 어쩌면 유럽으로 갈지도 몰라...";
			link.l1 = "좋아, 그래! 행운을 빌어.";
			link.l1.go = "Node_132_20";
		break;
		
		case "Node_132_20":
			dialog.text = "잠깐만... 이 장신구는 우리 아버지의 보물 중 하나였어. 난 쓸 일이 없지만, 너라면 마음에 들지도 모르지. 제발, 내가 받은 은혜에 대한 내 개인적인 감사의 표시로 받아 줘. 내 몫에서 나온 거야, 하하하!";
			link.l1 = "이런 젠장, 이거 정말 멋진 선물이군. 고맙다"+GetSexPhrase(", 이쁜이","")+"... 좋은 신랑감이나 찾아봐라, 알겠지...";
			link.l1.go = "Node_132_21";
		break;
		
		case "Node_132_21":
			chrDisableReloadToLocation = false;		
			RemovePassenger(pchar, npchar);			
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
            LAi_SetActorType(npchar); // отправил восвояси чтоб не стояла. лесник.
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
            pchar.quest.EncGirl_EnterToSea.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.	
            PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.						
		break;
		
		case "Node_133":
			dialog.text = "하지만 내가 뭘 할 수 있겠소? 여주인님의 명령을 무시할 수는 없지, 그러다간 산 채로 가죽이 벗겨질 테니까.";
			link.l1 = "정착지의 교회에서 나를 기다려라 "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", 내가 새 목걸이를 만들 진주를 가져올게.";
			link.l1.go = "Node_133_1";
			if(sti(pchar.money) >= 15000)
			{
				link.l2 = "여기 있다. 이 15,000페소를 가져가라. 이 정도면 목걸이용 진주를 고르거나 새 목걸이를 사기에 충분하고도 남을 거다.";
				link.l2.go = "Node_135";
			}							
		break;
		
		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";	
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");// лесник - девица убегает если ГГ сказал ждать в цервки
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);			
			Diag.TempNode = "Node_134"; 
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1"); 
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","")); 
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins)); 
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins)); 		
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_134":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Captain","아가씨")+", 다시 만나서 정말 기뻐요! 목걸이용 진주를 모으는 데 성공했나요?","안녕하세요, 선장님! 진주를 가져오셨나요? 아시다시피, 제 여주인께서 꽤나 초조해하고 계십니다...");
			if (GetCharacterItem(pchar, "jewelry52") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry53") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = "그래. 여기 진주들이 있다. 이것들을 네 주인에게 가져가서 다음엔 더 조심하라고 전해라.";
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = "아직 아니야. 그렇게 쉽지 않거든... 하지만 내가 데려올 거야, 두고 봐.";
				link.l1.go = "Node_134_2";
			}	
		break;
		
		case "Node_134_1":
			TakeNItems(pchar, "jewelry52", -sti(pchar.GenQuest.EncGirl.BigCoins)); 
			TakeNItems(pchar, "jewelry53", -sti(pchar.GenQuest.EncGirl.SmallCoins)); 
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = "오, "+GetSexPhrase("Captain","아가씨")+", 당신을 만나서 정말 기뻐요! 저를 위해 해주신 모든 일에 대한 감사의 표시로 이 장신구와 보석들을 드리고 싶어요. 유용하게 쓰시길 바랍니다.";
			link.l1 = "이런 젠장! 그래, 너도 고맙다"+GetSexPhrase(", 미인아","")+", 이럴 줄은 몰랐소... 안녕히 가시오, 행복하길 바라오.";
			link.l1.go = "Node_134_End";
		break;
		
		case "Node_134_2":
			dialog.text = "오, "+GetSexPhrase("선장","아가씨")+", 나는 너를 믿고 있다.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;
		
		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			TakeNItems(pchar, "jewelry1", 15+hrand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			dialog.text = "오, "+GetSexPhrase("선장","아가씨")+", 오늘 두 번째로 저를 도와주셨군요. 정말 감사합니다. 당신의 친절을 절대 잊지 않겠습니다.";
			link.l1 = "천만에. 네 주인 아가씨에게 안부 전해 줘...";
			link.l1.go = "Node_135End";
		break;
		
		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;	
		
		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga") 
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse")) 
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}	
				else
				{	
					iRnd = 1;
				}	
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = RandPhraseSimple("그들에게 돈을 줘서는 안 됐어. 걔네들 거짓말하고 있었어.","그놈들 말 믿지 마라. 다 거짓말쟁이들이다. 그리고 돈도 주지 말았어야 했어.");
					link.l1 = "내가 그들을 죽였어야 했나?";
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = "오, 참으로 고귀한 행동이군! 당신이 그런 분이라는 걸 바로 알아챘소 "+GetSexPhrase("진짜 신사","귀족 부인")+"! 제 진심 어린 감사를 받아주십시오. 그 불한당들이 한 말을 믿으신 건 아니겠지요?";
					link.l1 = "그건 중요하지 않아. 정글에서 소녀랑 오합지졸 무리라니, 그야말로 자연스러운 일이잖아...";
					link.l1.go = "Node_210";
					link.l2 = "무슨 소리야, "+GetSexPhrase("아름다움","친애하는")+"? 내가 어떻게 그래?";
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = "감사합니다, 선장님. 이런 불쾌한 일에 당신을 끌어들여 정말 죄송합니다만, 달리 방법이 없었습니다.";
					link.l1 = "음, 너도 꽤 곤란한 상황에 처한 것 같군. 어쩌다 이렇게 된 거지?";
					link.l1.go = "Node_220";		
				break;
			}
		break;
		
		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = "아마도... 이제 그들은 절대 나를 내버려두지 않겠지.";
				link.l1 = "아, 제발! 그냥 집에 가. 이제 두려워할 것 없어.";
				link.l1.go = "Node_200End";
				link.l2 = "이런 젠장! 왜 그렇게 남자들을 싫어하는 거야?";
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = "당연히 아니지! 하지만 저놈들이 나를 그냥 두지 않을 거야. 나를 그 정착지로 데려다줄 수 있겠나 "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", 부탁해?";
				link.l1 = "그냥 집에 가. 너한텐 손도 안 댈 거야. 지금쯤이면 쉽게 번 돈이나 탕진하러 선술집으로 갔을 테니까.";
				link.l1.go = "Node_200End";
				link.l2 = RandPhraseSimple("너무 걱정하지 마, 진짜로... 좋아, 가자.","넌 정말 겁쟁이구나, 그렇지? 좋아, 내가 거기로 데려다줄게..");
				link.l2.go = "Node_121Next";
			}
		break;
		
		case "Node_201":
			dialog.text = "오, 이런, 무슨 소리야? 저 악당들을 나는 너무 잘 알아. 그놈들은 우리 아버지의 옛 친구들이었어. 지금 아버지가 보물을 숨긴 곳을 찾으려고 하고 있잖아.";
			link.l1 = "그리고 네 아버지는 무슨 사연이 있는데?";
			link.l1.go = "Node_202";
		break;
		
		case "Node_202":
			dialog.text = "그는 한때 해적선의 선장이었지. 최근에 죽었어... 장례식 때는 모두가 그렇게 예의를 차렸는데, 시간이 지나자 그를 잊었고, 곧 명예와 정직함도 잊었지. 내가 그놈들을 눈여겨본 게 다행이야. 보물의 위치를 알게 되는 순간, 내 꼴은 끝장이야.";
			link.l1 = "그거 참 안타까운 이야기군. 그래서, 계속 그들한테서 숨어 지낼 생각이야?";
			link.l1.go = "Node_203";
		break;
		
		case "Node_203":
			dialog.text = "나는 집에 보석을 둘 수 없어, 나를 지켜줄 사람이 없거든. 그래서 돈이 떨어지면 밤에 동굴로 가는 거야...\n제발 나를 동굴로 데려다줘, 그러면 내가 그들에게 준 돈을 당신에게 줄게... 당신이 함께 있으면 해적들도 우리를 따라올 엄두를 못 낼 거라 생각해.";
			link.l1 = "미안해, 자기야, 하지만 난 다른 계획이 있어. 보물은 다음에 챙기도록 해.";
			link.l1.go = "Node_200End";
			link.l2 = "좋아, 가자. 나를 두려워하지 않는다면 말이지.";
			link.l2.go = "Node_204";
		break;
		
		case "Node_204":
			dialog.text = "있잖아, 왠지 나는...";
			link.l1 = "음, 그거 다행이군.";
			link.l1.go = "Node_205";
		break;
		
		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = "선장님, 저를 동굴로 데려가 주시겠다고 약속하셨잖아요.";
			link.l1 = "가자...";
			link.l1.go = "exit";
		break;
		
		case "Node_207":
			dialog.text = "좋아요, 선장님, 필요한 만큼 챙겼습니다. 이제 돌아갈 수 있습니다.";
			link.l1 = "네 친구들은 안 보이네.";
			link.l1.go = "Node_208";
		break;
		
		case "Node_208":
			dialog.text = "신께 감사하네. 더 이상 문제는 필요 없어... 자, 이 주괴들을 가져가게... 그걸로 경비는 충분할 거야. 혼자 가게, 나는 다른 길로 갈 테니...";
			link.l1 = "좋아, 겁나지 않는다면 행운을 빌어.";
			link.l1.go = "Node_209";
		break;
		
		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = makeint(sti(pchar.GenQuest.EncGirl.price)/100.0);
			TakeNItems(pchar, "jewelry6", i);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;
		
		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_210":
			dialog.text = "흠, "+GetSexPhrase("선장","아가씨")+", 네 비꼼이 마음에 들지 않는군.";
			link.l1 = "이제 가도 돼, "+GetSexPhrase("아름다움","친애하는")+". 그리고 그들이 다시 쫓아오기 전에 어서 마을로 가는 게 좋을 거요.";
			link.l1.go = "Node_1End";
		break;
		
		case "Node_211":
			dialog.text = "정말 불안했어요! 저를 그 정착지의 선술집으로 데려다주실 수 있나요? "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"아니면, 또 나를 쫓아올까 봐 두렵소.";
			link.l1 = "어쩌면 네 말이 맞을지도 모르지. 가자...";
			link.l1.go = "Node_122Next";
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
		break;
		
		case "Node_220":
			dialog.text = "아이고, 선장님, 그건 긴 이야기라서 선장님께서 흥미로워하실지 모르겠군요. 하지만... 지금은 선장님의 도움이 없으면 할 수 없을 것 같습니다. 혹시 저를 그 정착지의 선술집까지 데려다주실 수 있겠습니까\n "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"? 놈들이 나를 그냥 두질 않더군.";
			link.l1 = "미안해, 자기야, 지금 그럴 시간 없어. 할 일이 있거든.";
			link.l1.go = "Node_221";
			link.l2 = "왜 그렇게 비밀스럽게 구는 거야?";
			link.l2.go = "Node_222";
		break;
		
		case "Node_221":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_222":
			dialog.text = "모두가 내 불행을 이용해 이득을 보려 드는데, 내가 어찌 비밀스럽지 않을 수 있겠소?";
			link.l1 = "좋아, 그럼...";
			link.l1.go = "Node_223";
		break;
		
		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();		
		break;
		
		case "Node_224":
			dialog.text = "선장님, 저를 그 정착지의 선술집에 데려가 주시겠다고 약속하셨잖아요 "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("기억나.","걱정 마, 거기서 보자.");
			link.l1.go = "exit";
		break;
		
		case "Node_225":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15)
				{
					dialog.text = "거긴 사람이 너무 많아. 개인실로 가자. 할 말이 있어.";
					link.l1 = LinkRandPhrase("이미 너한테 해줄 만큼 다 해줬으니, 이제 작별이다.","내 호의를 남용하면 안 돼. 또 보자, 자기야.","이제부터 네 얘기는 필요 없어, 네가 알아서 다 해결해.");
					link.l1.go = "Node_226";
					link.l2 = "흠, 알겠다. 그럼 바텐더에게서 열쇠를 받아오지.";
					link.l2.go = "Node_227";
				}
				else
				{
					dialog.text = "도와주셔서 정말 감사합니다, 선장님. 이 은혜 잊지 않겠습니다.";
					link.l1 = "아, 신경 쓰지 마시오. 앞으로는 좀 더 조심하게나.";
					link.l1.go = "Node_226_1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") // Addon-2016 Jason, французские миниквесты (ФМК)
				{
					dialog.text = "도와주셔서 정말 감사합니다, 선장님. 이 은혜 잊지 않겠습니다.";
					link.l1 = "아, 신경 쓰지 마시오. 앞으로는 좀 더 조심하도록 하시오.";
					link.l1.go = "Node_226_1";
				}
				else
				{
					dialog.text = "거긴 사람이 너무 많아. 개인실로 가자. 너한테 할 말이 있어.";
					link.l1 = LinkRandPhrase("이미 너한테 해줄 만큼 다 해줬으니, 이제 이만 작별이다.","내 호의를 악용하지 마. 잘 있어, 자기야.","이제부터 네 얘기는 필요 없어, 네가 알아서 다 해결해.");
					link.l1.go = "Node_226";
					link.l2 = "흠, 알겠어. 그럼 바텐더한테서 열쇠를 받아올게.";
					link.l2.go = "Node_227";
				}
			}
		break;
		
		case "Node_226":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_226_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar,"GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = "그래서, 아직도 내 이야기를 듣고 싶어?";
				link.l1 = "흠... 이제 내가 가야 할 때인 것 같군. 잘 있어!";
				link.l1.go = "Node_232";
				link.l2 = "그래, 얼른 말해 봐.";
				link.l2.go = "Node_233";	
			}
			else						
			{
				dialog.text = "오, 나의 고귀한 구원자님, 드디어 여인으로서 할 수 있는 유일한 방식으로 당신께 감사를 전할 수 있게 되었어요\n정글에서 당신을 보았을 때, 제 안의 모든 것이 변했어요. 저를 해치려던 자들과 뺨을 할퀴던 날카로운 야자수 잎도 모두 잊었어요. 어디로 도망쳐야 하는지, 왜 도망쳐야 하는지도 잊었죠... 오직 당신만 보였어요. 그리고 오직 당신만을 원했어요... 그리고 당신이 저를 위해 해주신 일 이후로는...";
				link.l1 = "이런 젠장! 성질 한번 고약하군! 널 쫓는 놈들이 누구를 쫓아야 할지 제대로 알았던 모양이야...";
				link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
				link.l2 = "이봐, 미인아, 네 마음은 충분히 이해하겠어. 하지만 제발, 화는 좀 참아줘.";
				link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
			}
		break;
		
		case "Node_229":
			dialog.text = "지금 내게로 와요, 나의 영웅...";
			link.l1 = "오, 자기야...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;
		
		case "Node_230":
			dialog.text = "오! 이, 이게 무슨 짓이야?! 이런 개자식! 한 소녀가 온 마음과 영혼을 다해 고마워했는데, 너는...";
			link.l1 = "글쎄, 네가 그렇게 추파를 던지고 처음 만난 남자한테 들이대지만 않았어도, 분명히 문제도 덜 생겼을 거다. 이제는 정글에서 그런 바람둥이 구해주지 않을 거야...";
			link.l1.go = "Node_231";
		break;
		
		case "Node_231":
			dialog.text = "나는 이런 말을 누구에게서도 들어본 적이 없어! 그리고 절대 용서하지 않을 거야! 나를 반드시 기억하게 될 거다!";
			link.l1 = "얼른 가라니까, 알았지? 그리고 좀 정신 차려, 또 구출당하고 싶지 않으면...";
			link.l1.go = "Node_231_1";
		break;
		
		case "Node_231_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();		
		break;
		
		case "Node_232":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = "내 가족은 정착지에 살고 있어 "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.Parents_City)+". 나는 우연히 여기 오게 되었어요. 약혼자가 저를 그의 부모님께 데려가려고 배에 태웠는데, 그 배가 해적들에게 붙잡혔어요. 배는 빼앗겼고, 승객들은 이곳에서 멀지 않은 만에 상륙시켰죠. 약혼자는 배에 해적들이 들이닥칠 때 죽었고, 저는 정글을 건너다가 심하게 병이 들었어요\n이 지역 사창가의 마담이 저를 간호해서 건강을 되찾게 해줬지만, 제가 일어설 수 있게 되자 치료비를 갚으라며 일을 시켰어요. 저는 창녀가 되었지만 마담의 마음에 들지 못해서, 그녀는 치료비라도 건지려고 저를 산적들에게 팔아넘겼어요. 그 뒤 이야기는 이미 아시잖아요.";
			link.l1 = "그냥 그만두고 집에 가! 왜 놈들한테 노예처럼 당하고 있어?!";
			link.l1.go = "Node_234";
		break;
		
		case "Node_234":
			dialog.text = "안 돼! 내 모든 소지품들, 멀쩡한 옷, 돈, 서류... 전부 사창가에 있어, 내 여행 가방 안에. 데이트 방에 숨겨 놨어. 그리고 지금 이런 꼴로 입고 있으면, 항구에 있는 선원들이 전부 나를 쫓아올 거야. 서류나 돈도 없이 누가 나를 배에 태워 주겠어? 이제는 마을에 얼굴도 못 비추겠어, 나가면 감옥에 처넣을 테니까...";
			link.l1 = "문제없을 거야. 가자. 내가 직접 집까지 데려다줄게.";
			link.l1.go = "Node_235";
			link.l2 = "여기서 기다려. 내가 네 여행 가방 가져올게.";
			link.l2.go = "Node_236";													
			if(sti(pchar.money) >= 5000) 
			{
				link.l3 = "네 서류 따위 누가 신경 써? 집에 가려면 돈이 얼마나 필요해?";
				link.l3.go = "Node_237";							
			}			
		break;
		
		case "Node_235":
			dialog.text = "아, 고맙습니다, 선장님... 하지만... 있잖아요, 드릴 돈이 전혀 없어요.";
			link.l1 = "무슨 대가를 말하는 거야? 들키기 전에 가자...";
			link.l1.go = "Node_240";				
		break;
		
		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit(); 		
		break;
		
		case "Node_236":
			dialog.text = "아이고, 선장님, 있잖아요, 저는 감히 부탁드릴 생각도 못 했습니다...";
			link.l1 = "두려워하지 마라. 곧 돌아올 테니.";
			link.l1.go = "Node_239";				
		break;		
		
		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";
						
			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
		
		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = "아, 혹시 무슨 일이 생긴 건 아닐까 걱정하고 있었소.";
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = "무슨 일이 일어나겠어? 자, 네 물건 가져가.";
				link.l1.go = "Node_241";
			}	
			else
			{
				link.l1 = "이봐, 거기서 아무것도 못 찾았어. 정말로 연회실에 여행 가방을 두고 왔다는 게 확실해?";
				link.l1.go = "Node_242";			
			}	
		break;
		
		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = "감사합니다, "+GetSexPhrase("고귀한 선장","귀족 아가씨")+". 당신이 저에게 해준 일을 절대 잊지 않겠습니다. 가진 건 많지 않지만, 이 부적을 받아주십시오. 해적의 습격 때 제 목숨을 구해준 것도 어쩌면 이 장신구였을지 모릅니다.";
			link.l1 = "감사합니다, 안전한 항해 되시길! 이제 안녕히 가십시오...";
			link.l1.go = "Node_243";
		break;
		
		case "Node_242":
			dialog.text = "정말로 내 가방을 찾았대?";
			if(sti(pchar.money) >= 5000)
			{
				link.l1 = "집에 돌아가려면 돈이 얼마나 필요하지?";
				link.l1.go = "Node_237";
			}
			link.l2 = "아마 그랬을지도. 어쨌든, 이제 여기서 우리 길은 갈라지네. 잘 가라!";
			link.l2.go = "Node_244";
		break;
		
		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_245":
			dialog.text = "감사합니다, 선장님. 있잖아요, 제가 드디어 집에 돌아왔다는 게 아직도 믿기지 않아요. 제발, 저와 함께 가주세요. 부모님께 선장님을 소개해 드릴게요.";
			link.l1 = "들어봐, "+GetSexPhrase("아름다움","여보")+", 지금은 정말 그럴 시간이 없어. 다음에 하자고 할까?";
			link.l1.go = "Node_246";
		break;
		
		case "Node_246":
			dialog.text = "정말 안타깝군요... 자, 그럼 작별입니다. 주님께서 당신을 지켜주시길. 보답할 것은 없지만, 이 부적을 받아주십시오.";
			link.l1 = "고마워! 이제 집에 가서 부모님을 기쁘게 해 드려!";
			link.l1.go = "Node_247";
		break;
		
		case "Node_247":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);		
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl","sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "Node_248":
		break;
		
		case "Node_237":
			dialog.text = "글쎄요, 잘 모르겠어요... 어쩌면 지나가는 배를 기다려야 할지도 모르겠네요. 하지만 당신에게 돈을 달라고는 못 하겠어요.";
			if(makeint(pchar.money)>=5000)
			{
				link.l1 = "알겠네. 좋아, 5000페소 가져가게. 그 정도면 충분하겠지.";
				link.l1.go = "Node_237_1";
			}
			if(makeint(pchar.money)>=25000)
			{
				link.l2 = "알겠다. 좋아, 25,000페소를 가져가서 집으로 돌아가라.";
				link.l2.go = "Node_237_2";
			}
			if(makeint(pchar.money)>=35000)
			{
				link.l3 = "알겠네. 좋아, 35,000페소를 가져가게. 그 정도면 배에서 제일 좋은 선실을 살 수 있을 거야.";
				link.l3.go = "Node_237_3";
			}
		break;
		
		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			dialog.text = "감사합니다, "+GetSexPhrase("고귀한 선장","귀족 아가씨")+". 당신이 내게 해준 일을 절대 잊지 않겠소.";
			link.l1 = "그럼, 좋은 항해 되시오. 잘 가게...";
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;
		
		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			dialog.text = "감사합니다, "+GetSexPhrase("고귀한 선장","귀족 아가씨")+". 당신이 나에게 해준 일을 절대 잊지 않겠소.";
			link.l1 = "그럼, 좋은 항해 되시길. 안녕히 가시오...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			dialog.text = "감사합니다, "+GetSexPhrase("고귀한 선장","귀족 아가씨")+". 당신이 나에게 해준 일을 절대 잊지 않겠소.";
			link.l1 = "그럼, 좋은 항해 되시길. 안녕히 가시오...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney") 
			{
				AddSimpleRumour(RandPhraseSimple("Have you heard? A whore was trying to sneak on board of a ship without documents, but she was caught and taken back to the brothel. They say she owed the madam quite a sum.",  
				"Have you heard? A whore without documents was caught at the port. They say she had cleaned out madam's coffers before attempting to flee from the brothel. I say, that source of filth and thievery must have been closed off long ago. Our kids are even seeing this and what can they learn from such an example?"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_250":
			dialog.text = "내 인생 망치지 마요, 선장님! 아버지가 저를 그 고리대금업자 아들, 그 더러운 겁쟁이와 결혼시키려고 해요... 그냥 그 아버지가 돈이 많다는 이유로요! 차라리 평생 그 녀석이랑 사는 것보단 정글에서 야수에게 잡아먹히는 게 낫겠어요!";
			link.l1 = "결혼에 무슨 문제가 있소, "+GetSexPhrase("아름다움","여보")+"? 너한테 청혼하려는 사람을 꼭 붙잡고 행복하게 살아. 시간이 좀 지나면 그 멍청이랑 결혼하는 게 기쁠 수도 있겠지만, 그땐 이미 늦었을지도 몰라...";
			link.l1.go = "Node_251";
		break;
		
		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "안 돼! 안 돼, 선장님, 나는 사랑해 "+pchar.GenQuest.EncGirl.sLoverId+" 그리고 나는 다른 남자와 결혼하지 않을 거야! 아버지도 아무 말도 듣고 싶어하지 않으셔! 아버지께서는 "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+" 여긴 그냥 방문객일 뿐이라서 절대 일자리를 구하지 못할 거고, 결국 가난하게 죽을 운명이에요, 저도 그와 함께요! 그 사람 곁에 있기만 하다면 세상 끝까지라도 따라갈 거예요! 제발 그 사람에게 데려다 주세요, 부탁드려요!";
			link.l1 = "좋아, 가자. 너를 어떻게 할지 곧 알게 되겠지...";
			link.l1.go = "Node_252";
		break;
		
		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl","sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId); 
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_253":
			Diag.TempNode = "Node_253";
			dialog.text = "선장님, 저를 그 정착지로 데려가시겠다고 약속하셨잖아요 "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("기억나.","걱정 마, 내가 거기로 데려다줄게.");
			link.l1.go = "exit";			
		break;
		
		case "Node_260":
			chrDisableReloadToLocation = false;
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("감사합니다, "+GetSexPhrase("선장","아가씨")+", 다시 한 번. 정말로, 당신에게 큰 신세를 졌소.","정말 감사합니다, "+GetSexPhrase("선장","아가씨")+". 당신의 도움이 없었더라면 어찌했을지 모르겠소.");
				link.l1 = RandPhraseSimple("그것이 너에게 교훈이 되었으면 좋겠군. 좋아, 행운을 빌지...","다음엔 좀 더 조심해야 할 거야... 이제 집에 가, 난 할 일이 있으니까.");
				link.l1.go = "Node_260End";
				link.l2 = "어떻게 그렇게 부주의할 수가 있지? 왜 혼자 정글로 들어간 거야?";
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = "오, "+GetSexPhrase("선장","아가씨")+", 정말 어떻게 감사드려야 할지 모르겠습니다.";
				link.l1 = "별거 아니오. 언제든 도와드릴 수 있어 기쁩니다...";
				link.l1.go = "Node_261";
			}
		break;
		
		case "Node_260End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");			
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_261":
			dialog.text = "선술집까지 데려다줄 수 있나요? 이모를 기다려야 하고 좀 쉬어야겠어요, 이 '모험' 때문에 완전히 기운이 빠졌거든요...";
			link.l1 = "아니, "+GetSexPhrase("아름다움","여보")+", 그 정도면 나한텐 충분해. 할 일이 많거든.";
			link.l1.go = "Node_262";
			link.l2 = ""+GetSexPhrase("아, 여자들! 남자의 도움이 없으면 못하는 게 과연 있긴 한가?","왜 이렇게 무기력해?")+" 가자...";
			link.l2.go = "Node_263";
		break;
		
		case "Node_262":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";					
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
				
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation.nobility) >= 80)
			{
				dialog.text = "저에게 약간의 돈이 있습니다... 제 감사의 표시로 받아 주십시오!";
				Link.l1 = "감사합니다. 다음에는 더 조심하세요.";
				Link.l1.go = "exit";
			}
			else 
			{
				if(hrand(1) == 0)
				{
					dialog.text = "내가 당신에게 구원받았다고 모두에게 말하겠소! 모두가 알게 하시오, "+GetSexPhrase("정말 용감하고 대담한 사람이구나","정말 용감하고 대담한 여인이시군요")+"!";
					Link.l1 = "감사합니다. 이제 집으로 돌아가십시오.";
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = "저에게 약간의 돈이 있습니다... 제 감사의 표시로 받아 주십시오!";
					Link.l1 = "고마워. 다음엔 좀 더 조심해.";
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = "내가 당신에게 구원받았다고 모두에게 말하겠소! 모두가 알게 하시오, "+GetSexPhrase("정말 용감하고 대담한 사람이구나","정말 용감하고 대담한 여인이시군요")+"!";
			Link.l1 = "감사합니다. 이제 집으로 돌아가야겠군요.";
			Link.l1.go = "exit";
		break;
	}
}
