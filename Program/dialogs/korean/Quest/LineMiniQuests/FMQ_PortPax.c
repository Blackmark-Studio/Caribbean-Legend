// Addon-2016 Jason, французские миниквесты (ФМК) Порт-о-Пренс
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "명백한 버그야. 개발자들에게 알려 줘.";
			link.l1 = "그래, 그렇게 할게.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "officer":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "여기서 도대체 무슨 일이 벌어지고 있소, 나리들? 싸우는 소리를 들었는데.";
			link.l1 = "이봐, 장교. 여자가 비명을 지르는 소리를 들었는데...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_2":
			dialog.text = "";
			link.l1 = ""+GetFullName(pchar)+". 선장 "+GetFullName(pchar)+".";
			link.l1.go = "officer_3";
		break;
		
		case "officer_3":
			dialog.text = "지금은 가도 좋소, 선장. 여기서 무슨 일이 있었는지 알겠으니, 궁금한 점이 있으면 다시 부르겠소.";
			link.l1 = "좋아...";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "여기서 대체 무슨 일이 벌어지고 있소, 신사 여러분? 싸우는 소리를 들었소.";
			link.l1 = "휴... 경관 나리, 저는 선술집 여종업원의 부탁을 받고 왔습니다 — 누군가 여기서 살해당하고 있다고 해서 왔는데, 정말이었어요 — 저 두 악당이 이 신사분을 공격했습니다. 안타깝게도 구하지 못했어요. 저 자식들이 끝내 죽이고 말았어요.";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			dialog.text = "제기랄... 저 자식 스페인 놈이잖아! 여긴 왜 온 거지? 흠. 그럼, 넌 누구냐, "+GetAddress_Form(NPChar)+"?";
			link.l1 = ""+GetFullName(pchar)+". 선장 "+GetFullName(pchar)+".";
			link.l1.go = "officer_7";
		break;
		
		case "officer_7":
			dialog.text = "선장, 지금은 가도 좋소. 자네 말이 증인의 진술과 일치하니 말이오. 필요하면 다시 부르겠소.";
			link.l1 = "좋아...";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
		break;
		
		case "noble":
			dialog.text = "모든 걸 설명하겠습니다, 장교 나리! 저는 산토도밍고에서 온 돈 도밍고 오르티스 알발라테입니다. 한 아가씨의 초대로 포르토프랭스로 왔지요. 만남을 기다리며 선술집에 머물렀습니다. 그런데 두 시간도 채 지나지 않아, dos canallas malditas가 제 방으로 들이닥쳤고, 만약 제때 도움을 받지 못했다면\n "+GetSexPhrase("나타난 이 좋은 나리","갑자기 나타난 이 아름다운 세뇨리타")+", 큰일 날 뻔했지.";
			link.l1 = "돈 도밍고 오르티스 알발라테? 너 스페인 놈이냐?";
			link.l1.go = "noble_1";
		break;
		
		case "noble_1":
			dialog.text = "레 페리페 나리만큼이나 스페인 사람이지, 하! 그리고 내 서류들도 완벽하게 정돈되어 있다는 점을 강조하고 싶군. 나는 에스파냐의 귀족이야, 그 더러운 해적 따위가 아니라고!";
			link.l1 = "Don Domingo, 이런 불미스러운 일에 대해 진심으로 사과드립니다! 잠시 저희와 함께 주둔지로 가셔서 몇 가지 질문과 와인 한 잔 하시지요. 모든 것은 저희가 처리하겠습니다. 그리고 너는...";
			link.l1.go = "noble_2";
		break;
		
		case "noble_2":
			DialogExit();
			sld = CharacterFromID("FMQP_off");
			sld.Dialog.currentnode = "officer_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "noble_3":
			PlaySound("Voice\English\LE\Domingo\Domingo_01.wav");
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" 선장님! "+UpperFirst(GetAddress_Form(NPChar))+" "선장님! 산티아고와 성모 마리아께 맹세코, 당신은 고귀한 분이십니다. 카스티야의 진정한 아들은 이런 고결함에 반드시 보답하지요! 여기서 내 볼일이 끝나면, 꼭 당신께 보답하는 모습을 보고 싶소. 부디 산토 도밍고에 있는 내 누추한 집에 들러 주시겠소? 도시 성문 근처에 있소. 당신을 위해 성대한 연회를 준비하겠소,"\n "+GetSexPhrase("내 좋은 친구","내 구원자")+"! 내 이름을 기억해 둬, 나는 돈 도밍고 오르티스 알발라테다!";
			link.l1 = "...";
			link.l1.go = "noble_4";
		break;
		
		case "noble_4":
			DialogExit();
			AddMapQuestMarkCity("santodomingo", true);
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "FMQP_AfterFightInTown");
		break;
		
		case "noble_5":
			dialog.text = "Captain "+pchar.lastname+"?! 오 마드레 데 디오스! 이게 무슨 재앙이야! 이건 학살이잖아! 여기서 무슨 일이 있었던 거지,\n "+GetSexPhrase("내 좋은 친구","나를 구해준 이")+"? 이 자들은 누구지?";
			link.l1 = "뵙게 되어 반갑습니다, Don Domingo. 이들은... 제가 당신을 찾아왔습니다. 저기 있는 저 사람 보이십니까? 저 사람이 바로 우고, 당신의 하인이고, 그는...";
			link.l1.go = "noble_6";
		break;
		
		case "noble_6":
			dialog.text = "우고?! 이런, 속았구나, 선장!";
			link.l1 = "알겠어, 나한테도 이런 일이 자주 일어나더라고. 세 놈이 네 집에 침입해서 충직한 우고를 죽였지 – 위층에서 이미 시신을 발견했어 – 그리고 널 노리고 매복까지 했더군. 내가 도착한 건 그놈들 계획에 없었던 일이야. 결국 우리 만남에서 살아남지 못했지.";
			link.l1.go = "noble_7";
		break;
		
		case "noble_7":
			dialog.text = "산타 마리아, 오라 프로 노비스! 당신은 톨레도 검술 대가들처럼 검을 휘두르는군! 당신이 내 편이라서 다행이야! 오, 내 불쌍한 우고! 그는 내가 어릴 때부터 키워줬는데, 이제는... 저 저주받은 악당들에게 살해당하다니!";
			link.l1 = "Don Domingo, 아직 위험에서 벗어나지 못한 것 같소. 당신 부하 우고가 뭔가 알고 있었던 모양이오, 이 쪽지를 읽어보시오. 탁자 위에서 찾았소.";
			link.l1.go = "noble_8";
		break;
		
		case "noble_8":
			ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
			RemoveItems(pchar, "letter_parol", 1);
			dialog.text = "내놔... (읽으며) 이럴 수가... 이런, 안 돼! 믿을 수 없어! 티오 루이스... 하지만...";
			link.l1 = "이 짓을 한 놈에 대해 아는 거라도 있나?";
			link.l1.go = "noble_9";
		break;
		
		case "noble_9":
			dialog.text = "의심뿐이야... 끔찍한 의심이지, "+GetSexPhrase("내 좋은 친구","나를 구해준 이")+"! 우리 어머니의 오라버니가 어떻게 그런 짓을 할 수 있단 말이야?";
			link.l1 = "자초지종을 좀 말해 주시겠소? 미안하오, Don Domingo 나리, 하지만 내 경험상 친척들이야말로 사람에게 가장 위험한 적이 되는 경우가 많더이다...";
			link.l1.go = "noble_10";
		break;
		
		case "noble_10":
			dialog.text = "그래, 네 말이 맞아, "+GetAddress_Form(NPChar)+"! 내가 다 말할게! 자네가 벌써 두 번이나 나를 구해줬고, 지금은 자네만이 내가 믿을 수 있는 사람인 것 같아! 하지만 이 끔찍한 곳은 벗어나자, 속이 뒤집힌다. 이 엉망진창을 알칼데에게 알려야 해, 그들이 불쌍한 우고를 돌봐줄 거야. 신경을 좀 가라앉히려고 근처 선술집에서 포도주 한잔 어때?";
			link.l1 = "너야말로 신경 좀 달래야겠군, 앞장서라, 나리!";
			link.l1.go = "noble_11";
		break;
		
		case "noble_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Santodomingo_tavern", "sit", "sit_base2", "FMQP_InSantoDomingoTavern");
		break;
		
		case "noble_12":
			LAi_SetSitType(pchar);
			dialog.text = "그러니까, 친구여, 내 가족사에 대해... 축약된 버전으로 이야기해 주지. 내 어머니 도냐 이사벨라 오르티스는 내 아버지, 리카르도 알발라테 후작과 결혼했고, 관례에 따라 그의 성을 따랐지. 그녀의 오빠 루이스 오르티스는 식민지의 주둔지 사령관이었으나, 어머니가 결혼한 후 아버지의 임명으로 포르토벨로에서 멀지 않은 사탕수수 농장의 관리인이 되었네\n이 농장은 매우 넓고 부유했으며, 정말 수익성이 좋았지. 몇 해 전 부모님이 바다에서 비극적으로 돌아가신 뒤, 외아들인 내가 모든 것을 상속받았고, 그 농장도 내 몫이 되었네. 삼촌은 계속 그 자리를 지켰고, 나는 그가 내게 내는 임대료에 만족하며 지냈지. 그는 항상 제때에 돈을 보내주었어.";
			link.l1 = "그래서 네 삼촌이...";
			link.l1.go = "noble_13";
		break;
		
		case "noble_13":
			dialog.text = "그래. 지금은 그저 세입자일 뿐이야. 내가 그 플랜테이션의 주인이지, 그가 아니야. 하지만! 내게 무슨 일이 생기면 그 땅은 그의 소유가 될 거다.";
			link.l1 = "있잖아, 도밍고, 나는 저것보다 훨씬 시시한 보물을 위해 자기 가족 전부를 싸늘하게 죽일 놈들도 알았어.";
			link.l1.go = "noble_14";
		break;
		
		case "noble_14":
			dialog.text = "카를로스, 너는 분명 더 나은 사람들과 어울려야겠구나. 내 사랑하는 우고가 마지막 편지에서 삼촌의 서류를 언급했어... 이건 직접적인 단서야. 아, 이걸 믿고 싶지 않아! 하지만... 내 사촌 마르가리타 오르티스가 얼마 전에 스페인에서 약혼했거든. 그게 원인일까,\n "+GetAddress_Form(NPChar)+" 선장인가?";
			link.l1 = "너를 끔찍이 아끼는 삼촌이 갑자기 돈이 좀 필요할지도 몰라...";
			link.l1.go = "noble_15";
		break;
		
		case "noble_15":
			dialog.text = "돈?! 물론이지... 하지만 후작 작위도 잊지 마시오! 그래야 내 사촌이 미래의 남편과 제대로 어울릴 수 있을 테니까! 예수 그리스도여! 내가 얼마나 어리석었는지!";
			link.l1 = "그 작위는 설탕 농장보다 더 가치 있지.";
			link.l1.go = "noble_16";
		break;
		
		case "noble_16":
			dialog.text = "잠깐만! 방금 생각났어, 이게 내 목숨을 노린 첫 번째 시도가 아니었어! 몇 주 전에 거리에서 거지 하나를 만났거든! 그 취한 놈이 나를 무시하는데 도저히 참을 수가 없더라고. 그런데 그 자식, 검술이 제법이었어. 칼을 뽑더니 내가 죽이기 전에 레이피어로 나를 상처까지 입혔지.";
			link.l1 = "도대체 어떻게 포르토프랭스 선술집까지 굴러들어온 거야? 젊은 세뇨리타 얘길 했던가?";
			link.l1.go = "noble_17";
		break;
		
		case "noble_17":
			dialog.text = "(얼굴이 붉어지며) 나리... 네, 선장님, 현장에 젊고 예쁜 세뇨리타가 있었습니다... 이제 보니 그 여자가 함정의 미끼였네요. 이놈의 자식들, 사방에 배신자뿐이야, 아무도 믿을 수 없어! 불쌍한 우고... 이제 죽었어요.";
			link.l1 = "이 일 좀 어떻게 해야겠어, Domingo. 스페인으로 도망치는 건 어때?";
			link.l1.go = "noble_18";
		break;
		
		case "noble_18":
			dialog.text = "스페인으로 가라고? 그리고 내 농장을 그 악당에게 넘기라고? 선장, 나는 도밍고 오르티스 알발라테 후작이오!";
			link.l1 = "하지만...";
			link.l1.go = "noble_19";
		break;
		
		case "noble_19":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", 도와줄 수 있겠소? 우고가 죽고 나니 내 곁에 믿을 사람이 아무도 없소. 당신이 이미 두 번이나 나를 구해줬지! 두 번이나! 정말 큰 은혜를 입었소, 평생 갚아도 모자라오. 그런데도 또 한 번 부탁을 드리려 하오. 성모 마리아께 맹세코, 반드시 보답하겠소!";
			if (startHeroType == 2)  
			{
				link.l1 = "무엇을 도와드릴까요, "+npchar.name+"?";
				link.l1.go = "noble_20";
			}
			else
			{
				link.l1 = "좋아, 스페인 놈치고는 괜찮은 사람이군. 뭘 도와주면 되겠나, 도밍고?";
				link.l1.go = "noble_20";
			}
			
		break;
		
		case "noble_20":
			dialog.text = "포르토벨로에 있는 내 플랜테이션으로 가자! 지금 내 삼촌이 카르타헤나에 있다는 걸 알고 있어. 우고가 어떤 서류에 대해 언급했으니, 돈 루이스 오르티스의 장부와 문서들을 확인해 보자! 그의 더러운 음모를 만천하에 드러낼 만한 무언가를 찾을 수도 있을 거야. 포르토벨로까지 거리가 꽤 되지만, 항해 대가는 전액 지불하겠어!";
			link.l1 = "이 시점에서 당신을 거절하는 건 어리석은 일이겠지, 돈 도밍고. 이제 와서 물러설 수 없을 만큼 깊이 빠졌으니까.";
			link.l1.go = "noble_21";
		break;
		
		case "noble_21":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "신께 감사하네, 자네가 도와줄 줄 알았어, 친구! 여기, 포르토벨로까지 항해해 준 대가로 이 이만 페소를 받게. 언제 출항하지? 내 삼촌이 카르타헤나에서 돌아오기 전에 서둘러야 해!";
			link.l1 = "그럼 시간 낭비하지 말자.";
			if (startHeroType != 2 && CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 20 && GetNationRelation2MainCharacter(SPAIN) == RELATION_NEUTRAL) {link.l1.go = "noble_22";}
			else {link.l1.go = "noble_22x";}
		break;
		
		case "noble_22x":
			GiveNationLicence(HOLLAND, 20);
			dialog.text = "여기 네덜란드 서인도 회사 면허장이 있다네. 유효기간은 이십 일이야, 자, 여기에 자네 이름만 적으면 되지. 됐다. 이걸로 코스타 가르다와의 문제는 피할 수 있을 거야.";
			link.l1 = "훌륭해!";
			link.l1.go = "noble_22";
		break;
		
		case "noble_22":
			dialog.text = "이제 당신 배에 올라가도 되는 겁니까, 선장님?";
			link.l1 = "스스로를 귀한 손님이라 생각하게. 바람만 제대로 불면 곧바로 출항한다네.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_OnBoard");
			AddMapQuestMarkCity("portobello", true);
		break;
		
		case "noble_23":
			dialog.text = "그러면, Carlos 선장, 여기까지 왔군. 이제 내 삼촌 집을 찾아서 안에 뭐가 있는지 봐야겠어.";
			link.l1 = "Don Domingo 나리, 경비대와 문제 생길 일 있겠소?";
			link.l1.go = "noble_24";
		break;
		
		case "noble_24":
			dialog.text = "아니. 하지만... 흠. 루이스가 그들을 내게서 돌아서게 만들었을 가능성도 있지. 어쨌든, 신중함이 용기보다 나을 때가 많아. 우리가 찾아야 할 집부터 찾자.";
			link.l1 = "이미 알고 있지 않아? 그건 네 플랜테이션이야.";
			link.l1.go = "noble_25";
		break;
		
		case "noble_25":
			dialog.text = "흠... 솔직히 말해서, 내가 여기 마지막으로 왔을 때는 겨우 여덟 살이었어. 그래도 최대한 빨리 이걸 만회할 생각이야!";
			link.l1 = "알겠어. 그럼 찾아보자. 네 삼촌 집이 여기서 제일 클 거야.";
			link.l1.go = "noble_26";
		break;
		
		case "noble_26":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("FMQ_Portpax", "7");
		break;
		
		case "noble_27":
			dialog.text = "여기 뭐가 있지, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "한번 보십시오, Don Domingo. 회계 기록처럼 보입니다. 이거 흥미로울지도 모르겠군요.";
			link.l1.go = "noble_28";
		break;
		
		case "noble_28":
			ChangeItemDescribe("Almanac", "itmdescr_Almanac");
			RemoveItems(pchar, "Almanac", 1);
			dialog.text = "(읽으며) 흠... 그래. 이것 좀 봐... 아이 카람바! 십만 페소! 그리고 또 십오만 페소! 그리고 여기... (페이지를 넘기며) 루이스 삼촌!";
			link.l1 = "재미있는 거라도 있나?";
			link.l1.go = "noble_29";
		break;
		
		case "noble_29":
			dialog.text = "흥미로운 게 있냐고! 우리 삼촌은 나한테 말한 것보다 다섯 배나 더 많은 수입이 있었어! 도둑놈! 횡령범!";
			link.l1 = "놀랍지도 않군. 실제 상황을 가끔씩 확인하지 않고는 누구도 완전히 믿을 수 없어. 그게 상식이지.";
			link.l1.go = "noble_30";
		break;
		
		case "noble_30":
			dialog.text = "상식이란 평범한 자들에게나 통하지. 나는 고귀한 신사라 믿었던 자들의 이런 기만을 알아채지 못하도록 자라왔지! 역시 네 말이 옳았어, 카를로스! 내 친삼촌이 나를 속이고 있었어! 젠장! 이건 내 잘못이지만, 내가 바로잡을 거야. 이 농장은 내 소유고, 오늘부로 삼촌은 모든 직무에서 해임됐어! 이제 그는 아무것도 아니야! 내가 반드시 그 자를 용서하지 않을 거다!\n";
			link.l1 = "돈 도밍고... 삼촌께서 그런 결정에 반대하실 수도 있지 않을까?";
			link.l1.go = "noble_31";
		break;
		
		case "noble_31":
			dialog.text = "나는 그 자가 동의하든 말든 신경도 안 써! 나는 마르케스 도밍고 오르티스 알발라테고, 루이스 오르티스는 고작 세입자일 뿐이야, 그것도 예전 세입자였지! 그리고 그는...";
			link.l1 = "진정하시오, 나리. 당신은 여기서 낯선 얼굴이고, 나는 네덜란드 허가증을 가진 프랑스인인데... 스페인 해적 단속대와도 과거가 좀 복잡하오. 당신의 삼촌 말인데, 이 마을은 거의 그 사람이 주인이나 다름없소. 경비병들이나 현지 총독도 생각해 보시오. 정말로 그들이 당신 편을 들어줄 거라 생각하오?";
			link.l1.go = "noble_32";
		break;
		
		case "noble_32":
			dialog.text = "네가 핵심을 제대로 찔렀군... 아마도... 아니. 스페인 병사들이 감히 귀족에게 손을 대는 일은 없지! 내 삼촌이 용기가 있다면 나에게 도전해 보라고 해!";
			link.l1 = "그래도 나는 다른 길을 제안하네. 법정은 어떤가?";
			link.l1.go = "noble_33";
		break;
		
		case "noble_33":
			dialog.text = "하! 네 말이 맞아, 카를로스. 이제 정식 당국과 이야기하러 가자. 내 삼촌이 밀수업자들과 거래한 내용을 노트에 정확히 적어둔 게 실수였지. 그는 그들에게서 노예를 아주 싸게 샀어. 이 장부들이 우리에게 큰 도움이 될 거야. 그 자식이 감옥에 처박혀 있는 동안 나한테 해를 끼칠 수 있을 거라곤 전혀 생각하지 않아. 가자! 포르토벨로로!\n";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PrepareUncle");
		break;
		
		case "noble_34":
			//PlaySound("Voice\English\LE\Domingo\Domingo_04.wav");
			dialog.text = "이건 더럽고 뻔뻔한 거짓말일 뿐이야! 감히 내 부모님의 좋은 이름을 그 비열한 입으로 더럽히다니! 저주받을 놈, 반드시 대가를 치르게 하겠다! 칼을 뽑아라, 이 암살자 놈아!";
			link.l1 = "";
			link.l1.go = "noble_35";
		break;
		
		case "noble_35":
			DialogExit();
			sld = CharacterFromID("FMQP_Uncle");
			sld.Dialog.currentnode = "uncle_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noble_36":
			PlaySound("Voice\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "루이스 아저씨는 그의 영혼을 위해 마련된 적절한 곳, 지옥에 있지... "+pchar.name+", 수호천사가 당신을 내게 보냈군! 이 악당의 말을 믿지 않아서 정말 다행이야. 솔직히 말해서, 네가 날 여기 혼자 두고 이 카날라와 싸우게 둘까 봐 걱정했었지\n그래 "+GetAddress_Form(NPChar)+", 나도 완벽하진 않지만 이건... 이 더러운 거짓말, 내가 해적들을 고용해서 내 부모님을 죽였다는 소문이라니! 나에게 이 모든 죄를 뒤집어씌우다니... 이런! 쯧, 당연한 운명이지.";
			link.l1 = "무사히 도착해서 다행이오, Don Domingo. 이제 어떻게 할까요? 스페인 법에 걸린 건 아니겠지?";
			link.l1.go = "noble_37";
		break;
		
		case "noble_37":
			dialog.text = "법하고? 하하! 아니, "+pchar.name+", 이 훌륭한 장부를 보여주겠어. 내 삼촌의 밀수 작전이 모두 기록되어 있지. 내 목숨을 노린 여러 번의 시도도 잊지 마. 방금 전 마지막 시도에는 증인도 아주 많아졌으니. 걱정하지 마라, "+GetAddress_Form(NPChar)+". 여기가 내 마을이니, 이제 모두에게 보여줄 때다!";
			link.l1 = "조심해서 움직이시오, 나리. 그들이 당신의 작고한 삼촌보다 당신을 더 좋게 생각하게 하시오.";
			link.l1.go = "noble_38";
		break;
		
		case "noble_38":
			dialog.text = "그게 내 계획이야, 카피탄. 하지만 감히 나에게 대적하는 놈한테는 절대 자비를 베풀지 않을 거다. 진심으로 고마움을 전하지. "+pchar.name+"! 제발, 선술집에 가서 좀 쉬고, 술도 한두 잔 해. 나도 같이 하고 싶지만, 네 말이 맞았어. 이제는 내가 직접 농장을 관리할 때가 된 것 같아. 내일 여기서 다시 보자, 선장!";
			link.l1 = "알겠습니다, Don Domingo. 내일 뵙겠습니다.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PlantatonPause");
		break;
		
		case "noble_39":
			DelLandQuestMark(npchar);
			PlaySound("VOICE\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "아, 여기 있었군, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "잘 지내십니까, Domingo 돈? 당신의 플랜테이션은 어떻습니까?";
			link.l1.go = "noble_40";
		break;
		
		case "noble_40":
			dialog.text = "플랜테이션은 훌륭하지만, 돈은 그렇지 않네 – 알고 보니 내 친애하는 삼촌이 모든 자금을 카르타헤나 은행으로 옮기고 있었더군. 내 금을 되찾으려면 변호사들이 한참 걸릴 거야. 하지만 괜찮아, 내가 알아서 처리할 수 있어. 너무 슬퍼하지 마, 선장. 너의 고귀함과 정직함, 그리고 우정에 대한 보상은 반드시 지킬 테니!";
			link.l1 = "당신 편에서 싸울 때는 보상 같은 건 생각도 안 했소, 나리...";
			link.l1.go = "noble_41";
		break;
		
		case "noble_41":
			dialog.text = "그건 알고 있소, 선장님, 그리고 그 점이 선장님의 인품을 잘 보여주오! 선행에는 반드시 보상이 따라야 하오. 지금 당장은 돈이 없지만, 내 농장에서 나온 상품을 선장님의 배에 실으라고 명령하겠소. 커피 말이오, 아주 많은 양이네. 분명 큰 이익을 남기고 팔 수 있을 것이오.";
			link.l1 = "오! 이거 괜찮은데...";
			link.l1.go = "noble_42";
		break;
		
		case "noble_42":
			dialog.text = "게다가, 나한테는 별로 쓸모 없지만 너 같은 선원에게는 아주 귀한 물건 몇 개가 있지. 좋은 망원경 하나랑 부적 세 개야. 받아라, 이제 전부 네 거다.";
			link.l1 = "감사하오!";
			link.l1.go = "noble_43";
		break;
		
		case "noble_43":
			Log_Info("You have received a good spyglass");
			Log_Info("You have received three amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "마지막으로, 나의 한없는 감사의 표시로 이 레이피어를 드리오. 이 검은 내게 큰 도움이 되었소; 이제는 그대에게 더 큰 힘이 되길 바라오. 이 검을 보며 그대의 좋은 스페인 친구, 도밍고 알발라테 후작을 기억해 주시오!";
			link.l1 = "정말 감사합니다, 나리! 이렇게까지 기대하지는 않았는데...";
			link.l1.go = "noble_44";
		break;
		
		case "noble_44":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "이제, 아아, 작별을 고해야겠군. 포르토벨로에 가서 총독을 뵙고, 그 다음엔 카르타헤나로 가야지...\n요약하자면, 내 한가로운 삶은 끝났고, 이제 어른답게 살아야 할 때가 온 거야.";
			link.l1 = "이제 훨씬 똑똑해졌군...";
			link.l1.go = "noble_45";
		break;
		
		case "noble_45":
			dialog.text = "그렇지. 즐거웠어, "+GetAddress_Form(NPChar)+"! 언젠가 나를 찾아오게나. 바다에서 행운을 빌지!";
			link.l1 = "당신의 플랜테이션 사업도 잘되길 바라오, 돈 도밍고!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_ReceiveReward");
		break;
		
		case "noble_46":
			PlaySound("Voice\English\YoungMan02.wav");
			dialog.text = "에이, 우리가 늦었군, 나리! 아쉽게도 우리 좋은 옛 삼촌께서 이미 서류를 싹 정리해버렸네. 누가 산토도밍고 이야기를 전해준 모양이고, 삼촌은 미리 대비한 것 같아... 하지만 이대로 끝내진 않을 거야! 포르토벨로의 총독을 찾아가 삼촌을 상대로 법적 절차를 밟아야겠어. 내 재산을 삼촌이 마음대로 하는 건 이제 질렸거든.";
			link.l1 = "좋은 결정이야.";
			link.l1.go = "noble_47";
		break;
		
		case "noble_47":
			dialog.text = "감사드리고 싶소, 선장님! 정말 즐거웠소! 내 감사의 표시로 이 레이피어를 드리겠소. 이 검은 나를 잘 지켜줬으니, 이제는 선장님을 더 잘 지켜주길 바라오. 이 검을 볼 때마다 당신의 좋은 스페인 친구, 도밍고 알발라테 후작을 기억해 주시오!";
			link.l1 = "정말 감사합니다, 나리! 이렇게까지 기대하지는 않았어요...";
			link.l1.go = "noble_48";
		break;
		
		case "noble_48":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			dialog.text = "이제, 아쉽지만 그대와 작별을 고해야겠군. 포르토벨로로 가야 하네. 내 한가로운 시절은 끝났으니, 이제 어른답게 살아야 할 때지. 바다에서 행운을 빌겠네!";
			link.l1 = "삼촌과 잘 해결하시길 빕니다, 도밍고 나리! 분명 이기실 거라 믿어요!";
			link.l1.go = "noble_49";
		break;
		
		case "noble_49":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 40.0);
			pchar.questTemp.FMQP = "fail";
			AddQuestRecord("FMQ_Portpax", "13");
			CloseQuestHeader("FMQ_Portpax");
			sld = &Locations[FindLocation("PortoBello_Plantation")];
			sld.soldiers = true;
		break;
		
		case "uncle":
			PlaySound("Voice\English\OliverTrast02.wav");
			if (pchar.sex == "woman") { dialog.text = "내가 딱 맞춰 도착한 것 같군. 내 말썽꾸러기 조카랑 그 새 애인, 선장 "+GetFullName(pchar)+"... 그래, 그래, "+GetSexPhrase("젊은이","아가씨")+", 놀라지 마시오 — 내가 자네에 대해 좀 알아봤거든."; }
			else { dialog.text = "딱 맞춰 도착한 것 같군. 내 말썽꾸러기 조카와 그의 수호천사, 선장\n "+GetFullName(pchar)+"... 그래, 그래, "+GetSexPhrase("젊은이","아가씨")+", 놀라지 마라 — 내가 너에 대해 좀 알아봤거든."; }
			link.l1 = "루이스 오르티스?";
			link.l1.go = "uncle_1";
		break;
		
		case "uncle_1":
			dialog.text = "맞아, 선장. 하지만 나머지는 전부 틀렸소. 남의 집안일에 코를 들이밀지 마시오. 자네가 누구를 감싸고 있는지 전혀 모르는구먼. 내 방탕한 조카 도밍고는 쓸모없는 난봉꾼이자, 모든 선술집과 창관의 단골 1번 손님이오. 눈에 띄는 여자마다 침대에 들거나, 적어도 들려고 애쓰지. 내가 매달 그의 집세를 내주지만, 며칠 만에 다 탕진하고는 항상 더 달라고 조르지. 또, 또, 또. 그의 끊임없는 못된 행동 때문에 그의 어머니, 내 누이까지 미쳐버렸소.\n들리는 소문에 따르면, 이 못된 놈이 영국 사략선 몇 놈을 고용해 리카르도 알발라테 후작의 배를 습격하게 했다고 하더군. 그 배는 후작과 내 소중한 누이까지 함께 가라앉았지. 도밍고는 우리 집안 돈이 그렇게도 갖고 싶어서, 살인까지도 서슴지 않았던 거요... 안타깝게도, 이 악당을 교수대에 올릴 만한 증거를 충분히 찾아내지 못했소.";
			link.l1 = "";
			link.l1.go = "uncle_2";
		break;
		
		case "uncle_2":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_34";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "uncle_3":
			if (pchar.sex == "woman") { dialog.text = "내 사랑하는 조카는 여전히 자기 세상에 빠져 있군. 시끄러운 소리, 부딪히는 칼, 부딪히는 잔소리만 가득하고, 정작 알맹이는 없지. 나로서는 그 아이에게서 뭘 보시는지 모르겠소, 세뇨리타, 그는..."; }
			else { dialog.text = "내 사랑하는 조카놈, 언제나 그렇듯 자기 세상에 빠져 있군. 시끄러운 소리, 칼 부딪히는 소리, 잔 부딪히는 소리만 요란하지, 정작 알맹이는 없지. 도대체 저런 못난 녀석을 도와주겠다고 마음먹게 만든 게 뭔지 모르겠구나...\n"; }
			link.l1 = "내가 알기로는, 조카에 대한 증거를 찾는 데 실패하자 암살자들을 보내기 시작했다지. 그냥 소송만 걸었어도 됐을 텐데.";
			link.l1.go = "uncle_4";
		break;
		
		case "uncle_4":
			dialog.text = "거짓말하지 마. 여기 도밍고는 적을 한도 끝도 없이 만들었지. 지나온 길마다 버림받은 연인들과 바람맞은 남편들이 줄을 섰다니까. 어떻게 지금까지 살아남았는지 궁금할 정도야! 직접 물어봐, 결혼식을 몇 번이나 망쳤는지? 모욕당한 약혼자들을 몇 명이나 다치게 하거나 죽였는지?\n";
			link.l1 = "그의 하인 우고...";
			link.l1.go = "uncle_5";
		break;
		
		case "uncle_5":
			dialog.text = "아, 우고! 저놈들 중에서도 제일 악질이지! 우고는 자기 방탕한 주인을 정말로 좋아했어. 주인의 모든 죄악도 우고한테는 그냥 어린애 장난에 불과했지. 기억해,\n "+GetSexPhrase("젊은이","아가씨")+", 집안일은 가족만이 할 수 있는 거야. 쓸데없이 캐묻거나 참견하면 큰일을 당하게 될 거다.";
			link.l1 = "이제 나를 협박하겠다는 거냐.";
			link.l1.go = "uncle_6";
		break;
		
		case "uncle_6":
			int icpy = GetOfficersQuantity(pchar);
			iTotalTemp = 10000+10000*icpy;
			dialog.text = "경고다. 잘 들어, 선장: "+GetSexPhrase("너무 지나쳤지만, ","")+"내가 너를 적으로 보지 않으니—그저 잘못 이끌린 사람일 뿐이라 생각하니—제안을 하나 하지. 돌아가서 떠나라. 피를 흘리고 싶지 않다. 우리 집안 문제는 너 없이 해결하겠다. "+GetSexPhrase("내 조카와 관련된 모든 비용을 내가 보상할 준비가 되어 있소:","좀 더 쉽게 해주려고, 내가 너한테 돈을 줄 준비가 되어 있어:")+" "+FindRussianMoneyString(iTotalTemp)+" 현금이야. 가져가고 이곳은 잊어버려. 그렇지 않으면 내 경비병들이 널 그냥 죽여버릴 거다.";
			link.l1 = "'가족이 먼저'라는 게 내 신조지. 그럼 내 알 바 아니니까, 돈이나 넘기고 '신의 가호를' 받으라고 해.";
			link.l1.go = "uncle_7";
			link.l2 = "네 얘기는 네 농장의 비료보다 더 구려. 돈 도밍고가 성인은 아닐지 몰라도, 너, 나리, 악마구나!";
			link.l2.go = "uncle_8";
		break;
		
		case "uncle_7":
			AddMoneyToCharacter(pchar, iTotalTemp);
			dialog.text = "당신이 이성적인 사람인 줄 알았소. 돈이나 챙기고, 아디오스, 카피탄. 앞으로는 남의 더러운 속사정 뒤지지 말도록 해 - 고마워하는 사람 아무도 없으니까.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_UncleExit");
		break;
		
		case "uncle_8":
			if (pchar.sex == "woman") {dialog.text = "이제 알겠군. 너는 내 조카랑 똑같아 — 어리석고 무모한 계집애지. 그 녀석이랑 딱 어울리겠어. 이제 둘 다 혼 좀 나야겠다!";}
			else {dialog.text = "이제 알겠군. 너도 내 조카랑 다를 바 없구나 — 어리석고 건방진 녀석이지! 둘 다 제대로 혼내줄 때가 됐다!";}
			link.l1.go = "exit";
			AddDialogExitQuest("FMQP_UncleFight");
		break;
		
		case "ugo":
			pchar.quest.FMQP_SantoDomingoOver.over = "yes";
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = TimeGreeting()+" "+GetAddress_Form(NPChar)+". 무엇을 도와드릴까요?";
			link.l1 = "안녕하세요. 실례합니다만, 여기가 도밍고 알발라테 나리의 댁입니까?";
			link.l1.go = "ugo_1";
		break;
		
		case "ugo_1":
			dialog.text = "그래, 여기가 알발라테 집이야. 소박하지만 편안하지. 내 이름은 우고고, 어린 주인님을 모시고 있어. 그분을 찾아온 거야?";
			link.l1 = "그래, 나리. 돈 도밍고가 얼마 전에 나를 자기 집으로 초대했어. 아주 설득력 있더군. 그를 만나도 되겠나?";
			link.l1.go = "ugo_2";
		break;
		
		case "ugo_2":
			dialog.text = "아아, 내 좋은 "+GetSexPhrase("기사 나리","아가씨")+", 돈 도밍고 나리는 지금 집에 없소. 사실 나도 그 말썽꾸러기 녀석이 어디 있는지 알고 싶을 지경이오... 에이, 실례, 젊은 나리. 그에게 무슨 볼일이 있으시오?";
			link.l1 = "음... 나는 우연히 돈 도밍고를 도왔어. 그가 포르토프랭스 선술집에서 두 악당에게 습격당했거든. 네 주인께서 그놈들... 뭐라고 불렀더라... 말디타 카나야, 그놈들한테서 스스로를 지키는 걸 도왔지. 돈 도밍고가 조사가 끝나면 여기로 찾아오라고 초대했어. 이제쯤이면 모든 일이 정리됐을 거라 생각해서, 집에서 그를 만날 줄 알았지.";
			link.l1.go = "ugo_3";
		break;
		
		case "ugo_3":
			dialog.text = "마드레 데 디오스! 여기서 무시무시한 이야기를 하고 있군! 나는 당장 사령관을 만나야겠어 – 지금 돈 도밍고가 겪고 있는 위험에 대해 경고해야 하니까! "+UpperFirst(GetAddress_Form(NPChar))+", 너는 가야 하고 나는 서둘러야 해!";
			link.l1 = "진정해, 우고. 네 젊은 주인님은 무사해. 서류도 다 갖췄다고 하더군. 이미 풀려나야 했으니 내가 여기 온 거야. 곧 그를 볼 수 있을 거라 믿어.";
			link.l1.go = "ugo_4";
		break;
		
		case "ugo_4":
			dialog.text = "오! 어떻게 그럴 수가 있지? 그 순진한 소년이... 게다가 개구리나 먹는 프랑스 놈들 손에?! 목숨까지 노리는 라드로네들이 있다는 건 말할 것도 없고? 안 되겠어, 내가 직접 사령관을 만나야겠어! "+UpperFirst(GetAddress_Form(NPChar))+", 제발 가!";
			link.l1 = "알았어, 알았어, 그렇게 들이대지 마. 나 간다.";
			link.l1.go = "ugo_exit";
			link.l2 = "나리, 왜 그렇게 긴장하시오? 이미 말씀드렸듯이 당신 주인에게는 아무런 위험이 없소. 여기 머물며 도밍고 나리의 도착을 기다리게 해주시오. 긴 항해로 매우 피곤하니 당신의 환대를 부탁하오. 시원한 물과 목의 소금기를 씻어낼 뜨거운 목욕을 하고 싶소. 그 후에는 지역 주둔지에 가서 원하는 대로 하시오.";
			link.l2.go = "ugo_5";
		break;
		
		case "ugo_exit":
			DialogExit();
			LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "houseSp4", "FMQP_SDMFail");
		break;
		
		case "ugo_5":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", 당장 이 집에서 나가!";
			link.l1 = "우고, 하인 주제에 신사 손님에게 이런 식으로 말해도 되는지 정말 의심스럽군. 그리고 돈 도밍고 나리께서 자기 목숨을 구해준 사람을 이렇게 대하는 걸 좋아하실지도 의문이야!";
			link.l1.go = "ugo_6";
		break;
		
		case "ugo_6":
			dialog.text = "정말이야? (위층을 향해 외치며) 얘들아, 내려와! 문제가 생겼어!";
			link.l1 = "뭐야, 이게?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_SantoDomingoFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
