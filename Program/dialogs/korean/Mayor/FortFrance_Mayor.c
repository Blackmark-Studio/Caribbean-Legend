// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 용건이오? 물어보시오.","듣고 있소, 무슨 질문이오?"),"두 번째로 다시 묻는 것이오...","당신이 다시 물어보려는 것이 이번이 세 번째입니다...","언제 끝날 것이오?! 나는 식민지의 일로 바쁜 사람인데, 그대는 아직도 뭔가를 물으려 하는 것이오!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소...","지금은 아니오. 장소와 시간이 맞지 않소."),"그렇소... 하지만 나중에, 지금은 아니오...","물어보겠소... 하지만 조금 이따가...","죄송합니다, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "나리, 저는 정글에서 산적의 시신을 발견하였습니다. 그는 인디언들에게 살해당한 것 같습니다. 그의 시신에서 귀걸이가 나왔는데, 유럽에서 가져온 것처럼 보입니다. 아마도 이 마을의 귀족 중 한 분의 소유였을지도 모르겠습니다.";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_Potopil"))
			{
				link.l1 = "각하, 임무를 완수하였습니다! 그러나 유감스럽게도 범죄자가 교전 중에 사망하여 처형을 받지 못하게 되었음을 알려드립니다.";
                link.l1.go = "TK_Potopil";
			}
			if (CheckAttribute(pchar, "questTemp.TK_Plen"))
			{
				link.l1 = "각하, 임무를 완수하였습니다! 죄수는 제 감방에서 운명을 기다리고 있습니다.";
                link.l1.go = "TK_Plen";
			}
			//<-- Травля крысы
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "저는 필리프 드 푸앵시 총독의 명을 받아 귀하의 무장 프리깃함의 지휘를 맡으러 왔습니다.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l1 = "저는 프리깃함을 제 함대에 편입할 준비가 되어 있습니다.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "message")
			{
				link.l1 = "초대해 주셔서 왔습니다, 나리...";
                link.l1.go = "goldengirl";
			}
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "girl_prisoner")
			{
				link.l1 = "유감이로군요, 나리";
                link.l1.go = "goldengirl_10";
			}
			// andre39966 ===> В плену великого улова.
			if (CheckAttribute(pchar, "questTemp.VPVL_Magor_Dialogue"))
			{
				link.l1 = "각하, 이 해안에서 곧 불법 거래가 이루어질 것이라는 정보를 입수하였습니다. 이 사안이 각하의 관심을 받을 만한 가치가 있다고 감히 말씀드립니다.";
				link.l1.go = "VPVL_Magor_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable"))
			{
				link.l1 = "각하, 전에 논의했던 그 밀수선에 대한 소식을 듣고자 왔습니다.";
				link.l1.go = "VPVL_Magor_4";
			}
			//  <=== В плену великого улова.  
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "무엇을 가지고 왔는지 보자꾸나... 믿을 수가 없군! 정말로 놀랍네, Charles! 이것은 내 아내의 귀걸이야. 내가 유럽을 떠나 식민지로 오기 전에 그녀에게 선물했던 것이지. 몇 달 전에 수상한 정황 속에서 사라졌었네. 도둑맞은 줄 알았지!\nCharles, 네가 곧장 나에게 와서 이 소중한 물건을 상인들에게 팔지 않은 것이 정말 기쁘네. 너의 호의에 반드시 보답하겠네. 듣자하니, 배를 살 생각이라던데? 이제 바다에 나설 결심을 했으니, 우리 군도의 지도가 반드시 필요할 걸세. 여기, 가져가게. 분명히 큰 도움이 될 것이네!";
			link.l1 = "감사합니다, 각하!";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_normal");
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		
		//--> Sinistra, Травля крысы
		case "TK_Potopil":
			dialog.text = "유감이오, Charles, 하지만 우리는 주어진 상황에 적응해야 하오. 여기 보상이 있소: 세금을 제하고 오천 페소요.";
			link.l1 = "생피에르와 나리께 직접 봉사하게 되어 기쁩니다. 전투는 힘들었으나, 그 속에서도 약간의 즐거움을 찾을 수 있었습니다.";
			link.l1.go = "TK_Potopil_3";
			link.l2 = "험난한 전투였사옵니다, 각하. 제 배가 큰 피해를 입었나이다. 손실에 대한 보상을 받을 수 있겠사옵니까?";
			link.l2.go = "TK_Potopil_4";
			DeleteAttribute(pchar, "questTemp.TK_Potopil");
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			
			CloseQuestHeader("TravlyaKrys");
		break;
		
		case "TK_Potopil_3":
			dialog.text = "브라보, Charles! 그대는 틀림없이 우리 계급에서 크게 출세할 것이라 믿어 의심치 않소.";
			link.l1 = "다시 뵙는 그날까지, 각하.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Potopil_4":
			dialog.text = "솔직히 말하자면, 당신의 요청에 조금 놀랐소, Charles... 좋소, 내 개인적으로 선의의 표시로 이천 페소를 추가로 내겠소. 안녕히 가시오.";
			link.l1 = "감사합니다, 각하.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 7000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		
		case "TK_Plen":
			dialog.text = "훌륭하오, Charles! 그대의 성공이 몰타 친구들의 미묘한 작전에 도움이 될 것이라는 소식을 들으면 기뻐할 것이오... 여기 보상금이 있소. 세금 공제 후 8,000페소요.";
			link.l1 = "생피에르와 기사단, 그리고 나리께 직접 봉사하게 되어 기쁩니다. 전투가 쉽지는 않았으나, 그 속에서도 나름의 만족을 느꼈습니다.";
			link.l1.go = "TK_Plen_3";
			link.l2 = "힘든 전투였사옵니다, 각하. 제 배가 상당한 피해를 입었사옵니다. 손실에 대한 보상을 청해도 되겠습니까?";
			link.l2.go = "TK_Plen_4";
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			CloseQuestHeader("TravlyaKrys");
			DeleteAttribute(pchar, "questTemp.TK_Plen");
			sld = CharacterFromID("TK_Heiter2");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
		break;
		
		case "TK_Plen_3":
			dialog.text = "브라보, Charles! 나는 그대가 크게 성공하리라 믿소.";
			link.l1 = "다시 뵐 때까지, 각하";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 8000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Plen_4":
			dialog.text = "자네가 받을 자격이 있다고 생각하오. 내 개인적으로 선의의 표시로 이천을 더 가지시오. 고맙네, 친구.";
			link.l1 = "감사합니다, 각하.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		//<-- Травля крысы
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "배는 준비되어 있지만, 당신의 함대에 이 배를 위한 빈 정박지가 없습니다.\n선장님, 함대 규모를 줄이고 다시 오십시오. 그러면 즉시 프리깃을 드리겠습니다.";
				link.l1 = "좋소.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "예, 물론입니다. 배는 출항 준비가 되어 있습니다. 선장도 알고 있으며, 나리의 모든 명령을 따를 것입니다.";
				link.l1 = "그럼 이제 출발하겠습니다. 안녕히 계십시오, 나리.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "훌륭하오. 새 배를 맞이할 준비를 하시오.\n그 배의 선장은 이미 알고 있으며, 당신의 모든 명령을 따를 것이오.";
			link.l1 = "그럼 이제 출발하겠습니다. 안녕히 계십시오, 각하.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "goldengirl":
			dialog.text = "샤를 드 모르 선장, 드디어 오셨군요! 오래도록 기다렸습니다! 부디 들어오셔서 저와 함께하시지요.";
			link.l1 = "각하께도 좋은 하루 되시길. 이렇게 공손하신 데에는 언제나 이유가 있지요. 이번에는 무슨 일입니까? 해적입니까, 스페인인입니까, 아니면 붉은 피부 식인종들입니까?";
			link.l1.go = "goldengirl_1";
		break;
		
		case "goldengirl_1":
			dialog.text = "빈정거리지 마시오, 선장님. 우리가 항상 곤경에 빠지는 것이 제 잘못은 아니지 않습니까, 선장님과 저는. 하지만 제발 걱정 마십시오, 이번에는 총격전은 없을 것이오... 아마도요.";
			link.l1 = "흥미롭군, 계속 말하게. 내가 어떻게 도와줄 수 있겠는가?";
			link.l1.go = "goldengirl_2";
		break;
		
		case "goldengirl_2":
			dialog.text = "마담 보토의 훌륭한 업소에 대해 들어본 적 있소? 포위전 동안 우리... 사창가는 잿더미가 되었지. 어느 날, 한 숙녀가 그것을 다시 세우겠다고 자원했소.";
			link.l1 = "기생집에 불이 났는데 나 없이? 그런데 그날 나도 스페인 놈들에게 총을 맞았지.";
			link.l1.go = "goldengirl_3";
		break;
		
		case "goldengirl_3":
			dialog.text = "제길, Charles, 오늘따라 왜 이러는 거요? 재치도 도가 지나치오! 국정과 직접 관련된 일은 아니지만, 내게는 여전히 중요한 일이오! 자네의 도움이 필요하오! 제발 정신 좀 차리고 내 말 좀 들어주시오!";
			link.l1 = "용서해 주십시오, 각하. 그저 큰 안도감을 느끼고 있을 뿐입니다. 사실, 이 끊임없는 전투와 싸움에 지쳐버렸습니다. 나리께서 또다시 저를 폭력의 소용돌이로 끌어들이실까 봐 그렇게 생각했을 뿐입니다. 계속 말씀하시지요. 이 마담 보토라는 사람에 대해서는 들어본 적이 없습니다.";
			link.l1.go = "goldengirl_4";
		break;
		
		case "goldengirl_4":
			dialog.text = "옳소, 이 고귀하신 숙녀께서 이곳의 격을 완전히 끌어올리셨소. 이제는 예전처럼 쥐구멍이 아니라, 고상하고 귀족적인 사교의 장이 되었지요. 품격 있는 향락, 값비싼 와인, 그리고 무제한 도박의 장소이오. 직접 눈으로 확인하게 될 것이오!";
			link.l1 = "각하, 저는 결코 고지식한 사람이 아니오. 그리고 각하의 묘사는 매우 생생하였소만, 왜 저에게 이런 말씀을 하시는 것이오?";
			link.l1.go = "goldengirl_5";
		break;
		
		case "goldengirl_5":
			dialog.text = "명단에 있으니까 그렇지, 그 외에 이유가 있겠어?! 봐, 내가 후작부인 일로 미안한 마음이 들어서 내일 그녀가 여는 파티에서 너를 소개해 주기로 약속했어. 줄리아나는 이런 자리를 자주 마련하지 않으니, 부디 우리와 함께해 주게. 이번에는 싸움도, 총질도, 추격도 없을 거라고 약속하네. 모든 것이 예의 바르고 품위 있게 진행될 걸세: 와인, 아름다운 여인들, 카드, 그리고 다른 귀족들의 향락이 준비되어 있네.";
			link.l1 = "카드와 창녀라... 한때는 그런 삶도 있었지. 하지만 아직도 당신을 이해하지 못하겠소. 왜 하필 나입니까?";
			link.l1.go = "goldengirl_6";
		break;
		
		case "goldengirl_6":
			dialog.text = "귀가 멀었소? 줄리아나 보토는... 빛나고 유명한 인물들을 모으지. 그 사람들이 그녀의 파티를 특별하고 신선하게 만드오. 당신은 이미 상당한 명성을 얻었고, 후작부인께서 오랫동안 당신을 손님으로 맞이하길 기다려왔소. 내 실수가 그녀에게 기회를 주었으니, 만약 그녀가 다시 나를 받아주지 않는다면 나는 더 이상 나아갈 수 없소. 당신을 그녀에게 데려가지 않으면 내가 얻을 수 있는 것은 이것뿐이오!";
			link.l1 = "각하께서는 준수한 미망인이시며 총독이십니다... 어찌하여 어떤 창부의 의견에 신경을 쓰십니까? 그들이야말로 각하의 총애를 구해야지, 반대가 되어서는 아니 되옵니다.";
			link.l1.go = "goldengirl_7";
		break;
		
		case "goldengirl_7":
			dialog.text = "마르키즈 보토는 앙리 드 레비-방타뒤르 백작의 보호 아래 있소. 그분은 폐하의 은총으로 북아메리카 신프랑스의 주권자이시지요. 믿으시오, 샤를, 이곳에서 그분을 거스르고 싶은 자는 아무도 없소.";
			link.l1 = "여기서 거의 속을 뻔했소 – 나는 이것이 단순히 욕망과 사랑에 관한 일인 줄 알았소. 이제 보니 처음부터 정치였군. 하찮지만, 예상했던 일이오. 좋소, 도와드리리다. 하룻밤이라도 젊은 시절로 돌아가는 것이 달콤하겠구려.";
			link.l1.go = "goldengirl_8";
		break;
		
		case "goldengirl_8":
			dialog.text = "선장, 그대는 분명 경험 많은 분이오. 하지만 굳이 노인인 척할 필요는 없소. 이것은 단지 정치만의 문제가 아니오. 나는 줄리아나의 존재를 소중히 여기며, 그대의 도움에 감사하고 있소. 이는 내게 개인적으로도, 진심으로 중요한 일이오. 내일 해가 진 뒤 마르키즈 보토 나리의 저택으로 오시오. 정치가 그 밤을 망치지 않으리라 약속하오.";
			link.l1 = "와인, 카드, 여자들. 예전 좋은 시절처럼 말이오. 안녕히 계십시오, 각하!";
			link.l1.go = "goldengirl_9";
		break;
		
		case "goldengirl_9":
			DialogExit();
			bDisableFastReload = true;//закрыть переход
			pchar.quest.GoldenGirl_bronca.win_condition.l1 = "location";
			pchar.quest.GoldenGirl_bronca.win_condition.l1.location = "FortFrance_town";
			pchar.quest.GoldenGirl_bronca.function = "GoldenGirl_GirlAngry";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("GoldenGirl_TimeOver", 0, 0, 2, false); // таймер до завтрашней полуночи
			SetFunctionTimerCondition("GoldenGirl_BrothelDoor", 0, 0, 1, false); // таймер на закрытие дверей борделя
			pchar.quest.GoldenGirl_eventstart.win_condition.l1 = "Timer";
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.hour  = 21.00;
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l2 = "location";
			pchar.quest.GoldenGirl_eventstart.win_condition.l2.location = "FortFrance_SecBrRoom"; // возможно закрыть бордель и вход только через боковую комнату
			pchar.quest.GoldenGirl_eventstart.function = "GoldenGirl_Party"; // таймер на начало вечеринки
			pchar.questTemp.GoldenGirl = "brothel";
			AddQuestRecord("GoldenGirl", "2");
		break;
		
		case "goldengirl_10":
			dialog.text = "찰스, 무슨 일입니까, 몰골이 말이 아니군요!";
			link.l1 = "앙제랑, 저주받을 치비우스입니다, 각하. 어젯밤 제 프리깃을 훔쳐 갔습니다. 제 포획 선원들을 처형하고 안개 속으로 떠났습니다.";
			link.l1.go = "goldengirl_11";
		break;
		
		case "goldengirl_11":
			dialog.text = "유쾌하지 않은 상황임을 이해하오. 하지만 믿으시오—이런 결과는 상당히 만족스러운 편이오. 그대는 선박과 인원이 절실히 부족한 처지도 아니고, 드 레비 반타두르는 최근 벌어진 결투의 진실을 감추기 위해 상당한 금액을 지불할 것이오. 아니면 우리가 그 일을 무상으로 덮어준 사실을 기억하게 될 터이니, 그것 또한 상당한 가치가 있지. 드 시에부스는 두 번이나 부정직한 짓을 했으나, 지금은 멀리 떨어져 있고, 우리는 여전히 그를 상대로 쓸 수 있는 괜찮은 패를 가지고 있소.";
			link.l1 = "세 번이나 그랬습니다, 각하. 앙제랑이 우리 카드 게임에서 속임수를 썼다고 자백했습니다. 하지만 그가 제게 돈으로 보상해줄 생각은 없는 듯합니다, 만약 그 뜻이라면 말이지요. 그는 도를 넘었습니다. 오늘 아침 그 배에는 어떤 분이 계셨는데... 저에게 아주 소중한 분입니다! 그 자식이 그분께 해를 끼치게 두지 않겠습니다! 들으시오, 자크, 절대 그렇게 두지 않을 겁니다!";
			link.l1.go = "goldengirl_12";
		break;
		
		case "goldengirl_12":
			dialog.text = "누구를 말하는지 알 것 같소 - 그대가 어떤... 남장하고 해적처럼 무장한 여인과 함께 있는 걸 본 기억이 있소. 찰스, 어리석게 굴지 마시오! 그대는 운이 좋아 큰 화를 피했소. 그런데 이제 또다시 스스로 문제에 휘말리려 하오? 그만두시오. 드 쉬에부는 도망 중이니, 신께 감사해야지! 그리고 그대의 '무기 든 여자 친구'에 대해서는, 친구의 충고를 따르시오 - 줄리아나를 찾아가 이 모든 일을 잊으시오.";
			link.l1 = "말도 안 됩니다, 각하. 어떤 일들은 각하께서 이해할 수 없는 영역이지요, 알겠습니까? 이제 그 자식에 대해 아는 것을 모두 말하십시오. 그가 생피에르에서 어디로 갈 수 있겠소? 그리고 다시는 내 결심을 꺾으려 하지 마시오 - 나는 네덜란드 동인도 회사와도 맞섰고, 해적 남작들과도 싸웠으며, 총독들, 심지어 성스러운 종교재판소와도 맞붙었소! 나는 쉽게 겁먹는 사람이 아니오. 어떤 대가를 치르더라도 반드시 그녀를 되찾을 것이오!";
			link.l1.go = "goldengirl_13";
		break;
		
		case "goldengirl_13":
			dialog.text = "샤를, 총독을 누가 임명하는지에 대해 한 번이라도 생각해 본 적이 있소? 여기는 완전히 다른 세계요! 자네는 아직 그 겉만 살짝 건드렸을 뿐, 자네의 이해를 넘어선 곳이오. 자네는 마치 화약고에 들어온 아이와 같소. 그런데 나에게 불붙은 촛불을 달라고 하는 것이오. 총독에 관해서 말하자면, 드 푸앵시는 결코 백작의 뜻을 거스르지 않소, 돈이든 정치든 마찬가지요. 평민들 사이에서 흔히 쓰는 '부왕'이라는 호칭이 앙리 드 레비 벙타두르에게는 딱 어울릴 것이오.";
			link.l1 = "그리고 나는 지금 그의 유일한 남자 상속자를 해치울 계획을 세우고 있소. 내가 어떤 위험을 감수하는지 잘 알고 있소. 이제, 내게 말해주시오: 나에게 도움이 될 만한 유용한 정보가 있소?";
			link.l1.go = "goldengirl_14";
		break;
		
		case "goldengirl_14":
			dialog.text = "다른 날이었다면, 네가 권총을 뽑으려는 것을 우리의 우정의 끝으로 받아들였을 것이네, Charles. 하지만 자네의 지금 심정을 이해하네. 그래서 이번만큼은 넘어가 주겠네. 자네에게 쓸모 있는 정보는 아무것도 모르네; 프리깃은 오늘 아침 일찍 서쪽으로 떠났네. Marquise를 찾아가 보게... 잠깐, 그렇게 가지는 말게! Julianna는 자네의 적에 대해 많은 것을 알고 있고, 그의 아버지와도 한동안 직접... 교분이 있었지. 그녀에게 물어보게. 나와 달리, 그녀는 자네를 막으려 하지 않을 걸세.";
			link.l1 = "그게 제 계획입니다. 뵙겠습니다, 각하. 시간 내주셔서 감사합니다.";
			link.l1.go = "goldengirl_15";
		break;
		
		case "goldengirl_15":
			DialogExit();
			LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); 
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_58";
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			pchar.questTemp.GoldenGirl = "find_girl";
		break;
		
		// В плену великого улова, andre39966
		case "VPVL_Magor_1":
			dialog.text = "밀수품이라고 하셨소? 흠... 매우 흥미롭군. 자, 그 발견의 구체적인 내용을 말씀해 주시겠소?";
			link.l1 = "사흘 전, 밀수품을 실은 선박이 르 마랭 만에 정박할 예정이었소. 그 배는 약속된 시간에 도착하지 못했으나, 조만간 반드시 입항할 것이라 믿을 만한 충분한 근거가 있소. 도적들이 도착하면 각하의 부하들이 이들에게 마땅한 환영을 준비해줄 수 있겠소?";
			link.l1.go = "VPVL_Magor_2";
			pchar.questTemp.VPVL_DontSpawnSmugglersShip = true; 
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Magor_2":
			dialog.text = "이름 없는 선박에 정체 모를 화물을 실었다고... 그리고 그대는 이런 모호한 정보만으로 폐하의 군대를 파견하라고 생각하시오?";
			link.l1 = "각하, 정보가 부족함을 인정하옵니다. 그러나 부디, 이 정보가 제게 어떻게 들어왔는지 말씀드릴 기회를 주시옵소서. (컷신)";
			link.l1.go = "VPVL_Magor_3";
		break;

		case "VPVL_Magor_3":
			dialog.text = "좋소, 그대의 지략을 시험해 보겠소. 정말로 밀수품을 실은 선박이 르 마랭 해안에 정박한다면, 국왕을 위한 그대의 공로에 걸맞은 후한 보상을 내리겠소. 사흘 뒤에 다시 나를 찾아오시오. 그때쯤이면 모든 불확실성의 안개가 걷힐 것이오.";
			link.l1 = "훌륭하군요. 그럼 사흘 뒤에 뵙겠습니다.";
			link.l1.go = "VPVL_Delete_Spawn_Ship";
			AddDialogExitQuest("VPVL_SetGovernorDialogueFlag");
			AddQuestRecord("VPVL", "6");
		break;

		case "VPVL_Magor_4":
			dialog.text = "아, 선장님! 다시 뵙게 되어 반갑습니다. 선장님의 정보가 정말로 큰 도움이 되었소. 내 부하들이 선장님이 알려준 바로 그 지점에서 배를 가로막았소. 여기, 갓 주조된 스페인 더블룬 150개요. 무겁게 주머니에 담아가시오. 내 감사의 뜻이오.";
			link.l1 = "감사드립니다, 각하. 제 작은 정보가 국왕 폐하의 이익에 보탬이 되었다니 다행입니다. 다시 기회가 온다면, 제 검과 예리한 눈은 언제든 각하를 위해 쓰일 준비가 되어 있음을 아시기 바랍니다.";
			link.l1.go = "VPVL_Delete_Flag";
			AddItems(PChar, "gold_dublon", 150);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Delete_Flag":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable");
			DeleteAttribute(pchar, "questTemp.VPVL_DontSpawnSmugglersShip");
		break;

		case "VPVL_Delete_Spawn_Ship":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
		break;
		// <=== В плену великого улова
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
