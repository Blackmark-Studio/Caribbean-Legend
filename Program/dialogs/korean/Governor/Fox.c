// полковник Фокс - бравый командир морской пехоты 'морские лисы'.
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
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyReward"))
			{
				dialog.text = "무슨 일로 오셨소, 나리? 오... 이런... 잠깐! 당신은 내 딸을 르바쇠르의 하수인들 손아귀에서 구해준 프랑스 선장이로군요! ";
				link.l1 = "캐서린이 이미 내 이야기를 했군...";
				link.l1.go = "terrapin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Usurer") && !CheckAttribute(npchar, "quest.utensil"))
			{
				dialog.text = "무엇을 원하시오, 나리?";
				link.l1 = "안녕하십니까, 대령 나리. 다소 '특이한' 일로 찾아왔습니다. 잠시 시간 내주실 수 있겠습니까?";
				link.l1.go = "guardoftruth";
				break;
			}
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "eng_reward")
			{
				dialog.text = "제가 틀리지 않았다면, 당신이 바로 "+GetSexPhrase("선장","여선장")+" 신트마르턴에서 내 부하들이 임무를 수행하는 데 도와준 자가 누구였소? "+TimeGreeting()+"!";
				link.l1 = TimeGreeting()+", 대령 나리. 네, 접니다.";
				link.l1.go = "FMQN";
				break;
			}
			dialog.text = "무슨 일이오, 나리?";
			link.l1 = "아무것도 아닙니다, 대령님. 이만 물러가겠습니다.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guardoftruth":
			dialog.text = "여기까지 왔으니, 어서 털어놔라...";
			link.l1 = "당신은 최근에 네덜란드 해적 롤리 더 캡이 지휘하는 스쿠너에 승선하여 선장을 여기 세인트 존스로 데려왔소.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "선장이라고? 허, 웃기지 마시오! 이 범죄자 쓰레기는 이런 명예로운 칭호를 받을 자격이 없소. 나는 저주받은 해적, 늑대 무리의 두목을 잡았소. 저자는 영국 상인과 무역상을 약탈하고 살해한 자요. 그리고 나는 그와 그의 패거리들이 마땅한 벌을 받게 했소 – 세인트 존스의 모든 이가 부두에서 그들의 교수형을 지켜봤소!";
			link.l1 = "이제 이 악당을 심문할 수 없겠군요... 대령, 혹시 도와주실 수 있겠습니까? 그 해적이 자기 것이 아닌 황금 향로를 가지고 있었습니다. 혹시 그에게서 그런 물건을 발견하셨습니까?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "아니, 우리가 그 자를 수색했는데 그 악당은 아무 소지품도 없었소. 게다가, 그가 가진 것들도 분명 모두 정직한 상인들에게서 빼앗은 것일 테지! 그리고 그대가 걱정하는 것에 대해서는... 흠, 아니오, 우리는 그것을 찾지 못했소. 그런데 향로가 해적선에 있을 리가 있겠소? 정말 그들 중에 신부라도 있었다고 생각하시오?";
			link.l1 = "아니, 모릅니다. 롤리 더 캡이 윌렘스타드의 고리대금업자에게서 그것을 샀는데, 그 고리대금업자는 또 다른 해적에게서 샀다고 하더군요. 그 향로는 상태도 좋고 값비싼 물건이라서, 저는 정당한 주인에게 돌려주려고 합니다. 롤리가 까치처럼 그 물건에 눈독을 들였던 모양입니다.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "사실 롤리의 배를 우리가 올라타서 점령했을 때, 선창은 텅 비어 있었고, 몇 개의 상자에 두블룬만 조금 있었소. 쓰레기뿐이었지. 값진 물건도, 황금 향로도 없었소. 해적에게 어울리지 않는 그런 물건이 있었다면 내가 기억했을 것이오.\n내 생각엔 그 빌어먹을 해적이 도미니카에 자기 재산을 숨긴 것 같소. 우리도 거기에 상륙해서 주변을 뒤졌지만 아무것도 찾지 못했소. 하지만 섬에 오래 머물거나 깊숙이 탐험하지는 않았소. 야만인들이 너무 많았기 때문이오.";
			link.l1 = "흠... 해적이 훔친 물건들과 함께 향로를 도미니카 어딘가에 숨겨뒀을 수도 있겠군... 아쉽소. 처형 전에 해적을 심문해 보았소?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "내가 그렇게 했지... 그런데 그 자가 내 얼굴을 보고 그냥 웃기만 하더군. 하지만 난 그의 은닉처에는 별로 관심 없었어. 롤리 더 캡이 교수형을 당한 게 가장 중요한 일이었으니까.";
			link.l1 = "알겠습니다. 이야기와 시간을 내주셔서 감사합니다, 대령 나리. 안녕히 가십시오...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("GuardOT_Fox_DlgExit");
		break;
		
		case "terrapin":
			dialog.text = "여러 번이나, 선장! 프랑스인에게서 이런 명예롭고 용감한 행동을 기대하기는 어려웠소. 군인으로서도, 아버지로서도 그대에게 감사하오. 이 세상에서 내 딸보다 소중한 것은 없소...";
			link.l1 = "제가 도움이 될 수 있어 기쁩니다. 언젠가 제 행동이 프랑스에 대한 나리의 마음을 바꿀 수 있기를 바랍니다.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "낯선 영국 소녀를 위해 목숨을 걸 정도로 명예롭고 관대한 신사인 당신 같은 분이 계시니, 나의 당신 동포들에 대한 감정이 크게 누그러질 것 같소!";
			link.l1 = "어느 나라의 쥐떼 속에도 정직한 사람이 있기 마련이오, 대령...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "그리고 그대는 그것을 증명했소! 보상이 기다리고 있소, 선장. 물론 딸의 생명은 값을 매길 수 없지만, 조너선 폭스는 항상 빚을 갚는 사람이오, 맹세하오! 그대는 진정한 군인이라 내 선물도 군인에게 어울리는 것이오. 자, 한번 보시오.\n이것은 블런더버스요, 훌륭한 해군 머스킷으로 한 손으로도 사용할 수 있소. 특수 볼트로 장전하면 가장 단단한 흉갑도 뚫을 수 있소. 산탄도 발사할 수 있고, 견고한 구조 덕분에 못을 넣어 쏠 수도 있소. 자, 받아두시오, 이제 그대 것이오.";
			link.l1 = "군인에게 이보다 더 훌륭한 선물이 어디 있겠습니까, 감사합니다, 대령님!";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			Log_Info("You have received a blunderbuss");
			Log_Info("You have received 10 arrows");
			Log_Info("You have received 10 charges of nails");
			Log_Info("You have received instructions for creating the harpoon arrows");
			Log_Info("You have received instructions for creating the charge of nails");
			GiveItem2Character(pchar, "pistol8");
			TakeNItems(pchar, "harpoon", 10);
			TakeNItems(pchar, "GunEchin", 10);
			GiveItem2Character(pchar, "recipe_harpoon"); 
			GiveItem2Character(pchar, "recipe_GunEchin"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "또한 소량의 탄약과 그것을 만드는 방법에 대한 지침도 드리겠소. 그 힘을 최대한 활용하지 않는다면 아쉬울 테니!";
			link.l1 = "감사합니다, 대령 나리. 이런 선물을 마다할 이유는 없지만, 저는 보상을 바라고 캐서린을 구한 것이 아니라는 점을 알아주셨으면 합니다. 저는 그저 무방비한 소녀가 해를 입는 것을 두고 볼 수 없었을 뿐입니다.";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "그 점은 알고 있소, 선장. 그것만으로도 두 배로 존경받을 만하오. 카트린도 정말로 감명을 받았소, 그녀에게 좋은 인상을 남기는 건 결코 쉬운 일이 아니오. 다시 한 번 그녀를 구해준 데 대해 감사드리오. 내가 빚을 졌소!";
			link.l1 = "음, 선물 고맙소, 대령. 캐서린에게 내 안부를 전해 주시오, 그리고 다음에는 아버지 말씀을 잘 들었으면 하오.";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "알겠습니다, 선장님! 안녕히 가십시오, 안전한 항해 되시길!";
			link.l1 = "안녕히 가십시오, 대령님.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Terrapin_KathyReward");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
			ChangeCharacterNationReputation(pchar, ENGLAND, 20);
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "보고서를 읽어보았소. 그대의 행동은 매우 높이 평가되었으니, 반드시 보상을 받아야 하오. 원정 임무에 대해 삼만 페소와, 군인으로서의 용맹에 무기를 내리겠소. 이 검과 아르케부스를 받으시오. 이제 모두 그대의 것이오!";
			link.l1 = "감사합니다, 나리.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "물론이지요, 선장님. 당신은 또한 영국 식민지들과 당국, 그리고 나 개인적으로도 사랑과 존경을 받게 되었소. 내 부하들을 버리지 않고 그들의 임무를 도와주어 고맙소!";
			link.l1 = "기쁩니다, 대령님...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "이제 실례하겠습니다 - 다른 볼일이 있소. 행운을 빕니다, 선장. "+pchar.lastname+".";
			link.l1 = "안녕히 가십시오, "+GetAddress_Form(NPChar)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
