// НПС офиса ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "뭐 필요해?";
			link.l1 = "아니.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// офицер
		case "HWIC_officer":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "경보다! 적이 나타났다! 무기를 들어라!\n";
				link.l1 = "젠장!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "이봐, 거기 멈춰! 네 얼굴 어디서 본 것 같은데... 그렇지! 네 죄로 수배 중이잖아! 얘들아, 저놈 잡아라!";
				link.l1 = "젠장!";
				link.l1.go = "fight";
				break;
			}
			chrDisableReloadToLocation = true;
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				dialog.text = "네덜란드 서인도 회사에 온 것을 환영하오. 할 말이 있으면 빨리 하시오, 시간은 돈이니까.";
				link.l1 = "나는 무역 업무로 왔소. 면허증, 항해 도구 등등...";
				link.l1.go = "HWIC_officer_3";
				link.l2 = "회사에 내 힘을 보태고 싶소. 물론 금을 받는 대가로 말이오. 사람을 뽑고 있소?";
				link.l2.go = "HWIC_officer_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "네덜란드 서인도 회사에 온 것을 환영하오. 할 말이 있으면 빨리 하시오, 시간은 곧 돈이니.";
				link.l1 = "미안하오, 내가 착각했던 것 같소. 이만 떠나겠소.";
				link.l1.go = "HWIC_officer_exit";
				link.l2 = "나는 무역 업무로 왔소. 면허증, 항해 도구 등등...";
				link.l2.go = "HWIC_officer_3";
				break;
			}
			dialog.text = "빨리 말해라, 시간은 돈이다.";
			link.l1 = "나는 무역 업무 때문에 여기 왔소. 면허증, 항해 도구 등등...";
			link.l1.go = "HWIC_officer_3";
			link.l2 = "회사에 내 힘을 보태고 싶소. 물론 금을 받는 대가로 말이오. 사람을 뽑고 있소?";
			link.l2.go = "HWIC_officer_2";
		break;
		
		case "HWIC_officer_1":
			dialog.text = "그럼 위층에 있는 로덴부르흐 나리의 집무실로 올라가시오.";
			link.l1 = "감사합니다, 이제 가보겠습니다.";
			link.l1.go = "HWIC_officer_exit";
			// belamour legendary edition переехали по другому адресу
			LocatorReloadEnterDisable("GVIK", "reload2", false);//кабинет откроем
		break;
		
		case "HWIC_officer_2":
			dialog.text = "지금은 회사에서 사람을 뽑지 않는다.";
			link.l1 = "안타깝군. 폐를 끼쳐 미안하오.";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_3":
			dialog.text = "미네르 헤리츠와 이야기해 보시오. 안으로 들어가면 왼쪽에 그의 자리가 있소. 그는 계약된 선장들과 거래를 하오.";
			link.l1 = "고맙소, 장교 나리...";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_exit":
			DialogExit();
			// belamour legendary edition переехали
			LAi_ActorGoToLocation(npchar, "soldiers", "soldier3", "GVIK", "soldiers", "soldier3", "", 5);
			DoQuestCheckDelay("ReturnTalkerToOfficer", 5.0); // 140313
			NextDiag.TempNode = "HWIC_officer";
		break;
		
		// солдаты
		case "HWIC_soldier":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "경보! 적이 왔다! 무기를 들어라!";
				link.l1 = "젠장!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "아하! 네가 누군지 알 것 같군... 그래, 분명하지! 네 죄로 수배 중이잖아! 이 녀석 잡아라, 얘들아!";
				link.l1 = "젠장!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "우리 장교들이나 헤릿츠 나리에게 말해라. 나는 너에게 할 말이 없다. 나는 근무 중이다.";
			link.l1 = "그대의 규율은 감탄할 만하오.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_soldier";
		break;
		
		// клерки
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "경보! 적이 왔다! 군인들!";
				link.l1 = "젠장!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "헤리츠 나리에게 가서 이야기하시오.";
			link.l1 = "좋아, 알겠어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_clerk";
		break;
		
		// главный клерк - минхер Герритц
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "경보! 적이 나타났다! 병사들, 저 자를 잡아라!";
				link.l1 = "젠장!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "흠. 뭔가 수상한 구석이 있군... 아, 그렇지! 네놈은 네덜란드에 대한 수많은 범죄로 수배 중이었지! 병사들, 저 자를 잡아라!";
				link.l1 = "젠장!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "뭐 필요한가, 나리?";
			if (!CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				link.l1 = "네덜란드 서인도 회사의 무역 허가증을 사고 싶소.";
				link.l1.go = "licence";	
			}
			if (!CheckAttribute(npchar, "quest.trade"))
			{
				link.l2 = "여기서 항해 도구나 다른 유용한 물건들을 살 수 있다고 들었소. 정말이오?";
				link.l2.go = "trade";	
			}
			else
			{
				link.l2 = "오늘은 무엇을 팔고 있소?";
				link.l2.go = "trade_1";	
			}
			if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
			{
				link.l3 = "흥미로운 문서를 하나 가져왔소, 나리. 처음 몇 줄을 한번 보시오. 공화국의 존속과 회사의 이익에 관한 내용이오. 어떤 회합의 좌표도 들어 있지. 관심 있다면 이 정보를 팔겠소. 물론 후한 값을 쳐 주면 말이오.";
				link.l3.go = "depeshe";	
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
			{
				link.l4 = "레지널드 잭슨이라는 이름의 선장이 당신 밑에서 일하고 있을 텐데요. '하피'라는 제벡을 타고 다닌다고 들었습니다. 그를 어떻게 찾을 수 있는지 알려주실 수 있겠습니까? 그와 중요한 일이 있습니다.";
				link.l4.go = "caleuche";	
			}
			// Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_RazgovorGerrits"))
			{
				link.l4 = "저는 로덴부르흐 나리를 급히 만나야 합니다. 매우 중요한 일입니다. 그분이 어디 계십니까?";
				link.l4.go = "PZ_RazgovorGerrits_1";
			}
			link.l9 = "아니, 아무것도 아니야.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "HWIC_headclerk";
		break;
		
		// торговые лицензии
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = "좋소, 원한다면 구매해도 되오. 하지만 경고하겠소. 회사는 엄격한 중립성을 중시하므로, 이 면허를 소지한 동안에는 어느 나라의 무역선도 공격하는 것이 금지되어 있소\n만약 그런 행위가 적발된다면, 즉시 면허를 취소할 것이오. 또한 네가 네덜란드나 회사와 어떤 이유로든 충돌하게 된다면, 면허 역시 취소될 것이오. 이해했소?";
				link.l1 = "수정처럼 분명하군. 명심하겠소.";
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = "면허를 구매하셔도 됩니다. 자, 며칠로 하시겠습니까?";
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = "이 면허증은 어떤 나라의 항구든 자유롭게 드나들 수 있는 권한을 주며, 당신의 평화로운 의도와 목적이 교역임을 보여줍니다. 하지만 법적인 문제가 생기면 아무 소용이 없소. 그런 경우엔 그저 면허증을 빼앗아 갈 뿐이오. 명심하시오, \n어느 항구로 들어가기 전에 반드시 우호적인 깃발을 올리는 걸 잊지 마시오. 순찰대와 요새 포수들은 일단 쏘고 나서 질문하는 걸 더 좋아하오\n면허증의 최소 기간은 20일, 최대 기간은 6개월 또는 180일이오\n아, 맞다, 거의 잊을 뻔했군... 우리 고귀한 전통에 따르면, 면허와 관련된 모든 거래는 두블룬으로 결제해야 하오. 이제 조건을 논의해 봅시다. 면허를 얼마나 오래 원하시오?";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "미안하지만, 좀 더 생각해봐야겠어. 나중에 보자.";	
			link.l2.go = "exit";
		break;
		
		case "licence_1":
			float fQty = stf(dialogEditStrings[6]);
			npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*7;
			if (fQty < 1)
			{
				dialog.text = "마인헤르, 좀 더 크게 말씀해 주십시오. 제대로 듣지 못했습니다. 그래서, 얼마나 오래입니까?";
				link.l1 = "잠깐 생각 좀 해보자...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 0 && fQty < 20)
			{
				dialog.text = "면허의 최소 기간은 20일이오. \n그래서? 20일 이상으로 하겠소?";
				link.l1 = "잠깐 생각 좀 해보자...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = "면허의 최대 기간은 반년이오. 180일 이하라는 말이오?";
				link.l1 = "잠깐 생각 좀 해보자...";
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = "For "+FindRussianDaysString(sti(fQty))+"? 아주 좋소. 비용은 "+FindRussianDublonString(sti(npchar.quest.lcc_summ))+". 그 조건이 받아들일 만하오?";
			if (PCharDublonsTotal() >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = "그래, 나다.";
				link.l1.go = "licence_2";
			}
			link.l2 = "안타깝게도 지금은 그만한 돈이 없어. 면허는 나중에 다시 오겠어.";
			link.l2.go = "exit";
		break;
		
		case "licence_r":
			dialog.text = "";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "미안하지만, 아직 더 생각해봐야겠어. 나중에 보자.";	
			link.l2.go = "exit";
		break;
		
		case "licence_2":
			int iQty = sti(dialogEditStrings[6]);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.lcc_summ));
			GiveNationLicence(HOLLAND, iQty);
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "start")
			{
				if(iQty < 180) 
				{
					Log_info("Quest: 'Together with the Shark' - your license is less than 180 days");
				}
				else 
				{
					pchar.questTemp.SharkGoldFleet.LicenceOk = true;
					AddQuestRecord("SharkGoldFleet", "2");
				}
				pchar.questTemp.SharkGoldFleet = "afterGvik";
			}
			dialog.text = "잠깐만... 여기 표지와 도장을 찍어야지... 봉인 완료. 서류 가져가시오.";
			link.l1 = "고맙소! 안녕히 가시오, 나리.";
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = "그렇소, 여기서는 나침반, 아스트롤라베, 크로노미터, 모래시계 같은 항해 도구를 살 수 있소. 하지만 항상 모든 물품이 준비되어 있는 건 아니오. 모래시계 정도만 예외일 뿐, 나머지 도구들은 우리 계약자들이나 선장들이 금방 사가 버리거든. 그러니 원하는 물건이 없다면, 일주일 뒤에 재입고될 때 다시 찾아오시오.\n지도와 망원경도 판매하오. 구경해 보시겠소?";
			link.l1 = "네, 부탁합니다.";
			link.l1.go = "trade_1";
			npchar.quest.trade = "true";
		break;
		
		case "trade_1":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 7)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// депеша Кромвеля
		case "depeshe":
			dialog.text = "흠, 보여 줘...(읽으며) 오, 이런... 크롬웰의 욕심이 점점 커지는군. 캉커! 저 청교도 개새끼들이 자기 섬에서 흘린 피도 모자라 이곳까지 더럽히려는 거냐!? 이 전갈은 어디서 구했지?";
			link.l1 = "영국 사신에게서 빼앗았지. 자, 이걸 살 생각 있나?";
			link.l1.go = "depeshe_1";
		break;
		
		case "depeshe_1":
			dialog.text = "예. 피터 스튜이베산트가 이걸 읽으면 정말 기뻐할 것이오, 틀림없소. 그리고 반드시 이걸 막기 위한 실질적인 조치를 취할 거요... 금화 두블룬으로 지불할 수도 있고, 아니면 반년짜리 면허증을 써줄 수도 있소. 어느 쪽이 좋소?";
			link.l1 = "나는 금을 선택하겠소.";
			link.l1.go = "depeshe_dublon";
			link.l2 = "면허증을 원해.";
			link.l2.go = "depeshe_licence";
		break;
		
		case "depeshe_dublon":
			TakeNItems(pchar, "gold_dublon", 700);
			Log_Info("You have received 700 doubloons");
			dialog.text = "아주 좋소. 여기 칠백 두블론이 있소. 훌륭히 임무를 완수한 대가로서 멋진 보상이오.";
			link.l1 = "여기 당신의 공문이오.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			GiveNationLicence(HOLLAND, 180);
			dialog.text = "좋소. 여기 반년짜리 면허증이오.";
			link.l1 = "감사합니다! 그리고 여기 당신의 전달문이오.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //снять прерывание
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = "감사하오. 그대가 양심과 공화국에 대한 충성을 보여주어 다행이오. 그대의 선행을 마티아스 벡과 피터 스타이베산트에게 전하겠소.";
			link.l1 = "알아두면 좋겠군. 안녕!";
			link.l1.go = "exit";
		break;
		
		// Sinistra Путеводная звезда
		case "PZ_RazgovorGerrits_1":
			dialog.text = "그는 이미 슈네우르 가문과 함께 구세계로 떠났소. 아마 당신에게 말했을 거요.";
			link.l1 = "맞아, 그랬지. 하지만 나는 그가 최근 군도에서 생긴 일 때문에 늦었을지도 모른다고 생각했네. 말해보게, 게리츠, 회사에서 로덴부르흐 나리와 연락을 주고받는 사람이 있나? 혹시 사신선 같은 걸로?";
			link.l1.go = "PZ_RazgovorGerrits_2";
		break;
		
		case "PZ_RazgovorGerrits_2":
			dialog.text = "전혀 아닙니다 - 떠나기 전에 우리에게 절대 자신을 귀찮게 하지 말라고 했어요 - 새로운, 더 나은 삶을 시작한다고 했거든요.";
			link.l1 = "우리 삶도 더 나아지길 바라자. 잘 가.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PZ_RazgovorGerrits");
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "적하목록 기록을 좀 확인해 보지... 이케마, 이메르질, 야콥스... 잭슨, 찾았군. 흠, 레지널드 잭슨 선장은 현재 포트 로열과 필립스버그 사이에서 정기 운송 업무를 하고 있네. 그 항로에서 그를 찾아보게. 이제, 선장, 미리 경고하겠네—무슨 장난을 꾸미고 있다면 그만두는 게 좋을 걸, 왜냐하면 그 잭슨 선장은 우리 보호 아래 있거든. 서로 이해한 건가, 나리?";
			link.l1 = "난 그저 그와 볼일이 있을 뿐이야. 단순한 거래일 뿐이지. 그를 해칠 생각은 전혀 없어.";
			link.l1.go = "caleuche_1";
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
		break;
		
		case "caleuche_1":
			dialog.text = "훌륭하군. 잭슨 카피타인은 보통 포트 로열이나 필립스버그에 오래 머무르지 않아. 결국 시간도 돈이니까. 그의 배가 짐을 내리고 다시 싣자마자 곧바로 출항하는 게 보통이지. 바닷길에서 그를 만날 확률이 더 높을 거야.";
			link.l1 = "감사합니다!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_PrepareCreateGarpiya");
		break;
		
		// новый босс ГВИК
		case "HWIC_Boss":
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if (!CheckAttribute(npchar, "quest.silk_info"))
				{
					if (sti(pchar.reputation.nobility) > 60)
					{
						dialog.text = "아하, 카피텐 "+GetFullName(pchar)+"! 와줘서 반갑소. 당신에게 사업 제안이 있소.";
						link.l1 = "흥미롭군! 듣고 있소, 나리.";
						link.l1.go = "silk_info";
						break;
					}
					else Notification_Reputation(false, 61, "low");
				}
			}
			dialog.text = "좋은 하루요, 카피텐 "+GetFullName(pchar)+"! 무엇을 도와드릴까요?";
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if(CheckAttribute(npchar, "quest.silk")) // торговля шелком
				{
					if (GetDataDay() == 1 || GetDataDay() == 15)
					{
						link.l1 = "그 배의 비단에 대해 말인데...";
						link.l1.go = "trade_silk";
					}
				}
			}
			link.l2 = "좋은 하루요. 아니, 아무것도 필요 없소, 그냥 인사나 하려고 왔소.";
			link.l2.go = "exit";			
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "silk_info":
			dialog.text = "최근에 나는 리옹에서 온 상인과 카리브 해에 선박용 비단을 공급하는 거래를 트기 시작했소. 알고 있소? 이 비단으로 만든 돛이야말로 세상에서 가장 뛰어난 품질이니, 자네도 관심이 있을 것이라 생각하오.";
			link.l1 = "내가 죽을 지경이군, 그래, 그 말은 듣기 좋다. 조건이 뭐지?";
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = "작지만 꾸준하게 물건을 공급하지. 2주마다 삼십 통씩 따로 빼놓을 수 있어. 한 통에 이십 두블룬이네. 이렇게 하자고: 매달 1일과 15일에 삼십 통을 너를 위해 따로 챙겨두겠네. 그때 와서 가져가지 않으면, 다른 손님에게 팔겠네.";
			link.l1 = "그럼 아무 의무도 없는 건가?";
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = "정확합니다, 카피텐. 비단을 사고 싶으면 사시오. 전부 합쳐서 육백 두블룬이오. 단골 손님이 되길 바라오.";
			link.l1 = "제안해 주셔서 감사합니다, 마인헤르. 거래하겠소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			npchar.quest.silk_info = "true";
			npchar.quest.silk = "true";
			AddQuestRecordInfo("Unique_Goods", "3");
		break;
		
		// торговля шелком
		case "trade_silk":
			if (CheckAttribute(pchar, "questTemp.UpgradeSilk"))
			{
				dialog.text = "물론이지, 카피텐. 네 비단은 준비되어 있어. 값을 치를 준비됐나?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "물론이지! 여기, 2,550 더블룬을 가져가시오.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "젠장, 돈을 내 배에 두고 왔군. 금방 가져올게!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "물론이지, 카피텐. 네 비단은 준비되어 있어. 값을 치를 준비됐나?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "물론이지! 여기, 600두블룬을 가져가시오.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "젠장, 돈을 내 배에 두고 왔군. 금방 가져올게!";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && !CheckAttribute(pchar, "questTemp.GVIKSilkBlock")) // увеличить объём поставок шёлка
			{
				link.l4 = "Mijnheer "+npchar.name+", 비단 공급을 늘릴 가능성에 대해 논의하고 싶소.";
				link.l4.go = "UpgradeSilk";
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && CheckAttribute(pchar, "questTemp.GVIKSilkPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок шёлка, если в первый раз не принесли
			{
				link.l4 = "당신의 두블론을 가져왔소, Mijnheer "+npchar.name+". 받아 주십시오.";
				link.l4.go = "UpgradeSilk_Agreed";
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "trade_silk_1":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You have given 600 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "거래하게 되어 기쁘군, 카피텐. 네 비단은 롱보트를 통해 네 배로 전달될 거야.";
			link.l1 = "고마워!";
			link.l1.go = "trade_silk_2";
		break;
		
		case "trade_silk_2":
			dialog.text = "곧 다시 뵙기를 바랍니다. 또 찾아오십시오.";
			link.l1 = "그래. 또 보자!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 30);
			DeleteAttribute(npchar, "quest.silk");
			SetFunctionTimerCondition("Silk_TraderAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk": //
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "그대의 사업적 접근을 높이 평가하며, 요청을 고려할 용의가 있소. 물량을 다섯 배로 늘리는 것도 가능할 듯하오. 하지만 그런 공급을 준비하려면 상당한 자원이 필요하오. 창고를 확장하고, 경비를 강화하며, 신뢰할 수 있는 운송 경로도 확보해야 하오. 이익이 그대에게도 돌아가니, 비용은 우리 둘이 나누어 부담하는 것이 어떻겠소?";
				link.l1 = "이 모든 말이 합리적으로 들리는군. 이런 비용을 충당하려면 얼마가 필요하다고 생각하오?";
				link.l1.go = "UpgradeSilk_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "물자 공급을 늘리고자 하는 당신의 관심은 이해하오. 하지만 지금 단계에서는 그런 변화를 받아들이기가 어렵소. 당신의 발전에 대한 야망은 의심하지 않지만, 이런 거래는 무역에 대한 훨씬 더 많은 경험과 자신의 행동에 대한 확신이 필요하오. 협상의 기술을 더 깊이 익힌 뒤, 보다 구체적인 제안으로 다시 찾아오시오. 준비가 되면, 기꺼이 우리 협력을 강화하겠소.";
				link.l1 = "흠... 알겠소. 이 대화는 나중에 다시 하겠소.";
				link.l1.go = "exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_1":
			dialog.text = "모든 사정을 감안하면, 경의 부담금은 금화 더블룬 삼천 개가 되겠소. 이 자금으로 우리는 지체 없이 필요한 조치를 취할 수 있을 것이오.";
			link.l1 = "Mijnheer "+npchar.name+", 삼천 두블론이라고? 농담하는 건가? 나는 정직한 제안을 가지고 왔는데, 보급품 마련 하나에 이렇게 터무니없는 돈을 내라고?";
			link.l1.go = "UpgradeSilk_2";
		break;
		
		case "UpgradeSilk_2":
			dialog.text = "저를 오해하지 마시길 바랍니다. 저는 결코 당신을 속이려는 것이 아닙니다. 이 돈은 우리가 보급품 조직에 있어서 적절한 질서를 보장할 수 있게 해주는 금액입니다.\n창고 확장이나 경비 강화뿐 아니라, 이 사업의 예측 불가능함에도 불구하고 물자가 지연이나 손실 없이 제대로 전달되도록 보장하는 데 필요한 자금입니다.\n이 정도 규모라면 표준적인 지출입니다. 결국 당신의 투자는 충분히 보상받을 것이며, 물품도 제대로 된 상태로 제때에 받게 될 것입니다.";
			link.l1 = "당신의 설명을 들으니 조금은 안심이 되는군, 미인헤르. 하지만 여전히 이 금액은 너무 많소. 가격을 적어도 이천오백 두블룬으로 낮춘다면 당신의 조건을 받아들이겠소. 그 정도면 보급을 준비하고 모든 안전 조치를 지키기에 충분하다고 확신하오.";
			link.l1.go = "UpgradeSilk_3";
		break;
		
		case "UpgradeSilk_3":
			dialog.text = "알겠습니다, 금액이 큰 것은 이해하지만, 이미 말씀드렸듯이 일의 원활한 진행을 위해 꼭 필요한 액수입니다. 금액을 줄일 수는 없습니다. 그렇게 하면 우리의 모든 노력이 위험해질 수 있으니까요. 하지만 속았다고 느끼지 않으시도록, 앞으로 제공되는 모든 물자에 대해 15퍼센트 할인을 해드릴 준비가 되어 있습니다. 이것으로 경비를 어느 정도 보전하실 수 있기를 바랍니다.";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "흠, 15퍼센트 할인이라면 물론 진전이 있군. 좋아. 가격이 내게는 너무 비싸 보이지만, 제안을 받아들이겠네. 우리의 협력이 내 기대에 부응하길 바라지. 여기 돈이네.";
				link.l1.go = "UpgradeSilk_Agreed";
			}
			link.l2 = "Mijnheer "+npchar.name+", 당신의 제안이라면 어쩔 수 없군. 삼천 두블룬으로 하겠소, 꽤 큰 금액이지만. 하지만 지금 당장 전부를 지불할 수는 없소. 돈을 마련하는 대로 바로 돌아오겠소.";
			link.l2.go = "UpgradeSilk_5";
			link.l3 = "15퍼센트 할인이라고? 나리 "+npchar.name+", 이건 내가 기대한 게 아니오. 이 금액은 단순한 비용이 아니라, 대놓고 강도질하는 것이오! 하지만 나는 당신과의 거래를 끊을 생각은 없소. 이전 조건으로 돌아가겠소 - 비단 30필, 한 필에 20두블룬이오.";
			link.l3.go = "UpgradeSilk_4";
		break;
		
		case "UpgradeSilk_Agreed":
			dialog.text = "동의해 줘서 기쁘군, "+pchar.name+". 이제 세부 사항에 대해 말씀드리죠: 비단 150필을 한 필당 17두블룬에 드립니다. 전체 합계는 2550두블룬입니다. 물건은 평소처럼 매달 1일과 15일에 가져가시면 됩니다.\n이번 거래는 양측 모두에게 좋은 이익이 될 것이라 생각합니다.";
			link.l1 = "훌륭하군! 이제야 제대로군. 안녕히 계시오, 나리. 곧 다시 보지.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "3_1");
			pchar.questTemp.UpgradeSilk = true;
			pchar.questTemp.GVIKSilkBlock = true;
			DeleteAttribute(pchar, "questTemp.GVIKSilkPotom");
		break;
		
		case "UpgradeSilk_4":
			dialog.text = "이건 단순한 사업 거래일 뿐이지, 자네가 생각했을지도 모를 강도질이 아니야. 하지만, 자네 뜻대로 하게. 평소처럼 1일과 15일에 비단을 받으러 오게나; 새로운 거래를 맺게 되어 기쁘네.";
			link.l1 = "물론이지요, 나리. 안녕히 가십시오.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_5":
			dialog.text = "올바른 결정을 내려주어 기쁘오. 돈을 가져오는 즉시 거래의 모든 세부 사항을 논의하고 실행에 옮기겠소.";
			link.l1 = "안녕히 가십시오, 나리 "+npchar.name+". 필요한 금액을 모으는 대로 다시 보지.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			pchar.questTemp.GVIKSilkPotom = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "fight":
			DialogExit();
			sld = characterFromId("HWIC_officer");
			LAi_SetGuardianTypeNoGroup(sld);
			LAi_group_Attack(sld, Pchar);
			for (i=1; i<=6; i++)
			{	
				sld = characterFromId("HWIC_sold_"+i);
				LAi_group_Attack(sld, Pchar);
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
