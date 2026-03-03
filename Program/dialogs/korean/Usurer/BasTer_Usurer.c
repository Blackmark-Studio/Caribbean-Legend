// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무엇을 묻고 싶으십니까?","무엇을 도와드릴까요?"),"얼마 전에 그 질문을 나에게 하려고 했었지...","그래, 맞지... 또 뱅뱅 도는 거야?","이봐, 여기서 재정은 내가 맡고 있어, 질문엔 답하지 않아...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없소."),"음, 내 기억이 다 어디로 갔지...","맞췄군요, 유감입니다...","알겠습니다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "continue")
            {
                link.l1 = "나는 선장이오 "+GetFullName(pchar)+". 당신 부하가 당신이 나를 보자고 했소. 말씀하시지요.";
                link.l1.go = "FMQG";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "sucsess")
            {
                link.l1 = "또 나요, 나리 "+GetFullName(pchar)+". 내가 베르트랑 피네트를 데려왔소. 그는 내 화물칸에 있소.";
                link.l1.go = "FMQG_14";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "letter")
            {
                link.l1 = "또 나요, 나리 "+GetFullName(pchar)+". 이야기 좀 합시다.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers")
            {
                link.l1 = "또 나요, 나리 "+GetFullName(pchar)+". 이야기를 나눕시다.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
            {
                link.l1 = "또 나요, 나리 "+GetFullName(pchar)+". 다시 나를 보게 될 줄은 몰랐겠지.";
                link.l1.go = "FMQG_23";
            }
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "아, 선장님 "+GetFullName(pchar)+"! 이렇게 다시 만나서 정말 반갑소! 오랫동안 기다렸소... 좋아. 물어볼 것이 있소. 얼마 전, 베르트랑 피네트라는 자가 항구에서 당신에게 접근해 배에 태워 달라고 했지. 호화로운 가발을 쓴 부유해 보이는 사내였소. 기억나오?";
			link.l1 = "네, 그렇습니다. 그가 정말로 바로 이 목적을 가지고 저에게 접근했지요.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			DelLandQuestMark(npchar);
			Log_Info("You have received a heavy purse");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "purse3");
			dialog.text = "그가 당신과 당신의 배를 고용하고 싶어 했습니까? 선장님, 이 사건의 모든 세부 사항을 말씀해 주신다면 저에게 큰 은혜를 베푸는 셈이오. 그에 합당한 보상을 해드리겠소. 여기, 동전으로 가득 찬 주머니요. 이제 이건 당신 것이니, 부디 베르트랑 피네트에 대해 말씀해 주시오.";
			link.l1 = "알겠습니다. 피네트 나리가 내 배를 빌려 자신과 친구 두 명을 과들루프에서 스페인 본토로 데려다 달라고 했습니다.\n좀 더 구체적으로는 포르토벨로 근처의 모스키토 만이었지요. 나는 일을 마쳤고, 그들은 내 배에서 내려 바로 정글로 들어갔습니다.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "알겠습니다. 피네트 나리가 최종 목적지를 언급했습니까? 그리고 그의 동행들에 대해서는요?";
			link.l1 = "그 사람 말로는 파나마로 향하고 있었다 하더군. 친구들도 꽤 흥미로웠지. 한 명은 스페인 장교, 또 한 명은 프랑스 장교였어. 도대체 무슨 인연으로 뭉친 건지 아직도 모르겠지만, 나는 질문하라고 돈 받은 게 아니었으니까.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "스페인 장교? 그리고 프랑스 장교까지? 오! 이거 정말 대단하군! 잘했어, 피네트 나리! 정말 교활한 사람이야! 여기서도 돈 벌 궁리를 하다니! 파나마라고 했지?";
			link.l1 = "그래, 내가 아는 건 다 말했어. 이제 가도 되겠나?";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			dialog.text = "잠깐만요, 선장님. 당신께 제안할 사업이 있습니다. 돈 좀 벌어보는 거, 어떻습니까? 하지만 먼저, 당신의 승객들에 대해 말씀드릴 게 있습니다.";
			link.l1 = "좋아, 말해 보게.";
			link.l1.go = "FMQG_5";
		break;
		
		case "FMQG_5":
			dialog.text = "베르트랑 피네트 나리는 2년 전에 우리 식민지에 도착하자마자 곧장 선장들과 거래를 시작했소. 그 사업이란 것도... 음, 꽤 수상쩍은 일이었지. 그는 이곳에서 매우 부족한 물품들—귀중품, 밀수품, 때로는 노예까지—을 받아내곤 했소... 내 사무실에서 불법 사업을 위해 체계적으로 대출을 받았지만, 항상 이자까지 모두 갚았었지.\n당신의 후한 도움을 받고 섬을 떠나기 전에, 그는 평소보다 훨씬 큰 금액의 대출을 받았소. 그는... 아니, 그는 신뢰받는 고객이었고 신용 기록도 완벽했기에 내가 대출을 내주었지. 큰 실수였소. 피네트 나리는 도망쳤고, 내 돈을 갚을 생각이 전혀 없어 보이오.";
			link.l1 = "금액이 얼마나 되는지 여쭈어도 되겠습니까?";
			link.l1.go = "FMQG_6";
		break;
		
		case "FMQG_6":
			dialog.text = "엄청나지. 도블룬으로 약 십오만 페소야. 상자 열 개에, 각 상자마다 도블룬 백오십 개씩 들어 있지. 그리고 그건 이자까지 합친 것도 아니야.";
			link.l1 = "흠... 그가 2년 동안 너에게 돈을 주면서 익숙하게 만들고, 큰돈을 빌린 뒤에 배신했군. 영악하네.";
			link.l1.go = "FMQG_7";
		break;
		
		case "FMQG_7":
			dialog.text = "정확합니다, 선장님. 그래서 당신에게 일을 맡기고 싶소. 그 악당을 찾아 이리로 데려오시오. 총독과 사령관, 그리고 내가 그의 빚을 반드시 갚게 만들 방법을 찾아내겠소. 그 남자를 이미 봤으니, 당신이 그의 승객이었고, 그 말은 곧 누구보다도 피네트 나리를 찾을 가능성이 높다는 뜻이오. 물론 그의 신세를 위해 현상금 사냥꾼들도 고용하겠지만, 당신의 도움이 더 효과적일 것 같은 예감이 드는군.";
			link.l1 = "보상은 어떻게 됩니까?";
			link.l1.go = "FMQG_8";
		break;
		
		case "FMQG_8":
			dialog.text = "일을 해주면 두블룬이 가득 든 상자를 주겠네, 모두 백오십 닢이네.";
			link.l1 = "스페인 마을에서 살아 있는 사람을 추적해 납치한 대가치고는 이건 참 한심한 보상이라 말할 수 있겠군.";
			link.l1.go = "FMQG_9";
		break;
		
		case "FMQG_9":
			dialog.text = "선장님, 제 제안을 이렇게 헐값으로 여기시는 걸 보니 피네트 나리가 제 돈으로 충분히 보수를 치른 모양이군요. 하지만 제안의 가치는 그 이상임을 장담합니다. 물론 거절하실 권리는 충분히 있으시지요... 하지만 드릴 말씀이 하나 있는데, 분명 마음을 바꾸게 될 겁니다.";
			link.l1 = "그게 무엇입니까?";
			link.l1.go = "FMQG_10";
		break;
		
		case "FMQG_10":
			dialog.text = "피네트가 과들루프에서 탈출하기 며칠 전, 바스테르 감옥에서 죄수 한 명이 탈옥했소. 그의 이름은 돈 카를로스 데 밀리아르, 스페인 귀족이자 장교요. 그는 프랑스 해병대 중위의 배신 덕분에 탈출에 성공했지... 내 말이 무슨 뜻인지 아시겠소?";
			link.l1 = "흠... 그게 나와 무슨 상관이지? 나는 그저 승객만 운송했을 뿐이야.";
			link.l1.go = "FMQG_11";
		break;
		
		case "FMQG_11":
			dialog.text = "그래, 분명 그랬겠지! 나는 개인적으로 자네가 돈 데 밀리아르의 탈출을 조직하는 데 아무런 관련이 없었다고 의심하지 않네. 하지만 우리 총독과 사령관은 그렇게 생각하지 않을 수도 있지. 운이 좋으면 공범 혐의, 운이 나쁘면... 더 말하고 싶지 않군. 자네 스스로 생각해 보게, 도망친 스페인 장교를 배에 태웠잖나, 아마도 어딘가 숨겨진 만에서 말이야... 맞지, 선장?";
			link.l1 = "알겠어. 날 협박하는 거군. 여기 온 게 실수였어...";
			link.l1.go = "FMQG_12";
		break;
		
		case "FMQG_12":
			dialog.text = "뭐라 하십니까, 선장?! 협박하는 게 아닙니다! 저는 그저 좋은 보상을 드릴 테니 저를 도와달라는 것뿐입니다. 나리 피네트를 찾아 바스테르로 데려다주실 수 있겠습니까? 귀하의 귀환을 기다리겠습니다. 파나마까지 갔다 오는 데 두 달이면 충분하다고 생각합니다.";
			link.l1 = "나에게 선택의 여지가 없군. 하지만 그런 사업 방식으로 우리가 친구가 될 수 있을 거라곤 생각하지 않소. 안녕히 가시오, 나리.";
			link.l1.go = "FMQG_13";
		break;
		
		case "FMQG_13":
			DialogExit();
			LocatorReloadEnterDisable("Baster_town", "reload1_back", false);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", false);
			LocatorReloadEnterDisable("Baster_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.FMQG = "headhunter_panama";
			ReOpenQuestHeader("FMQ_Guadeloupe");
			AddQuestRecord("FMQ_Guadeloupe", "7");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 122, false);
			}
			else SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 61, false);
			AddMapQuestMarkCity("panama", false);
			AddLandQuestMark(characterFromId("Panama_tavernkeeper"), "questmarkmain");
			
			// Sinistra - Старт квеста "Мерзкий Божок"
			PChar.quest.ChickenGod_StartLoc.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_StartLoc.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_StartLoc.function = "ChickenGod_BrothelCheck";
		break;
		
		case "FMQG_14":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "훌륭한 소식이오, 선장! 곧바로 내 부하들을 보내 당신 배에서 이 자식을 데려가게 하겠소. 이번엔 이 놈이 내 손아귀에서 절대 못 빠져나갈 거요... 당신은 보상을 받을 자격이 있소, 이 상자를 가져가시오. 부디 노여워하지 마시오, 여기 당신을 위한 부적이 있소. 선물이오.";
			link.l1 = "감사합니다. 당신의 침묵도 내 보상의 일부라고 생각해도 되겠소?";
			link.l1.go = "FMQG_15";
		break;
		
		case "FMQG_15":
			Log_Info("You have received a chest full of doubloons");
			Log_Info("You have received a 'Fisherman' amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "obereg_7");
			dialog.text = "침묵? 무슨 일로? 내 고객들 중에 당신이 있다면 기쁘겠소. 침묵과 금에 대해 사람들이 뭐라고 하는지 아시오?";
			link.l1 = "가끔은 금보다 더 값질 때도 있지요, 나리. 교훈을 얻었습니다. 안녕히 가십시오!";
			link.l1.go = "FMQG_16";
		break;
		
		case "FMQG_16":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			ref sld = characterFromId("FMQG_pass_1");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "23");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		case "FMQG_17":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("baster");
			dialog.text = "듣고 있소. 베르트랑 피네트가 당신 배에 있겠지?";
			link.l1 = "아니. 하지만 당신에게 훨씬 더 좋은 것이 있소. 이것을 읽으시오.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_18":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "이게 뭐지?";
			link.l1 = "계속 읽으십시오, 나리. 나중에 다시 이어가겠습니다.";
			link.l1.go = "FMQG_19";
		break;
		
		case "FMQG_19":
			LAi_Fade("", "");
			dialog.text = "(읽으며) 음 ... 열병 환자에 대한 이 말도 안 되는 소리는 뭐지?";
			link.l1 = "정말이오? 좋아, 이 '헛소리'를 총독에게 가져가겠소. '커리지'호와 그 다이아몬드 화물의 실종에 대해 진실을 알게 된다면 총독께서 크게 흥미를 보이실 거라 믿소... 왜 그렇게 창백해졌소?";
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter")) link.l1.go = "FMQG_24";
			else link.l1.go = "FMQG_20";
		break;
		
		case "FMQG_20":
			dialog.text = "그래서 결국 피네트를 찾았군...";
			link.l1 = "예. 그래서 제안을 하나 드리지요. Carlos de Milyar, Jean Deno 그리고 그 밖의 훌륭한 신사분들은 잊으십시오. 그렇게 하신다면 저도 이 편지는 잊겠습니다.";
			link.l1.go = "FMQG_21";
		break;
		
		case "FMQG_21":
			dialog.text = "좋습니다, 선장님... 당신의 조건에 동의하겠습니다.";
			link.l1 = "좋군요. 저에게 화내지 않으셨으면 합니다, 이제 우리는 끝난 것 같군요. 안녕히 가십시오.";
			link.l1.go = "FMQG_22";
		break;
		
		case "FMQG_22":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			pchar.questTemp.FMQG = "cave";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.quest.FMQG_cave.win_condition.l1 = "location";
			pchar.quest.FMQG_cave.win_condition.l1.location = "Guadeloupe_Cave";
			pchar.quest.FMQG_cave.function = "FMQG_InCave";
			// заполним сундук
			pchar.GenQuestBox.Guadeloupe_Cave = true;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse1 = 5;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse2 = 2;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse3 = 1;
			SetFunctionTimerCondition("FMQG_ClearBox", 0, 0, 3, false);
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
			{
				SetFunctionTimerCondition("FMQG_RemoveHunterScore", 0, 0, 1, false);
				AddQuestRecord("FMQ_Guadeloupe", "29");
				DeleteAttribute(pchar, "questTemp.FMQG.Letter");
			}
			else AddQuestRecord("FMQ_Guadeloupe", "25");
		break;
		
		case "FMQG_23":
			dialog.text = "하... 맞습니다, 선장님.";
			link.l1 = "당신에게 줄 것이 있소. 이것을 받아 읽으시오.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_24":
			dialog.text = "그래서 결국 피네트를 찾았군...";
			link.l1 = "예. 그래서 제안을 하나 드리겠소. 프랑스 식민지들에서 내 명예를 회복시켜 준다면 이 편지는 잊도록 하겠소.";
			link.l1.go = "FMQG_25";
		break;
		
		case "FMQG_25":
			dialog.text = "하지만...";
			link.l1 = "나는 네가 어떻게 하든 신경 안 쓴다. 내일 내 목에 걸린 현상금 사냥이 끝나지 않으면, 총독이 전부 알게 될 거다.";
			link.l1.go = "FMQG_21";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
