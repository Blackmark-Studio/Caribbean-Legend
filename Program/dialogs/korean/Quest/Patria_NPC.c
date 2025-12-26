// диалоги НПС по квесту НСО
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "뭘 찾고 있지?";
			link.l1 = "아무것도 아니다.";
			link.l1.go = "exit";
		break;
		
		// инспектор Ноэль Форже
		case "noel":
			dialog.text = "만나서 반갑소, 선장!";
			link.l1 = "저도 만나서 반갑습니다, Forget 나리. 이 외딴 곳에서 본국에서 온 손님을 만나는 일은 드문 일이죠...";
			link.l1.go = "noel_1";
		break;
		
		case "noel_1":
			DialogExit();
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_3";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "noel_2":
			dialog.text = "이번 항해 동안 선장님의 배에 탈 수 있게 되어 기쁩니다. 드 푸앵시 기사께서 선장님에 관한 흥미로운 이야기들을 많이 들려주셨지요.\n식당에서 저녁 식사를 마치고 나면 나눌 이야깃거리가 아주 많을 것이라 확신합니다. 와인 한 잔도 곁들이면 좋겠군요.";
			link.l1 = "나는 언제든지 따뜻하게 이야기 나누는 거 좋아하지, 특히 배불리 먹었을 때는 더 그렇지. 기꺼이 당신의 동행이 되어 드리겠소, 남작 나리. ";
			link.l1.go = "noel_3";
		break;
		
		case "noel_3":
			dialog.text = "완벽하군. 우리가 식민지에 가면, 자네가 총독에게 안내해 주었으면 하네. 내가 직접 그분께 무엇을 해야 하는지 설명할 것이네. 자네는 내가 볼일을 마칠 때까지 기다리면 되네. 약속하지?";
			link.l1 = "그래, Forget 나리. 배에 온 걸 환영하오!";
			link.l1.go = "noel_4";
		break;
		
		case "noel_4":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 12.0);
		break;
		
		case "noel_5":
			dialog.text = "토르투가는 작은 식민지입니다, 선장님. 이 섬에서 필요한 모든 것을 점검하려면 사흘쯤 걸릴 것 같습니다.";
			link.l1 = "알겠습니다, 남작 나리. 사흘 뒤에 여기로 모시러 오겠습니다. 행운을 빕니다!";
			link.l1.go = "noel_6";
		break;
		
		case "noel_6":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "Patria_VisiterTortuga");
		break;
		
		case "noel_7":
			dialog.text = "토르투가에서 할 일은 끝났으니, 이제 닻을 올릴 시간이야.";
			link.l1 = "알겠습니다, 남작님. 즉시 출항하겠습니다.";
			link.l1.go = "noel_8";
		break;
		
		case "noel_8":
			DialogExit();
			Patria_VisiterTortugaSail();
		break;
		
		case "noel_9":
			dialog.text = "그래, 그래, 우리는 반드시 이 일을 캡스터빌에 보고하겠소. 이렇게 중요한 식민지가 정복당할 위협이라니... 상상도 할 수 없는 일이오. 내가 직접 슈발리에 드 푸앵시가 엄격하고 무자비한 조치를 취하도록 하겠소! 선장, 나는 이 섬에 일주일 머물 것이오; 이곳에는 플랜테이션이 많으니 시간이 좀 걸릴 거요.";
			link.l1 = "알겠습니다, 남작 나리. 7일 후에 총독 관저 앞에서 기다리고 있겠습니다. 즐기시고 너무 무리하지 마십시오!";
			link.l1.go = "noel_10";
		break;
		
		case "noel_10":
			DialogExit();
			DoQuestReloadToLocation("PortPax_town", "reload", "reload3", "Patria_VisiterPortPax");
		break;
		
		case "noel_11":
			dialog.text = "거기 계셨군요, 선장님. 히스파니올라에서의 제 일은 끝났으니, 이제 닻을 올릴 때입니다.";
			link.l1 = "알겠습니다, 남작 나리. 곧바로 출항하겠습니다.";
			link.l1.go = "noel_12";
		break;
		
		case "noel_12":
			DialogExit();
			Patria_VisiterPortPaxSail();
		break;
		
		case "noel_13":
			dialog.text = "선장님, 이 섬이 낯이 익은데요. 세인트 크리스토퍼 아니오?";
			link.l1 = "그래요, 남작 나리, 맞습니다. 거의 다 왔습니다.";
			link.l1.go = "noel_14";
		break;
		
		case "noel_14":
			dialog.text = "거의 다 왔다고?! 우리 생마르탱에도 들르기로 하지 않았어? 거기도 프랑스 식민지 중 하나잖아.";
			link.l1 = "신트마르턴 말입니까? 네덜란드 식민지입니다, 포르게 나리.";
			link.l1.go = "noel_15";
		break;
		
		case "noel_15":
			dialog.text = "그래? 파리에서는 그게 프랑스 것이라고 여겼는데. 왜 그렇지?";
			link.l1 = "모르겠습니다, 남작 나리. 제가 처음 이 제도에 발을 들인 이후로 신트마르턴은 줄곧 네덜란드 식민지였습니다. 제가 모르는 무언가가 있을지도 모르지요. 이 일에 관해서는 슈발리에 드 푸앵시와 상의해 보시는 게 좋겠습니다.";
			link.l1.go = "noel_16";
		break;
		
		case "noel_16":
			dialog.text = "좋소, 선장님, 그렇게 하시지요. 어차피 우리는 거의 캡스터빌에 다 왔으니.";
			link.l1 = "...";
			link.l1.go = "noel_17";
		break;
		
		case "noel_17":
			DialogExit();
			Island_SetReloadEnableGlobal("Nevis", true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			pchar.quest.Patria_visiter_fin.win_condition.l1 = "location";
			pchar.quest.Patria_visiter_fin.win_condition.l1.location = "Charles_Roomtownhall";
			pchar.quest.Patria_visiter_fin.function = "Patria_VisiterFin";
			pchar.questTemp.Patria = "epizode_2_return";
		break;
		
		case "noel_18":
			dialog.text = TimeGreeting()+", 선장님. 뵙게 되어 반갑습니다. 승진하셨다고 들었는데, 축하드립니다! 사실을 말씀드리자면, 당신은 드 푸앵시 휘하에서 가장 현명하고 재능 있는 장교 중 한 명이십니다.";
			link.l1 = "감사합니다, 나리.";
			link.l1.go = "noel_19";
		break;
		
		case "noel_19":
			dialog.text = "마침내 이제 한 개의 식민지, 생마르탱만 남았군. 솔직히 말해서, 이런 여행도 이제 지겹네. 이번 시찰을 끝내고 다음 프랑스령 서인도 무역 원정 준비를 시작할 수 있으면 좋겠어. 닻을 올릴 준비는 다 됐나?";
			link.l1 = "예, 남작 나리. 타십시오.";
			link.l1.go = "noel_20";
		break;
		
		case "noel_20":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBaron", 5.0);
		break;
		
		case "noel_21":
			dialog.text = "선장님, 방금 무슨 일이 있었는지 말씀해 주실 수 있습니까? 이게 전쟁을 의미하는 겁니까? 도대체 왜 우리가 네덜란드 놈들에게 거의 침몰당할 뻔했습니까?";
			link.l1 = "남작 나리, 저도 아무것도 이해하지 못하겠습니다! 분명히 무슨 오해가 있는 게 틀림없습니다.";
			link.l1.go = "noel_22";
		break;
		
		case "noel_22":
			dialog.text = "선장님, 이 '오해'에는 분명 이름이 있을 겁니다! 바로 피터 스토이브산트, 생마르탱의 이른바 '임차인'이자 우리 친애하는 슈발리에 드 푸앵시의 동료지요!";
			link.l1 = "저도 모르겠습니다, 남작 나리. 서둘러 캡스터빌로 가서 이 일을 총독께 보고하는 게 좋겠습니다.";
			link.l1.go = "noel_23";
		break;
		
		case "noel_23":
			dialog.text = "의심할 여지 없이, 바로 그렇게 할 거요! 그리고 나는 반드시 해명을 요구하겠소! 네덜란드인에게 섬을 빌려준 게 큰 실수라는 걸 알았지! 누가 우리를 쫓아오기 전에, 선장, 이곳을 최대한 빨리 떠납시다!";
			link.l1 = "정확합니다, 나리 ...";
			link.l1.go = "noel_24";
		break;
		
		case "noel_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBack", 5.0);
		break;
		
		case "noel_25":
			dialog.text = "나리, 먼저 승진을 축하드립니다! 저는 몽세뉴르 드 푸앵시께서 당신께 부제독의 계급을 수여하기로 결정하신 것을 진심으로 지지했습니다. 이 칭호는 정말로 당신께 어울립니다! 이제, 저는 최근에 생마르탱에서 돌아왔습니다. 필립스버그의 창고에서 우리가 조사를 실시했고, 모든 네덜란드 상품은 압수되어 이제 프랑스 국고의 소유가 되었습니다. 작전의 지휘관이신 당신께도 전리품의 일부가 할당되었습니다. 저는 슈발리에와 마찬가지로 이것이 공정하다고 생각합니다. 당신의 물품은 세인트 크리스토퍼 상점의 창고로 옮겨졌으니, 원하실 때 언제든 찾아가시면 됩니다.";
			link.l1 = "감사합니다, 남작 나리. 물건들은 잠시 그곳에 두십시오. 제가 퀴라소에서 돌아오면 가져가겠습니다.";
			link.l1.go = "noel_26";
		break;
		
		case "noel_26":
			dialog.text = "다음 원정에서도 행운을 빕니다, 부제독님! 반드시 승리하여 그 악당 스튜이베산트를 정의롭게 처벌하고 돌아오실 것이라 확신합니다.";
			link.l1 = "...";
			link.l1.go = "noel_27";
		break;
		
		case "noel_27":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_start";
			AddQuestRecord("Patria", "58");
			pchar.questTemp.Patria.GoodsSM = "true";
		break;
		
		case "noel_28":
			dialog.text = "여기 누가 왔나! 샤를 드 모르 부제독이군! 만나서 반갑소! 포르토프랭스에는 무슨 일로 오셨소?";
			link.l1 = "저도 만나서 반갑습니다, 남작 나리. 저는 임무 때문에 왔습니다; 제레미 데샹 뒤 뮈사카 나리께 예의상 방문을 드려야 했거든요...";
			link.l1.go = "noel_29";
		break;
		
		case "noel_29":
			dialog.text = "이 만남은 정말 행운이로군. 오랫동안 직접 만나기를 기다려 왔소. 당신과 이야기하고 싶지만, 여기서는 곤란하오.";
			link.l1 = "그럼 선술집으로 가자, 어때?";
			link.l1.go = "noel_30";
		break;
		
		case "noel_30":
			DialogExit();
			FreeSitLocator("PortPax_tavern", "sit_base1");
			DoQuestReloadToLocation("PortPax_tavern", "sit", "sit_base1", "Patria_CondotierTavern");
		break;
		
		case "noel_31":
			LAi_SetSitType(pchar);
			dialog.text = "여기에는 듣는 귀가 없으니, 마음껏 이야기해도 되겠군...";
			link.l1 = "듣고 있소, 남작 나리.";
			link.l1.go = "noel_32";
		break;
		
		case "noel_32":
			dialog.text = "부제독 나리, 당신은 명예로운 분으로 보이오. 그렇게 용감한 해군 장교라면 당연히 그래야 하지...";
			link.l1 = "흠... 나는 자네 말을 완전히 이해하지 못하겠군, 나리...";
			link.l1.go = "noel_33";
		break;
		
		case "noel_33":
			dialog.text = "드 모르 나리, 묻고 싶은 게 있습니다. 당신의 주군인 필리프 드 푸앵시 총독에 대해 어떻게 생각하십니까?";
			link.l1 = "장교의 임무는 상관을 생각하는 것이 아니라, 명령을 따르는 것이다.";
			link.l1.go = "noel_34";
		break;
		
		case "noel_34":
			dialog.text = "아, 그만두시오, 부제독 나리. 여긴 병영도 아니고, 드 푸앵시의 관저도 아니잖소. 이렇게 말하겠소: 드 푸앵시 나리가... 권력을 남용한다고 생각하지 않소? 난 아직도 생마르탱 요새의 대포 때문에 우리가 거의 침몰할 뻔했던 걸 잊지 못하겠소. 네덜란드 놈들의 배신에도 분명 이유가 있었을 거요.";
			link.l1 = "그들은 그 섬을 정복하고 싶어 했어.";
			link.l1.go = "noel_35";
		break;
		
		case "noel_35":
			dialog.text = "그래, 그래. 하지만 내가 점검하기로 결심한 바로 그 순간에 왜 이런 일이 일어난 거지? 왜 한 달 전에 아니면 두 달 후에 일어나지 않았을까? 이건 우연이라고는 믿을 수 없소, 나리. 의심 가는 점은 없소? 우리 둘 다 그곳에서 목숨이 걸려 있었잖소.";
			link.l1 = "저는 매일 목숨을 걸고 있습니다, 포르게 나리. 당신도 그 점을 이해하고 계시겠지요...";
			link.l1.go = "noel_36";
		break;
		
		case "noel_36":
			dialog.text = "그대의 용기는 의심할 여지가 없소. 하지만 내가 말하고 싶었던 건 그게 아니오. 있지... 그대가 해방한 생마르탱에서 일을 하던 중, 섬 깊은 곳에 있는 어떤 광산에 대해 현지인들이 수군거리는 소리를 여러 번 들었소. 내가 그들에게 물어보려 했지만, 다들 바보처럼 굴더군. 두려워하는 게 분명했소... 내가 별로 신뢰받지 못하는 것 같았지만, 오히려 그게 내 의심을 더 키웠지. 혹시 이 수수께끼 같은 광산이 모든 일의 원인일 수도 있지 않겠소, 드 모르 나리? 전쟁이란 결국 금 때문에 벌어지는 것 아니오?\n";
			link.l1 = "군도에는 수많은 광산이 있지. 대부분은 다 고갈돼서 쓸모가 없어졌어. 내가 아는 한 제대로 운영되는 금광은 하나뿐인데, 남아메리카 본토의 스페인 놈들이 소유하고 있지. 하지만 생마르탱에서 금을 캔다는 얘기는 들어본 적 없어.";
			link.l1.go = "noel_37";
		break;
		
		case "noel_37":
			dialog.text = "말재주가 뛰어나시군요, 부제독 나리! 이해합니다. 저를 믿지 못하시겠지요. 저도 이곳에 온 지 얼마 안 됐으니까요... 드 모르 나리, 하지만 저는 파리에서 영향력 있는 사람입니다. 재무부 장관이 제 절친이고, 저는 왕을 정기적으로 뵙습니다. 제 권위는 필리프 드 푸앵시보다 훨씬 큽니다. 물론 형식적으로는 그렇지요. 이곳에서는 총독이 가장 큰 권한을 가졌으니까요. 하지만 솔직히 말하자면, 이 식민지에서는 결국 힘이 곧 법입니다.";
			link.l1 = "나도 거기에 전적으로 동의해.";
			link.l1.go = "noel_38";
		break;
		
		case "noel_38":
			dialog.text = "하지만 파리에서는 아니오. 그곳에서 가장 영향력 있는 사람들은 국왕과 재무장관... 그리고 내 절친이오. 드 모르 나리, 당신은 뛰어난 군인이지만, 내 생각에 필리프 드 푸앵시는 당신을 자신의 사적인 목적으로 이용하고 있소. 당신은 영리하니, 의심이 들 법도 하오. 나를 믿으시오. 나는 파리 당국의 전적인 익명 보장과 지원을 약속하오. 내 작위를 걸고 맹세하오.";
			link.l1 = "***푸앵시에게 충성을 지켜라***";
			link.l1.go = "noel_39"; // развилка
			link.l2 = "***바론 포르게 편에 서기***";
			link.l2.go = "noel_53";
		break;
		
		case "noel_39":
			dialog.text = "";
			link.l1 = "이해하오, Forger 나리. 이곳의 사고방식에 익숙하지 않은 이라면 드 푸앵시의 행동이 정말 이상하게 보일 수도 있지. 나 역시 처음 군도에 도착했을 때, 이곳에서 벌어지는 일들에 진심으로 충격을 받았소. 아직도 처음 들었던 말을 기억하오. '방비되지 않은 스페인 배를 만나면, 승선을 시도해도 된다.' 배신, 배반, 기만—이곳에서는 어디에나 있소. 해적질, 약탈, 강도...";
			link.l1.go = "noel_40";
		break;
		
		case "noel_40":
			dialog.text = "";
			link.l1 = "우리는 유럽에서는 스페인과 평화 상태다. 하지만 여기서는, 우리가 사나운 적이지. 네덜란드 놈들은 오늘은 친절하고 해가 없어 보여도, 내일이 되면 회사 관리가 갑자기 수입 금지라며 네 물건을 압수해 버린다. 네가 알 길도 없었는데도 말이지. 영국 장교는 대놓고 해적질을 하며 회사 배를 침몰시키고, 회사는 또 다른 악당을 고용해서 유령선으로 위장하게 하고 영국 상인들을 공포에 떨게 하지...\n";
			link.l1.go = "noel_41";
		break;
		
		case "noel_41":
			dialog.text = "";
			link.l1 = "이 늑대 소굴에서는, 이 모든 것에 익숙하지 않은 이들에게는 명확하지 않을 수 있는 이상한 결정을 내릴 때가 있지. 그리고 자네에게 수상해 보이는 일이 사실은 유일하게 옳은 행동일 때도 있네. 여러 개의 의자에 동시에 앉으면서도 본국에 이익을 보내는 건 쉽지 않은 일이야. 드 푸앵시 기사 나리는 이걸 완벽하게 해내지. 그는 노련한 행정가이자 선견지명이 있는 정치가야. 물론 실수할 때도 있겠지만, 우리 모두 인생에서 한 번쯤은 그러지 않나...";
			link.l1.go = "noel_42";
		break;
		
		case "noel_42":
			dialog.text = "";
			link.l1 = "그리고 너는 모든 것과 모든 사람을 상대해야 해. 온 신세계가 자기들 것이라 믿는 스페인 놈들의 야심, 네덜란드 상인들의 탐욕, 그리고 영국 놈들의 냉정한 신중함과 무자비한 잔혹함까지도 말이지. \n심지어 해적들까지도 상대해야 해.";
			link.l1.go = "noel_43";
		break;
		
		case "noel_43":
			dialog.text = "해적들이랑?!";
			link.l1 = "그래, 제대로 들었어. 네덜란드랑 영국이 해적들과 적극적으로 협력하고 있지... 물론 비공식적으로 말이야. 코스트의 형제단은 이 지역에서 어떤 나라든 맞설 수 있는 강력한 세력이야; 만나는 모든 이들과 끊임없이 충돌하고, 그 누구도 그들을 막을 수 없어. 그나마 덜 위험한 이유는 놈들이 흩어져서 각자 이익을 위해 움직인다는 점이지. 혹시 토르투가의 전 총독 르바쇠르가 사실상 해적들만 믿고 나라 안에 또 다른 나라를 만들었다는 거 알고 있었나?";
			link.l1.go = "noel_44";
		break;
		
		case "noel_44":
			dialog.text = "그 얘기, 어디선가 들은 것 같은데...";
			link.l1 = "토르투가 항구에는 섬을 지키던 강력한 사략선 몇 척이 항상 정박해 있었다. 르바쇠르는 프랑스를 배신하고 일종의 현지 권력자가 되었지. 그리고 이제, 토르투가의 해적 소굴이 그 우두머리와 함께 파괴된 뒤로, 해적들은 프랑스인들에게 몹시 분노하고 있어...";
			link.l1.go = "noel_45";
		break;
		
		case "noel_45":
			dialog.text = "정말이야!";
			link.l1 = "그래. 우리가 그렇게 할 수밖에 없었지, 그렇지 않으면 토르투가는 우리 손에서 완전히 멀어졌을 거야. 하지만 우리가 얻은 결과는 그리 좋지 않았어. 이제 카리브 해에서 프랑스 무역선은 어느 하나도 안전하다고 할 수 없어. 스페인 놈들은 해적 남작들과 협정이 없어도, 튼튼한 갈레온과 강력한 전함 함대를 가지고 있어서 해적들을 물리칠 수 있지. 네덜란드도 동인도 상선이랑 제벡을 가지고 있고. 하지만 우리는 그런 걸 자랑할 수 없어, 안타깝게도. 게다가 프랑스 해적들은 프랑스 상인들까지 자주 털어.";
			link.l1.go = "noel_46";
		break;
		
		case "noel_46":
			dialog.text = "이건 미친 짓이야! 이걸 끝낼 방법은 없는 거냐?";
			link.l1 = "많은 이들이 시도했지. 결국 싸우는 대신, 금으로 충성을 사들이더군. 사략선 면허를 발급한다는 말이야.";
			link.l1.go = "noel_47";
		break;
		
		case "noel_47":
			dialog.text = "흠...";
			link.l1 = "그러니 경험에서 말하자면, 이 군도에 프랑스 무역 회사를 세우는 건 아주 나쁜 생각이야. 이제 네가 어떤 어려움에 직면하게 될지 알겠나? 여기서 수익을 챙기려는 놈들이 얼마나 많은지 아나? 그리고 그놈들이 쉽게 포기할 리도 없지. 해적들 말인데, 그 자식들은 상상도 못할 짓을 저지를 수 있어. 미쳤다고 해도 되지만, 더러운 목적은 거의 항상 이루고 말지. 상선을 보호하려면 대규모 군함대를 유지해야 할 텐데, 그게 과연 돈이 될까?";
			link.l1.go = "noel_48";
		break;
		
		case "noel_48":
			dialog.text = "하지만 프랑스 상인들도 여기서 어떻게든 살아남고 있나?";
			link.l1 = "그래, 어떻게든 말이야. 특히 지금은, 토르투가에 있던 르바쇠르의 해적 요새가 점령당했으니...";
			link.l1.go = "noel_49";
		break;
		
		case "noel_49":
			dialog.text = "네 말이 드 푸앵시가 한 말과 일치하는군.";
			link.l1 = "그게 사실이야. 여기 군도에서는 원래 다 그렇게 돌아가. 예전부터 그랬지.";
			link.l1.go = "noel_50";
		break;
		
		case "noel_50":
			dialog.text = "말씀하시는 걸 보니 참 열정적이군. 나조차도 이런 것들은 잘 몰랐고, 자네 말이 맞아. 아직도 잘 모르겠네. 푸앵시를 의심했던 건 괜한 일이었던 것 같군. 자네 덕분에 눈을 떴네. 고맙네, 부제독. 하지만 프랑스 장관은 회사 설립을 기대하고 있네. 국왕께서도 그 돈이 필요하시지...\n";
			link.l1 = "알겠습니다. 하지만 제가 방금 말한 것을 꼭 고려해 주십시오; 프랑스령 서인도 제도의 창설이 불가피하다면, 반드시 그것을 지킬 강력한 군함대를 마련해 주시기 바랍니다.";
			link.l1.go = "noel_51";
		break;
		
		case "noel_51":
			dialog.text = "정말 감탄스럽습니다, 부제독 나리! 참으로 고귀한 기품이십니다! 이렇게 오래 이곳에 머무르시고 서둘러 귀국하지 않으신 것도 놀랍지 않군요. 하지만 우리는 다시 만날 것입니다. 반년 뒤에 제가 이곳으로 돌아오겠소. 프랑스 무역회사는 반드시 번영할 것이오. 그리고 해적들에 대해서는, 나리께서 약간 과장하신 것 같군요. 어쨌든 우리에겐 전함과 용감한 선장들, 바로 나리 같은 분들이 있으니 말입니다.";
			link.l1 = "죄송합니다, 남작 나리. 하지만 저는 혼자뿐이고, 프랑스에는 저 말고 군도에 튼튼한 배가 '에클라탕' 한 척뿐입니다. 이걸로는 부족합니다; 얻는 것보다 잃는 게 훨씬 많을 겁니다... 에휴, 뭐, 어쩔 수 없지요. 그동안 뭔가 방법을 생각해 보겠습니다... 프랑스로는 언제 떠나실 생각이십니까?";
			link.l1.go = "noel_52";
		break;
		
		case "noel_52":
			dialog.text = "이 주일 후에 나는 세인트 크리스토퍼로 돌아갈 것이고, 거기서 고향으로 향할 거요. 드 푸앵시 나리가 훌륭한 배를 주었소. '파보리'라는 브리그와 멋진 선장이오. 배는 빠르고 선장은 노련하지만, 물론 자네와 함께 있을 때가 더 안전하다고 느꼈지. 우리가 군도 곳곳을 함께 여행했던 기억이 나는군, 부제독 나리. 정말 멋진 경험이었소.";
			link.l1 = "친절한 말씀 감사합니다, 남작 나리. 자, 이제 우리도 이만 헤어질 때가 된 것 같군요...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToPirates");
		break;
		
		case "noel_53":
			dialog.text = "";
			link.l1 = "여기서는 모두가 서로를 이용하지. 내가 해군 장교가 되기 훨씬 전부터 슈발리에가 자기 거래에 나를 이용했어.";
			link.l1.go = "noel_54";
		break;
		
		case "noel_54":
			dialog.text = "그게 괜찮다고 생각하나? 자네 생각은 어떤가?";
			link.l1 = "아니. 하지만 슈발리에가 나에게 선택권을 주지 않았지. 그의 명령을 따르거나, 내 형제가 평생 감옥에 갇혀 있어야 했고, 우리 집안의 명예도 완전히 더럽혀질 뻔했으니.";
			link.l1.go = "noel_55";
		break;
		
		case "noel_55":
			dialog.text = "끔찍하군! 이건 완전한 테러야! 그자가 그런 협박을 할 만한 이유라도 있었나?";
			link.l1 = "내 형도 그 자의 신임을 받는 사람이 되는 불운을 겪었지. 지금의 나처럼 말이야.";
			link.l1.go = "noel_56";
		break;
		
		case "noel_56":
			dialog.text = "지금 네 형은 어디 있지?";
			link.l1 = "나는 그를 풀어줬지만, 바로 다음 날에 놓쳐버렸어; 그는 더 이상 누구 밑에서도 일하지 않기로 했지.";
			link.l1.go = "noel_57";
		break;
		
		case "noel_57":
			dialog.text = "나는 푸앵시가 자기가 주장하는 사람이 아니라는 걸 알고 있었소! 양의 탈을 쓴 늑대지! 부제독 나리, 저를 믿으셔도 됩니다. 나는 명예로운 사람이오. 그리고 만약 그의 범죄 행위에 대한 확실한 증거를 찾을 수 있다면, 당신을 그 '후원자'의 멍에에서 구해내겠소. 스타이베산트와 관련된 이 지루한 이야기, 혹시 아는 게 있소? 솔직하게 말하시오, 걱정하지 마시오 – 당신은 군인일 뿐이고, 명령을 수행할 의무가 있었으니.";
			link.l1 = "알고 있지. 생마르탱에는 정말로 광산이 있어. 하지만 거기서 금이 아니라 소금을 캐지. 그 소금은 스페인 놈들 사이에서 수요가 아주 많아. 푸앵시는 스페인 놈들과 직접 거래할 수 없어서, 스튀베상트가 중개인 역할을 했지.";
			link.l1.go = "noel_58";
		break;
		
		case "noel_58":
			dialog.text = "그럼 푸앵시와 스토이베산트가 사업 파트너란 말이야?";
			link.l1 = "예전엔 그랬지. 네가 생마르탱을 조사하고 싶다고 하자, 스토이베상트가 푸앵시를 판에서 밀어내고 소금광산의 이익을 전부 자기 것으로 챙기기로 했거든. 푸앵시는 아무에게도 말할 수 없었지... 하지만 스토이베상트가 오산했어, 우리가 지금 보고 있듯이.";
			link.l1.go = "noel_59";
		break;
		
		case "noel_59":
			dialog.text = "아직도 그 광산이 운영되고 있다고 생각해?";
			link.l1 = "확실해. 이제 푸앵시에게 새로운 무역 동맹이 생긴 것 같아. 다름 아닌 도일리 대령 그 자신이야.";
			link.l1.go = "noel_60";
		break;
		
		case "noel_60":
			dialog.text = "우리가 어떤 증거라도 내무부에 제출할 수 있을까?";
			link.l1 = "흠. 광산을 습격할 때, 참고로 그건 네덜란드인이 아니라 스페인 놈들이 한 짓이었지, 우리는 소유주를 생포했어. 그 자는 아직 내 배에 있어. 가서 직접 얘기해 봐도 돼. 자유를 대가로 흥미로운 얘기를 많이 해줄지도 몰라.";
			link.l1.go = "noel_61";
		break;
		
		case "noel_61":
			dialog.text = "당장 네 배로 가자. 네 포로를 선실로 데려가라고 명령해. 내가 그와 얘기 좀 하겠다.";
			link.l1 = "좋아, 가자.";
			link.l1.go = "exit";
			npchar.greeting = "noel_4";
			AddDialogExitQuestFunction("Patria_CondotierToCabin");
		break;
		
		case "noel_62":
			dialog.text = "좋습니다, 부제독님. 제가 그와 이야기해 보겠습니다. 여기 계십시오.";
			link.l1 = "물론이지...";
			link.l1.go = "noel_63";
		break;
		
		case "noel_63":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "rld", "aloc1", "", -1);
			DoQuestFunctionDelay("Patria_CondotierInCabinTalk", 3.0);
		break;
		
		case "noel_64":
			dialog.text = "네 포로에게서 들은 모든 증거를 내가 적어두었고, 그가 그 아래에 서명도 했네. 이제 내가 그에게 약속한 것을 지켜야 하네. 적당한 기회가 있을 때마다 카르타헤나에 들러 그를 내려주게. 하지만 자네도 모든 걸 직접 들었지.\n이봐, 우리 푸앵시가 얼마나 못된 놈인지 알겠나! 네덜란드인들에게 섬을 임대하고, 거기서 불법 행위를 저질렀으며, 스페인 놈들까지 들여보내 광산을 관리하게 했어! 저자의 이기심 때문에 국왕의 금고에서 얼마나 많은 돈이 빠져나갔을지 상상도 하기 싫군!";
			link.l1 = "그 증거로 푸앵시를 기소할 수 있을까?";
			link.l1.go = "noel_65";
		break;
		
		case "noel_65":
			dialog.text = "유감이지만, 안 될 것 같소. 증거가 매우 중요하긴 하지만, 충분하지 않소. 하지만 우리 둘 다 그 이유를 알기에, 당신이 이 일에 휘말리는 건 원치 않소.";
			link.l1 = "스페인 사람이 위원회가 여기에 도착하면 증언하겠다고 동의했습니다.";
			link.l1.go = "noel_66";
		break;
		
		case "noel_66":
			dialog.text = "이 일은 지금으로부터 최소한 여섯 달 뒤에나 일어날 거야. 그때쯤이면 이 스페인 놈이 어떻게 될지, 우리가 나중에 카르타헤나에서 그를 찾을 수 있을지 누가 알겠어... 우리는 훨씬 더 가치 있는 증거가 필요해. 즉, 그 광산이 여전히 비밀리에 운영되고 있고 우리 총독 나리의 주머니를 계속 채우고 있다는 증거 말이야.";
			link.l1 = "그러니까 우리 보고 생마르탱으로 가자는 거야?";
			link.l1.go = "noel_67";
		break;
		
		case "noel_67":
			dialog.text = "그래. 광산으로 가는 길을 아나?";
			link.l1 = "그래.";
			link.l1.go = "noel_68";
		break;
		
		case "noel_68":
			dialog.text = "그럼 밤에 너랑 나랑 몰래 거기로 숨어들어가서, 아무도 못 보게 조용히, 거기서 무슨 일이 벌어지는지 확인하자.";
			link.l1 = "아주 좋군.";
			link.l1.go = "noel_69";
		break;
		
		case "noel_69":
			dialog.text = "그런데 슈발리에에 대해서는 어쩔 건데, 응? 이제야 왜 그가 그렇게 대놓고 군도에 프랑스 무역회사를 세우는 게 이득이 안 된다고 넌지시 말했는지 알겠군... 당연히, 그놈한테는 제일 손해겠지!";
			link.l1 = "이제 우리가 동맹이 되었으니, 남작 나리, 진실을 모두 말씀드리겠습니다. 푸앵시가 저에게 부탁했지요... 당신이 이곳에 무역 회사를 세우지 않도록 설득해 달라고 했습니다.";
			link.l1.go = "noel_70";
		break;
		
		case "noel_70":
			dialog.text = "그렇군! 적어도 그자가 너더러 나를 칼이나 권총으로 해치우라고 하진 않았겠지?";
			link.l1 = "아니. 넌 다른 방법으로 설득당해야 했지.";
			link.l1.go = "noel_71";
		break;
		
		case "noel_71":
			dialog.text = "퐁시 놈이 대가를 치르게 될 거다. 하지만 지금은 당장 생마르탱으로 항해해야 해. 그 스페인 놈은 나중에 본토로 넘기지. 출발한다, 부제독!";
			link.l1 = "내 배를 타고 섬을 떠난다니 좀 이상하게 보일 텐데, 그렇지 않나?";
			link.l1.go = "noel_72";
		break;
		
		case "noel_72":
			dialog.text = "그렇게 생각하지 않아. 네가 나를 설득해야 하는 거 아니었나? 그걸 제대로 해냈잖아, 하하! 그래, 유럽으로 떠나기 전에 슈발리에에게 그의 주장에 동의한다고, 그리고 무역회사는 설립되지 않을 거라고 말할 거야. 당분간은 거짓된 평화 속에서 살게 두지... 가자!";
			link.l1 = "...";
			link.l1.go = "noel_73";
		break;
		
		case "noel_73":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierToSMartin", 5.0);
		break;
		
		case "noel_74":
			dialog.text = "앞장서시오, 부제독. 밤의 어둠이 우리를 감춰줄 것이오.";
			link.l1 = "나를 따라와...";
			link.l1.go = "noel_75";
		break;
		
		case "noel_75":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.Patria_Condotier_inMine.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_inMine.win_condition.l1.location = "Location_reserve_03";
			pchar.quest.Patria_Condotier_inMine.function = "Patria_CondotierInMine";
		break;
		
		case "noel_76":
			dialog.text = "(속삭이며) 나 봤어! 나 정말 봤어! 너도 봤어? 붉은 군복 놈들! 저놈들은 영국군이야!";
			link.l1 = "내가 말했잖아 - 이제 푸앵시는 도일리 대령하고 거래해.";
			link.l1.go = "noel_77";
		break;
		
		case "noel_77":
			dialog.text = "네 말이 맞았어. 이제 충분히 봤으니, 들키기 전에 최대한 빨리 여기서 나가자!";
			link.l1 = "동의하지...";
			link.l1.go = "noel_78";
		break;
		
		case "noel_78":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload2_back", "Patria_CondotierToBeach", -1);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "noel_79":
			dialog.text = "우리 친애하는 슈발리에의 '상업 프로젝트'가 어떤 결과를 가져왔는지 보게! 영국 놈들이 프랑스 섬에서 주인 행세를 하고 있잖아! 이건 말도 안 돼!";
			link.l1 = "우린 움직여야 해, 안 그러면 누가 분명히 여기 올 거야. 우리가 들키면 안 되니까.";
			link.l1.go = "noel_80";
		break;
		
		case "noel_80":
			dialog.text = "부제독님, 우리가 생마르탱으로 가는 내내 계속 생각해 봤는데, 결정을 내렸습니다. 피터 스토이베산트와의 만남을 주선해 주실 수 있겠습니까?";
			link.l1 = "스튜이베선트하고? 그런데 왜?";
			link.l1.go = "noel_81";
		break;
		
		case "noel_81":
			dialog.text = "예전 사업 파트너가 중요한 단서와 슈발리에들의 연루를 입증할 만한 확실한 증거를 가지고 있을지도 몰라. 스토이베상트가 푸앵시에 대해 별로 좋게 생각하지 않을 거고, 특히 최근 일들 때문에 복수를 꾀할 게 분명해...\n";
			link.l1 = "그렇다고 생각합니다, 남작 나리. 저는 개인적으로 스타이베산트의 궁전에는 감히 가지 못하겠소. 제가 그들에게 저지른 일들을 생각하면, 저에겐 너무 위험하오...";
			link.l1.go = "noel_82";
		break;
		
		case "noel_82":
			dialog.text = "이미 생각해 뒀어. 우리는 퀴라소로 가서, 도시에서 멀리 떨어진 만에 상륙한 다음, 광산에 있던 붙잡은 스페인 놈을 편지와 함께 스튀베상트에게 보낼 거야.\n거기서 너에 대해서는 언급하지 않을 거고, 대신 내가 푸앵시를 상대로 조사 중이라는 식으로 알릴 거야. 네덜란드 놈이 약속 장소에 나올 거라고 본다.";
			link.l1 = "흠. 이건 좋은 생각 같지 않군. 스토이베산트는 바보가 아니야; 얻을 수 있는 건 다 챙기는 놈이지, 심지어 널 감옥에 가두고 거액의 몸값을 요구할 수도 있어. 하지만 이 모든 일이 푸앵시 때문이라고 믿게 만들면, 우리 편을 들 수도 있지. 뭐, 그렇게까지 결심했다면 한번 해보자고.";
			link.l1.go = "noel_83";
		break;
		
		case "noel_83":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Shore40", "reload1_back", false);
			LocatorReloadEnterDisable("Shore40", "boat", false);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_LocationDisableOfficersGen("shore40", false);
			LAi_LocationDisableOfficersGen("Location_reserve_01", false);
			LAi_LocationDisableOfficersGen("Location_reserve_03", false);
			pchar.quest.Patria_CondotierCuracao.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCuracao.win_condition.l1.location = "shore22";
			pchar.quest.Patria_CondotierCuracao.function = "Patria_CondotierOnCuracao";
			AddQuestRecord("Patria", "81");
		break;
		
		case "noel_84":
			dialog.text = "드 모르 나리, 제 어리석음을 용서해 주십시오. 스타이베산트에 대해 나리 말씀이 옳았습니다. 드 푸앵시에게 도전할 수 있는 자는 더 큰 악당뿐이라는 걸 미리 알았어야 했습니다!";
			link.l1 = "하! 백만이라니... 푸앵시도 백만을 원했고, 스튜이베산트도 백만을 원하고... 계속 제자리걸음만 하는 것 같군...";
			link.l1.go = "noel_85";
		break;
		
		case "noel_85":
			dialog.text = "무슨 말씀입니까, 부제독 나리?";
			link.l1 = "내가 카리브에 도착했을 때, 푸앵시가 내 동생 몸값으로 백만을 내라고 했지.";
			link.l1.go = "noel_86";
		break;
		
		case "noel_86":
			dialog.text = "그렇게 많이 주고 샀다고?";
			link.l1 = "나는 그 돈을 벌었고, 갚았지. 물론 한 달 만에 한 건 아니야. 사실 그땐 나도 그냥 뭍사람이었거든. 그래도 슈발리에가 미셸을 그냥 보내주진 않았어.";
			link.l1.go = "noel_87";
		break;
		
		case "noel_87":
			dialog.text = "그리고 나서 푸앵시 밑에서 일하겠다고 자원했단 말이오? 솔직히 이해가 안 되는군.";
			link.l1 = "나는 프랑스와 내가 사랑하는 이들을 위해 입대했지, 왕 말고는 누구에게도 머리 숙이지 않아.";
			link.l1.go = "noel_88";
		break;
		
		case "noel_88":
			dialog.text = "실례합니다, 드 모르 나리. 물론, 당신은 프랑스와 국왕을 섬기고 계시지요! 푸앵시는 모든 일에 대해 책임을 질 것입니다! 당신에게 준 모든 고통까지도 말입니다.";
			link.l1 = "좋소, 남작 나리, 내가 쓸 수 있는 백만을 찾아보지. 배에 올라타시오... 내가 이 문제를 해결하겠소.";
			link.l1.go = "noel_89";
		break;
		
		case "noel_89":
			DialogExit();
			//chrDisableReloadToLocation = false; //17-add
			LAi_LocationFightDisable(&Locations[FindLocation("shore22")], false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10.0);
			pchar.questTemp.Patria = "epizode_12_stivesant";
			AddQuestRecord("Patria", "83");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Patria_CondotierStivesantTimeOver", 0, 0, 30, false); // таймер на месяц
		break;
		
		case "noel_90":
			dialog.text = "저를 만나고 싶으셨습니까, 부제독?";
			link.l1 = "그래. 슈타이베산트와 만남을 가졌지. 여기 그의 장부가 있어.";
			link.l1.go = "noel_91";
		break;
		
		case "noel_91":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "믿을 수가 없군! 흠, 어디 보자... (읽는 중)";
			link.l1 = "...";
			link.l1.go = "noel_92";
		break;
		
		case "noel_92":
			LAi_Fade("", "");
			dialog.text = "이게 다야! 우리 친애하는 슈발리에가 이제 끝장이야. 이 모든 회계 장부가 재무장관에게 넘어가는 순간... 그에게 무슨 일이 닥칠지 상상도 못 하겠어. 카르타헤나에서 온 스페인 놈을 굳이 찾을 필요도 없겠군. 드 모르 나리, 정말 이 책 한 권에 백만을 지불하셨소?";
			link.l1 = "내가 그랬지. 내가 다른 방법을 썼다면 프랑스는 내전 때문에 카리브 해의 식민지를 잃었을 거야. 내가 이길 수도 있었겠지만, 자기 국민과 싸우는 제독이 무슨 제독이겠나.";
			link.l1.go = "noel_93";
		break;
		
		case "noel_93":
			dialog.text = "정말 이름값을 하시는군요. 맹세코 말씀드리지만, 부제독 나리께 반드시 되찾아드리겠습니다. 푸앵시의 금고와 고리대금업자들 사이에서 상당한 금액을 찾아낼 수 있을 거라 확신합니다. 단지 제가 유럽에서 임명장을 받아 돌아올 때까지 6개월만 기다려 주시길 부탁드립니다.";
			link.l1 = "그리고 훈련 잘 받고 무장한 병사 한 연대도 꼭 데려오시오. 그리고 '에클라탕' 같은 배도 필요하네. 나는 또 '에클라탕'의 선장도 때가 되면 우리 편에 설 거라 믿고 있소.";
			link.l1.go = "noel_94";
		break;
		
		case "noel_94":
			dialog.text = "의심하지 마시오, 그도 명예로운 사람이오. 나는 도덕적 가치가 자신의 결정을 내리는 데 큰 역할을 한다는 것을 깨달았소. 나를 믿고 이 국가 범죄자를 폭로한 것은 정말 잘한 일이오. 이제 나를 캡스터빌로 데려가 주시오. 거기서 포인시에게 당신 임무의 성공을 보고할 것이오 – 당신은 나를 설득하는 데 성공했고, 나는 무역회사를 설립하려던 생각을 접겠소. 어쩌면 포인시가 당신에게 보상까지 내릴지도 모르니 – 떳떳하게 그 보상을 받으시오, 아무 걱정 말고. 당신만큼은 충분히 받을 자격이 있소. 당신이 이 일에 휘말릴 일도 없고, 당신의 이름이 상관의 악행으로 더럽혀질 일도 없소. 오히려 내가 왕을 만나면 당신에 대해 최고의 말만 할 것이오. 바롱 포르제는 명예로운 사람이자 약속을 지키는 사람이오.";
			link.l1 = "기쁘군요, 남작 나리. 출발합시다!";
			link.l1.go = "noel_95";
		break;
		
		case "noel_95":
			DialogExit();
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			Island_SetReloadEnableGlobal("Curacao", true);
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			pchar.questTemp.Patria = "epizode_12_baronwin";
			AddQuestRecord("Patria", "85");
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_CondotierBaron_win.function = "Patria_CondotierBaronWin";
		break;
		
		case "noel_96":
			dialog.text = "자, 부제독 나리, 드디어 도착했군요. 이제 임무는 끝났으니, 그 다음은 제 몫입니다. 당신 일에 신경 쓰시고, 이전처럼 프랑스의 이익을 지키십시오. 약 6개월쯤 지나면 이 더러운 이야기도 끝날 겁니다. 필요할 때 전령을 보내 당신을 찾게 하겠소. 안녕히 가시오, 드 모르 나리. 이곳에서 명예로운 분을 만나 정말 행운이었소! 장관과 국왕께도 당신 이야기를 전하겠다고 약속하오. 그리고 그분들은 오직 좋은 이야기만 듣게 될 것이오.";
			link.l1 = "감사합니다, 남작 나리. 좋은 항해 되십시오!";
			link.l1.go = "noel_97";
		break;
		
		case "noel_97":
			DialogExit();
			AddQuestRecord("Patria", "86");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		case "noel_98":
			dialog.text = "뵙게 되어 반갑습니다, 부제독 나리. 약속대로 다시 찾아왔습니다. 그리고 저와 함께 온 이는 재무부 장관의 수석 보좌관인 올리비에 부르댕 남작입니다.";
			link.l1 = "슈발리에 드 푸앵시가 어디 있지?";
			link.l1.go = "noel_99";
		break;
		
		case "noel_99":
			dialog.text = "그는 있어야 할 곳, 감옥에 있지. 체포되어 프랑스로 이송되어 조사와 재판을 받을 거야.\n지위가 있으니 처형은 피하겠지만, 막대한 벌금과 강등, 그리고 아마도 투옥은 피하지 못할 거야.";
			link.l1 = "체포는 평화롭게 이루어졌나?";
			link.l1.go = "noel_100";
		break;
		
		case "noel_100":
			dialog.text = "별로 그렇진 않아. 슈발리에가 이 저택에 충성스러운 병사들로 이루어진 경호대를 두고 있었지. 하지만 우리는 그런 사태가 벌어질 걸 미리 대비해 뒀거든.";
			link.l1 = "그렇다면, 축하하오, 남작 나리! 이제 프랑스 무역회사와 거래를 하실 생각이오?";
			link.l1.go = "noel_101";
		break;
		
		case "noel_101":
			dialog.text = "나? 그래. 부르댕 나리께서는 드 푸앵시 기사와 함께 프랑스로 돌아가실 거야. 그리고 부제독 나리, 당신도 곧 변화가 있을 거요. 이제 새로운 직책을 맡게 되었으니, 자세한 건 부르댕 나리께서 직접 말씀해 주실 거요.";
			link.l1 = "...";
			link.l1.go = "noel_102";
		break;
		
		case "noel_102":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Finansist");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_103":
			dialog.text = "드 모르 나리! 잠깐 기다리시오!";
			link.l1 = "예, 남작 나리. 듣고 있습니다.";
			link.l1.go = "noel_104";
		break;
		
		case "noel_104":
			dialog.text = "슈타이베선트에게 건넨 백만 금화에 관해서는... 내가 이 사실을 관청에 알리지 않았소, 그러니까... 프랑스 장교가 어떻게 그렇게 많은 돈을 손에 넣었는지 같은 질문을 피하기 위해서였지. 이게 자네에게 해가 되었을 수도 있겠군, 왜냐하면 그들이 자네에게 국왕의 금고를 자네 돈으로 채우라고 요구했을 테니 말이오.";
			link.l1 = "알겠습니다, 감사합니다.";
			link.l1.go = "noel_105";
		break;
		
		case "noel_105":
			dialog.text = "카스테르빌에서 푸앵시가 소지하고 있던 모든 돈은 부르댕 남작이 압수했소. 하지만 알고 보니, 푸앵시는 영국 돈놀이꾼들에게 따로 숨겨둔 비자금도 있었더군. 투자금을 돌려받는 문제는 내가 그와 직접 이야기해 보겠소, 그리고 그 후에 자네에게 보상할 방법을 찾아보겠네.";
			link.l1 = "영국 고리대금업자들 손에서 뭘 빼앗는 건 쉽지 않을 거다.";
			link.l1.go = "noel_106";
		break;
		
		case "noel_106":
			dialog.text = "동의하오. 하지만 우리가 계속 노력할 것이니, 결과가 나오면 계속 알려주겠소.";
			link.l1 = "원하시는 대로 하겠습니다.";
			link.l1.go = "noel_107";
		break;
		
		case "noel_107":
			dialog.text = "부제독 나리, 안색이 안 좋아 보이는데, 제 착각입니까? 이제 막 식민지에서 가장 높은 자리를 받으셨잖습니까!";
			link.l1 = "아니, 아니야, 전혀 그렇지 않아... 모든 일이 너무 갑작스럽게 일어나서, 내가 좀 당황했을 뿐이야.";
			link.l1.go = "noel_108";
		break;
		
		case "noel_108":
			dialog.text = "걱정하지 마. 곧 새 직책에 익숙해질 거야. 게다가, 너는 생마르탱의 총독으로 반년이나 꽤 성공적으로 일했으니, 이건 너한테 새로운 일도 아닐 거야.";
			link.l1 = "오, 곧 익숙해질 거야. 내가 카리브 해에서 지내면서 더 힘든 상황도 겪어 봤거든. 이것도 잘 넘길 수 있을 거라 생각해.";
			link.l1.go = "noel_109";
		break;
		
		case "noel_109":
			// belamour legendary edition -->
			dialog.text = "좋아, 알겠네. 게다가 자네를 위한 또 하나의 깜짝 선물이 있지. 분명 마음에 들 거야. 하지만 먼저, 관저로 돌아가 주게. 그곳에서 누군가 우리를 기다리고 있다고 믿네.";
			link.l1 = "흥미롭군요, Forget 나리. 자, 돌아갑시다.";
			link.l1.go = "noel_110";
		break;
		
		case "noel_110":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "ToEcliatonAward", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "noel_111":
			dialog.text = "괜찮습니다, Marquis 나리. 진정한 선장이라면 언제나 자기 배부터 챙겨야 하지 않겠습니까? Charles, 전함 'Eclatant'의 선장 Hubert Dassier Marquis 나리를 기억하시오?";
			link.l1 = "당연히 기억하지! 그 사람이 아니었으면 난 오늘 살아 있지도 않았을 거야. 해군 장교들 사이의 가장 강한 우정은 함께 싸운 전투에서 만들어지는 법이지. 그리고 Dassier 나리는 정말 경험 많은 선장임을 증명했어.";
			link.l1.go = "noel_112";
		break;
		
		case "noel_112":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_113":
			dialog.text = "부제독 나리, 다음과 같이 보고 드릴 영광을 갖게 되었습니다. 군도 내 프랑스 식민지의 총독 대행으로 임명되신 것 외에도, 나리의 기함 문제 또한 상부에 제기하였습니다.";
			link.l1 = "기함?";
			link.l1.go = "noel_114";
		break;
		
		case "noel_114":
			dialog.text = "정확히 그렇소. 내가 알기로, 그대가 프랑스의 봉사에 들어갔을 때, 중형 코르벳 '그리퐁도르'가 하사되었지. 훌륭한 배임에는 틀림없으나, 어디까지나 장교에게나 어울리는 배일 뿐, 지금의 부제독, 그리고 이제는 총독인 그대에게는 부족하오. 그대는 이곳에서 프랑스를 대표하는 얼굴이오. 그러니 기함도 그에 걸맞아야 하오. 그래서 우리는 이 카리브에서 첫 전투를 치른 그 배를 그대의 함대에 추가하기로 결정했소...";
			link.l1 = "포르게 나리, 지금 하려는 말이...";
			link.l1.go = "noel_115";
		break;
		
		case "noel_115":
			dialog.text = "지금부터 프랑스 해군의 자존심, 66문 전열함 '에클라탕'이 당신의 지휘하에 들어갑니다!\n이 결정은 국왕께서 승인하셨소!";
			link.l1 = "하지만 남작 나리, 그냥 가져갈 수는 없어요...";
			link.l1.go = "noel_116";
		break;
		
		case "noel_116":
			dialog.text = "할 수 있어, 샤를. 이건 논의할 문제가 아니야. 프랑스에서 '에클라탕'은 너를 위해 특별히 개조됐지. 알고 보니 카리브 해에는 유럽처럼 그렇게 대규모 해전이 없어서, 개별 선박에 대한 요구가 더 높더라고. 여기서는 배의 성능과 선장의 경험이 모든 걸 좌우해. '에클라탕'은 선체를 보강했고, 적재량과 선원 수도 늘렸어. 돛대 장비도 바람을 더 가까이 받고 항해할 수 있게 약간 손봤고, 모든 대포를 전부 42구경짜리로 교체했어. 우리가 가진 것 중 가장 강력한 대포지.";
			link.l1 = "그래, 이제 이 배야말로 진정한 바다의 지배자지... 하지만 포르게 나리, 이 배의 선장은 위대한 후베르 다시에르 후작이야. 내가 그분에게서 빼앗을 순 없어...";
			link.l1.go = "noel_117";
		break;
		
		case "noel_117":
			dialog.text = "아직 말씀드리지 않았지만, 마르키즈 본인께서 직접 당신의 지휘 아래에서 복무하고 싶다는 강한 뜻을 밝히셨습니다... 다시에 나리?";
			link.l1 = "...";
			link.l1.go = "noel_118";
		break;
		
		case "noel_118":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_119":
			dialog.text = "예, Dassier 나리, 더 이상 붙잡지 않겠습니다.";
			link.l1 = "...";
			link.l1.go = "noel_120";
		break;
		
		case "noel_120":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			sld = characterFromId("Ecliaton_Cap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "EcliatonAwardNoelTalk", -1);
		break;
		
		case "noel_121":
			dialog.text = "우리끼리 하는 말인데, Charles, 나는 자네가 후작을 계속 고용하는 게 좋겠네. 단언컨대, 저렇게 경험 많은 선장은 다시 못 구할 걸세.";
			link.l1 = "믿어주십시오, 남작 나리, 저는 스페인과 네덜란드와의 전투 중에 직접 이것을 목격하는 영광을 누렸습니다.\n다시에 나리는 정말 훌륭한 전투 장교이자 제 친구입니다.";
			link.l1.go = "noel_122";
		break;
		
		case "noel_122":
			dialog.text = "자, 이제 실례하겠습니다, 총독 각하! 일이 급해서 말입니다. 무역 회사를 세우는 일은 첫날부터 시작되어야 하니까요. 곧 다시 뵙겠습니다!";
			link.l1 = "행운을 빕니다, Forget 나리. 그리고 무역 사업에도 행운이 함께하길 바랍니다!";
			link.l1.go = "noel_123";
		break;
		
		case "noel_123":
			DialogExit();
			// ставим Эклятон после апгрейда в Европе
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_24";
			sld.DeckDialogNode = "ecliaton_cap_24";
			sld.Ship.Type = GenerateShipExt(SHIP_ECLIATON, true, sld);
			SetBaseShipData(sld);
			sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS42;
			UpgradeShipFull(sld);
			/* UpgradeShipParameter(sld, "SpeedRate");
			UpgradeShipParameter(sld, "TurnRate");
			UpgradeShipParameter(sld, "WindAgainstSpeed");
			UpgradeShipParameter(sld, "HP");
			UpgradeShipParameter(sld, "MaxCrew");
			sld.ship.HP = 11880; */
			sld.Ship.name = "Ecliaton";
			SetCrewQuantityFull(sld);
			AddCrewMorale(sld, 100);
			ChangeCrewExp(sld, "Sailors", 100);
			ChangeCrewExp(sld, "Cannoners", 100);
			ChangeCrewExp(sld, "Soldiers", 100);
			SetCharacterGoods(sld, GOOD_BALLS, 6000);
			SetCharacterGoods(sld, GOOD_GRAPES, 2000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 2000);
			SetCharacterGoods(sld, GOOD_BOMBS, 5000);
			SetCharacterGoods(sld, GOOD_FOOD, 4000);
			SetCharacterGoods(sld, GOOD_POWDER, 12000);
			SetCharacterGoods(sld, GOOD_WEAPON, 900);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
			SetCharacterGoods(sld, GOOD_RUM, 200);
			SetCharacterGoods(sld, GOOD_PLANKS, 100);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 100);
			Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
			Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
			Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
			Group_SetTaskNone("Ecliaton_group");
			Group_LockTask("Ecliaton_group");
			
			bDisableFastReload = false;//открыть переход
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Patria", "90");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.GenGovernor = "true"; // Шарль генерал-губернатор
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			DoQuestReloadToLocation("Charles_Town", "reload", "reload3", "OpenTheDoors");
		break;
		// <-- legendary edition
		
		case "noel_final":
			dialog.text = "부제독님께 진심으로 감사의 뜻을 전하고 싶습니다! 저를 그 빌어먹을 해적들로부터 구해주셔서 제 목숨을 살려주셨습니다. 당신과 필리프 드 푸앵시 모두에게 감사드립니다. 솔직히 말씀드리자면, 제가 그분을 오해했던 것이 완전히 잘못이었다는 걸 인정합니다. 그 점에 대해 용서를 구합니다. 당신과 슈발리에가 옳았습니다. 프랑스 무역회사는 이곳에서 큰 곤경을 겪게 될 것이고, 우리는 여기서 돈만 잃게 될 것 같습니다. 푸앵시처럼 경험 많은 이들과, 당신처럼 용감한 병사들만이 이곳 섬마다 들끓는 이리떼를 버텨낼 수 있습니다. 저는 이제 궁전으로 가야 하고, 그 뒤 가능한 한 빨리 유럽으로 떠나 이 악몽을 잊을 생각입니다.";
			link.l1 = "모든 일이 잘 해결되어 기쁩니다, 남작 나리. 안녕히 가십시오!";
			link.l1.go = "noel_final_1";
		break;
		
		case "noel_final_1":
			DialogExit();
			AddQuestRecord("Patria", "76");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		// капитан Эклятона
		case "ecliaton_cap":
			dialog.text = TimeGreeting()+", 나리. 무슨 일로 '에클라탕' 갑판에 오셨소?";
			link.l1 = TimeGreeting()+", 나리. 제 소개를 하겠습니다 - 샤를 드 모르 선장입니다. 저는 군도에 있는 프랑스 식민지 총독, 슈발리에 드 푸앵시의 명을 받고 왔습니다. 당신의 배를 내 함대에 편입시키고 내 지휘 아래 두라는 명령을 받았습니다. 여기 명령서가 있습니다...";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) link.l1.go = "ecliaton_cap_1";
			else link.l1.go = "ecliaton_cap_no";
		break;
		
		case "ecliaton_cap_no":
			dialog.text = "이건 뭔가 착오가 있군, 나리. 당신은 지금 프랑스 해군의 전열함에 올라와 있어. 나는 왕립 해군에 복무하는 자들의 명령만 듣지. 그런데 당신은 아무런 계급장도 없고 그 함대 소속도 아닌 것 같군. 혹시 우리 배를 다른 배로 착각한 게 아닌가?";
			link.l1 = "하지만...";
			link.l1.go = "ecliaton_cap_no_1";
		break;
		
		case "ecliaton_cap_no_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_no_2";
		break;
		
		case "ecliaton_cap_no_2":
			if(IsUniformEquip())
			{
				dialog.text = "허, 이 제복을 입으니 당신인 줄도 몰랐소, 선장. 자, 편지를 내보이시오. 내용을 좀 살펴보고 싶으니.";
				link.l1 = "여기.";
				link.l1.go = "ecliaton_cap_1";
			}
			else
			{
				dialog.text = "우리는 이미 모든 것을 이야기했소, 나리...";
				link.l1 = "흠...";
				link.l1.go = "ecliaton_cap_no_1";
			}
		break;
		
		case "ecliaton_cap_1":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "음, 어디 보자... (읽으며) 흥미롭군. 그러니까 내 배와 나는 당신의 지휘 아래 들어가게 되는 건가, 드 모르 선장?";
			link.l1 = "그것이 총독의 명령이다.";
			link.l1.go = "ecliaton_cap_2";
		break;
		
		case "ecliaton_cap_2":
			dialog.text = "그래, 그래, 명령에는 토 달지 않는 법이지. 좋아. 내 소개를 하지. 나는 위대한 프랑스 해군의 66문 함선 '에클라탕'의 선장이자, 잘 훈련된 이 선원들과 함께하는 위베르 다시에르 후작이오. 내 명예를 걸고 맹세하건대, 이 배는 프랑스가 가진 최고의 함선 중 하나라네.";
			link.l1 = "그 말을 들으니 다행이군, 우리가 총독에게서 맡은 임무는 항해와 포술에 대한 충분한 지식이 필요할 테니.";
			link.l1.go = "ecliaton_cap_3";
		break;
		
		case "ecliaton_cap_3":
			dialog.text = "다가올 작전의 세부 사항을 말해 주시겠습니까?";
			link.l1 = "물론이지. 우리는 여기서 남동쪽으로 일주일쯤 걸리는 스페인령 트리니다드 섬으로 이동할 거다.\n거기서 산호세 식민지를 지키는 요새를 기습 공격해 완전히 불태워버릴 거야.\n그 다음엔 최근 프랑스령 생피에르 정착지에 가해진 공격에 대한 보상을 두고 스페인 놈들과 협상할 거다.";
			link.l1.go = "ecliaton_cap_4";
		break;
		
		case "ecliaton_cap_4":
			dialog.text = "알겠소. 언제 출발하오?";
			link.l1 = "가능한 한 빨리. 이 임무는 한 달 안에 끝내야 하니, 시간은 넉넉해.";
			if (GetCompanionQuantity(pchar) > 4) link.l1.go = "ecliaton_cap_5_1";
			else link.l1.go = "ecliaton_cap_5";
		break;
		
		case "ecliaton_cap_5":
			dialog.text = "알겠습니다, de Maure 선장. 명령만 내리시면 출항하겠습니다.";
			link.l1 = "";
			link.l1.go = "ecliaton_cap_6";
		break;
		
		case "ecliaton_cap_6":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_AddEcliaton();
		break;
		
		case "ecliaton_cap_wait":
			dialog.text = "명령이나 질문이 있으십니까, de Maure 선장?";
			link.l1 = "아직 아니야...";
			link.l1.go = "ecliaton_cap_wait_1";
		break;
		
		case "ecliaton_cap_wait_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
		break;
		
		case "ecliaton_cap_5_1":
			dialog.text = "하지만, 드 모르 선장, 먼저 함대를 좀 더 줄이셔야 합니다\n제 배가 합류하면 함대가 너무 커져서 함께할 수 없습니다.";
			link.l1 = "흠. 네 말이 맞군. 여기 항구에 배 한 척을 남겨두겠다.";
			link.l1.go = "ecliaton_cap_5_2";
		break;
		
		case "ecliaton_cap_5_2":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_5_3";
		break;
		
		case "ecliaton_cap_5_3":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "아직 함대를 줄이지 않았소, 나리?";
				link.l1 = "그래, 그래, 기억하고 있어. 지금 하고 있잖아.";
				link.l1.go = "ecliaton_cap_5_2";
			}
			else
			{
				dialog.text = "자, '에클라탕'이 당신 함대에 합류할 준비가 되었소, 나리.";
				link.l1 = "그럼 나는 내 배로 가겠소, 당신도 출항 준비를 하시오.";
				link.l1.go = "ecliaton_cap_5";
			}
		break;
		
		case "ecliaton_cap_7":
			dialog.text = "안녕하십니까, 준장님. 또 한 번 전투가 기다리고 있습니까?";
			link.l1 = "그래, 맞아. 다시 한 번 힘을 합칠 거야. 우리는 필립스버그를 습격하러 간다. 총독께서 우리에게 생마르탱에서 네덜란드 놈들을 몰아내라고 명하셨지.";
			link.l1.go = "ecliaton_cap_9";
			link.l2 = "그렇습니다, 선장님, 하지만 조금 이따가요. 제가 때가 되면 말씀드리겠습니다. '에클라탕'은 언제든 출항할 준비가 되어 있어야 합니다.";
			link.l2.go = "ecliaton_cap_8";
		break;
		
		case "ecliaton_cap_8":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_7";
			npchar.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "ecliaton_cap_9":
			dialog.text = "모든 게 명확합니다. 힘든 임무가 되겠군요, 나리. 내가 듣기로는 필립스버그 요새에 대포가 아주 많답니다.";
			link.l1 = "확신하네, 친구야, 하지만 우리가 해낼 거야. 출항 준비해라, 곧 떠난다.";
			link.l1.go = "ecliaton_cap_10";
		break;
		
		case "ecliaton_cap_10":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_BastionAddEcliaton();
		break;
		
		case "ecliaton_cap_11":
			dialog.text = "'에클라탕' 갑판에서 뵙게 되어 반갑습니다, 부제독님! 명령이 무엇입니까?";
			link.l1 = "'에클라탕'을 출항 준비시켜라. 먼저 자메이카 해안으로 항해한 다음, 도일리 대령의 함대와 함께 퀴라소를 공격할 것이다.";
			link.l1.go = "ecliaton_cap_13";
			link.l2 = "명령은 나중에 내릴 것이오, 선장. 내가 언제인지 알려주겠소. '에클라탕'은 언제든 출항할 준비가 되어 있어야 하오.";
			link.l2.go = "ecliaton_cap_12";
		break;
		
		case "ecliaton_cap_12":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_11";
			npchar.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "ecliaton_cap_13":
			dialog.text = "'에클라탕'과 그 선원들이 준비됐습니다, 부제독님!";
			link.l1 = "훌륭하군. 그럼 바로 출발하자.";
			link.l1.go = "ecliaton_cap_14";
		break;
		
		case "ecliaton_cap_14":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_CuracaoAddEcliaton();
		break;
		
		// belamour legendary edition -->
		case "ecliaton_cap_15":
			dialog.text = "실례합니다, 신사 여러분. 배에서 명령을 내리느라 바빠서 일찍 합류하지 못했습니다. 이미 관저에서 여러분을 찾지 못해 꽤 늦었다고 생각했고, 그래서 막 배로 돌아가려던 참이었습니다...";
			link.l1 = "...";
			link.l1.go = "ecliaton_cap_16";
		break;
		
		case "ecliaton_cap_16":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_111";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_17":
			dialog.text = "당신과 함께 싸울 수 있어 영광이었습니다, de Maure 나리! 이렇게 유능하고 능숙한 장교는 좀처럼 만나기 힘들지요. 저라 해도 트리니다드의 그 스페인 식민지 요새를 그렇게 빨리 제압하지는 못했을 겁니다!";
			link.l1 = "자신을 과소평가하시는군요, Dassier 나리. 우리는 함께 해결했소.";
			link.l1.go = "ecliaton_cap_18";
		break;
		
		case "ecliaton_cap_18":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_113";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_19":
			dialog.text = "맞아요. 나는 후작이지만, 여전히 선원이오. 내게 카리브 제도는 새롭고, 미지이며, 모험으로 가득한 곳이오. 지난번엔 이곳에 몇 달밖에 머물지 못했지만, 유럽으로 돌아갔을 때 이곳이 그리워지는 나 자신을 발견했소. 나는 여기서 우리 조국을 위해 봉사하고 싶소. 그리고 당신은 매우 유능하고 경험 많은 선장이며, 내 진심 어린 존경과 우정을 얻게 되었소. 당신의 지휘 아래에서 복무하게 된다면 큰 영광이겠소, 부제독 나리!";
			link.l1 = "글쎄요, 나는 못 하겠고, 게다가 더 말하자면! - 당신을 거절하고 싶지도 않소, Dassier 나리!";
			link.l1.go = "ecliaton_cap_20";
		break;
		
		case "ecliaton_cap_20":
			dialog.text = "에클라탕이 이제 당신의 기함이 되었다는 것도 알고 있습니다. 그러니 당신이 직접 그 배를 지휘하기로 결정해도 저는 충분히 이해합니다. 그런 경우에는 저를 당신의 장교로 남겨두시거나, 다른 배를 맡기시거나, 아니면 제 임무를 해제하셔도 됩니다. 포르게 나리께서 친절히 약속해주셨는데, 그럴 경우 프랑스 서인도 회사 함대에서 제게 걸맞은 자리를 찾아주겠다고 하셨습니다.";
			link.l1 = "내가 장담할 수 있어, 친구. 그런 일은 절대 일어나지 않을 거야. 너는 내가 만난 선장들 중에서도 최고야. 네가 내 곁에 있다면 우리는 누구도 막을 수 없지.";
			link.l1.go = "ecliaton_cap_21";
		break;
		
		case "ecliaton_cap_21":
			dialog.text = "제 능력을 그렇게 높이 평가해 주셔서 감사합니다. 그리고 한 가지 더 말씀드리죠, 부제독 나리. 지금은 나리의 전대 규모를 알지 못하니, 만일을 대비해 저는 캡스터빌 부두에 정박한 에클라탕트호의 함장 교각에서 기다리고 있겠습니다. 나리께서 배를 직접 지휘하기로 결정하시면, 저에게 알려만 주십시오.";
			link.l1 = "좋습니다, Dassier 나리.";
			link.l1.go = "ecliaton_cap_22";
		break;
		
		case "ecliaton_cap_22":
			dialog.text = "그럼 물러날 허락을 구하겠습니다. 부제독 나리, 남작 나리...";
			link.l1 = "곧 뵙겠습니다, Dassier 나리.";
			link.l1.go = "ecliaton_cap_23";
		break;
		
		case "ecliaton_cap_23":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_119";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	
		case "ecliaton_cap_24":
			dialog.text = "부제독 나리, 승선을 환영합니다. 에클라탕을 지휘하시겠습니까?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				
				link.l1 = "아직 아닙니다, Marquis 나리. 명령을 기다리십시오.";
				link.l1.go = "ecliaton_cap_24_1";
			}
			else
			{
				link.l1 = "예, 후작 나리, 제 함대에 합류해 주시길 부탁드립니다. 이 아름다운 배는 카리브 해에서 프랑스의 위대함과 힘을 상징하게 될 것입니다!";
				link.l1.go = "ecliaton_cap_25";
			}
		break;
		
		case "ecliaton_cap_24_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_24";
			npchar.DeckDialogNode = "ecliaton_cap_24";
		break;
		
		case "ecliaton_cap_25":
			dialog.text = "전적으로 동의합니다, 각하!";
			link.l1 = "... 이제, 우리가 진짜로 어떤 놈들인지 보여주자!";
			link.l1.go = "ecliaton_cap_26";
		break;
		
		case "ecliaton_cap_26":
			DialogExit();
			DeleteAttribute(npchar, "ShipHideImmortal");
			SetCharacterRemovable(npchar, true);
			npchar.CompanionEnemyEnable = true; 
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			npchar.DeckDialogNode = "hired";
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.Payment = true;
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			
			// удаление группы Эклятона, иначе клон-призрак
			pchar.quest.Patria_EcliatonDelGroup.win_condition.l1 = "ExitFromSea";
			pchar.quest.Patria_EcliatonDelGroup.function = "Patria_EcliatonDelGroup";
		break;
		// <-- legendary edition
		
		// д'Ойли на Антигуа
		case "doily":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE)
			{
				PlaySound("Voice\English\LE\Doily\Edvard_Doily_01.wav");
				dialog.text = "오, 이게 누구야! 저기 있는 사람이 바로 샤를 드 모르 선장 아니신가?! 이제 프랑스 해군에서 자리를 잡았다고 들었소. 예전에 누구를 위해, 뭐랄까, '일'했는지 생각하면 정말 놀랍군...";
				link.l1 = "안녕하십니까, 나리. 혹시 이슬라 테소로 사건을 말씀하시는 겁니까? 아, 하지만 그 섬이 발견자의 유언에 따라 그의 상속인에게 넘어가도록 한 영국 법을 만든 건 제가 아니오. 그러니 그 일에 대해 저를 탓하실 수는 없소; 저는 그저 샤프 양이 정당하게 받을 권리를 찾도록 도와줬을 뿐이오.";
				link.l1.go = "doily_1";
			}
			else
			{
				dialog.text = TimeGreeting()+", 선장님. 프랑스 해군 대표가 중요한 목적을 가지고 앤티가에 도착한 것이겠지요?";
				link.l1 = "그렇습니다, 나리. 저는 프랑스 식민지 총독 필리프 드 푸앵시의 명으로 이곳에 왔습니다. 생크리스토퍼 섬이 스페인과 네덜란드 해군 함대에게 포위당했습니다. 슈발리에께서 당신과 조너선 폭스 나리에게도 도움을 요청하십니다. 여기 당신을 위한 그의 편지입니다, 대령 나리.";
				link.l1.go = "doily_3";
			}
		break;
		
		case "doily_1":
			dialog.text = "궁금하군요, 선장님, 이번 일로 얼마를 벌었습니까? 꽤 많이 벌었겠지요, 값비싼 악당 록슬리의 서비스를 쓸 수 있었으니 말입니다. 해적 남작들이 섬을 지키는 대가로 정기적으로 당신에게 몫을 내는 것도 분명하고요. 우리 둘 다 헬렌 샤프는 그저 가면일 뿐이라는 걸 잘 알고 있지 않습니까?";
			link.l1 = "대령, 우리 둘 다 잘 알다시피 해적 남작들은 대부분 영국의 이익을 위해 움직이고 있소, 물론 공식적으로는 아니지만... 그들이 없다면 이 지역에서 스페인의 패권에 맞서기가 꽤 힘들었을 것이오, 동의하지 않소? 그러니 정치가들 입장에서는, 코스트의 형제단이 그 섬을 자기들만의 것으로 지켜온 사실이 어쩌면 이슬라 테소로가 영국 해군 기지가 되는 것보다 더 이득이었을지도 모르겠군...\n";
			link.l1.go = "doily_2";
		break;
		
		case "doily_2":
			dialog.text = "그 말도 일리가 있소, 선장님, 하지만... 어찌 되었든. 중요한 목적이 있어 앤티가에 온 것이겠지? 혹시 프랑스와 홀란드, 두 옛 동맹국 사이의 관계가 크게 악화된 것과 관련이 있소?";
			link.l1 = "옳소. 나는 프랑스 식민지 총독 필리프 드 푸앵시에게서 파견받았소. 생크리스토프가 스페인과 네덜란드 해군에게 포위당했소. 슈발리에께서 당신의 도움을 요청하셨소. 여기 그분이 당신에게 보낸 편지요, 대령.";
			link.l1.go = "doily_3";
		break;
		
		case "doily_3":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "어디 보자... (읽는 중)";
			link.l1 = "";
			link.l1.go = "doily_3_1";
		break;
		
		case "doily_3_1":
			LAi_Fade("", "");
			dialog.text = "흠... 아주 흥미롭군! 선장, 당신의 지휘관은 정말 내 흥미를 자극할 줄 아는 사람이야. 사람들이 그를 교활한 여우라고 부르는 것도 이상할 게 없지. 네덜란드인들과 친구가 되려고 애쓰는 대신, 진작 이렇게 했어야 했어. 네덜란드 회사와 그 이사가 어떤 자들인지 우리 모두 잘 알잖아. 자, 이런 상황이라면 포위당한 카스터빌을 돕는 걸 거절할 이유가 없지, 그리고 우리 병력도 충분히 많아.\n그들의 전대에 소속된 함선의 수와 종류는 어떻게 되지, 선장?";
			link.l1 = "나는 여섯 척의 배를 세었어: 삼등급 80문 전열함 한 척과 사등급 배 다섯 척이야. 프리깃이나 갤리온도 있을지 몰라.";
			link.l1.go = "doily_4";
		break;
		
		case "doily_4":
			dialog.text = "흠... 우리는 일등급 100문 함선 한 척, 사등급 함선 두 척, 그리고 중형 프리깃 한 척으로 구성된 우리 전대를 저쪽에 맞서 출동시킬 수 있겠군.";
			if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger"))
			{
				link.l1 = "나리, 우리에게도 66문의 대포를 장착한 전함 '에클라탕'이 있습니다. 그 배가 과들루프 해안에서 생크리스토퍼 방어를 지원하러 항해 중입니다.";
				link.l1.go = "doily_5";
			}
			else
			{
				link.l1 = "일등급 함선이 다가오는 전투에서 큰 도움이 될 거야.";
				link.l1.go = "doily_5_1";
			}
		break;
		
		case "doily_5":
			dialog.text = "완벽하군. 그렇다면 이제 적들의 사정거리에서 완전히 벗어났어. 승리는 우리 것이 될 거야.";
			link.l1 = "그리고 내 배도 잊지 마시오, 나리. 이런 전투를 놓칠 생각은 없으니, 그런 생각은 아예 하지도 마시오.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_5_1":
			dialog.text = "그렇소. 카스터빌 요새의 지원만 있다면, 승리는 우리 것이 될 것이오.";
			link.l1 = "그리고 내 배도 잊지 마시오, 나리. 이런 전투를 놓칠 생각은 없으니, 그런 생각은 아예 하지도 마시오.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_6":
			dialog.text = "물론이지요, 드 모르 나리. 어찌 되었든, 당신의 항해 실력에 대한 소문은 군도 전체에 퍼져 있습니다. 당신의 기함이 함대를 이끌게 될 것입니다.";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "내가 내 함대의 나머지 배들을 붙잡아 두었다가, 다시 돌아와서 함께 포위당한 이들을 구하러 달려가겠소.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "곧 내 배를 준비해서, 포위당한 이들을 도우러 달려가겠소.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_7_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_7_2";
		break;
		
		case "doily_7_2":
			dialog.text = "그래서, 출항할 준비가 됐나?";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "잠시만 기다리시오, 나리.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "예, 나리.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_8":
			dialog.text = "그럼 시작하자, 신의 가호가 있기를!";
			link.l1 = "...";
			link.l1.go = "doily_9";
		break;
		
		case "doily_9":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Patria", "42");
			Patria_SiegeAddEngSquadron();
		break;
		
		case "doily_10":
			dialog.text = "더 궁금한 점이 있소, 나리?";
			link.l1 = "아니오, 대령님...";
			link.l1.go = "doily_11";
		break;
		
		case "doily_11":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			npchar.DeckDialogNode = "doily_10";
		break;
		
		case "doily_12":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_02.wav");
			dialog.text = "Stuyvesant에게 보낼 편지를 받아오게, 나리. 내가 누군지 모른다면 소개하지. 나는 에드워드 도일리 대령, 포트 로열의 총독이자 이번 원정의 지휘관이네!\n솔직히 말해서, 윌렘스타트라 불리는 산적 소굴을 완전히 쓸어버리고 싶은 충동이 크네. 카리브에서 가장 사악하고, 이중적이며, 비열한 조직인 네덜란드 서인도 무역회사가 바로 그곳이지. 그들은 군도 내 모든 무역이 자기들만의 권리라고 믿으며, 제이콥 반 베르그 같은 자들과 다른 해적들을 고용해 영국 상인의 배를 나포하고 침몰시키고 있네...";
			link.l1 = "...";
			link.l1.go = "doily_13";
		break;
		
		case "doily_13":
			dialog.text = "나는 이 무도한 짓거리를 끝내러 왔다. 다행히도 너희를 위해 외교적 해결책을 제안하지. 지금은 말이야... 하지만 이 흉악한 조직의 책임자가 협상하러 여기 오지 않는다면, 나는 그의 사업을 완전히 박살낼 거다. 우리가 도시를 습격한 뒤에는 잿더미만 남길 것이고, 발견하는 화약은 전부 너희 요새 지하에 쑤셔 넣고 폭파시킬 거다. 네 플랜테이션도 같은 운명을 맞이할 거고, 스튀베상트 본인도 내 기함의 야드암에 매달리게 될 거다...\n";
			link.l1 = "...";
			link.l1.go = "doily_14";
		break;
		
		case "doily_14":
			dialog.text = "식민지를 재건하려면 1년 이상 걸릴 거요, 그러면 그대는 더 이상 계략이나 음모를 꾸밀 시간도 없을 것이오. 내가 방금 한 말을 '마인헤르 국장'에게 모두 전하시오. 이게 농담이나 빈 협박이 아니라는 것도 명심하고. 내 인내심은 이미 바닥났으니, 내 말을 똑똑히 알아들어야 할 것이오. 알겠소, 장교?";
			link.l1 = "모든 것이 완전히 명확합니다, 대령님.";
			link.l1.go = "doily_15";
		break;
		
		case "doily_15":
			dialog.text = "좋아. 그럼 나가게. 이 일에 대해 생각할 시간을 딱 하루 주겠네. 만약 스물네 시간이 지나도 피터 스타이베선트가 지금 자네처럼 여기 서 있지 않다면, 그건 전적으로 그의 책임이니라.";
			link.l1 = "...";
			link.l1.go = "doily_16";
		break;
		
		case "doily_16":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_17";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "doily_17":
			dialog.text = "그 더러운 개 같은 스타이베산트가 여기 올 거라고 생각해. 그리고 안 온다면, 그건 전적으로 자기 잘못이지!";
			link.l1 = "...";
			link.l1.go = "doily_17_1";
		break;
		
		case "doily_17_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_17";
			AddQuestRecord("Patria", "63");
			Patria_CuracaoParlamenterGo();
		break;
		
		case "doily_18": // д'Ойли на берегу
			dialog.text = "요새에서 잘해주었소, de Maure 나리. 이제 우리는 육로로 도시 성문에 접근할 것이오. 나는 여기서부터 대포를 가져가겠소. 이 길이 더 짧고 수월하니, 그대는 산타 마리아 곶에 해병 부대를 상륙시켜 빌렘스타드로 진격하시오. 가는 길에 적을 만나면 어떻게 해야 할지 알 것이오. 우리 뒤에 아무도 남겨둘 수 없소.";
			link.l1 = "물론입니다, 대령님. 성문에서 뵙겠습니다!";
			link.l1.go = "doily_19";
		break;
		
		case "doily_19":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Patria", "61");
			npchar.dialog.currentnode = "doily_10";
			Patria_CuracaoGotoMarch();
		break;
		
		case "doily_20":
			dialog.text = "자, 이제 임무가 아주 성공적으로 끝난 것 같군. 축하하오, 선장! 아, 실례, 부제독 나리! 이제 배로 돌아가세. 내 부하들에게 경계하라고 하겠소 – 저 바보 스토이베산트가 우리가 퇴각할 때 공격할 용기는 없겠지만, 조심해서 나쁠 건 없으니.";
			link.l1 = "네덜란드인들이 막 체결된 조약을 impudently 깨뜨릴 용기는 없을 거라고 확신하오.";
			link.l1.go = "doily_21";
		break;
		
		case "doily_21":
			dialog.text = "당신과 함께 일해서 즐거웠습니다, de Maure 나리. 우리는 포트로얄이나 캡스터빌에서 다시 만나게 될 것 같군요.";
			link.l1 = "의심할 여지 없소, 대령님. 이제 우리 병사들에게 후퇴하라고 합시다.";
			link.l1.go = "doily_22";
		break;
		
		case "doily_22":
			DialogExit();
			AddQuestRecord("Patria", "64");
			Patria_CuracaoClear();
		break;
		
		case "doily_23":
			dialog.text = "네덜란드 놈들도 이제야 겨우 깨달았나 보군, 저 좁은 길로는 우리 포화 아래 요새에서 접근할 방법이 없다는 걸 말이야. 그리고 도시에 갇힌 놈들도, 완전히 미치지 않고서야 함부로 돌격하지는 못할 거다. 이제 우리 차례다, 놈들 좀 쫄게 만들어 주자고. 대포로 도시를 포격한다! 내 배 선원들이 그걸 보고 상륙 준비하는 척할 거다. 한두 시간만 지나면, 스토이베산트 놈 바지에 오줌 지리고, 휴전 사절 보낼 준비나 하겠지.";
			link.l1 = "모든 게 우리 계획대로 되고 있습니다, 대령님! 자, 시작합시다!";
			link.l1.go = "doily_24";
		break;
		
		case "doily_24":
			DialogExit();
			Patria_CuracaoTownBombing();
		break;
		
		// голландский парламентёр под стенами Виллемстада
		case "holoff":
			dialog.text = "여기에 협상을 시작하러 왔다. 요구 조건이 뭐지?";
			link.l1 = "우리는 회사 이사인 피터 스타이브센트와의 면담을 요구한다. 특히, 그의 회사의 태만과 그 자신의 책임으로 인해 현재 빌렘스타트가 파괴 위협에 처해 있다는 사실에 대해 논의하고자 한다.";
			link.l1.go = "holoff_1";
		break;
		
		case "holoff_1":
			dialog.text = "좋소, 이 일에 대해 스토이베산트 나리에게 말하겠소, 그리고 당신 대표단이 도시로 안전하게 들어올 수 있도록 길을 마련하겠소...";
			link.l1 = "그럼 안전하게 빠져나가는 건 어쩌지?";
			link.l1.go = "holoff_2";
		break;
		
		case "holoff_2":
			dialog.text = "무슨 말씀이신지 모르겠소, 나리?";
			link.l1 = "내가 말했지: 우리를 위해 도시에서 안전하게 나갈 길을 마련해 줄 수 있겠냐고? 그건 잘 모르겠어. 스타이베산트 나리께서 우리 사절들을 그냥 붙잡아 버릴지도 몰라서 걱정이야. 그래서 나는 스타이베산트 나리께 협상을 위해 이곳으로 오시라고 초대한 거야.";
			link.l1.go = "holoff_3";
		break;
		
		case "holoff_3":
			dialog.text = "하지만...";
			link.l1 = ""장교, 여기서는 우리가 조건을 정한다. 네 함대는 파괴됐고, 주둔군은 도시와 단절됐으며, 우리가 결심만 하면 프리깃함이 조각배를 부수듯 빌렘스타트의 방어선을 뚫고 들어갈 것이다. 이제 너는 스타이베산트 나리에게 전할 편지를 받을 것이고, 우리의 초대장과 함께 그에게 전달해야 한다..."\n";
			link.l1.go = "holoff_4";
		break;
		
		case "holoff_4": // перекидываем pchar на офицера и говорим с д'Ойли
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Curacao_parlamenter_1"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		// офицер-испанец на маяке Тринидада
		case "SanJoseSpanish":
			dialog.text = "그래서, 선장님, 당신이 요구 조건을 내세우려고 휴전 사절들을 부른 겁니까?";
			link.l1 = "정확히 맞는 말씀입니다, 나리. 내가 트리니다드에 온 이유를 간단히 설명하겠소 – 이것은 당신이 최근 생피에르를 공격한 것에 대한 우리의 대응이오. 당신은 그 도시를 크게 손상시켰고, 이제 그에 대한 보상을 해야 할 것이오. 보상금은 삼십만 페소요. 그리고 마르티니크에서 당신 병사들이 저지른 악행을 생각하면, 그리 큰 금액도 아니오.";
			link.l1.go = "SanJoseSpanish_1";
		break;
		
		case "SanJoseSpanish_1":
			dialog.text = "실례지만, 나리, 산호세가 생피에르와 무슨 상관이 있습니까? 왜 우리 식민지가 돈을 내야 하죠?";
			link.l1 = "공격자들은 네덜란드인이나 영국인이 아니라 스페인 놈들이었소. 그러니 당신은 돈 데 멘도사에게 보낼 청구서를 프로비던스로 보내시오, 그리고 내 진심 어린 인사도 함께 전해주시오. 알다시피, 배상금을 거부한다면 내 부하들에게 상륙을 명령할 것이고, 그러면 산호세는 훨씬 더 큰 손해를 입게 될 것이오. 나는 당신네 식민지 총독이 올바른 결정을 내릴 거라 확신하오. 답변할 시간은 하루뿐이오. 행운을 빌겠소, 나리들.";
			link.l1.go = "SanJoseSpanish_2";
		break;
		
		case "SanJoseSpanish_2":
			DialogExit();
			npchar.dialog.currentnode = "SanJoseSpanish_3";
			Patria_SanJoseMayakSpanishGo();
		break;
		
		case "SanJoseSpanish_3":
			dialog.text = "";
			link.l1 = "그러니까, 내가 이해한 대로라면 총독이 올바른 결정을 내린 거지?";
			link.l1.go = "SanJoseSpanish_4";
		break;
		
		case "SanJoseSpanish_4":
			AddMoneyToCharacter(pchar, 300000);
			dialog.text = "삼십만 가지고 우리 식민지에서 썩 꺼져.";
			link.l1 = "훌륭하오, 나리들. 내가 장담하건대, 이것이 최선의 방법이었소. 이 일로 멘도사 돈과 다른 이들이 우리 식민지를 공격하려는 마음을 꺾길 바라오. 프로비던스와 그에게 직접 전갈 보내는 것 잊지 마시오. 행운을 빌겠소, 신사분들.";
			link.l1.go = "SanJoseSpanish_5";
		break;
		
		case "SanJoseSpanish_5":
			DialogExit();
			Patria_SanJoseMayakSpanishFin();
		break;
		
		// вестовой на 5 задание
		case "fraofficer":
			dialog.text = "Charles de Maure 선장, 보고 드리겠습니다:\nChevalier Philippe de Poincy께서 Baron Noel Forget가 Saint-Martin으로 출항할 준비가 되었으며, 부두에서 당신을 기다릴 것이라고 전해 달라고 하셨습니다.";
			link.l1 = "훌륭하군! 감사합니다, 나리.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			Patria_SanMartinSetBaron();
		break;
		
		case "fraofficer_2":
			dialog.text = "샤를 드 모르 선장! 지금 총독 나리께서 당신을 부르고 계십니다. 강력한 적 함대가 생크리스토퍼 앞바다에 나타났습니다!";
			link.l1 = "그럼 지체하지 말자!";
			link.l1.go = "fraofficer_3";
		break;
		
		case "fraofficer_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			Patria_SiegeHovernor();
		break;
		
		// патруль у рудника
		case "engofficer":
			dialog.text = "너 누구야? 여기서 뭐 하고 있어?";
			link.l1 = "으으...";
			link.l1.go = "engofficer_1";
		break;
		
		case "engofficer_1":
			dialog.text = "여기는 낯선 자 출입 금지다! 너희 누구냐, 첩자들인가? 사령관실로 데려가겠다, 거기서 알아서 처리할 거다.";
			link.l1 = "하지만 우리는 사령관 사무실에 갈 수 없어...";
			link.l1.go = "engofficer_2";
		break;
		
		case "engofficer_2":
			dialog.text = "네가 스스로 가지 않겠다면, 우리가 억지로 끌고 갈 수밖에 없지! 무기 내놔!";
			link.l1 = "거래는 없어...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierBeachFight");
		break;
		
		// бывший управляющий рудника
		case "miner":
			dialog.text = "";
			link.l1 = "그래서, 다 이해했나?";
			link.l1.go = "miner_1";
		break;
		
		case "miner_1":
			dialog.text = "예, 나리. 이 편지는 반드시 피터 스타이베선트 나리 또는 마티아스 벡 나리에게 직접 전달해야 합니다.";
			link.l1 = "빌렘스타드에서 카르타헤나로 가는 배를 찾는 데 어려움은 없을 거요.\n여정과 숙박에 필요한 자금도 모두 제공했으니 걱정 마시오.\n그리고 혹시 필요하다면, 6개월 후 프랑스 위원회 앞에서 보고를 확인해 줄 수 있겠소?";
			link.l1.go = "miner_2";
		break;
		
		case "miner_2":
			dialog.text = "나리, 저는 제 말을 지킵니다.";
			link.l1 = "좋소. 그럼 행운을 빌지. 이 길이 윌렘스타드로 이어지니 따라가시오. 여기서 멀지 않소.";
			link.l1.go = "miner_3";
		break;
		
		case "miner_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Patria_CondotierOnCuracaoWait", 15.0);
			AddQuestRecord("Patria", "82");
			ReleasePrisoner(npchar);
		break;
		
		// курьер в Капстервиль
		case "cureer":
			dialog.text = "샤를 드 모르 부제독, 맞지?";
			link.l1 = "정확합니다. 누구와 말씀을 나누는 영광을 누리고 있습니까?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "노엘 포르게 남작이 전하라고 한 메시지가 있어. 가능한 한 빨리 카스터빌의 총독 관저로 오라고 했어.";
			link.l1 = "오! 정말 기쁜 소식이군! 고맙네, 바로 출발하겠네!";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			Patria_EuropePrepare();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		break;
		
		case "burden":
			dialog.text = "안녕하십니까, 부제독 나리. 포르게 남작께서 당신에 관한 이야기를 들려주셨소. 정말 많은 이야기였지요. 식민지에서 프랑스의 이익을 위해 충성스럽고 훌륭하게 봉사해 주신 데 대해, 그리고 사기꾼 드 푸앵시의 음모를 밝혀내는 데 도움을 주신 데 대해 진심으로 감사드립니다. 이제 재무장관과 내가 직접 그를 처리할 것이니, 당신은 당분간 전임 지휘관의 자리를 맡게 될 것이오.";
			link.l1 = "하지만...";
			link.l1.go = "burden_1";
		break;
		
		case "burden_1":
			dialog.text = "변명은 필요 없소, 부제독! 이 결정은 이미 내려졌고 국왕께서도 승인하셨소. 여기 국왕께서 친히 서명하신 명령서가 있소, 그대가 군도 내 프랑스 식민지의 사실상 총독으로 임명되었소. 이 자리에 그대보다 나은 후보는 없소. 그대의 탁월한 전쟁 경험, 이 지역과 이곳 모든 일에 책임 있는 사람들에 대한 지식, 그리고 그대의 능력과 재능은 모두 이 높고 존경받는 자리에 걸맞소. 솔직히 말하자면, 시간이 좀 지나면 '사실상'이라는 수식어 없이 다시 이 자리에 임명될 것이라 기대하오.";
			link.l1 = "하지만 나는 파리로 돌아가는 꿈을 꾸었지...";
			link.l1.go = "burden_2";
		break;
		
		case "burden_2":
			dialog.text = "프랑스가 여기서 당신을 필요로 하오! 지금 유럽에서 재무장관이 해군을 모으고 있으며, 우리 또한 이 군도에서의 존재감을 숨길 수 없을 것이오. 당신의 주요 임무는 식민지를 강화하고 요새화하며, 우리 함대의 군사력을 증대시키는 것이오. 포르게 남작과 프랑스 서인도 무역회사는 무역과 내정 발전에 집중할 것이니! 프랑스 해군을 준비시키는 데 당신만큼 적임자가 또 어디 있겠소?\n그러니 어서 일에 착수하시오, 총독 나리! 하루 종일 방 안에 앉아 있는 걸 좋아하지 않는다는 건 알지만, 이번 임무는 그럴 필요도 없소!";
			link.l1 = "즉시 따르겠습니다, 각하! 명령에는 이의가 없습니다!";
			link.l1.go = "burden_3";
		break;
		
		case "burden_3":
			dialog.text = "내 말을 제대로 이해해줘서 기쁘네. 그리고 드 포앵시 기사님을 한번 찾아가 주었으면 하네. 그분이 자네를 꼭 만나고 싶다고 고집했거든. 파리로 떠나기 전에 그분께 그런 기쁨을 빼앗을 수는 없지 않겠나? 그분은 감옥에 계실 걸세.";
			link.l1 = "알겠습니다, 각하...";
			link.l1.go = "burden_4";
		break;
		
		case "burden_4":
			DialogExit();
			DoQuestReloadToLocation("Charles_prison", "goto", "goto19", "Patria_EuropePuancieInPrison");
		break;
		
		// Портной Пуанси Xenon
		case "Tailor":
			dialog.text = "...멈출 거야, 알겠어? 이 자재들 몇 달 전에 주문했어!";
			link.l1 = "...";
			link.l1.go = "Tailor_01";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "그런데 첫 번째 배에는 뭘 싣고, 두 번째 배에는 뭘 실을지 어떻게 결정한 거지?! 나는 시골에서 온 평범한 재봉사가 아니야 - 총독 각하, 슈발리에 드 푸앵시께서 직접 내린 명령서도 있다고!";
			link.l1 = "...";
			link.l1.go = "Tailor_03";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_03":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor_02";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_04":
			dialog.text = "음, 이제 내가 뭘 더 할 수 있겠나... 기다릴 수밖에. 하지만 알아둬라: 명령이 이행되지 않아도 나는 책임지지 않을 거야!";
			link.l1 = "안녕하시오. 무슨 곤란한 일이라도 있소?";
			link.l1.go = "Tailor_05";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_05":
			dialog.text = "문제냐고? 그 정도로는 약하지! 오, 너를 어디서 본 것 같은데... 네가 새로 온 부제독 맞지?";
			link.l1 = "눈치가 빠르군. 맞아, 네 앞에 서 있는 이는 프랑스 식민지의 2인자이자 프랑스 함대의 부제독, 샤를 드 모르다.";
			link.l1.go = "Tailor_06";
			link.l2 = "형식적인 말은 집어치워, 여긴 배가 아니니까. 그리고 걱정 마, 네가 바로 나를 못 알아봤다고 해서 경비병을 부르진 않을 거야. 그냥 나를 샤를 드 모르라고 불러.";
			link.l2.go = "Tailor_07";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tailor_06":
			AddCharacterExpToSkill(pchar, "Leadership", 300);//харизма
			dialog.text = "각하, 바로 알아뵙지 못해 용서를 구합니다! 네, 맞습니다, 예상치 못한 상황을 겪었습니다.";
			link.l1 = "그게 무슨 사정이오? 내가 알기로는 파리에서 아무런 자재도 가져오지 않았다던데?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_07":
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			dialog.text = "아, 정말 고맙습니다. 말씀대로 예상치 못한 상황을 겪어서, 바로 앞에 누가 있는지 바로 알아차리지 못했습니다.";
			link.l1 = "그게 어떤 사정이오? 내가 알기로는 파리에서 아무런 자재도 가져오지 않았다는데?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_08":
			dialog.text = "그래, 맞아. 내가 몇 달 전에 그걸 주문했지. 그때 총독이 자네 임명 명령서에 서명했고, 수도에서 승인될 거라 확신하면서 새 제독 제복에 필요한 모든 재료를 준비하라고 내게 강하게 당부했네.";
			link.l1 = "그리고 자재도 전달되지 않았겠지?";
			link.l1.go = "Tailor_09";
		break;
		
		case "Tailor_09":
			dialog.text = "이런 일이 다 있나! 내가 얼마나 중요한지 설명도 하고 주문도 넣었는데... 걔네들은 더 급한 화물부터 챙긴다지 뭐야! 내가 뭘 어쩌란 말이냐? 1년 전에 미리 주문해두고, 그놈들이 언젠가 재료를 가져다주길 바래야 하나?";
			link.l1 = "정확히 무엇이 부족한 거지? 어쩌면 카리브 해에서 찾을 수 있을지도 모르겠군?";
			link.l1.go = "Tailor_10";
		break;
		
		case "Tailor_10":
			dialog.text = "설령 가능하다고 해도, 어디서 구해야 할지 전혀 모르겠어... 여기서는 좋은 재료를 못 구할 거야. 그래도... 네가 예전에 입던 장교 재킷을 바탕으로 쓸 수는 있겠지, 허락만 해 준다면. 곧 제독 제복을 입게 되면 그 재킷은 필요 없을 테니까, 맞지?";
			link.l1 = "내가 제독의 제복을 가지고 있다면, 당연히 평범한 장교 재킷은 필요 없지. 또 뭐가 있지?";
			link.l1.go = "Tailor_11";
		break;
		
		case "Tailor_11":
			dialog.text = "제복에 쓸 커프스 단추랑 칼라를 찾아야 해. 보통은 파리 장인들에게 직접 주문하지. 아주 기본적인 것들이라도 내가 손봐서 좀 더 그럴듯하게 만들 수 있거든. 하지만 그러려면 더 많이 필요하겠지...\n";
			link.l1 = "카리브에는 파리 공방이 없으니, 내가 여기서 분리 가능한 칼라와 소매가 달린 현지 옷들을 한 벌 챙겨주지. 또 뭐가 필요하지?";
			link.l1.go = "Tailor_12";
		break;
		
		case "Tailor_12":
			dialog.text = "마무리를 위해서는 아주 고급스러운 천이 필요해. 내게는 거친 섬유로도 그런 천을 짤 수 있는 방적공이 있지. 하지만 그러려면 재료가 필요해. 이상적으로는 면화가 좋겠어. 한 타래면 충분하고도 남아.";
			link.l1 = "그것도 마련할 수 있지. 다음은 뭐지?";
			link.l1.go = "Tailor_13";
		break;
		
		case "Tailor_13":
			dialog.text = "파리에서 제독의 삼각모를 가져오기로 했었지만, 재료만 있으면 내가 직접 만들 수 있어. 너한테 줄 삼각모는 원래 천으로 만들려고 했지만, 카리브 해의 짠 바람과 작열하는 태양에는 가죽이 더 나을 거야.\n가죽으로 만들면 더 오래 쓸 수 있지.";
			link.l1 = "가죽은 내가 구해올게. 걱정 마. 에스파뇰라 정글에서 황소를 쫓아다닐 필요도 없을 거야. 그게 다야?";
			link.l1.go = "Tailor_14";
		break;
		
		case "Tailor_14":
			dialog.text = "그들은 리옹에서 온 최고급 비단도 전달해야 했어. 그 비단은 가볍고 통기성이 좋으며, 습기를 잘 흡수하고 훨씬 더 빨리 마른다네.\n그리고 가장 중요한 건, 늘어나지 않고 형태를 잘 유지한다는 거지.";
			link.l1 = "그래, 무슨 비단 얘기하는지 알겠어. 하지만 식민지에서는 그걸 구하기가 좀 더 어려울지도 몰라.";
			link.l1.go = "Tailor_15";
		break;
		
		case "Tailor_15":
			dialog.text = "자, 자재는 이걸로 끝이야. 프랑스에서 최고의 훈장을 받았다고도 들었어... 생루이 훈장은 허리띠에 아무렇게나 달고 다닐 물건이 아니지. 그 훈장은 제자리가 있으니, 나한테 가져오면 제대로 달아줄게.";
			link.l1 = "좋아, 그것도 가져올게. 그냥 잃어버리지만 마!";
			link.l1.go = "Tailor_16";
		break;
		
		case "Tailor_16":
			dialog.text = "절대 안 돼! 내 목숨 걸고 지킬 거야!";
			link.l1 = "알겠소. 그게 다라면, 내가 가서 재료를 가져오겠소.";
			link.l1.go = "Tailor_17";
		break;
		
		case "Tailor_17":
			dialog.text = "한 가지 더 있어... 내 재봉 도구들이 못 쓰게 됐어. 파리에서 새 도구를 주문했지만, 안타깝게도 아직이야... 만약 필요한 재료들을 모두 구해오고, 네가 도구를 가지고 있다면 잠깐만 빌려줘, 나중에 새 걸로 돌려줄게! 그러면 바로 바느질을 시작할 수 있어.";
			link.l1 = "뭐, 내가 뭘 할 수 있겠어? 네가 필요한 건 다 가져다줄게. 어디서 널 찾으면 되지? 항만청에서 기다리고 있는 건 아니겠지?";
			link.l1.go = "Tailor_18";
		break;
		
		case "Tailor_18":
			dialog.text = "내 작업장은 부두 바로 옆 건물에 있어요 - 상륙하면 오른쪽에 보일 거예요.";
			link.l1 = "거래지. 내가 자재를 구해올게.";
			link.l1.go = "Tailor_19";
		break;
		
		case "Tailor_19":
			DialogExit();
			AddQuestRecord("Patria", "65_1");
			chrDisableReloadToLocation = false;
			ChangeCharacterAddressGroup(npchar, "Charles_houseS3", "barmen", "Stay");
			npchar.dialog.currentnode = "Tailor_20";
			LAi_SetOwnerType(npchar);
			pchar.questTemp.PatriaTailor = true;
		break;
		
		case "Tailor_20":
			dialog.text = "안녕하십니까, 부제독 나리! 새 제복에 필요한 모든 것을 가져오셨습니까?";
			link.l1 = "아직 아니야, 시간이 없었어. 잠깐만, 내가 다 챙길게.";
			link.l1.go = "Tailor_20_exit";
			if(CheckCoatItems())
			{
				link.l2 = "그래, 다 가져왔어. 여기 내 오래된 재킷, 기사단 훈장, 그리고 재봉 도구들이야. 나머지 재료들은 내 선원들이 곧 네 작업장으로 가져다줄 거야.";
				link.l2.go = "Tailor_21";
			}
		break;
		
		case "Tailor_20_exit":
			npchar.dialog.currentnode = "Tailor_20";
			DialogExit();
		break;
		
		case "Tailor_21":
			RemoveItems(pchar, "talisman9", 1);
			RemoveItems(pchar, "suit1", 1);
			RemoveItems(pchar, "tailor_tool", 1);
			RemoveCharacterGoods(pchar, GOOD_CLOTHES, 1);
			RemoveCharacterGoods(pchar, GOOD_COTTON, 1);
			RemoveCharacterGoods(pchar, GOOD_LEATHER, 1);
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			dialog.text = "훌륭하군! 솔직히, 네가 이 모든 걸 구해올 수 있을 거라곤 생각 못 했지. 나는 파리산 직물만 다루는 데 익숙했는데, 이곳 재료로도 꽤 괜찮은 옷을 만들 수 있겠구나.";
			link.l1 = "내 새 제복이 언제쯤 준비되지?";
			link.l1.go = "Tailor_22";
		break;
		
		case "Tailor_22":
			dialog.text = "보통은 최소 일주일은 걸리지만, 이번 의뢰인은 식민지에서 프랑스의 최고위 관리 두 분이시니... 사흘 뒤에 저를 찾아오십시오. 모든 것이 완벽하게 준비되어 있을 것을 약속드리오! 치수는 따로 잴 필요 없습니다, 손님의 예전 재킷을 참고해서 다 만들겠소.";
			link.l1 = "좋아! 그럼 사흘 뒤에 다시 올게.";
			link.l1.go = "Tailor_23";
		break;
		
		case "Tailor_23":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
			SetFunctionTimerCondition("Patria_Tailor_Done", 0, 0, 3, false);
		break;
		
		case "Tailor_24":
			if(CheckAttribute(pchar,"questTemp.PatriaTailorDone"))
			{
				dialog.text = "부제독님! 뵙게 되어 반갑습니다!";
				link.l1 = "그래, 약속대로 새 제복 받으러 왔어.";
				link.l1.go = "Tailor_27";
			}
			else
			{
				dialog.text = "안녕하십니까, 부제독님! 죄송하지만, 제복이 아직 준비되지 않았습니다.";
				link.l1 = "음, 적어도 무슨 일이 벌어지고 있는지 살짝 볼 수는 있을까?";
				link.l1.go = "Tailor_25";
			}
		break;
		
		case "Tailor_25":
			dialog.text = "아니, 아니야! 지금은 전혀 보여줄 만한 상태가 아니니, 네 기대를 실망시키고 싶지 않아. 조금만 기다려 줘.";
			link.l1 = "알겠어, 기다릴게.";
			link.l1.go = "Tailor_26";
		break;
		
		case "Tailor_26":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
		break;
		
		case "Tailor_27":
			dialog.text = "네, 물론이지! 말해두겠는데, 파리에서 만든 것 못지않게 잘 나왔어! 네 말이 맞았어, 식민지에서도 어디를 찾아야 할지만 알면 쓸 만한 재료를 구할 수 있더군. 잠깐만. 여기 있어! 자, 확인해 보고 한번 입어봐.";
			link.l1 = "감사합니다. 품질이 훌륭하군요! 그리고 잘 맞아요.";
			link.l1.go = "Tailor_28";
		break;
		
		case "Tailor_28":
			dialog.text = "잘했다는 말로는 부족하지! 이제 자네는 식민지 프랑스의 부제독으로서 이걸 자랑스럽게 착용할 수 있네! 그리고 약속했던 대로, 자네의 기사단 훈장도 이제 허리띠에 매달려 있지 않고 마땅한 자리에 있네.";
			link.l1 = "잘했어! 슈발리에 드 푸앵시를 만나면 내가 만족한다고 전해도 된다.";
			link.l1.go = "Tailor_29";
		break;
		
		case "Tailor_29":
			dialog.text = "반드시 전하겠습니다! 그 제복이 당신에게 잘 어울리길 바랍니다! 행운을 빕니다!";
			link.l1 = "감사합니다! 안녕히 가십시오.";
			link.l1.go = "Tailor_30";
		break;
		
		case "Tailor_30":
			DialogExit();
			npchar.dialog.currentnode = "first time";
			npchar.lifeday = 0;
			DeleteAttribute(pchar,"questTemp.PatriaTailorDone");
			DeleteAttribute(pchar, "questTemp.PatriaTailor");
			//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			GiveItem2Character(pchar, "suit5");
			EquipCharacterbyItem(pchar, "suit5");
			GiveItem2Character(pchar, "hat5");
			EquipCharacterbyItem(pchar, "hat5");
			AddItems(pchar, "tailor_tool", 1);
			Log_Info("You have received the Vice-Admiral's uniform!");
			AddQuestRecord("Patria", "65_2");
		break;
		
		//belamour legendary edition
		case "BladeUpg":
			string sItem, attrL, attrB;
			ref rItem;
			aref arItems; 
			int i, n, iItemsNum;
			dialog.text = "어떤 검을 업그레이드하고 싶으십니까?";
			
			i = 1;
			makearef(arItems, pchar.items);
			iItemsNum = GetAttributesNum(arItems);
			for(n=0; n<iItemsNum; n++)
			{
				sItem = GetAttributeName(GetAttributeN(arItems, n));
				rItem = ItemsFromID(sItem);
				if(!CheckAttribute(rItem, "groupID")) continue;
				if(rItem.groupID != BLADE_ITEM_TYPE) continue;
				if(rItem.price == 0) continue;
				if(IsEquipCharacterByItem(pchar, rItem.id)) continue;
				if(sItem != "" && rItem.groupID == BLADE_ITEM_TYPE) 
				{
					attrL = "l" + i;
					Link.(attrL) = GetItemName(rItem) + ": Attack - " + FloatToString(stf(rItem.attack),1) + ", balance - " + FloatToString(stf(rItem.Balance),1) + ", weight - " + FloatToString(stf(rItem.Weight),1);
					Link.(attrL).go = "bladeindex_"+GetItemIndex(rItem.id);
					i++;
				}
			}
			
			link.l500 = "내 마음이 바뀌었어";
			link.l500.go = "exit";
		break;
	}
} 

bool CheckCoatItems()
{
	if(GetSquadronGoods(pchar, GOOD_CLOTHES) > 0
	&& GetSquadronGoods(pchar, GOOD_COTTON) > 0
	&& GetSquadronGoods(pchar, GOOD_LEATHER) > 0
	&& GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0
	&& GetCharacterFreeItem(pchar, "talisman9") > 0
	&& GetCharacterFreeItem(pchar, "suit1") > 0
	&& GetCharacterFreeItem(pchar, "tailor_tool") > 0)
	return true;
	
	return false;
}
