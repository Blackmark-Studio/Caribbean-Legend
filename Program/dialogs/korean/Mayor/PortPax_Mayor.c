// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무엇을 원하시오? 물어보시오.","듣고 있소, 무슨 질문이오?"),"이것이 두 번째로 질문하려고 시도하는 것이오...","이것이 세 번째로 질문하려는 시도이오...","이게 도대체 언제 끝나겠소?! 나는 식민지 업무로 바쁜 사람인데, 자네는 아직도 나를 귀찮게 하는구려!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내가 마음을 바꿨소...","지금은 아니오. 장소와 시간이 맞지 않소."),"그렇소... 하지만 나중에, 지금은 아니오...","물어보겠소... 하지만 조금 있다가...","죄송하오, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+" 나리. 저는 총독 대리 슈발리에 드 푸앵시의 명령을 받고 이 자리에 왔습니다. 제 임무는 본국에서 식민지 시찰 임무를 띠고 온 노엘 포르게라는 남작을 토르투가로 모시는 것입니다. 그의 주된 목적은 프랑스 서인도 무역 회사를 설립하는 데 있습니다. 그분을 소개해 드리겠습니다... 자세한 내용은 직접 설명드릴 것입니다.";
                link.l1.go = "patria_portpax";
			}
			// Rebbebion, квест "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk"))
			{
				link.l1 = "나리, 저를 부르셨습니까?";
				link.l1.go = "PZ_1";
			}
			// Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogMayor"))
			{
				link.l1 = "각하, 매우 민감한 사안에 대한 정보를 가지고 왔으니 부디 주목해 주시기 바랍니다.";
				link.l1.go = "UV_1";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("이미 모든 것을 가져갔소. 또 무엇을 원하시오?","아직 챙기지 않은 것이 남아 있소?");
            link.l1 = RandPhraseSimple("그냥 둘러보고 있습니다...","그냥 확인하는 중이오, 뭔가 빠뜨릴까 봐서...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		// Jason НСО
		case "patria_portpax":
			dialog.text = "당신을 만나게 되어 매우 기쁩니다, Charles de Maure 선장님, 그리고 남작님. Monsieur Forget께서 우리 식민지에서 최대한 편안히 머무실 수 있도록 모든 노력을 다하겠습니다. 그리고 이렇게 높은 신분의 나리께서 저를 방문해 주신 기회를 빌려 한 가지 청을 드리고자 합니다.";
			link.l1 = "매우 흥미롭군요! 하시는 일에 대해 말씀해 주시지요, 각하.";
			link.l1.go = "patria_portpax_1";
		break;
		
		case "patria_portpax_1":
			dialog.text = "최근 몇 달 동안 우리 식민지에는 총독의 어떤 대표도 방문하지 않았소. 마치 그들이 세인트키츠의 우리를 완전히 잊은 것 같소! 그런데 그 사이, 히스파니올라 전체를 스페인 땅으로 만들고자 하는 스페인인들이, 섬 서쪽의 프랑스 정착민들과 부카니어들을 큰 골칫거리로 여기며 공격을 준비하고 있소! 내 순찰 장교들, 무역 선장들, 심지어 평범한 어부들까지도 산티아고에 강력한 스페인 함대가 집결하고 있으며, 포르토프랭스를 공격할 준비를 하고 있다고 보고했소!";
			link.l1 = "증거가 충분히 명확합니까, 폐하?";
			link.l1.go = "patria_portpax_2";
		break;
		
		case "patria_portpax_2":
			dialog.text = "정확한 정보는 없으나, 완전히 무작위인 여러 사람들에게서 들려오는 소문이 단순한 헛소문일 리는 없소. 우리 식민지는 프랑스에게 매우 중요한 곳이며, 이곳에는 최고의 플랜테이션이 있소. 이는 남작께서도 직접 확인하실 수 있을 것이오. 이 식민지를 잃거나 약탈의 위험에 노출시키는 일은 결코 용납할 수 없소!";
			link.l1 = "귀하의 증거를 고려하여 슈발리에 드 푸앵시에게 보고하겠습니다. 분명 그가 즉각적인 조치를 취할 것입니다.";
			link.l1.go = "patria_portpax_3";
		break;
		
		case "patria_portpax_3":
			dialog.text = "감사합니다, 선장님...";
			link.l1 = "";
			link.l1.go = "patria_portpax_4";
		break;
		
		case "patria_portpax_4":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
		
		case "PZ_1":
			DeleteAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk");
			dialog.text = "아니오, 내가 당신을 부른 적은 없소, 나리. 무슨 용건이라도 있소?";
			link.l1 = "어찌 그럴 수 있겠습니까? 하지만 나리의 사자가 우리를 맞이하였고, 나리께서 저를 위해 마을의 한 집을 준비해 두셨다고 전하더이다...";
			link.l1.go = "PZ_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_2":
			dialog.text = "무슨 집이오, 무슨 전령이오, 이 무례함은 또 무엇이오?!";
			link.l1 = "무슨 말씀이십니까, 어떤 전령이라니... 그의 이름은 앙리 티보이고, 그리고...";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "뭐라고? 자네, 그가 누구인지나 아는가? 모르는 모양이군. 하지만 상관없다. 레바쇠르의 조카가 내 도시에 무슨 일로 온 것이지?";
			link.l1 = "오, 맙소사...";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "드 모르, 들리시오? 나리?";
			link.l1 = "...";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload1", "PZ_SharleBezhitObratno", -1);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			SetMusic("music_teleport");
			pchar.questTemp.lockedMusic = true;
		break;
		
		//--> Украденное воспоминание
		case "UV_1":
			dialog.text = "중대한 일이라 하셨소? 내 흥미를 자극하셨군, 선장. 계속 말씀하시지—온전히 귀 기울이겠소.";
			link.l1 = "문제는 당신의 조카 줄리와 관련된 일입니다. 그녀가 도난당한 목걸이를 되찾기 위해 제게 도움을 요청했소.";
			link.l1.go = "UV_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			DelLandQuestMark(npchar);
		break;

		case "UV_2":
			dialog.text = "목걸이인가? 이상하군. 그녀의 소지품 중에 그런 물건이 있었다는 기억이 없소.";
			link.l1 = "사실을 순서대로 말씀드리겠습니다, 총독 나리. 문제의 목걸이를 무사히 되찾았습니다. 조사 결과, 도둑은 나리의 조카 아가씨를 모시는 시녀 지젤이었습니다. 도난품을 구입한 상인을 관찰한 바, 이 일이 그녀의 처음도 마지막도 아닐 것이라 강하게 의심됩니다.";
			link.l1.go = "UV_3";
		break;

		case "UV_3":
			dialog.text = "매우 계몽적이군요. 계속 말씀해 주시지요.";
			link.l1 = "제가 주목한 것은, 각하, 줄리가 이 문제에 대해 각하의 도움을 구하지 않았다는 점이었습니다. 목걸이는, 보아하니, 각하께서 그녀가 교류하지 못하도록 명확히 금지하신 인물로부터 받은 선물이었던 것 같습니다. 각하의 제약이 가장 현명하고 보호적인 의도에서 비롯된 것임을 믿기에, 이 일을 각하께 직접 알리고 목걸이를 직접 돌려드리는 것이 제 의무라 생각했습니다.";
			link.l1.go = "UV_4";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
		break;

		case "UV_4":
			dialog.text = "그대의 판단이 현명함을 증명하였소"+GetSexPhrase(", 선장","")+". 내 조카의 젊은 경솔함에 휘말리지 않고 이 일을 직접 내게 가져온 그대의 신중함을 칭찬하오.";
			link.l1 = "저는 오직 그녀의 안녕만을 생각하며 행동하였습니다, 총독 나리. 나리의 지도 또한 같은 염려와 지혜에서 비롯된 것임을 의심치 않습니다.";
			link.l1.go = "UV_5";
		break;

		case "UV_5":
			dialog.text = "그렇소, 선장. 나는 그녀의 삼촌이자 보호자로서 그녀의 안녕이 무엇보다 중요하오. 당신의 신중함에 대한 감사의 표시로 이 150두블론을 받아주시오.\n또한 이 항해용 나침반도 드리니, 위험한 바다를 건널 때 당신의 길잡이가 되길 바라오.";
			link.l1 = "각하의 너그러우심에 영광으로 생각하오나, 이토록 큰 보상은 과분하였습니다. 유감스럽게도 이제 작별을 고해야 하옵니다—조수는 그 누구도 기다려주지 않으니, 제 배가 저를 필요로 하오니 말입니다.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_End");
			AddItems(pchar, "gold_dublon", 150);
			GiveItem2Character(PChar, "compass1");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		//<-- Украденное воспоминание
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
