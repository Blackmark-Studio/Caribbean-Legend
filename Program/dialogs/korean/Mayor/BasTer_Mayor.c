// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무엇을 원하시오? 물어보시오.","듣고 있소, 무슨 질문이오?"),"두 번째로 다시 묻는 것이오...","세 번째로 다시 묻는 것이오...","언제 끝날 것이오?! 나는 식민지 업무로 바쁜 사람이오, 그런데도 그대는 아직도 뭔가를 물으려 하는 것이오!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소...","지금은 아니오. 장소와 시간이 맞지 않소."),"그렇소... 하지만 나중에, 지금은 아니오...","물어보겠소... 하지만 조금 이따가...","죄송하오, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "당신께 맡기고 싶은 민감한 일이 있소. 얼마 전, 한 사략선장이 바세테르 교구에 청금석이 박힌 황금 십자가를 기증하였소. 문제는 그 십자가가 산티아고 교구에서 도난당한 것이며, 그 도난 과정에서 성직자가 살해되었다는 점이오...\n";
                link.l1.go = "guardoftruth";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "저는 필리프 드 푸앵시 총독의 명을 받고 귀하의 무장 프리깃함의 지휘를 맡으러 왔습니다.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l1 = "제가 프리깃함을 전대에 합류시킬 준비가 되었습니다.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "baster")
			{
				link.l1 = "여기서 누군가와 만날 약속이 있소...";
                link.l1.go = "baster_goldengirl";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_guber_1"))
			{
				link.l1 = "나리, 저는 이 항구에서 상업 활동을 할 생각입니다. 특히, 꾸준하고 대규모로 주류를 거래하는 데 관심이 있습니다.";
				link.l1.go = "TPZ_guber_1";
			}
			//<-- Торговля по закону

		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("이미 모든 것을 가져갔소. 이제 또 무엇을 원하시오?","아직 챙기지 않은 것이 남아 있소?");
            link.l1 = RandPhraseSimple("그저 둘러보고 있을 뿐이오...","그냥 확인하는 중이오, 뭔가 놓칠까 봐서...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = "흠. 꽤 흥미로운 이야기로군. 하지만 내가 왜 스페인인들의 문제에 관심을 가져야 한다고 생각하시오?";
			link.l1 = "스페인 사람들 때문이 아니오, 나리. 종교는 사람을 국적으로 나누지 않소. 당신 교구에는 성직자의 피로 물든 물건이 있고, 산티아고 교구에서는 신성 모독이 저질러졌소...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "정의를 베풀어 주시고, 신부님께 십자가를 주인에게 돌려주라고 명해 주시길 부탁드립니다.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "그런데 언제부터 그렇게 진지한 신앙인이 되었소, 하, "+pchar.name+"? 스페인인들은 우리와 친구가 아니오, 그리고 이 문제로 교황 성하를 압박할 이유도 없소. 십자가는 선물이었으니 그걸로 충분하오. 우리 신부는 그 도난과 살인 사건과 아무 관련이 없으니, 그러니...";
			link.l1 = "그리고 당신께서는 저를 도와주실 수 없다는 말씀이오, 그렇소?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "솔직히 말씀드리자면, "+pchar.name+", 굳이 그래야 할 필요는 없다고 생각하오. 나는 그 가톨릭 광신도들에게 아무런 애정도 없소.";
			link.l1 = "알겠습니다. 폐를 끼쳐 죄송하오, 나리...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "28");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "배는 준비되어 있지만, 당신의 함대에는 이 배를 위한 빈 정박지가 없습니다. 선장님, 함대 규모를 줄이고 다시 오십시오. 그러면 즉시 프리깃함을 드리겠습니다.";
				link.l1 = "좋소.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "예, 물론입니다. 배는 출항 준비가 완료되었습니다. 선장은 이미 알고 있으며, 나리의 모든 명령을 따를 것입니다.";
				link.l1 = "그럼 이제 출발하겠습니다. 안녕히 계십시오, 각하.";
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
			link.l1 = "그럼 출항하겠습니다. 안녕히 계십시오, 나리.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "baster_goldengirl":
			dialog.text = "아, 샤를 드 모르 나리, 정말 적절한 때에 오셨군요! 제 오랜 친구께서 당신을 매우 만나고 싶어 하시며 도착 소식을 꼭 알려 달라고 하셨습니다. 부디, 제 응접실로 오십시오. 제가 즉시 앙제랑에게 알리겠습니다. 그런데 두 분은 어떻게 알게 되셨습니까?";
			link.l1 = "함께 도박을 했소. 그가 졌고, 우리 사이에 약간의 실랑이가 있었지. 아마도 드 쉬에부 나리께서 우리 사이를 화해시키고 싶어 하실 것이오.";
			link.l1.go = "baster_goldengirl_1";
		break;
		
		case "baster_goldengirl_1":
			dialog.text = "의심할 여지가 없소! 두 분 사이의 문제를 잘 해결하시길 바라오. 앙제랑이 상대하기에 가장 유쾌한 인물은 아닐지라도, 영리하고 명예로운 사람임은 분명하오. 그 점은 자네와도 닮았지. 참으로 드문 인재라오.";
			link.l1 = "과찬이십니다, 각하. 괜찮으시다면 응접실에서 그를 기다리겠습니다.";
			link.l1.go = "baster_goldengirl_2";
		break;
		
		case "baster_goldengirl_2":
			dialog.text = "하지만 물론이지, 편히 계시게. 이곳을 내 집처럼 생각하시오. 잠시 기다리셔야 할 수도 있소. 음료를 가져오라고 시키겠소.";
			link.l1 = "감사합니다, 각하. 하지만 사양하겠습니다. 저는 그냥 앉아서 우리 서로의... 친구를 기다리겠습니다.";
			link.l1.go = "baster_goldengirl_3";
		break;
		
		case "baster_goldengirl_3":
			DialogExit();
			pchar.questTemp.GoldenGirl = "baster1";
			DoQuestReloadToLocation("CommonResidence_3", "reload", "reload1", "GoldenGirl_AngerranInResidence");
		break;
		
		//--> Торговля по закону
		case "TPZ_guber_1":
			dialog.text = "선장, 나를 찾아온 것은 현명한 선택이었소. 이 섬에서 불법 무역을 근절하기 위해 모든 노력을 다하고 있소. 합법적인 경로로 사업을 하려는 올곧은 선장들을 진심으로 환영하오.";
			link.l1 = "그러면, 교역을 시작하기 위해 필요한 조건과 절차는 무엇입니까?";
			link.l1.go = "TPZ_guber_2";
			DelLandQuestMark(npchar);
		break;

		case "TPZ_guber_2":
			dialog.text = "매우 간단하오. 주류를 거래하려면 매달 100두블룬의 세금을 국고에 납부하고, 적절한 장부를 유지하며, 정기적으로 활동 보고서를 제출해야 하오.\n자금이 입금되면 본격적으로 거래를 시작할 수 있소.";
			link.l1 = "훌륭하오. 조건은 전적으로 합리적이오. 크리스티앙 들뤼스라는 현지 주민이 내 대리인으로 행동할 것이오. 그것이 문제가 되지 않으리라 믿소만?";
			link.l1.go = "TPZ_guber_3";
		break;

		case "TPZ_guber_3":
			dialog.text = "원하시는 대로 하겠습니다, 선장님. 하지만 명심하십시오 – 그대의 보호자가 저지르는 모든 일에 대한 책임은 전적으로 그대에게 있습니다. 만약 그가 잘못을 저지른다면, 그 결과 역시 함께 감당해야 할 것입니다.";
			link.l1 = "물론입니다. 설명해 주셔서 감사합니다, 총독 나리. 준비를 하겠으며, 크리스티안이 세금 납부를 담당할 것입니다.";
			link.l1.go = "TPZ_guber_4";
		break;

		case "TPZ_guber_4":
			dialog.text = "훌륭하오. 이렇게 성실하게 임하는 모습을 보니 기쁘구려. 그대의 사업에 큰 성공이 있기를 바라오.";
			link.l1 = "대단히 감사하오. 우리의 협력이 이 도시에 큰 도움이 되길 믿소. 안녕히 가시오.";
			link.l1.go = "TPZ_guber_5";
		break;

		case "TPZ_guber_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TPZ_guber_1");
			AddQuestRecord("TPZ", "11");

			sld = CharacterFromID("TPZ_Kristian");
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_21";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
