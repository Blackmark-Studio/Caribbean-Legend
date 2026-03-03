// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("어서 말해라, 무엇을 원하는가?","우리가 방금 그 얘기를 하고 있었소. 당신이 잊은 게 틀림없군...","오늘만 벌써 세 번째로 그 질문을 꺼내는군...","이봐, 여긴 상점이야. 사람들은 여기서 물건을 사 간다네. 나를 방해하지 마시오!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 아마 다음번에.","맞아요, 무슨 이유에선지 잊고 있었네요...","그래, 정말 이번이 세 번째야...","흠, 나는 안 하겠어...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			//Jason --> ----------------------------------мини-квест Бесчестный конкурент------------------------------------
			if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
			{
				if(pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "제 부탁을 들어주셔서 감사합니다, 선장님. 이제, 언제\n "+pchar.questTemp.Shadowtrader.Guardername+" 여기 있으니, 적어도 조금은 안심할 수 있겠군.";
					link.l1 = "흠... 참견하는 것처럼 보이고 싶진 않지만, 뭔가 곤란한 일이 있는 것 같군요. 무슨 일인지 말씀해 주시겠습니까 – 어쩌면 제가 도와드릴 수 있을지도 모르겠군요?"; 
					link.l1.go = "Shadowtrader_fort";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "그래서? 내 편지 전달했나?";
					link.l1 = "있소. 사령관이 구두로 답하길, 당신의 편지에 담긴 증거만으로는 시 경비대가 아무런 조치도 취할 수 없다고 하였소."; 
					link.l1.go = "Shadowtrader_trouble";
					pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && CheckAttribute(pchar, "questTemp.Shadowtrader.EndFort"))
				{
					dialog.text = "이미 소식을 들었습니다 - 오늘 밤 경비병들이 밀수업자들이 운영하던 불법 거래소를 발견하고 모두 체포했지요. 아주 드문 악당이 지휘하고 있었지만, 이제 괜찮습니다; 당분간은 더 이상 누구에게도 해를 끼치지 못할 겁니다.\n사령관이 당신이 이 일에서 한 역할에 대해 말해주었습니다, 정말 감사드립니다! 약속을 지키셨군요! 자, 여기 돈입니다 - 15,000페소. 당신 덕분에 살았습니다. 이제 내 사업에는 아무 위협도 없습니다!";
					link.l1 = "천만에요. 쉬운 일이었소."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "그래서, 좋은 소식이라도 있소, "+pchar.name+"?";
					link.l1 = "당신의 경쟁자를 찾았습니다. 이제 더 이상 당신을 괴롭히지 않을 겁니다 – 내가 그를 설득해서... 이 섬을 떠나게 했거든요. 그의 '가게'는 도시 성문 근처의 한 집에 있었습니다.\n버려진 화물은 이제 당신이 어떻게 할지 결정해야 합니다. 당국에 넘길 수도 있고, 직접 챙길 수도 있습니다."; 
					link.l1.go = "Shadowtrader_Escape_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "나는 이미 소식을 들었소 - 오늘 밤 경비병들이 어느 집 아래에서 밀수꾼들의 은신처를 발견했소. 두 악당이 죽은 채로 발견됐지. 훌륭한 일이오, "+pchar.name+", 존경스럽군요! 자, 보상으로 15,000페소를 받으시오. 당신 덕분에 살았소! 이제 진짜로 장사를 할 수 있겠군!\n궁금한 것이 있는데, 그들의 두목도... 죽은 두 사람 중에 있었소?";
					link.l1 = "아니오. 하지만 그는 다시는 당신네 마을에 얼굴을 비추지 않을 겁니다. 지금쯤 이 섬에서 수십 마일은 떨어져 있을 거라 생각합니다."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "나는 이미 소식을 들었소 - 어젯밤 경비병들이 어느 집에서 밀수업자의 비밀 상점을 발견했다 하오. 악당 셋이 죽은 채로 발견되었지. 훌륭한 일이오,\n "+pchar.name+", 존경스럽소! 자, 보상으로 15,000페소를 받으시오. 당신 덕분에 내가 살았소! 이제야 제대로 장사를 할 수 있겠군!\n궁금한 것이 있소 - 그들의 두 시체 중에... 두목도 있었소?";
					link.l1 = "예. 당신은 영원히 경쟁자를 제거했소. 이제 다시는 당신을 괴롭히지 않을 것이오."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
			}
			//<-- мини-квест Бесчестный конкурент
		break;
		
		// --> мини-квест Бесчестный конкурент
		case "Shadowtrader_begin":
			pchar.questTemp.Shadowtrader = "true";
			pchar.questTemp.Shadowtrader_Block = true;
			pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "술집에 가서 이름이 이런 사람을 찾아 주시겠습니까 "+pchar.questTemp.Shadowtrader.Guardername+" 그리고 그에게 가능한 한 빨리 여기로 오라고 전해 주시겠습니까? 나는 가게를 비울 수 없고, 저 멍청이는 선술집에 앉아 럼주만 들이키고 있으니, 당번임에도 불구하고 여기 올 생각조차 안 할 겁니다.";
			link.l1 = "언제든 도와줄 수 있어 기쁘지, 친구야 – 어차피 선술집에 가려고 했으니까.";
			link.l1.go = "Shadowtrader_begin_1";
			link.l2 = "나를 놀리는 건가? 내가 네 심부름꾼으로 보여? 선술집은 바로 코앞이니 직접 가라.";
			link.l2.go = "exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		
		case "Shadowtrader_begin_1":
			dialog.text = "감사합니다! 그에게 지금 당장 여기로 오라고 전해 주십시오. 아이고, 왜 그렇게 성가시게 구는지...";
			link.l1 = "걱정하지 마시오. 그를 당신에게 보내겠소.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.City = npchar.City;
			pchar.questTemp.Shadowtrader.nation = sti(npchar.nation);
			//создаем охранника
			sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder" , "officer_7", "man", "man", 10, sti(npchar.nation), 5, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
			sld.name = pchar.questTemp.Shadowtrader.Guardername;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowGuarder";
			sld.greeting = "pirat_common";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
			SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Shadowtrader_fort":
			dialog.text = "아, 선장님, 정말로 도와주신다면 감사하겠습니다. 이 편지를 가능한 한 빨리 사령관에게 전달해 주실 수 있겠습니까? 이 사소한 일에 대해 300코인을 드리겠습니다 – 이미 말씀드렸듯이, 저는 가게를 비울 수가 없습니다.";
			link.l1 = "문제없소. 그 편지를 주시오.";
			link.l1.go = "Shadowtrader_fort_1";
			link.l2 = "아니, 좋은 양반, 그 헛소리에 더 이상 시간을 낼 수 없소.";
			link.l2.go = "Shadowtrader_fort_end";
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fort_1":
			dialog.text = "여기 있습니다. 오늘 꼭 그에게 전해 주시고, 그의 답장을 가져다주십시오.";
			link.l1 = "걱정 마시오, 내가 하겠소.";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
			pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
			SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
			pchar.questTemp.Shadowtrader = "current"
			pchar.questTemp.Shadowtrader.Fort = "true";
			AddQuestRecord("Shadowtrader", "1");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
		break;
		
		case "Shadowtrader_fort_end":
			dialog.text = "음, 아무래도 다른 사람에게 물어봐야겠군. 귀찮게 해서 미안하오, 선장.";
			link.l1 = "문제없소. 안녕히 가시오!";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_trouble":
			dialog.text = "그 자가 그렇게 말했다고? 그럼 내게서 무슨 증거를 더 원한다는 거지?! 내 시체라도 필요하단 말인가? 이런 식으로 계속 가면 곧 시체 하나 생기겠군!..";
			link.l1 = "이봐, 이봐, "+npchar.name+", 진정하시오, 그러다 쓰러지겠소. 자, 물이나 좀 마시시오... 이제 말씀해 보시오, 무슨 일입니까 - 어쩌면 내가 도와줄 수 있을지도 모르오?";
			link.l1.go = "Shadowtrader_trouble_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_trouble_1":
			dialog.text = "아이고, 선장님! 제발, 여기 300페소 가져가십시오 - 거의 잊을 뻔했네요... 물론 말씀드리겠지만, 선장님이 어떻게 도와주실 수 있을지는 잘 모르겠습니다. 제 사업은 거의 망하기 직전입니다 - 다 저주받은 밀수꾼들과 그들을 이끄는 정체불명의 악당 때문이지요.";
			link.l1 = "밀수업자들인가?";
			link.l1.go = "Shadowtrader_trouble_2";
			AddMoneyToCharacter(pchar, 300);
		break;
		
		case "Shadowtrader_trouble_2":
			dialog.text = "바로 그거요! 저 악당들이 분명히 나를 이 마을에서 쫓아내려는 게 틀림없소! 그전까지만 해도 모든 게 평소와 같았지요. 금지된 물건을 되팔고, 순찰대에게 잡히면 숨거나 뇌물을 주곤 했소. 그런데 요즘엔 어디 뒷골목에 가게를 차려서는, 가장 인기 있는 물건들을 터무니없이 싼값에 팔기 시작했소!\n나는 그런 사치를 누릴 수 없소. 오히려 세금까지 내야 하니 점점 가난해지고 있지요. 선원들도 이제 내 물건엔 거의 관심이 없고, 저 불한당들에게서 다 사가버린다오.";
			link.l1 = "하지만 관청에 호소했어야지! 결국 그런 무법 행위를 막는 게 그들의 일이잖소.";
			link.l1.go = "Shadowtrader_trouble_3";
		break;
		
		case "Shadowtrader_trouble_3":
			dialog.text = "지난 탄원 결과는 당신도 직접 봤을 것이오. 총독은 너무 바쁘고, 사령관은 밀수업자들이 뒷골목 가게를 조직했다는 걸 믿지 않거나, 믿는 척을 안 하오. 내 생각엔 그게 사실이겠지\n물론, 왜 그들이 그런 일을 하겠소? 내 말은 이렇소. 분명 나를 망하게 하고 이 마을에서 쫓아내려는 어떤 악당이 이 모든 걸 꾸며냈고, 그 다음엔 조용히 내 사업을 차지해서 자기 더러운 손을 깨끗하게 하려는 거요.";
			link.l1 = "흠... 그 의견이 전혀 근거 없는 건 아니지. 상인들이란 본래 남을 이용해 먹는 법이니까... 아, 미안하오, 물론 그대는 아니었소. ";
			link.l1.go = "Shadowtrader_trouble_4";
		break;
		
		case "Shadowtrader_trouble_4":
			dialog.text = "아, 아무것도 아니오... 그런데 최근에 어떤 불량배가 내게 와서 뻔뻔하게 계속 소란을 피우면 내 가게를 불태우겠다고 하더군.\n그래서 경호원을 고용했소. "+pchar.questTemp.Shadowtrader.Guardername+" 값이 싸지는 않지만, 그는 전문가라서 그의 보호 아래 있으면 조금은 안심이 되지.";
			link.l1 = "그렇군요... 정말 불쾌한 이야기입니다. 분명 당신 말이 맞았소 - 내가 도와드릴 수 있는 일이 없군요. 하지만 그래도, 모든 일은 결국 제자리를 찾게 마련이오 - 그런 수상한 업소들은 오래가지 못하니까요. 자, 행운을 빕니다!";
			link.l1.go = "Shadowtrader_end";
			link.l2 = "알겠소. 음, 그래도 내가 도와줄 수 있을지도 모르겠군...";
			link.l2.go = "Shadowtrader_trouble_5";
		break;
		
		case "Shadowtrader_trouble_5":
			dialog.text = "어쨌든 내게 도움을 주겠다는 거요? 그런데 어떻게 하실 생각이오?";
			link.l1 = "그 '동료'라는 자를 찾아서... 당신을 더 이상 괴롭히지 않도록 설득해 보겠소. 사람을 설득하는 데는 내가 나름의 수완이 있거든.";
			link.l1.go = "Shadowtrader_trouble_6";
		break;
		
		case "Shadowtrader_trouble_6":
			dialog.text = "진심이오? 주께서 그 정의로운 뜻에 축복을 내리시길! 그 오물을 없애 주신다면, 내가 당신에게 큰 빚을 지겠소.";
			link.l1 = "좋소, 거래가 성사된 걸로 하겠소. 그럼 바로 수색을 시작하겠소.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.seeksmugglers = "true";
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
			AddQuestRecord("Shadowtrader", "2");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddQuestUserData("Shadowtrader", "sSex1", GetSexPhrase("ся","ась"));
		break;
		
		case "Shadowtrader_end":
			pchar.questTemp.Shadowtrader = "true";
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DialogExit();
		break;
		
		case "Shadowtrader_Escape_complete":
			dialog.text = "정말입니까? 이제 아무 두려움 없이 장사를 할 수 있겠군요? 아, 정말 감사합니다! 여기 보상금 15,000페소를 드리겠습니다. 그 집에 있던 물건들은 사령관에게 넘기는 것이 좋겠지요. 다시 한 번 감사드립니다!";
			link.l1 = "천만에요. 그렇게 어렵지 않았어요. 제가 설득에 능하다고 말했잖아요.";
			link.l1.go = "Shadowtrader_complete";
		break;
		
		case "Shadowtrader_complete":
			dialog.text = "다시 찾아오십시오, 선장님 - 언제든 당신을 뵙게 되어 기쁠 것입니다.";
			link.l1 = "물론이지! 이제 실례하겠소 – 할 일이 있어서 말이오! 안녕히 계시오, 장사에 행운이 있기를 바라오,\n "+npchar.name+"!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Shadowtrader = "complete";
			AddQuestRecord("Shadowtrader", "11");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DeleteAttribute(pchar, "questTemp.Shadowtrader.EndFort");
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		//<-- мини-квест Бесчестный конкурент
	}
	UnloadSegment(NPChar.FileDialog2);
}
