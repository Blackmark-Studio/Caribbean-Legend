// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 용건이오? 물어보시오.","듣고 있소, 무슨 질문이오?"),"이것이 두 번째로 질문하시는군요...","이것이 세 번째 시도이오...","이것이 언제 끝나겠소?! 나는 식민지 업무로 바쁜 사람이오, 그런데도 아직도 나를 귀찮게 하다니!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내가 마음을 바꿨소...","지금은 아니오. 장소와 시간이 맞지 않소."),"그렇소... 하지만 나중에, 지금은 아니오...","물어보겠소... 하지만 조금 이따가...","죄송합니다, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToGovernor")
			{
				link.l1 = "각하, 정말로 훌륭하고 긴급한 소식이 있어 이렇게 찾아왔습니다! 포르투갈인 바르톨로메오를 생포하였으며, 그 불한당은 지금 경비 아래 공정한 재판을 기다리고 있습니다! 그리고 혹시 상회로부터 약간의 감사라도 기대해도 되겠는지요...";
				link.l1.go = "Portugal";
			}
			//Португалец
			
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "governor")
			{
				link.l1 = "저를 꼭 만나시겠다고 하셨지요, 나리 총독...";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_battle_complete")
			{
				link.l1 = "영국 첩자들 문제로 찾아왔습니다, 나리 총독님...";
				link.l1.go = "FMQN_7";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("이미 모든 것을 가져갔소. 더 무엇을 원하시오?","아직 챙기지 않은 것이 남아 있소?");
            link.l1 = RandPhraseSimple("그냥 둘러보고 있습니다...","그냥 확인하는 중이오, 뭔가 놓칠까 봐서...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Jason, Португалец
		case "Portugal":
			dialog.text = "바르톨로메오... 포르투갈인 바트가 내 도시에 있다고?! 살아 있다고?!!";
			link.l1 = "그렇습니다, 각하. 그는 신뢰할 만한 경비 아래에 있습니다. 저는 회사에서 약속한 바트의 머리에 대한 보상을 받은 후에 그를 넘기겠습니다. 황금 두블룬도 괜찮습니다만...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "빌, 두블룬? 제정신이오?! 이런 괴물을 내 도시에 데려오다니 무슨 생각이었소?! 그자가 여기 있다면, 그의 프리깃도 이 섬에서 멀지 않을 것이고, 선원들 역시 지금 이 도시에 있을 수도 있소!";
			link.l1 = "그와 함께 있던 자들은 내가 죽였소. 다른 이들에 대해서는 모르겠으나, 어차피 별로 중요하지 않다고 생각하오. 왜냐하면 바르톨로메오는...";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "그렇소! 자네, 자기가 무슨 짓을 저질렀는지 정말 모르는 것이오?! '알바트로스'가 섬 근처에 있고, 자네는 그 잔혹함에 자기 피에 굶주린 선원들마저 두려워하는 해적을 붙잡았소! 어서 여기서 나가시오! 섬에서 떠나시오! 그리고 이 괴물도 데리고 가시오!";
			link.l1 = "하지만 들어보시오, 약속한 보상은 어찌 되고...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "나는 당신의 탐욕과 회사의 복수심 때문에 내 도시가 불타는 꼴을 보고 싶지 않소! 내 요새에는 이제 막 들어온 신병들뿐이며, 그들 중 절반은 누가, 왜 라벨린을 공격하는지 알게 되면 바로 도망칠 것이오! 그러면 학살이 시작될 것이니... 나는 그런 위험을 감수할 생각이 없소, 내 말 들리오?! 당장 꺼지시오, 그리고 회사가 그 자의 목을 그토록 원한다면 직접 쿠라사오로 데려가시오!\n지금 당장 하시오, 너무 늦기 전에! 그리고 그 자를 어떻게 하든 내 알 바 아니니, 심지어 당신 배 갑판에서 내던져도 상관없소, 단 내 도시에서만은 절대 안 되오!\n한스! 한스, 어디 있느냐, 이 게으른 바보야! 발레리안 약초든 뭐든 가져오고, 누가 좀 이 모험가를 내 관저에서 당장 내쫓아 주게!";
			link.l1 = "하지만 각하...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Marigo_town", "reload", "reload3_back", "PortugalOutResidence");
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "알겠소! 자, 선장, 우리 섬에 접근하는 길에 영국의 군함이나 상선을 마주친 적이 있소?";
			link.l1 = "아니오, 마인헤르 나리. 이곳 영해에서는 영국 국기를 단 군함이나 상선을 전혀 보지 못하였습니다.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "알겠소. 여기 얼마나 머무를 예정이오?";
			link.l1 = "사흘 정도...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "그렇다면, 제안을 하나 드리겠소. 우리 정보에 따르면 이곳에 영국 첩자들이 있을 위험이 있소. 섬이나 마을, 그 주변, 해안 등에서 수상한 선박이나 인물에 관한 정보를 제공하면 만 페소의 보상을 드리겠소. 만약 적을 체포하거나 제거하는 데 당국을 도우면 보상은 크게 늘어날 것이오.\n모든 민간 선장들은 수사에 참여하고, 첩자를 찾기 위해 현지 해안과 정글을 순찰하는 것이 환영받소.\n혹시 우리 군함 제파르트(Zeepard)를 마주칠 수도 있으니 놀라지 마시오, 순찰 중이오. 만약 영국인을 발견한다면 그 선장의 접근을 자유롭게 하시오.";
			link.l1 = "유감입니다, 각하. 그러나 저는 오직 평화로운 교역의 목적으로 이곳에 왔습니다. 보급을 마치고 볼일을 끝내는 대로 이 섬을 떠나야 하겠습니다.";
			link.l1.go = "FMQN_3";
			link.l2 = "매우 솔깃한 제안이오! 나도 참여하여 그대 섬의 해역과 해안을 약탈해 볼 생각이오. 어쩌면 이곳에 잠시 머물지도 모르겠군.";
			link.l2.go = "FMQN_5";
		break;
		
		case "FMQN_3":
			dialog.text = "그저 정보일 뿐이오, 선장님. 부담 가질 필요 없소. 수상한 점을 보게 되면 누구에게 말씀드려야 할지 알고 계시지요.";
			link.l1 = "알겠습니다, 나리. 안녕히 가십시오!";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			DialogExit();
			pchar.questTemp.FMQN = "way_eng_1";
			AddQuestRecord("FMQ_Nevis", "8");
			chrDisableReloadToLocation = false;
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_5":
			dialog.text = "훌륭하오, 선장! 그렇게 진지하시니 우리 사령관과도 반드시 상의하시기 바라오. 그는 첩자 색출을 담당하고 있으니 추가 정보를 줄 수도 있소.";
			link.l1 = "좋습니다, 나리. 그를 뵈러 가겠습니다.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			DialogExit();
			pchar.questTemp.FMQN = "way_div";
			AddQuestRecord("FMQ_Nevis", "9");
			chrDisableReloadToLocation = false;
			AddLandQuestMarkToPhantom("marigo_prison", "marigoJailOff");
		break;
		
		case "FMQN_7":
			DelLandQuestMark(npchar);
			dialog.text = "기다리고 있었습니다, 나리\n "+GetFullName(pchar)+". 위험한 영국 약탈대를 소탕해 주신 데 대해 저희의 감사를 표하고자 합니다. 이 만 페소를 받아주십시오. 추가로: 선창에 선박용 비단 200필이 실릴 것이며, 아주 특별한 보상으로 네덜란드 서인도 무역회사의 3년짜리 면허증도 드리겠습니다. 이는 대단히 귀중한 문서이니, 그 사실을 알고 계시리라 믿습니다?";
			link.l1 = "물론이지요! 3년짜리 면허라니, 정말 큰일이오.";
			link.l1.go = "FMQN_8";
		break;
		
		case "FMQN_8":
			dialog.text = "부디, 보상금을 받아 주십시오. 또한, 네덜란드 시민들과 당국 모두의 감사도 잊지 마십시오. 필립스버그에서 당신은 화제의 인물이며, 다시 뵙기를 기쁘게 생각하겠습니다.";
			link.l1 = "이렇게 따뜻한 말씀을 듣는 것이 면허증보다 더 값집니다. 감사합니다, 정말 기뻤습니다. 이제 저는 길을 떠나야 하겠군요. 안녕히 계십시오!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandBattleComplete");
		break;
		
		// Jason НСО
		case "tomas":
			dialog.text = "항복하겠소! 신성한 모든 것의 이름으로 간청하오니, 필립스버그와 그 시민들을 약탈하거나 노략질하지 마시오! 그대의 요구를 들을 준비가 되어 있소!";
			link.l1 = "시민들에 대해 걱정하지 마시오, 마인헤르 나리. 프랑스 왕관의 신민이라면 프랑스 군인을 두려워할 필요가 없소.";
			link.l1.go = "tomas_1";
		break;
		
		case "tomas_1":
			dialog.text = "프랑스 왕실?";
			link.l1 = "정확하오. 이 섬은 프랑스의 소유이며, 그대들은 여기서 임차인일 뿐이오. 이 섬이 자기들 소유가 될 수 있다고 믿은 건방진 임차인들이지. 오늘부로 생마르탱에서의 네덜란드 권한은 끝났소. 이해했소?";
			link.l1.go = "tomas_2";
		break;
		
		case "tomas_2":
			dialog.text = "하지만... 하지만 우리에게, 당신에게 항복한 네덜란드 병사들에게, 그리고 부상자들에게는 무슨 일이 일어납니까? 그리고 또...";
			link.l1 = "그것은 오로지 당신에게 달려 있소, 토마스 나리. 만약 내 부탁을 들어준다면, 항복한 자들이 부상자들을 데리고 우리가 부두에서 찾을 배 또는 배들에 타고 쿠라사오로, 스타이베산트 나리에게 갈 수 있도록 허락하겠소.";
			link.l1.go = "tomas_2_1";
		break;
		
		case "tomas_2_1":
			dialog.text = "";
			link.l1 = "그렇지 않으면, 그대는 내 배의 창고와 세인트키츠의 감방에 갇히게 될 것이오.\n또한, 스타이베산트가 우리 식민지 정복에 흥미를 잃도록 하기 위해, 몇몇 중요한 네덜란드 관리들을 처형해야만 하겠소...";
			link.l1.go = "tomas_3";
		break;
		
		case "tomas_3":
			dialog.text = "(더듬으며) 무... 무슨... 무...슨 부탁을... 하시려는... 건가요?";
			link.l1 = "섬 깊은 곳에는 분쟁의 씨앗이 되는 소금 광산이 있소. 그곳에는 광부와 노예들뿐만 아니라, 무장한 네덜란드 병사들도 있다는 것을 알고 있소. 그들은 분명 동인도 회사 경비대 소속일 것이오, 그렇지 않소, 나리? 나는 그들에게 항복할 기회를 주겠지만, 거부한다면 무력을 사용할 것이오. 광산까지 길을 안내해 줄 안내자가 필요하오. 그런 안내자를 찾아주시오.";
			link.l1.go = "tomas_4";
		break;
		
		case "tomas_4":
			dialog.text = "소, 소금... 내, 내 것인가?";
			link.l1 = "그렇소. 두려워하지 마시오, 토마스 나리. 만약 광산 경비병들이 현명하게 무기를 내려놓는다면, 내가 그들에게 이 섬을 떠날 기회를 주겠소. 불필요한 유혈사태는 원치 않소. 걱정 마시오, 양심에 거리낄 일은 없을 것이오. 설령 나에게 광산의 위치를 말하지 않는다 해도, 생마르탱 섬은 충분히 작으니 그대의 도움 없이도 내가 광산을 찾을 수 있소. 다만 덤불과 늪을 헤매며 시간을 낭비하고 싶지 않을 뿐이오. 그러니 이 거래는 내게보다 그대에게 더 이익이 될 것이오.";
			link.l1.go = "tomas_5";
		break;
		
		case "tomas_5":
			dialog.text = "자, 자... 알겠소, 내가 광산으로 가는 길을 알려주겠소. 하지만, 약속하시오... 우리 모두가 이 섬을 떠날 수 있도록 해주겠다고!";
			link.l1 = "장교이자 귀족으로서 맹세하오.";
			link.l1.go = "tomas_6";
		break;
		
		case "tomas_6":
			dialog.text = "그랑 카스 만에서... 맨 끝, 물가 근처에... 돌들이 있소. 거기... 거기, 그 돌들 뒤로, 해안선을 따라가면 물가에 길이 있소, 거기... 그곳은 얕아서 허리 정도 깊이거나 그보다 얕소. 바위를 돌아가야 하고, 그러면 큰 해변에 도착하오, 그곳은... 그곳은 주위에 암초가 많아 배를 댈 수 없소. 이 해변에서 곧장... 광산으로 이어지는 길이 있소.";
			link.l1 = "훌륭하오. 나는 출발하겠소. 그리고 그대는, 나리, 내가 돌아올 때까지 내 병사들의 철저한 감시 아래 이곳에 머물 것이오.";
			link.l1.go = "tomas_7";
		break;
		
		case "tomas_7":
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			LAi_SetActorType(npchar);
			pchar.quest.Patria_BastionGate.win_condition.l1 = "location";
			pchar.quest.Patria_BastionGate.win_condition.l1.location = "Shore40";
			pchar.quest.Patria_BastionGate.function = "Patria_BastionShore";
			AfterTownBattle();
			AddQuestRecord("Patria", "50_1");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
