// Соломон Шнеур - старый еврей
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
//--------------------------------------за Голландию------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyFather")
				{
					dialog.text = "이 늙은 유대인한테서 뭘 원하는 거냐, 젊은이?";
					link.l1 = "솔로몬, 신중하게 생각해서 네가 난파당했던 잃어버린 섬을 기억해 봐. 거기에 네가 숨겨둔 비밀 창고가 있지. 네 딸과도 이미 얘기했어. 내 상사 루카스 로덴부르크가 네 가족의 이익을 위해 내가 자유롭게 행동할 수 있도록 허락했지. 내 생각에 지금 네게 가장 중요한 건 가족의 자본을 되찾는 거야. 내 도움이 없으면 그 금 냄새조차 맡지 못할 거다.";
					link.l1.go = "SolomonBonanza";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "오, 젊은이, 너였구나? 좋은 소식은 하나도 없느냐? 또 그리스도인들이 이 늙은 유대인에게 질문으로 괴롭히러 온 거냐?";
					if (CheckCharacterItem(pchar, "SkullAztec"))
					{
						link.l1 = "섬을 찾아냈소, 꽤 힘들었지만. 그리고 당신의 돈이 든 상자와 이 해골도 찾았소. 이게 당신이 말하던 조상 대부의 해골이겠지, 뭐였든 간에.";
						link.l1.go = "SolomonBonanza_2";
					}
					link.l2 = "섬을 찾아냈소, 쉽지 않은 일이었지. 돈이 든 상자도 찾았소. 하지만 그 상자에는 해골이 없었소.";
					link.l2.go = "SolomonBonanza_3";
					link.l3 = "아니오, 지금은 질문이 없습니다.";
					link.l3.go = "exit";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "GiveLucasMoney" && GetQuestPastDayParam("questTemp.HWIC.Holl.LucasMoney") > 7)
				{
					dialog.text = "오, 내 젊은이, 자네였나? 좋은 소식이라도 들려줄 수 있겠나? 아니면 또 이 불쌍한 늙은 유대인을 질문으로 괴롭히려는 건가?";
					link.l1 = "섬을 찾아냈소, 꽤 힘들었지만. 그리고 당신의 돈 상자도 찾았소. 여기 있소.";
					link.l1.go = "SolomonBonanza_5";
					break;
				}
				dialog.text = "안녕하시오, 젊은이. 이 가엾은 늙은 유태인에게 무슨 볼일이오?";
				link.l1 = "좋은 오후입니다. 아니요, 아무 일도 없습니다, 그냥 인사하러 왔습니다.";
				link.l1.go = "exit";
				break;
			}
//----------------------------------------за Англию-----------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "toAbigile")
				{
					dialog.text = "좋은 오후일세, 젊은이. 목적이 있어 온 것 같군... 무엇을 원하는가? 내가 얻을 게 있나, 아니면 내가 뭔가 놓친 건가?";
					link.l1 = "좋은 오후네, 솔로몬. 아비게일과 이야기하고 싶소.";
					link.l1.go = "Solomon_treasure";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "안녕하시오, 젊은이. 이 가난한 늙은 유태인에게 무슨 볼일이오?";
				link.l1 = "안녕하오, 솔로몬. 별일 없소, 그냥 인사하러 왔소.";
				link.l1.go = "exit";
				break;
			}
//-----------------------------------------против всех-------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "좋은 오후일세, 젊은이. 자네가 여기 온 데는 이유가 있겠지... 무엇을 원하는가? 내가 뭘 얻을 수 있나, 아니면 내가 뭔가 놓친 건가?";
					link.l1 = "아비게일과 얘기해야 해. 그녀에게 줄 편지가 있어.";
					link.l1.go = "Abigile_kidnap";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDayOver")
				{
					dialog.text = "안녕하오, 젊은이. 무슨 일로 왔나? 또 내 딸에게 편지를 전해주려는 건가?";
					link.l1 = "아니. 아비게일은 어디 있지?";
					link.l1.go = "Abigile_GoOver";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistory")
				{
					dialog.text = "어이... 내 돈 얘기하는 거냐, 젊은이?";
					link.l1 = "예, 마인헤르. 당신이 어떤 섬에 숨긴 돈에 대해서 말이오. 정말로 당신과 아비게일 모두 그 위치를 기억하지 못한다는 것이 사실이오?";
					link.l1.go = "Solomon_history";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryAfter")
				{
					dialog.text = "좋아. 그 플루트선과 선장을 기억하지. 암스테르담에서 그를 한 번 본 적도 있어. 배 이름은 '라이덴'이고, 선장 이름은 토프 켈러였어.";
					link.l1 = "좋아, 시작이군! 이제 단서가 생겼어.";
					link.l1.go = "Solomon_history_3";
					pchar.questTemp.HWIC.Self = "SolomonHistoryEnd";
					break;
				}
				dialog.text = "오이 베이, 이번엔 이 가엾은 늙은 유태인한테 뭘 또 원하시는 거요?";
				link.l1 = "좋은 오후입니다. 아니요, 아무 일도 없습니다, 그냥 인사하러 왔습니다.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "오이 베이, 이번에는 이 가엾은 늙은 유대인에게서 뭘 원하시오?";
			link.l1 = "안녕하세요. 아니요, 별일 없고, 그냥 인사하러 왔어요.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-----------------------------------------------За Голландию-----------------------------------
		case "SolomonBonanza":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "내가 뭘 해주길 바라는 거요? 내가 뭘 아는 사람처럼 보이나? 신도 버린 이런 날에, 저 밖에 아무나 와서 가져갈 수 있는 땅덩어리랑 물건, 금이 있을 줄 내가 어떻게 알았겠소? 저기 거리를 돌아다니는 이방인들이 나 같은 유대인을 골려서 내 돈을 가져가려고 얼마나 눈을 부라리는지 상상이나 해보시오!\n섬이 하나 있소. 거기엔 나랑 아비 말고는 아무도 없었지. 단 한 명도. 정말 아무도. 그 한가운데에 동굴이 있었소. 그 해적 놈, 아말렉한테서 내 상자를 지키려고 그 안에 숨겼지! 금으로 가득 찬 상자요, 잡동사니 하나 없소. 그걸 먼 옛날 고향에서부터 끌고 왔지! 내가 피땀 흘려 번 모든 게 그 안에 있소. 게다가 내 할아버지 해골도... 믿으시오, 그게 우릴 살렸소, 그래-그래\n오호호, 그건 탈무드 마법이 깃든 고대 부적이오! 신이시여, 아말렉에게서 우릴 구하소서! 오이구야, 이방인 세상에서 다시 시작하는 게 얼마나 힘든지! 젊은이, 자네가 알았으면 좋겠구려! 정말, 자네가 알았으면!";
			link.l1 = "도대체 무슨 헛소리를 하는 거야, 이 미친놈아? 누가 신경이나 쓰겠어. 내가 직접 처리하지. 잘 가!";
			link.l1.go = "SolomonBonanza_1";
		break;
		
		case "SolomonBonanza_1":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbySeekIsland";
			pchar.quest.Joakim_meeteng.win_condition.l1 = "location";
			pchar.quest.Joakim_meeteng.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Joakim_meeteng.function = "Create_Joakim";
		break;
		
		case "SolomonBonanza_2"://отдаем всё
			dialog.text = "이봐, 신은 계시고 당신은 진정한 의인이구려! 내 금을 되찾아줬을 뿐만 아니라 슈네우르 가문의 명예도 회복시켜줬소! 당신이 막아낸 수치가 얼마나 큰지! 로덴부르크 나리는 이런 선장들을 두고 자랑스러워해야 마땅하오. 나는 해골을 로덴부르크 나리께 드릴 것이오, 그분이 큰 돈을 주기로 약속했으니. 개인적으로 감사드리고 싶소, 당신은 훌륭한 샤보스 고이요. 이 유대인의 작은 감사의 표시로 이 부적을 받아주시오.";
			link.l1 = "어, 고맙긴 하네.";
			link.l1.go = "SolomonBonanza_4";
			RemoveItems(PChar, "SkullAztec", 1);
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			AddDialogExitQuestFunction("DeleteJoakimFromRoom");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Joakim"));
			pchar.questTemp.Caleuche.SolomonSkul = true;
		break;
		
		case "SolomonBonanza_3":
			dialog.text = "이봐, 신은 계시고 당신은 진정한 의인이구려! 내 금을 되찾아줬을 뿐만 아니라 슈네우르 가문의 명예도 되살려줬소! 당신 덕분에 큰 수치를 막았구려! 해골에 관해서는... 뭐, 신경 쓸 것 없소, 어차피 그 자는 미친 얼간이였으니! 로덴부르크 나리께서 당신 같은 선장을 두고 자랑스러워할 만하오. 내가 직접 감사 인사를 전하고 싶소. 당신은 훌륭한 샤보스 고이요. 이 부적을 기념으로 받아주시오.";
			link.l1 = "어, 고맙긴 하군.";
			link.l1.go = "SolomonBonanza_4";
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "obereg_10");
			pchar.questTemp.HWIC.Holl.ScullnotReturn = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			DelLandQuestMark(npchar);
		break;
		
		case "SolomonBonanza_4":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyLeavesMarried";//теперь можно говорить с Аби
			AddQuestRecord("Holl_Gambit", "1-32");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "SolomonBonanza_5":
			dialog.text = "뭐라고? 뭐라 하는 게냐, 젊은이? 이게 사실이란 말인가? 어디 좀 보자... ";
			link.l1 = "여기 돈이오. 당신과 아비게일의 것이오. 하지만 안타깝게도 당신 할아버지의 해골은 아직 찾지 못했소.";
			link.l1.go = "SolomonBonanza_6";
		break;
		
		case "SolomonBonanza_6":
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			dialog.text = "오, 돈이여, 돈이여, 돈이여, 참으로 멋진 돈이여... 흠, 그런데 이건 내 돈처럼 보이진 않는군... 내 사랑스러운 돈 냄새도 안 나고. 하지만 뭐, 돈이란 다 똑같지, 젊은이? 불평하진 않겠네. '공짜라면 이방인 입도 들여다보지 말라'고 우리끼리 말하곤 하지! 내 저축을 돌려줘서 정말 고맙네. 나도 자네에게 감사 인사를 하고 싶군, 이 부적을 받아주게. 이제 가서 아비에게 좋은 소식 전하게. 나는 이 돈을 세어봐야겠어.";
			link.l1 = "행운이 가득하길 바라네, 솔로몬.";
			link.l1.go = "SolomonBonanza_4";
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

//-------------------------------------------за Англию------------------------------------------------
		
		case "Solomon_treasure":
			dialog.text = "아이고, 조심해라! 로덴부르흐 나리는 내 사위 될 판이야. 내가 소리만 지르면 주둔지의 병사들이 금방 달려올 거다!";
			link.l1 = "너 도대체 누구야?";
			link.l1.go = "Solomon_treasure_1";
		break;
		
		case "Solomon_treasure_1":
			dialog.text = "내 말 잘 들어, 선장. 나는 그녀의 아버지 솔로몬이오. 옳은 일을 하시오, 내 잃어버린 동전들과 그녀의 증조부의 옥 해골을 가져오시오. 이 늙은 유태인이 자네만큼 교활하진 않지만, 그래도 자네가 내 딸에게서 뭔가를 원한다는 건 알고 있소.\n아마 누군가, 나를 아는 어떤 선장이 자네를 보냈겠지. 걱정 말고, 아비에게 모든 걸 말해주겠소. 지금 그녀는 집에 없소, 자네 같은 이방인 죄인들의 영혼을 위해 기도하고 있소.";
			link.l1 = "그게 도무지 말이 안 되잖아... 젠장, 너 정말 골치 아픈 놈이구나. 잘 있어라, 이 구두쇠 영감.";
			link.l1.go = "Solomon_treasure_2";
		break;
		
		case "Solomon_treasure_2":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-17");
			pchar.questTemp.HWIC.Eng = "AbigileInChurch";
			sld = characterFromId("Abigile");
			sld.greeting = "abigile_3";
			ChangeCharacterAddressGroup(sld, "Villemstad_church", "goto", "goto1");//Аби в церковь
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
//----------------------------------------------против всех---------------------------------------------	
		
		case "Abigile_kidnap":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Villemstad");
			dialog.text = "편지라고? 그럴 리가! 이봐, 꼬마야, 로덴부르크 나리는 내 사위가 될 사람이나 다름없어. 그러니 네 엉덩이 여기서 치워, 난 그가 마음에 드니까!";
			link.l1 = "듣게, 나는 자네 사위가 누군지 전혀 상관없어. 나는 이 편지를 반드시 아비게일에게 전해야 하네. 그녀가 어디 있는지 아나? 그리고 자네는 도대체 누구지?";
			link.l1.go = "Abigile_kidnap_1";
		break;
		
		case "Abigile_kidnap_1":
			dialog.text = "내가 누구냐고? 나는 그녀의 아버지, 솔로몬이다... 그리고 나는 네가 마음에 들지 않는다, 이방인아.";
			link.l1 = "네가 날 좋아한다고 하면 더 걱정됐을 거야. 자, 계속 나를 깔보며 굴 거야, 아니면 아비게일을 데려올 거야? 다시 말하지만, 나는 전령이야! 네 딸에게 전할 편지가 있다고!";
			link.l1.go = "Abigile_kidnap_2";
		break;
		
		case "Abigile_kidnap_2":
			dialog.text = "이 편지를 내게 주시오. 내가 내 딸에게 전하겠소.";
			link.l1 = "네 머리털을 밀어버리고 코도 비틀어 줄 테니, 이 편지는 내가 직접 전해줘야 한다. 나는 이 메시지를 그녀에게 직접 전달하라는 명령만 받았지, 그녀 아버지에 대해서는 한마디도 듣지 못했고, 신경 쓸 생각도 없다. 아비게일은 어디에 있지?";
			link.l1.go = "Abigile_kidnap_3";
		break;
		
		case "Abigile_kidnap_3":
			dialog.text = "내가 소리치기만 하면, 이 어린 녀석아, 마을의 모든 병사들이 바로 달려올 거다.\n그만 고집 부려라, 내가 모든 주도권을 쥐고 있다는 걸 뻔히 알지 않느냐.";
			link.l1 = "예수님, 마리아, 요셉! 정말이야? 그래서 어쨌다는 거지? 내가 편지 하나 전했다고 그놈들이 날 족쇄 채운다고? 말도 안 되는 소리 하지 마!";
			link.l1.go = "Abigile_kidnap_4";
		break;
		
		case "Abigile_kidnap_4":
			DialogExit();
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, "Villemstad_houseSP2", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_GoOver":
			dialog.text = "너 미쳤어? 네 편지 때문에 내 딸이 반쯤 죽을 지경이 됐잖아... 그 멍청한 영국 선장 따라가겠다고 결심했어! 첫 배에 올라타서 떠나버렸다고! 아이고, 내 불쌍한 딸아! 이 늙은 유대인은 이제 어쩌란 말이냐? 내 인생은 망했어! 이게 무슨 망신이냐! 그냥 날 내버려 두든, 아니면 옆에서 비웃든, 상관없다! 아이고, 내 불쌍한 아비가일! 네가 아버지의 백발을 절망 속에 무덤까지 끌고 가는구나!";
			link.l1 = "이런, 어쩔 수 없었나 보군! 한순간도 더 못 기다렸나 봐. 잘 있어, 솔로몬!";
			link.l1.go = "Abigile_GoOver_1";
		break;
		
		case "Abigile_GoOver_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-69");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
		break;
		
		case "Solomon_history":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "어떻게 보이냐고? 그냥 나랑 아비게일밖에 없는 섬일 뿐이야. 내가 내 상자를 숨긴 곳이지, 그 해적 놈 아말렉이 가져가지 못하게 하려고 말이야. 내가 땀 흘려 정직하게 번 모든 게 그 상자 안에 들어 있어...";
			link.l1 = "말해 보시오, 솔로몬. 혹시 따님이 언급한 플라이트의 이름을 기억하겠소? 그리고 그 배의 선장 이름은 무엇이었소?";
			link.l1.go = "Solomon_history_1";
		break;
		
		case "Solomon_history_1":
			dialog.text = "흠... 글쎄다. 이 불쌍한 늙은 유태인의 머리는 게필테 피시 한 냄비처럼 뒤죽박죽이구나! 그런데 왜 묻는 거냐, 젊은이?";
			link.l1 = "나는 그저 솔로몬, 당신 딸을 도와주고 싶을 뿐이오. 아무것도 약속할 수는 없지만, 시도해보고 싶소. 내 이전 상사가 그녀를 함부로 대했기에, 그 일 이후로 어떻게든 그녀가 정착할 수 있도록 도와야겠다는 의무감을 느끼오.";
			link.l1.go = "Solomon_history_2";
		break;
		
		case "Solomon_history_2":
			dialog.text = "오이 베이, 뭐, 그렇다면...";
			link.l1 = "";
			link.l1.go = "Solomon_history_3";
			pchar.questTemp.HWIC.Self = "SolomonHistoryNext";
		break;
		
		case "Solomon_history_3":
			DialogExit();
			sld = characterFromId("Abigile");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Solomon_thanks":
			dialog.text = "젊은이! 잠깐!";
			link.l1 = "예?";
			link.l1.go = "Solomon_thanks_1";
		break;
		
		case "Solomon_thanks_1":
			dialog.text = "젊은이! 나와 내 딸을 위해 해준 모든 일에 감사하고 싶네. 자네가 우리를 구했지. 처음 만났을 때 냉대하고 자네의 진심 어린 도움을 의심했던 것을 미안하게 생각하네. 부디 이 늙은 유태인을 용서해주게. 자네는 정말 이방인들 중에서도 축복받은 사람이야. 그런데, 동굴에서 내 돈 말고 다른 것도 찾지 않았나?";
			link.l1 = "아니, 솔로몬. 돈 말고는 아무것도 없었어. 반 베르크의 악당들과 싸워야 했지. 네 배를 몇 달 전에 침몰시킨 것도 바로 그 놈이야. 아마 그 자들이 이미 뭔가를 훔쳐갔을 수도 있겠지... 거기에 또 뭐가 더 있었어야 했나?";
			link.l1.go = "Solomon_thanks_2";
		break;
		
		case "Solomon_thanks_2":
			dialog.text = "오, 별거 아니야... 그냥 오래된 가보 하나지... 뭐, 됐다! 신경 쓰지 마, 어차피 바보였으니까! 그리고... 한 가지만 더, 젊은이... ";
			link.l1 = "계속해.";
			link.l1.go = "Solomon_thanks_3";
		break;
		
		case "Solomon_thanks_3":
			dialog.text = "너... 그래, 너에 대해 좀 알아냈지. 우리 총독께서 너를 높이 평가하고 계시고, 너는 이름난 선장이더군. 비밀 하나 알려주지... 내 딸이 너를 많이 좋아해. 직접 내게 말했거든. 어쩌면... 이 점을 생각해볼래? 아비게일은 정말 좋은 아이라네, 내가 장담하지. 네가 여행 중에 만났던 그 어떤 이교도 계집들보다 훨씬 나아.";
			link.l1 = "오이 베이... 그렇게 간단하지 않아, 솔로몬. 네 딸은 정말 귀한 보석이야. 잘 챙겨줘.";
			link.l1.go = "Solomon_thanks_4";
		break;
		
		case "Solomon_thanks_4":
			dialog.text = "곰곰이 생각해 보게, 젊은이. 다시 한 번 생각하고 돌아오게! 다시 만나면 정말 반가울 테니!";
			link.l1 = "그래... 잘 가, 솔로몬.";
			link.l1.go = "Solomon_thanks_5";
		break;
		
		case "Solomon_thanks_5":
			DialogExit();
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload1", false);
			AddQuestRecord("Holl_Gambit", "3-65");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "Solomon_poor":
			dialog.text = "오이이... 가끔은 새로운 삶을 시작하는 게 정말 불가능하구나, 젊은이. 가난하게 산다는 것, 나 같은 늙은 바보에게 이보다 더 끔찍한 일이 어디 있겠느냐?";
			link.l1 = "미안하오, 솔로몬. 굳건히 서서 그리스도를 찾으시오.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Solomon_poor";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("너는 "+GetSexPhrase("도둑이오, 나리! 경비병들아, 저 자를 잡아라","도둑이다, 저 계집애를 잡아라! 경비병들, 저년을 붙잡아!")+"!!!","저것 좀 봐! 내가 잠깐 생각에 잠긴 사이에 내 가슴을 뒤지다니! 도둑이야!!!","경비병들! 도둑이야! 저 도둑 잡아라!!!");
			link.l1 = "제기랄!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
