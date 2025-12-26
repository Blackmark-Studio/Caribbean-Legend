void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
			dialog.text = "뭐가 필요하지?";
			link.l1 = "아무것도 아니다.";
			link.l1.go = "exit";
		break;
		
		// Родриго Хименес
		case "Himenes_exit":
			dialog.text = "더 필요한 거 있습니까, 선장님?";
			link.l1 = "지금은 아무것도 없어...";
			link.l1.go = "Himenes_exit_1";
		break;
		
		case "Himenes_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
		break;
		
		case "Himenes":
			dialog.text = "하하하! 세뇨르 헤수크리스토! 수호자 산티아고 만세! 성모 마리아 만세! 우리가 살았다! 하하하!";
			link.l1 = "스페인 놈들이다! 무장해라!";
			link.l1.go = "Himenes_1_1";
			link.l2 = "안녕하세요. 무슨 문제가 있다고 들었습니다만? 누구십니까?";
			link.l2.go = "Himenes_2";
		break;
		
		case "Himenes_1_1":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "하하하하하하하하!";
			link.l1 = "알았어, 알았다고, 진정해. 그냥 습관일 뿐이야.";
			link.l1.go = "Himenes_2";
		break;
		
		case "Himenes_2":
			dialog.text = "하하! 나리, 내 이름은 Rodrigo Jimenez다. 나는 측량사이고, 운명의 장난으로 이 불쌍한 사람들의 jefe다.";
			link.l1.go = "Himenes_3";
		break;
		
		case "Himenes_3":
			dialog.text = "우리는... 여기 상륙당했소. 하지만, 나리, 우리는 범죄자가 아니오! 하하하하!";
			link.l1 = "뭐가 웃겨?";
			link.l1.go = "Himenes_4";
		break;
		
		case "Himenes_4":
			dialog.text = "아... 미안하오, 나리! 어릴 때부터 생긴 버릇인데, 너무 긴장하면 웃음이 나와버리오. 하.";
			link.l1 = "그래서 네가 우두머리로 뽑혔다고?.. 좋아. 사람들이 이유 없이 무인도에 상륙하진 않지, 나리. 설명 좀 해볼래? 기회는 딱 한 번뿐이다.";
			link.l1.go = "Himenes_5";
		break;
		
		case "Himenes_5":
			string nationManName[4];
			nationManName[0] = "English";
			nationManName[1] = "French";
			nationManName[2] = "If you are seeing this, it's a bug";
			nationManName[3] = "Spaniard";
			dialog.text = "미안하지만, 이름을 못 들었소, 나리. 당신은 영국인인가?";
			link.l1 = nationManName[sti(pchar.BaseNation)]+". 그게 그렇게 중요한가? 지금은 내 이름에 신경 쓰지 말자.";
			link.l1.go = "Himenes_6";
		break;
		
		case "Himenes_6":
			dialog.text = "실제로, 우리는 가톨릭 스페인 교회에 의해 이단자로 간주되고 있으니, 신성한 종교재판소의 정의로운 법정에 출두해야 하지. 그래서 자네의 국적이 우리에게 그렇게 중요한 거야. 스페인 선장이라면 우리를 현지 당국에 넘길 수밖에 없지. 그런 일을 또 겪는다면 살아남지 못할 거야! 하하!";
			if (sti(pchar.BaseNation) == SPAIN) dialog.text = "하하하하하! 우리 운이 그렇지 뭐, 어차피 잃을 것도 없잖아. "+dialog.text;
			link.l1 = "음, 너한텐 다행이군, 나는 종교재판소 일엔 관심 없어. 그래서 뭐? 너희 이교도들이냐?";
			link.l1.go = "Himenes_7";
		break;
		
		case "Himenes_7":
			dialog.text = "아니요, 맹세합니다! 우리 공동체는 영광스러운 카디스 시에서 50년 동안 수공업과 무역에 종사해 왔습니다. 모든 것이 잘 되어가고 있었고, 심지어 배와 제국 식민지들과의 무역 허가증도 얻었지요. 이제 와서야 그때 우리가 어떤 선을 넘었고, 새로운 경쟁자들과 그들의 방식에 전혀 대비가 되어 있지 않았다는 걸 알게 되었습니다...";
			link.l1 = "유럽에서 누구랑 거래를 안 해서, 그 결과로 공동체 전체가 카리브 해의 무인도에 발이 묶였다고?\n난 내 문제가 큰 줄 알았는데...";
			link.l1.go = "Himenes_8";
		break;
		
		case "Himenes_8":
			dialog.text = "안타깝게도 사실이오. 우리 공동체는 새 신앙으로 개종한 유대인들이 고향 스페인으로 돌아갈 기회를 얻어 세운 곳이오. 이 오래된 역사가 비난과 공식적인 조사의 빌미가 되었소.";
			link.l1 = "그래서 도망쳤군...";
			link.l1.go = "Himenes_9";
		break;
		
		case "Himenes_9":
			dialog.text = "그래! 하하하! 우리 배를 타고 있었지! 우리는 신세계를 찾아 큐라소로 가서 새 집과 새 사업을 시작하려 했어. 하지만 우리가 종교재판소의 집요함을 얕봤고, 그 대가를 톡톡히 치렀지. 그들의 심부름꾼이 여기서 멀지 않은 곳에서 우리를 가로채더니, 선장에게 우리를 다시 본국으로 데려가라고 명령했어...\n";
			link.l1 = "제기랄!";
			link.l1.go = "Himenes_10";
		break;
		
		case "Himenes_10":
			dialog.text = "아직 더 있어! 하! 우리 선장은 대서양을 다시 건너 우리를 데려가는 것도, 가장 가까운 항구에서 책임을 벗는 것도 귀찮았던 거지. 그래서 솔로몬처럼 현명한 결정을 내렸다며, 우리에게 식량을 주고 여기 내려놓고 끝이었어.";
			link.l1 = "정말 비극적인 이야기군, 의심할 여지가 없어. 정리해 보자면, 집으로 돌아갈 수도 없고, 우호적인 식민지들도 널 신고할 거고, 외국 항구들도 널 반기지 않을 거야 - 이 지역의 전쟁은 끝날 기미가 없지. 앞으로 어떻게 할 생각이냐?";
			link.l1.go = "Himenes_11";
		break;
		
		case "Himenes_11":
			dialog.text = "너무 암울하게 말씀하셔서, 나리, 할 말을 잃었습니다. 마치 이 섬 말고는 우리에게 더 나은 곳이 없는 것만 같습니다.";
			link.l1 = "난 그렇게 생각하지 않아, 더 좋은 섬이 있어.";
			link.l1.go = "Himenes_12";
		break;
		
		case "Himenes_12":
			dialog.text = "정말이야? 스페인어냐?";
			link.l1 = "내 거야. 운명처럼, 나는 무인도에 있던 옛 해적 소굴을 물려받았지. 이제 거기가 내 근거지고, 나는 그곳을 확장하고 섬을 탐험하며, 가능하다면 거기에 공장도 세우고 싶어.";
			link.l1.go = "Himenes_13";
		break;
		
		case "Himenes_13":
			dialog.text = "너 해적이냐?";
			link.l1 = "그래.";
			link.l1.go = "Himenes_14_1";
			link.l2 = "아니.";
			link.l2.go = "Himenes_14_2";
		break;
		
		case "Himenes_14_1":
			dialog.text = "신세계! 그래, 우리가 여기 왔지. 고향에서는 해적들이 진짜 악마라서 인간도 아니라고들 해. 아이들을 잡아먹고, 여자를 능욕하며, 착한 가톨릭 신자들의 가죽을 산 채로 벗긴다고 하더군. 그게 사실이야?";
			link.l1 = "그건 요일에 따라 달라. 이 이야기는 다음에 하자. 나는 사람을 찾고 있어. 몇 년 동안 문명에서 멀리 떨어져 살 각오가 된, 성실하고 유능한 사람들 말이야. 그런 일에 관심 있나?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_14_2":
			dialog.text = "이미 범죄자인 김에, 해적 한 놈쯤은 보고 싶었는데 아쉽군.";
			link.l1 = "아마 다시 그런 기회가 올지도 모르지. 이 이야기는 다음에 하자. 나는 몇 년 동안 문명과 멀리 떨어져 살 각오가 되어 있는 성실하고 유능한 사람을 찾고 있어. 그런 일에 관심 있나?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_15":
			dialog.text = "우리에겐 다른 선택지가 없어. 하지만 사실 그렇게 나쁜 선택도 아니지. 우리가 평화롭게 살고 일할 수 있게 해준다면 받아들이겠어. 언젠가 집으로 돌려보내겠다고 약속해 줘! 약속해 줘, 나리, 그리고 이름도 알려 줘...\n";
			link.l1 = "나, 선장 "+GetFullName(pchar)+", 맹세하지. ?";
			link.l1.go = "Himenes_16";
		break;
		
		case "Himenes_16":
			dialog.text = "하하! 우리는 살았다! 그렇게 하자! 우리는 몇몇 가족들로, 약 30명쯤 된다. 모두 글을 읽고 쓸 줄 알며, 수공예와 상업에도 능하다.";
			link.l1 = "운명이 정해졌소... 어서 배에 오르시오!";
			link.l1.go = "Himenes_17";
		break;
		
		case "Himenes_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto1", "none", "", "", "", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			IslaMona_TerksHimenesOnBoard();
		break;
		
		case "Himenes_18":
			dialog.text = "만나서 반갑소, Rodgar 나리. 앞으로 한동안 함께 지내며 일해야 할 것 같군... 이런, 이 더위를 어떻게 견디시오?";
			link.l1 = "";
			link.l1.go = "Himenes_19";
		break;
		
		case "Himenes_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_14";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_20":
			dialog.text = "괜찮으시다면, 제가 나서겠습니다: 선장님, 정착하고 재고와 땅을 빠르게 점검할 하루만 주십시오. 로드가르 나리께서 이 땅을 어떻게 활용할지 아이디어가 많으실 겁니다. 우리가 좋은 팀이 될 것 같습니다.";
			link.l1 = "선택권이 없지, 하이메네스. 하하!";
			link.l1.go = "Himenes_21";
		break;
		
		case "Himenes_21":
			dialog.text = "하하하하하하!";
			link.l1 = "";
			link.l1.go = "Himenes_22";
		break;
		
		case "Himenes_22":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_23":
			dialog.text = "네, 선장님?";
			link.l1 = "하이메네스, 나한테 좋은 소식 있나?";
			link.l1.go = "Himenes_24";
		break;
		
		case "Himenes_24":
			dialog.text = "선장님, 이건 악몽입니다. 물론 선장님의 집은 나쁘지 않지요. 하지만 그 외에는... 이런 오두막에서, 잡초에 둘러싸여 사는 건 도저히 불가능해요, 그리고 로드가르 나리는 섬 반대편에서 무슨 일이 벌어지는지도 전혀 모르고 있다니까요!! 믿을 수가 없어요! 하하!";
			link.l1 = "지금 긴장한 거야, 아니면 이 상황이 웃긴 거야?";
			link.l1.go = "Himenes_25";
		break;
		
		case "Himenes_25":
			dialog.text = "당연히, 웃기지! 그동안 이놈들은 뭘 하고 있었던 거야? 우선 집 두어 채를 더 짓고, 이 오두막들도 쓸 만하게 수리해야 해. 사람들이 제대로 살아야 열심히 일도 하지. 그리고 해적들에게 섬 전체를 정찰해 보라고 시킬 거야. 이곳이 바위랑 모래만 많은 게 아닐 수도 있으니까. 모든 게 끝나면, 이 땅을 어떻게 해야 할지 정확히 말해 줄 수 있을 거야.";
			link.l1 = "좋군! 내가 뭘 해야 하지?";
			link.l1.go = "Himenes_26";
		break;
		
		case "Himenes_26":
			AddQuestRecordInfo("IslaMonaData", "1");
			dialog.text = "집과 가구, 임시 거처에 쓸 자재들이오. 내가 전부 계산해 뒀소. 여기, 목록을 가져가시오.";
			link.l1 = "인상적이군...";
			link.l1.go = "Himenes_27";
		break;
		
		case "Himenes_27":
			dialog.text = "정말입니까? 나리, 우리는 대성당도 지었습니다! 이건 정말 대단하지 않습니까...";
			link.l1 = "믿어 주지! 근데 여기다 대성당이나 잘못 짓지 마라. 매번 자재를 잔뜩 실어 나르게 되는 거 아냐?";
			link.l1.go = "Himenes_28";
		break;
		
		case "Himenes_28":
			dialog.text = "아니, 이 자재들로 당분간은 버틸 수 있겠지만, 나중에는 또 뭔가를 들여와야 할 거야. 앞으로 이런 곤란을 피하고 싶으면 자재를 두 배로 가져오라고.";
			link.l1 = "그래, 설득당했어. 내가 할 수 있는 걸 알아볼게. 기한은 있어?";
			link.l1.go = "Himenes_29";
		break;
		
		case "Himenes_29":
			dialog.text = "아니오, 나리. 하지만 부디 지체하지 말아 주십시오. 이 일은 진행을 위해 반드시 해야 할 일입니다. 그리고 사람들도 살 곳이 필요하지요. 자재를 창고에 옮기고, 모든 준비가 끝나면 저에게 꼭 알려주십시오. 아, 깜빡할 뻔했군요! 섬 탐사에 관해서는 로드가 씨와 상의하십시오.";
			link.l1 = "동의한다!";
			link.l1.go = "Himenes_30";
		break;
		
		case "Himenes_30":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			pchar.questTemp.IslaMona = "stalk";
			AddQuestRecord("IslaMona", "6");
		break;
		
		case "Himenes_31":
			dialog.text = "예, 선장님?";
			if (IslaMona_CheckBuild()) // привез товары на стройку
			{
				link.l1 = "안녕, Jiménez. 창고 좀 확인해.";
				link.l1.go = "Himenes_32_1";
			}
			else // не привез товары на стройку
			{
				link.l1 = "안녕, Jiménez. 내 부하들이 섬 전체를 샅샅이 뒤졌어. 뭐라고 할래?";
				if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_32_2"; // привез еду и лекарства
				else link.l1.go = "Himenes_32_3";
			}
		break;
		
		case "Himenes_32_1":
			IslaMona_RemoveBuild(); // сразу удаляем товары со склада
			dialog.text = "이 책임을 훌륭하게 해냈군! 언제든 카디스에 오면 내 밑에서 창고지기로 일해 보지 않겠나!";
			link.l1 = "가는 중이야! 말해 봐, 친구, 이제 어떻게 할 거야?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_34_1"; // привез еду и лекарства
			else link.l1.go = "Himenes_34_2";
		break;
		
		case "Himenes_32_2":
			dialog.text = "선장 나리, 우선 숙소와 보급부터 처리합시다. 계획은 그다음에 세우도록 하지요. 창고에서 나리께서 적어주신 물품을 기다리고 있겠소.";
			link.l1 = "알겠어. 먼저 집을 짓고 이곳을 정리해야 해. 곧 물자가 도착할 거야.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_32_3":
			dialog.text = "선장님, 우선 숙소와 보급품부터 처리합시다. 계획은 나중에 세워도 됩니다. 창고에서 선장님이 적어주신 물품을 기다리고 있소. 그리고 선장님의 해적 친구도 식량과 약품을 기다리고 있소.";
			link.l1 = "알겠어. 먼저 집을 짓고 이곳을 정리해야 해. 곧 물자가 도착할 거야. 내 해적 친구를 위해서도 말이지.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_33":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_31";
		break;
		
		case "Himenes_34_1":
			dialog.text = "여섯 달만 주십시오, 선장님. 그럼 이곳이 완전히 달라질 겁니다.";
			link.l1 = "여섯 달 후면 너도, 이 정착지도, 여기 있는 자재들도 다 사라진다는 말이냐? 나중에 보자!";
			link.l1.go = "Himenes_37"; // все выполнил
		break;
		
		case "Himenes_34_2":
			dialog.text = "네가 이 도적과 일을 마무리하면 바로 작업을 시작하겠네. 그가 자네에게 식량과 약을 요구했지, 나도 그 의견에 동의하네 – 합리적인 요구라 생각하네.";
			link.l1 = "당신의 말을 그에게 전하겠습니다.";
			link.l1.go = "Himenes_35";
			AddQuestRecord("IslaMona", "11");
		break;
		
		case "Himenes_35":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_36";
		break;
		
		case "Himenes_36":
			dialog.text = "자, 선장님? 네 해적이 시킨 일 다 했나?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food"))
			{
				link.l1 = "Rodgar와의 모든 문제를 해결했어. 섬 정찰을 시작했고, 식량과 약품은 창고에 있다네.\n이제 자네 차례야.";
				link.l1.go = "Himenes_34_1";
			}
			else
			{
				link.l1 = "걱정 마, 우리가 해결할 거야. 이건 내가 처리할게.";
				link.l1.go = "Himenes_35";
			}
		break;
		
		case "Himenes_37":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			DeleteAttribute(pchar, "questTemp.IslaMona.Food");
			pchar.questTemp.IslaMona = "build";
			AddQuestRecord("IslaMona", "12");
			SetFunctionTimerCondition("IslaMona_BuildDone", 0, 0, 180, false);
		break;
		
		case "Himenes_38":
			dialog.text = "나리 선장! 어떻게 생각하시오? 하하하?";
			link.l1 = "훨씬 낫군. 보고하라, 히메네스!";
			link.l1.go = "Himenes_39";
		break;
		
		case "Himenes_39":
			dialog.text = "이제 여기서 정말로 살 수 있어! 우리가 모든 집을 청소하고 다시 지었어, 물론 네 집은 빼고 말이지. 아주 호화롭진 않지만, 우리 벨리즈보다 못하지도 않아.";
			link.l1 = "벨리즈는 오래전부터 영국 땅이었소, 히메네스.";
			link.l1.go = "Himenes_40";
		break;
		
		case "Himenes_40":
			dialog.text = "그 집안들이 그걸 아는지 잘 모르겠네요, 선장님, 하하!";
			link.l1 = "이제 살 곳도 생겼고, 정착지도 제법 문명화되어 보이네. 다음엔 뭐 할 거야?";
			link.l1.go = "Himenes_41";
		break;
		
		case "Himenes_41":
			dialog.text = "둘러보고, 얀센 나리와 이야기한 뒤 내게 돌아오게. 섬 정찰 결과와 앞으로의 계획을 논의하겠네.";
			link.l1 = "언제부터 로드가를 그렇게 부르기 시작했지? 너희 둘은 항상 사이가 안 좋지 않았어?";
			link.l1.go = "Himenes_42";
		break;
		
		case "Himenes_42":
			dialog.text = "그리고 그놈들은 아직도 우리한테 있지. 하지만 어떻게든 협력 관계를 만들어야 해.";
			link.l1 = "고맙소, Rodrigo. 곧 돌아오겠소.";
			link.l1.go = "Himenes_43";
		break;
		
		case "Himenes_43":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload6", "none", "", "", "", 10.0); // возможно будет иной локатор в новой локации
			pchar.questTemp.IslaMona = "village";
		break;
		
		case "Himenes_44":
			dialog.text = "선장님. 얀센 나리.";
			link.l1 = "어서, 섬 정찰 결과를 말해 줘.";
			link.l1.go = "Himenes_45";
		break;
		
		case "Himenes_45":
			dialog.text = "네, 선장님. 제가 직접 우리 탐사자와 함께 몇 군데를 살펴봤습니다. 뭐라고 해야 할지... 이슬라 모나는 가난하고 작으며 별로 특별할 것 없는 섬입니다. 건설할 공간도 거의 없고, 지형은 험하고 가파르며 비옥한 땅도 거의 없습니다. 해변이 세 곳, 물에 잠긴 동굴 하나, 빽빽한 덤불, 앵무새 몇 마리, 염소 떼, 그리고 우리뿐입니다...\n";
			link.l1 = "진심이야? 이 섬에서 가장 귀한 자산이 염소 떼라는 거냐?";
			link.l1.go = "Himenes_46";
		break;
		
		case "Himenes_46":
			dialog.text = "하하하하! 내가 물어보려고 했지, 나리! 하하! 네가 내 말을 끝까지 듣게 두질 않았잖아!";
			link.l1 = "";
			link.l1.go = "Himenes_47";
		break;
		
		case "Himenes_47":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_38";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_48":
			dialog.text = "";
			link.l1 = "좋아, 알았어, 진정하고 계속해. 있잖아, 나 이곳에 꽤 많이 투자했거든.";
			link.l1.go = "Himenes_49";
		break;
		
		case "Himenes_49":
			dialog.text = "헛된 일이 아니지! 동굴에는 신선한 물이 충분하고, 과실수가 자랄 만한 흙도 있어. 염소도 기를 수 있지. 낚시와 동료들의 노력만 있으면 식량 문제는 금방 해결될 거야.";
			link.l1 = "그래서 이제 더 이상 여기로 음식을 가져올 필요는 없겠군? 나쁘지 않네. 이곳이 내내 내 손길 없이도 버틸 수 있기를 바랐지. 계속하자.";
			link.l1.go = "Himenes_50";
		break;
		
		case "Himenes_50":
			dialog.text = "모든 말이 맞소, 나리. 하지만 그게 전부가 아니오! 우선, 로드가르 나리가 선술집을 짓겠다는 생각을 냈소. 그게 당신에게 어떤 이득이 될지는 모르겠지만, 저 악당이 뭔가 꿍꿍이가 있는 것 같소.";
			link.l1 = "걔는 취하고 싶어서 그런 거야!";
			link.l1.go = "Himenes_51";
		break;
		
		case "Himenes_51":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_40";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_52":
			dialog.text = "둘째로, 처음 생각했던 것보다 총독 만이 훨씬 더 깊다는 사실을 알게 되었소. 이제 제대로 된 부두를 지을 수 있겠군.";
			link.l1 = "내게 어떤 이득이 될지는 잘 모르겠지만, 그거면 이미 좋은 소식이지. 그게 전부는 아니겠지?";
			link.l1.go = "Himenes_53";
		break;
		
		case "Himenes_53":
			dialog.text = "우리는 보코테 나무 숲을 발견했어. 공장을 짓기에 딱 좋은 곳이야.";
			link.l1 = "나를 기쁘게 해주는구나, Rodrigo! 정말로, 훌륭한 소식이야!";
			link.l1.go = "Himenes_54";
		break;
		
		case "Himenes_54":
			dialog.text = "지금은 이게 다야, 나리. 앞으로 더 좋은 생각이 떠오를지도 몰라. 알겠지, 일하다 보면 최고의 아이디어가 나오는 법이니까! 뭘 물어보고 싶어?";
			link.l1 = "바코테에 대해 말해 봐. 뭔가 괜찮아 보이는데.";
			link.l1.go = "Himenes_55";
		break;
		
		case "Himenes_55":
			dialog.text = "내 생각에, 작은 공장이라면 이 귀한 목재를 몇 년 동안 채취할 수 있을 것이오. 비축량은 많지 않지만, 이 자원은 전략적이오. 섬 중앙에 부지를 정리해서 그곳에 창고가 딸린 집을 지을 수 있소. 그게 시작이오. 건축 자재 외에도 수갑과 머스킷 총이 각각 15세트쯤 더 필요하오.";
			link.l1 = "우리가 수갑이 왜 필요하지? 그리고 왜 하필 열다섯 개야?";
			link.l1.go = "Himenes_56";
		break;
		
		case "Himenes_56":
			dialog.text = "힘든 노동이지, 나리. 노예처럼 일하는 거라고도 할 수 있겠소.";
			link.l1 = "알겠어. 헤헤...";
			link.l1.go = "Himenes_57_1";
			link.l2 = "미쳤어? 나는 노예주가 되지 않을 거야!";
			link.l2.go = "Himenes_57_2";
		break;
		
		case "Himenes_57_1":
			dialog.text = "";
			link.l1 = "근데 우리는 왜 머스킷이 필요한 거지? 그리고 왜 딱 한 자루만?";
			link.l1.go = "Himenes_59";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Himenes_57_2":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_42";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Himenes_58":
			dialog.text = "나도 그 해적 말에 동의하오, 나리. 나는 당신을 이해하지 못하겠소, 선장. 이 지역의 경제 전체가 노예 노동에 기반하고 있고, 앞으로도 오랫동안 그럴 것이오. 우리가 뭐가 더 낫다는 것이오?";
			link.l1 = "내가 결정하겠다. 그동안 왜 머스킷이 필요한지 말해 봐라. 그리고 왜 하필 하나만 필요한 거지?";
			link.l1.go = "Himenes_59";
		break;
		
		case "Himenes_59":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_60":
			dialog.text = "물론, 공장은 유지보수가 필요할 것이오. 공장이 세워지면 이 섬은 당신을 주요 교역 파트너로 삼아 경제가 돌아가게 될 것이오.\n노예들의 식사는 우리가 책임지겠지만, 경비와 생산 비용은 당신이 직접 부담해야 하오.\n정착민들은 한 번에 20두블룬과 와인 다섯 병을 요구할 것이오.\n경비 문제는 얀센 나리와 직접 협상하시오.";
			link.l1 = "";
			link.l1.go = "Himenes_61";
		break;
		
		case "Himenes_61":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_46";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_62":
			dialog.text = "매달 마흔 단위씩이야. 그리고 금은 미래를 위한 거지. 언젠가 네가 우리를 여기서 데려갈 거라는 약속, 기억하지? 어떤 일이든 대가를 받아야 하고, 네 두블룬으로 우리는 정착지에서 사냥꾼과 장인들에게 일값을 치를 거야. 그렇게 하면 우리는 교역을 하게 되고, 교역이 있으면 문명도 따라오지!";
			link.l1 = "바로 그거야! 좋아! 지금은 모든 게 그럴듯하게 들리는군...";
			link.l1.go = "Himenes_63";
		break;
		
		case "Himenes_63":
			dialog.text = "또 뭐가 궁금해?";
			link.l1 = "그래서, 선술집 이야기는 뭐지? 왜 극장은 짓지 않는 거야?";
			link.l1.go = "Himenes_64";
		break;
		
		case "Himenes_64":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_65":
			dialog.text = "선장님, 제가 그에게 선장님이 그 집에 대해 탐탁지 않게 생각하실 거라고 경고했어요. 하지만 이게 유일한 방법입니다. 선장님 집이... 에헴, 마을에서 제일 크니까, 1층을 홀로 개조하고, 테이블과 주방을 마련하겠습니다. 지하실에는 술과 음식을 보관할 거고요. 요리하고 음악 연주할 사람들도 있습니다. 2층은 그대로 선장님께 남겨두고 손대지 않겠습니다. 1층에 있는 선장님 물건들은 저희가 직접 2층으로 옮기겠습니다.";
			link.l1 = "좋아. 그래서 선술집에서 우리에게 뭘 제공해 준다는 거지?";
			link.l1.go = "Himenes_66";
		break;
		
		case "Himenes_66":
			dialog.text = "우리가 문화를 불어넣을 테니, 자네는 카리브 한가운데에서 약 300명을 예비로 둘 기회를 얻게 될 거야.";
			link.l1 = "흥미롭군... 생각해 볼게.";
			link.l1.go = "Himenes_67";
		break;
		
		case "Himenes_67":
			dialog.text = "또 뭐가 궁금한가?";
			link.l1 = "그래, 부두는 어쩔 건데?";
			link.l1.go = "Himenes_68";
		break;
		
		case "Himenes_68":
			dialog.text = "간단하오. 우리가 총독의 만에서 암초를 치우고, 신호등을 설치한 다음, 부두를 지을 것이오. 얀센 나리가 말하길, 그 만에는 배 세 척이나 일류 함선 한 척을 정박시킬 수 있다 하오. 그리고 매번 해변에 딩기를 끌고 오지 않아도 되니, 여기로 돌아오는 것도 훨씬 편할 것이오.";
			link.l1 = "그러면 좋겠군.";
			link.l1.go = "Himenes_69";
		break;
		
		case "Himenes_69":
			dialog.text = "무엇을 알고 싶으십니까?";
			link.l1 = "지금은 이게 다야. 무엇을 지을지 결정하면 다시 올게.";
			link.l1.go = "Himenes_70";
		break;
		
		case "Himenes_70":
			dialog.text = "나리 선장, 이 문서를 받아주십시오. 여러 번 반복하지 않으려고 모든 세부 사항을 직접 적어두었습니다.\n읽어보고, 재료를 가져와서 일을 시작하십시오.";
			link.l1 = "감사합니다, Rodrigo.";
			link.l1.go = "Himenes_71";
		break;
		
		case "Himenes_71":
			DialogExit();
			IslaMona_HouseDialogFin();
		break;
		
		case "Himenes_72": // нода Хименеса строителя и управляющего факторией
			if (CheckAttribute(pchar, "questTemp.IslaMona.RecordPart")) // после защиты Исла Моны - нужно ещё 10 рабов
			{
				dialog.text = "나리 선장, 공장에서 일할 노예 10명이 필요합니다 - 제가 말씀드렸지요, 잊으신 건 아니겠지요?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 10)
				{
					link.l1 = "이미 전달했다. 짐을 내리고 생산을 시작해라.";
					link.l1.go = "Himenes_plantation_12";
				}
				else
				{
					link.l1 = "내 기억은 멀쩡해. 곧 가져올게.";
					link.l1.go = "Himenes_plantation_14";
				}
				break;
			}
			dialog.text = "그래서, 선장 나리, 뭐라 하시겠소?";
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Harbour"))
			{
				link.l1 = "나는 깨끗한 만과 안전한 부두가 필요하다. 내 함대의 근거지가 될 거다.";
				link.l1.go = "Himenes_harbour";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Tavern"))
			{
				link.l2 = "가서 선술집을 지어라. 모두가 고마워할 거고, 나도 여기서 비축해둘 수 있겠지.";
				link.l2.go = "Himenes_tavern";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Plantation"))
			{
				link.l3 = "플랜테이션을 짓기 시작해라. 이제 투자한 걸 회수할 때다.";
				link.l3.go = "Himenes_plantation";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Slave") && IslaMona_CheckSlave())
			{
				link.l4 = "로드리고, 가장 귀중한 전문가들과 장비가 공장에 도착했네. 이제 작업을 시작해도 되네.";
				link.l4.go = "Himenes_plantation_7";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Factory.Part") && sti(pchar.questTemp.IslaMona.Factory.Part) > 0)
			{
				link.l4 = "로드리고, 내 아이언우드 가지러 왔다.";
				link.l4.go = "Himenes_bacaut";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Tavern") && pchar.questTemp.IslaMona.Tavern == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Factory") && !CheckAttribute(pchar, "questTemp.IslaMona.Church"))
			{
				link.l5 = "로드리고, 우리 대공사를 끝냈나?";
				link.l5.go = "Himenes_church";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "start" && IslaMona_CheckChurch())
			{
				link.l5 = "Rodrigo, 네 교회를 짓자.";
				link.l5.go = "Himenes_church_10";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "Wait_candles" && IslaMona_CheckCandles())
			{
				link.l5 = "Rodrigo, 네 교회 물품을 가져왔어.";
				link.l5.go = "Himenes_church_10_3";
			}
			link.l10 = "지금은 아무것도 없어...";
			link.l10.go = "Himenes_73";
		break;
		
		case "Himenes_harbour":
			if (IslaMona_CheckHarbour())
			{
				dialog.text = "자재는 준비되어 있고, 모든 것이 갖추어졌소. 공사는 4개월 걸릴 것이오.";
				link.l1 = "서두르는 건 아니지! 그래, 행운을 빌어, Rodrigo.";
				link.l1.go = "Himenes_harbour_1";
			}
			else
			{
				dialog.text = "창고에 자재가 충분하지 않은 것 같소. 목록을 다시 한 번 확인해 주시오.";
				link.l1 = "내가 처리할게.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_tavern":
			if (IslaMona_CheckTavern())
			{
				dialog.text = "자재는 준비되어 있고, 모든 것이 갖추어졌소. 공사는 3개월 걸릴 것이오.";
				link.l1 = "서두르는 건 아니지! 그래, 행운을 빌어, Rodrigo.";
				link.l1.go = "Himenes_tavern_1";
			}
			else
			{
				dialog.text = "창고에 자재가 충분하지 않은 것 같소. 목록을 다시 한 번 확인해 주십시오.";
				link.l1 = "내가 처리할게.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_plantation":
			if (IslaMona_CheckPlantation())
			{
				dialog.text = "자재는 준비되어 있고, 모든 것이 갖추어졌소. 공사는 6개월 걸릴 것이오.";
				link.l1 = "너 그렇게 급한 건 아니지! 행운을 빌어, 로드리고.";
				link.l1.go = "Himenes_plantation_1";
			}
			else
			{
				dialog.text = "창고에 자재가 부족한 것 같소. 부탁이니, 목록을 다시 확인해 주시오.";
				link.l1 = "내가 처리할게.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_73":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_harbour_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveHarbour();
			pchar.questTemp.IslaMona.Harbour = "true";
			SetFunctionTimerCondition("IslaMona_BuildHarbour", 0, 0, 120, false);
		break;
		
		case "Himenes_harbour_2":
			dialog.text = "어서 오시오, 선장님. 새 항구는 마음에 드시오?";
			if (stf(environment.time) > 22.0 || stf(environment.time) < 5.0)
			{
				link.l1 = "어두워, 로드리고! 네가 자랑하는 부두에 거의 부딪칠 뻔했잖아! 그래도 불은 켜놔서 다행이야!";
				link.l1.go = "Himenes_harbour_3";
			}
			else
			{
				link.l1 = "나쁘지 않군, 로드리고! 별거 아닌 것 같아도, 이 나무판자를 따라 해안까지 걷는 게 참 좋구나. 그리고 만도 더 쉽게 드나들 수 있게 되었지. 자, 이제 이 작은 만에 더 많은 배를 댈 수 있겠군?";
				link.l1.go = "Himenes_harbour_4";
			}
		break;
		
		case "Himenes_harbour_3":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_51";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_harbour_4":
			sld = characterFromId("Islamona_carpenter");
			sld.portman.info = "true"; // если вдруг до сих пор не говорил об условиях стоянки
			pchar.questTemp.IslaMona.Harbour = "done"; // флаг - пристань построена и сдана
			dialog.text = "예, 선장님. 솔직히 말씀드리자면, 나름대로 자부심이 있습니다. 대규모 건설 프로젝트를 어떻게 진행하고 싶은지 언제든 말씀해 주십시오.";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && pchar.questTemp.IslaMona.Plantation == "complete") // если пересеклось со сдачей фактории
			{
				link.l1 = "건설 얘기가 나와서 말인데, 내 공장도 이제쯤 완공됐겠지. 그렇지, 로드리고?";
				link.l1.go = "Himenes_plantation_2";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Himenes_harbour_5";
			}
		break;
		
		case "Himenes_harbour_5":
			DialogExit();
			IslaMona_HarbourClear();
		break;
		
		case "Himenes_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveTavern();
			pchar.questTemp.IslaMona.Tavern = "true";
			SetFunctionTimerCondition("IslaMona_BuildTavern", 0, 0, 90, false);
		break;
		
		case "Himenes_tavern_2":
			dialog.text = "히-잇! 선장! 여기서 우리 축하하고 있어!";
			link.l1 = "로드가르. 로드리고. 젠장!";
			link.l1.go = "Himenes_tavern_3";
		break;
		
		case "Himenes_tavern_3":
			dialog.text = "왜 그러십니까, 선장님? 벽 색깔이 마음에 안 드십니까?";
			link.l1 = "이제야 너희 둘이 같은 이름을 가졌다는 걸 알겠구나! 하하하! 스페인 놈이랑 해적 놈이, 같은 이름으로 무인도에 선술집을 짓고는 인디언 신들이 모두를 잡아먹고 해 뜨기 전에 세상이 끝날 것처럼 같이 술을 마시고 있네! 하하! 나도 함께할게!\n";
			link.l1.go = "Himenes_tavern_4";
		break;
		
		case "Himenes_tavern_4":
			dialog.text = "하하하! 진짜 그렇지! 제대로 한 건 했군!";
			link.l1 = "득점이다!";
			link.l1.go = "Himenes_tavern_5";
		break;
		
		case "Himenes_tavern_5":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_ReloadTavern();
		break;
		
		case "Himenes_plantation_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemovePlantation();
			pchar.questTemp.IslaMona.Plantation = "true";
			SetFunctionTimerCondition("IslaMona_BuildPlantation", 0, 0, 180, false);
		break;
		
		case "Himenes_plantation_2":
			dialog.text = "모든 준비가 끝났소. 갈까? 공장을 보여주겠소.";
			link.l1 = "앞장서.";
			link.l1.go = "Himenes_plantation_3";
		break;
		
		case "Himenes_plantation_3":
			DialogExit();
			pchar.questTemp.IslaMona.Plantation.Harbour = "true"; // наложилась сдача пристани и фактории
			IslaMona_PlantationGo();
		break;
		
		case "Himenes_plantation_4":
			dialog.text = "선장님, 거의 모든 준비가 끝나 곧 작업을 시작할 수 있습니다. 일꾼들을 위한 숙소, 원자재 창고, 가공 구역까지 – 제대로 된 공장이 완성되었습니다. 정글에서는 벌목에 가장 적합한 나무들도 이미 표시해 두었습니다.\n일꾼 열다섯 명과 약속한 물품 – 족쇄 15개와 머스킷 15정 – 을 가져오시면 바로 작업을 시작하겠습니다.";
			link.l1 = "우리? 노예들을 말하는 거야?";
			link.l1.go = "Himenes_plantation_5";
		break;
		
		case "Himenes_plantation_5":
			dialog.text = "하! 노예들은 벌목하고, 정착민들은 가공하고, 해적들은 지킬 거야. 모두 할 일이 생기겠군 – 대단한 일을 시작했어, 선장.";
			link.l1 = "거의 약속의 땅 같군, 그치. 물건 기다려, 이제 사냥하러 갈 시간이야.";
			link.l1.go = "Himenes_plantation_6";
		break;
		
		case "Himenes_plantation_6":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Plantation.Slave = "true"; // привезти рабов, кандалы и мушкет для запуска фактории
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "IslaMona_factoria_residence", "sit", "sit1", "IslaMona_PlantationHouse", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5);
			pchar.questTemp.IslaMona.Plantation = "done"; // флаг - фактория построена и сдана
		break;
		
		case "Himenes_plantation_7":
			dialog.text = "슬픈 운명이군... 저들은 이곳을 영영 떠나지 못하겠지.";
			link.l1 = "로드가... 아니, 로드리고! 첫째로, 그들이 떠날 수도 있어. 그리고 둘째로, 네가 터크스에서 다른 사람을 만났어도 운명이 더 나아지진 않았을 거야.";
			link.l1.go = "Himenes_plantation_8";
		break;
		
		case "Himenes_plantation_8":
			dialog.text = "그건 잘 알고 있습니다, 선장님. 그리고 그걸 잊은 적도 없습니다. 이 공장의 운영에 대해 말씀드리죠. 다음 달부터, 매달 열다섯째 날에 가공된 바쿠트 목재 40통을 납품할 예정입니다. 물론 매달 직접 오실 필요는 없습니다 – 모든 배치는 이 공장에 보관되어 선장님을 기다릴 것입니다.";
			link.l1 = "그럼, 한 번에 여러 묶음을 가져갈 수 있다는 거야?";
			link.l1.go = "Himenes_plantation_9";
		break;
		
		case "Himenes_plantation_9":
			dialog.text = "물론 적당히 해야지 - 너무 오래 떠나 있지는 마. 사람들이 몇 년씩이나 돈도 못 받고, 유일한 손님이 살아 있는지도 모른 채 일하진 않을 거야. 여섯 번 정도 물건을 배달한 뒤에는 영업을 중단할 생각이야.";
			link.l1 = "한 번에 모든 물건을 다 가져가야 하나? 그리고 가격은 어떻게 되지, 다시 한 번 말해 줘?";
			link.l1.go = "Himenes_plantation_10";
		break;
		
		case "Himenes_plantation_10":
			dialog.text = "그래, 한 번에 다야. 표준 바카웃 통나무 한 개 값은 도블룬 열 개지. 게다가, 한 번 거래할 때마다 좋은 럼주 다섯 병이랑 와인도 다섯 병을 내야 해. 로드가르는 이런 가격은 세상 어디에도 없다고 큰소리치더라.";
			link.l1 = "정말 동의해! 고마워, Rodrigo. 이제 일하자!";
			link.l1.go = "Himenes_plantation_11";
		break;
		
		case "Himenes_plantation_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			DeleteAttribute(pchar, "questTemp.IslaMona.Plantation.Slave");
			AddQuestRecordInfo("Unique_Goods", "5");
			IslaMona_RemoveSlave();
		break;
		
		case "Himenes_plantation_12":
			dialog.text = "좋아! 이제 다시 일하자!";
			link.l1 = "좋아.";
			link.l1.go = "Himenes_plantation_13";
		break;
		
		case "Himenes_plantation_13":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_FactoryReActivar(); // запустить факторию
		break;
		
		case "Himenes_plantation_14":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_bacaut":
			dialog.text = "물론입니다, 선장님, 가져가십시오. 다음 선적을 위해 준비된 물품 목록은 다음과 같습니다: "+sti(pchar.questTemp.IslaMona.Factory.Part)+", 그게 "+sti(pchar.questTemp.IslaMona.Factory.Goods)+" 통나무지. 그러니 우리에게 빚진 거야 "+sti(pchar.questTemp.IslaMona.Factory.Dublon)+" 두블룬, "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" 럼주 병들과, 그리고\n "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" 포도주 병들, 그거 다 가지고 있나?";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Factory.Dublon) && PCharItemsTotal("potionrum") >= sti(pchar.questTemp.IslaMona.Factory.Bottle) && PCharItemsTotal("potionwine") >= sti(pchar.questTemp.IslaMona.Factory.Bottle))
			{
				link.l1 = "물론이지. 여기 네 보수다.";
				link.l1.go = "Himenes_bacaut_1";
			}
			else
			{
				link.l1 = "아직 다 준비하지 못한 것 같군. 금방 가져오겠소.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_1":
			if (IslaMona_CheckBacautSpace())
			{
				dialog.text = "훌륭합니다. 우리가 공장에서 당신의 창고로 바쿠트를 옮길 테니, 원할 때마다 가져가면 됩니다.";
				link.l1 = "좋아. 다음 분량을 준비해.";
				link.l1.go = "Himenes_bacaut_2";
			}
			else
			{
				dialog.text = "잠깐만요, 선장님! 창고가 가득 찼어요 - 수확한 바쿠트를 전부 실을 수 없습니다. 창고에 자리를 좀 비우고 다시 오십시오.";
				link.l1 = "좋아, 내가 처리할게.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_2":
			dialog.text = "물론이죠, 선장님!";
			link.l1 = "...";
			link.l1.go = "Himenes_73";
			IslaMona_FactoryTrade();
		break;
		
		case "Himenes_church":
			dialog.text = "하! 선장님, 더 이상 뭔가를 짓는 건 쓸데없는 허영과 사치일 뿐이라고 생각합니다. 물론...";
			link.l1 = "무슨 경우가 아니라면?";
			link.l1.go = "Himenes_church_1";
		break;
		
		case "Himenes_church_1":
			dialog.text = "선장님, 이런 걸 여쭤보기 좀 민망합니다만... 이미 이곳에 상당한 금액을 투자하셨잖아요!";
			link.l1 = "기생집?";
			link.l1.go = "Himenes_church_2_1";
			link.l2 = "교회?";
			link.l2.go = "Himenes_church_2_2";
		break;
		
		case "Himenes_church_2_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "성 산티아고께 맹세컨대, 그거 나쁘지 않겠군! 하지만 첫날 밤에 우리 여자들이 그걸 불태워버릴 거야. 우리까지 같이 말이지. 아니, 선장, 내가 말하는 건 교회야. 그래, 우리에겐 괜찮은 집도 있고, 월급도 받고, 바다도 있고, 즐길 거리도 있지, 가족과 친구들도 있고. 하지만 뭔가가 여전히 부족해, 무슨 말인지 알겠지?";
			link.l1 = "상상할 수 있지.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_2_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			AddCharacterExpToSkill(pchar, "Defence", 500);
			dialog.text = "나를 꿰뚫어보는군, 선장. 그래, 우리에겐 괜찮은 숙소와 급여, 바다와 오락, 가족과 친구들이 있지. \n하지만 뭔가가 여전히 부족해, 그거 알겠나?";
			link.l1 = "상상할 수 있지.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_3":
			dialog.text = "맞아요. 당신의 도움이 없이는 하나님의 집을 지을 수 없소. 그런 곳은 특별해야 하고, 이 세상과는 달라야 하오. 그래서 값이 비쌀 수밖에 없지. 촛불, 금괴, 호박, 그리고 물론 건축 자재도 필요하오. 값싼 것들은 안 되지. 당신에게 이익이 되는 일은 아니니, 감히 부탁드릴 수 없겠소.";
			link.l1 = "그래서 여기 신부를 데려와야 하냐?";
			link.l1.go = "Himenes_church_4";
		break;
		
		case "Himenes_church_4":
			dialog.text = "아니.";
			link.l1 = "너희 중에 이미 신부가 있느냐?";
			link.l1.go = "Himenes_church_5";
		break;
		
		case "Himenes_church_5":
			dialog.text = "아니오, 선장님. 그리고 이미 모든 걸 이해하셨으리라 생각합니다.";
			link.l1 = "그래서, 종교재판소의 신부들이 너희를 박해할 만한 이유가 있었던 거냐? 너희는 이단이냐?";
			link.l1.go = "Himenes_church_6";
		break;
		
		case "Himenes_church_6":
			dialog.text = "정교회 법에 따르면, 우리는 가장 극악한 이단자요. 우리는 신과 소통하는 데 반드시 이 세상의 중개자가 필요하다고 믿지 않소.";
			link.l1 = "이 세상에서?";
			link.l1.go = "Himenes_church_7";
		break;
		
		case "Himenes_church_7":
			dialog.text = "선장님, 우리는 사탄 숭배자도 아니고, 우리 공동체가 사이비 집단도 아닙니다. 우리도 당신처럼 그리스도인입니다. 다만 우리는 세상을 아주 넓은 시각으로 보고 있지요. 어떤 학식 있고 훌륭한 이들에겐 너무 넓다고도 하더군요. 만약 언젠가 마음을 열고 이해하려는 생각이 들면, 그때 더 말씀드리겠습니다. 하지만 지금은 이 목록을 받아두십시오. 만일을 위해서요.";
			link.l1 = "이런 일은 진작 말했어야지, 로드리고. 어느 날 갑자기 돌아와 보니 내 땅에서 마녀들의 집회나 새로운 신앙이 태어나고 있는 건 보고 싶지 않다! 기다리고 있으라. 내가 결정을 내릴 테니.";
			link.l1.go = "Himenes_church_8_1";
			link.l2 = "대단한 목록이군. 이제야 왜 신부님들이 그렇게 많은 돈이 필요한지 알 것 같아! 네 제안은 생각해 보마, 로드리고, 그리고 결정 내리겠네.";
			link.l2.go = "Himenes_church_8_2";
		break;
		
		case "Himenes_church_8_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "";
			link.l1 = "만약 긍정적이라면, 네가 적어준 목록의 모든 물건을 창고로 가져오고, 보물은 네 앞 탁자에 펼쳐놓을게.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_8_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			dialog.text = "";
			link.l1 = "긍정적인 답이 오면, 네가 적어준 목록의 모든 물건을 창고로 가져오고, 보물은 네 앞 탁자에 펼쳐놓을게.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_9":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "start";
			AddQuestRecord("IslaMona", "14");
			AddQuestRecordInfo("IslaMonaData", "3");
		break;
		
		case "Himenes_church_10":
			dialog.text = "우리 모두를 대표해서 감사드립니다, 선장님. 절대 후회하지 않으실 겁니다, 맹세합니다!";
			link.l1 = "네가 완전히 엉망으로 지으면 그때만 후회할 거야.";
			link.l1.go = "Himenes_church_10_1";
		break;
		
		case "Himenes_church_10_1":
			dialog.text = "선장님, 모든 건축 자재가 준비되어 있습니다! 명시된 사치품들을 가져오시면 바로 건설을 시작하겠습니다. 그 물품들은 보석과 의식 도구 제작에 쓰일 것입니다. 다시 한 번 진심으로 감사드립니다, 선장님! 무차스 그라시아스!";
			link.l1 = "천만에!";
			link.l1.go = "Himenes_church_10_2";
		break;
		
		case "Himenes_church_10_2":
			DialogExit();
			IslaMona_RemoveChurch();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "Wait_candles";
			pchar.questTemp.IslamonaChurch.GoldNugget = 50;
			pchar.questTemp.IslamonaChurch.Candle = 100;
			pchar.questTemp.IslamonaChurch.Amber = 30;
			pchar.questTemp.IslamonaChurch.BlueAmber = 1;
		break;
		
		case "Himenes_church_10_3":
			IslaMona_RemoveCandles();
			string sAdd = "";
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Candle"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Candle)+ " candles,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Amber"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Amber)+ " amber,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget"))
			{
				sAdd += " "+ sti(pchar.questTemp.IslamonaChurch.GoldNugget) + " ingots,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber"))
			{
				sAdd += " and one blue amber"
			}
			if(sAdd == "")
			{
				dialog.text = "대단히 감사합니다, 선장님! 모든 준비가 끝났으니 이제 공사를 시작하겠습니다. 두어 달 후에 첫 번째 서비스를 받으러 오십시오. 아, 그리고 한 가지 더, 포도가 익었습니다! 집에서 직접 와인을 만들고, 축하 연회를 열어 선장님을 위해 진수성찬을 차리겠습니다!";
				link.l1 = "우리 모두 축하할 자격이 있다고 생각해. 두 달 후에 돌아올게.";
				link.l1.go = "Himenes_church_12";
			}
			else
			{
				dialog.text = "선장님, 아직도 "+sAdd+" 떠났다.";
				link.l1 = "알겠어, 조금만 더 시간 줘. 솔직히 말해서, 촛불만 아니었으면 네가 보물을 묻으려는 줄 알았을 거야.";
				link.l1.go = "Himenes_church_11";
			}
		break;
		
		case "Himenes_church_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_church_12":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "build";
			AddQuestRecord("IslaMona", "15");
			//IslaMona_RemoveChurch();
			SetFunctionTimerCondition("IslaMona_ChurchComplete", 0, 0, 60, false);
		break;
		
		case "Himenes_church_13":
			dialog.text = "하하하하하하하하하하하!";
			link.l1 = "난 네가 그 멍청한 버릇을 고친 줄 알았는데.";
			link.l1.go = "Himenes_church_14";
		break;
		
		case "Himenes_church_14":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "that we won't have to sit here for weeks waiting for events to unfold.";
			else sTemp = "that not everyone will have to participate in the battle.";
			dialog.text = "하하하하하... 하. 나도 그렇게 생각했소, 선장님! 로드가르 말이 맞소, 당신이 여기 있다는 것만으로도 이미 의미가 있지, "+sTemp+"";
			link.l1 = "무슨 일이 있었는지는 이미 알고 있어. 사상자는 있나?";
			if (GetCharacterIndex("Mirabella") != -1) link.l1.go = "Himenes_church_15";
			else link.l1.go = "Himenes_church_16";
		break;
		
		case "Himenes_church_15":
			DialogExit();
			sld = characterFromId("Mirabella"); 
			sld.dialog.currentnode = "mirabelle_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_16":
			dialog.text = "너무 걱정하지 마, 로드가. 네 잘못이 아니야, 총병들이 너무 빨리 도착했거든. 어차피 우리 진영 뒤에 붙잡아 둘 수도 없었고, 전부 베어버릴 시간도 없었지.";
			link.l1 = "스페인 놈들은 어쩔 건데?";
			link.l1.go = "Himenes_church_17";
		break;
		
		case "Himenes_church_17":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) // решил проблему самостоятельно
			{
				dialog.text = "우리에게 도착한 건 셋뿐이었고, 그중 한 명만 살아남았어. 바로 선장 본인이야! 꽤나 높은 해군 장교 같더군. 하지만 아직 우리를 도울 수는 없어 – 최소 며칠은 더 누워 있어야 한대. \n그건 그렇고, 선장, 총소리가 들렸는데, 당신 꼴을 보니 당신도 들은 모양이군.";
				link.l1 = "그렇다고 할 수 있지. 불청객들은 이런 뜻밖의 방문을 전혀 예상하지 못했고, 결국 다시 바다로 쫓겨났거든.";
				link.l1.go = "Himenes_church_20";
			}
			else
			{
				dialog.text = "그들 중 세 명만 우리에게 도착했고, 그 중 한 명만 살아남았어. 바로 선장 자신이야! 꽤나 엄격한 해군 장교로 보이더군. 하지만 아직 우리를 도울 수는 없어 – 최소 며칠은 더 누워 있어야 할 거야.";
				if (i >= 50) 
				{
					link.l1 = "지난번에 내가 여기 경비로 사람들을 꽤 많이 남겨뒀으니, 너희가 푸질리에들보다 훨씬 많았어야 했을 텐데. 왜 한 번에 전부 바다에 쳐넣지 않았지?";
					link.l1.go = "Himenes_church_17_1";
				}
				else 
				{
					link.l1 = "좋아, 이 문제를 해결하자. 계획은 이렇다: 내가 놈들을 유인해서 정면 공격을 걸겠다, 그리고 지금 당장 실행한다. 미룰 이유가 없다. 산탄과 머스킷 준비해라, 해적들은 문 앞에 대기하고, 나머지는 집 안에 있으면서 꼼짝 말고 있어라.";
					link.l1.go = "Himenes_church_18";
				}
			}
		break;
		
		case "Himenes_church_17_1":
			dialog.text = "선장님, 저놈들은 전부 전문 군인들이고, 지휘관도 있어요. 우린 제대로 된 무기도 없잖아요. 물론, 인원수로 밀어붙일 수도 있었겠지만, 그랬다간 최소 두 배는 더 많은 사상자가 나왔을 겁니다. 여기선 한 사람 한 사람이 다 소중하고 꼭 필요하니까요.";
			link.l1 = "좋아, 이 문제를 해결하자. 계획은 이렇다: 내가 놈들을 유인해서 지금 당장 정면으로 공격할 거다. 더 미룰 필요 없어. 산탄과 머스킷 준비해라, 해적들은 문 앞에 대기하고, 나머지는 집 안에 있으면서 꼼짝 말고 있어라.";
			link.l1.go = "Himenes_church_18";
		break;
		
		case "Himenes_church_18":
			dialog.text = "선장님, 전투 준비 완료입니다!";
			link.l1 = "알고 있어, Rodrigo. 하지만 내 말 끝까지 들어봐. 만약 적 한 놈이라도 성문을 뚫고 들어오면, 모두가 사방에서 달려들어야 해. 전투 중엔 총알이나 파편에 맞을 확률도 줄어들지. 더 궁금한 거 있나?";
			link.l1.go = "Himenes_church_19";
		break;
		
		case "Himenes_church_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_68";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_20":
			dialog.text = "잘했네! 물론 동료들에게 그런 운명이 닥친 건 안타깝군. 하지만 다시 한 번 우리 편이 되어줘서 고맙네.";
			link.l1 = "쉽지 않았어, Rodrigo. 평범한 사람들은 그걸 배신이라고 부를 거고, 그 말이 맞지.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "여기가 내 땅이야, 로드리고. 누가 침범하든 반드시 지켜야 해.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20a":
			dialog.text = "그래, 늙은 로드리고는 카디스를 떠날 때 신세계에서 이런 모험이 자신을 기다리고 있으리라고는 전혀 예상하지 못했지.";
			link.l1 = "말하지 마. 가끔 나도 똑같은 생각을 해.";
			link.l1.go = "Himenes_church_20b";
		break;
		
		case "Himenes_church_20b":
			dialog.text = "네 동포들에게 그런 운명이 닥친 건 안타깝지. 하지만 네가 다시 한 번 우리 편에 서 줘서 고맙다.";
			link.l1 = "쉽지 않았어, Rodrigo. 평범한 사람들은 그걸 배신이라고 부르겠지, 그리고 그 말이 맞아.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "여기는 내 땅이야, 로드리고. 누구에게서든 반드시 지켜야 해.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "알겠습니다, 선장님. 그럼, 선장님이 부재 중이었을 때 우리 정착지의 상황을 간단히 설명드리겠습니다.";
			link.l1 = "정말이야? 잠깐만... 선장?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_20_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			dialog.text = "알겠습니다, 선장님. 그러면, 선장님이 부재하신 동안 우리 정착지의 상황을 간략히 설명드리겠습니다.";
			link.l1 = "정말이야? 잠깐만... 선장?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_21":
			dialog.text = "기분 상하게 하려던 건 아니야. 그냥 로드가르가 그 말을 너무 맛깔나게 해서 나도 한번 써보고 싶었거든. 아주... 해적답잖아.";
			link.l1 = "문제 없어, 그냥 놀랐을 뿐이야. 그래서 여기서 무슨 일이 있었던 거지?";
			link.l1.go = "Himenes_church_22";
		break;
		
		case "Himenes_church_22":
			dialog.text = "우선, 우리가 교회를 지었소. 잠깐이면 되니 들어오시오. 볼 것이 있소. 큰일을 해냈구려, 선장. 자네는 잘 모를 수도 있지만, 우리에게 신과 소통할 수 있다는 건 정말, 정말 중요한 일이오. 오늘부터 우리는 이슬라 모나를 우리 집이라 부르겠소.";
			link.l1 = "집, 달콤한 내 집인가? 꼭 한번 살펴보지. 내가 그 많은 촛불을 괜히 들고 온 건 아니겠지?";
			link.l1.go = "Himenes_church_23";
		break;
		
		case "Himenes_church_23":
			dialog.text = "공짜로 하는 건 아니야! 두 번째로, 공장이 망해서 일꾼들을 전부 잃었지. 새 노예들을 데려와야 할 거야. 다행히도 작업 효율을 다시 평가해 보니, 노예 열 명이면 충분하다는 결론이 나왔어. 그러니 너도 좀 덜 고생하겠군.";
			link.l1 = "알겠어. 또 할 말 있어?";
			link.l1.go = "Himenes_church_24";
		break;
		
		case "Himenes_church_24":
			dialog.text = "축하 준비는 모두 끝났어. 아니, 거의 다 됐지. 여기 좀 치우고, 불쌍한 자들의 시신도 묻어야 하거든...\n그러니 내일 교회로 오면 우리가 시작할 거야.";
			link.l1 = "교회로 간다고? 파티를 시작하기엔 이상한 곳인데. 혹시 프러포즈라도 할 생각이야, 로드리고?";
			link.l1.go = "Himenes_church_25";
		break;
		
		case "Himenes_church_25":
			dialog.text = "하하! 아니요, 선장님, 우리 여자애들 중 몇 명은 싫지 않겠지만요. 당신이 해도 우리는 상관없어요.";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && IsOfficer(characterFromId("Mary")))
			{
				link.l1 = "";
				link.l1.go = "Himenes_church_25_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && IsOfficer(characterFromId("Helena")))
				{
					link.l1 = "";
					link.l1.go = "Himenes_church_25_2";
				}
				else
				{
					link.l1 = "알겠소, 내일 교회로 가겠소. 물론 기도하러 말이오.";
					if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common") || CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) link.l1.go = "Himenes_church_28";
					else link.l1.go = "Himenes_church_26";
				}
			}
		break;
		
		case "Himenes_church_25_1":
			DialogExit();
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_25_2":
			DialogExit();
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_26":
			dialog.text = "그리고 한 가지 더, 선장. 축하 연회 전에 먼저 죄수 문제부터 처리하시오. 결정을 내려야 하며, 어느 쪽이든 유쾌하지 않을 거라는 건 나도 잘 알고 있소.";
			link.l1 = "알겠어. 지금 바로 갈게.";
			link.l1.go = "Himenes_church_27";
		break;
		
		case "Himenes_church_27":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_factoria", "reload", "reload1", "IslaMona_DefFraPrisoner"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_28":
			DialogExit();
			WaitDate("", 0, 0, 0, 3, 5); //крутим время
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			IslaMona_DefBattleLightClear();
			DoQuestReloadToLocation("IslaMona_town", "quest", "detector1", "");
		break;
		
		case "Himenes_church_29":
			dialog.text = "다들 모였군! 나리, 우리가 처음에 이곳에서 무엇을 원했는지, 혹은 지금 당신이 이곳을 어떻게 생각하는지 우리는 모릅니다. 우리에게 이곳은 처음엔 어쩔 수 없는 피난처였지만, 이제는 진정한 고향이 되었소. 당신의 선원들, 해적들, 그리고 도망쳐 온 스페인 이단자들이 여기서 살고 있지. 세상의 다른 곳이었다면 벌써 서로의 목을 베었을 거요. 하지만 여기서는 우리가 친구가 되었고, 함께 일하며 인생을 즐기고 있소. 이슬라 모나는 우리 누구에게도 이 세상 지도에서의 마지막 목적지는 아니지만, 어쩌면 여기서 우리 인생에서 가장 행복하고 결실 많은 세월을 보내게 될지도 모르지. 이것은 모두 당신의 업적이며, 당신의 땅이고, 당신의 사람들이오. 무차스 그라시아스, "+pchar.name+"!";
			link.l1 = "";
			link.l1.go = "Himenes_church_30";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_30":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_86";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		case "Himenes_church_31":
			dialog.text = "알겠소, 알겠어. 선장님, 우리가 선장님을 위해 선물을 모아왔소 – 쓸모 있는 것들과 그냥 기분 좋은 것들이 아주 많소. 일부는 우리가 직접 가져왔고, 일부는 우리가 직접 만들었소. 이 선물을 순수한 마음으로 받아주시고, 나머지는 우리의 땀과 노력으로 드리겠소.";
			link.l1 = "고마워... 이런 일은 기대하지 않았어. 내 여정엔 이렇게 밝은 순간이나 인간적인 행동이 정말 드물거든... 내게 큰 의미가 있어, 정말이야.";
			link.l1.go = "Himenes_church_32";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_32":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "GunEchin", 10);
			TakeNItems(pchar, "slave_01", 10);
			TakeNItems(pchar, "grenade", 10);
			TakeNItems(pchar, "obereg_7", 1);
			TakeNItems(pchar, "purse3", 1);
			TakeNItems(pchar, "jewelry47", 1);
			TakeNItems(pchar, "jewelry52", 1);
			TakeNItems(pchar, "berserker_potion", 1);
			TakeNItems(pchar, "potion5", 10);
			TakeNItems(pchar, "cannabis7", 1);
			dialog.text = "이제 다시 일하러 가자!";
			link.l1 = "아니, 이제는—선술집으로 가자! 로드리고, 가자!";
			link.l1.go = "Himenes_church_33_1";
			link.l2 = "그래, 이 멋진 순간을 좀 더 오래 즐기자.";
			link.l2.go = "Himenes_church_33_2";
		break;
		
		case "Himenes_church_33_1":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_Town", "sit", "sit_base2", "IslaMona_ChurchToTavern"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_33_2":
			DialogExit();
			LAi_SetActorType(pchar);
			ChangeShowIntarface();
			ResetSound();
			SetMusic("music_terrain");
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			pchar.GenQuest.FrameLockEsc = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("IslaMona_ChurchTavernExit", 45.0);
		break;
		
		case "Himenes_74":
			dialog.text = "하하! 힉!";
			link.l1 = "그런데, 이젠 아무 이유 없이 마구 웃던 것도 거의 멈췄군. 카리브의 신선한 공기 덕분인가?";
			link.l1.go = "Himenes_75";
		break;
		
		case "Himenes_75":
			dialog.text = "로드가르의 타락한 영향이 더 맞지. 저 자식을 보면서, 뭐든 다 엿이나 먹으라고 보내는 법을 배웠지.";
			link.l1 = "";
			link.l1.go = "Himenes_76";
		break;
		
		case "Himenes_76":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_90";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_77":
			dialog.text = "나는 그곳 출신의 존경받는 사람들을 많이 알고 있지.";
			link.l1 = "";
			link.l1.go = "Himenes_78";
		break;
		
		case "Himenes_78":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_93";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_79":
			dialog.text = "아니, 난 그냥 럼주나 더 마시면서 너나 째려볼란다.";
			link.l1 = "";
			link.l1.go = "Himenes_80";
		break;
		
		case "Himenes_80":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_96";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_81":
			dialog.text = "선장님! 힉!";
			link.l1 = "너도 안녕, 로드리고. 오늘 밤에 무슨 일 있었나 보군?";
			link.l1.go = "Himenes_82";
		break;
		
		case "Himenes_82":
			dialog.text = "더 이상... 묻지 마. 한 달 동안... 술 안 마실 거야. 아, 소식 있어! 선장님이... 정신을 차리셨대.";
			link.l1 = "유일하게 살아남은 스페인 놈인가?";
			link.l1.go = "Himenes_83";
		break;
		
		case "Himenes_83":
			dialog.text = "힉! 아이고! 그래, 그를 팩토리아에 가뒀어, 경비가 지키는 집에 말이야.";
			link.l1 = "그래. 내가 그에게 갈게. 무리하지 말고 조심해.";
			link.l1.go = "Himenes_84";
		break;
		
		case "Himenes_84":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10); /// ОН ИДЕТ НА ВЫХОД, ПОСТАВИТЬ ПРАВИЛЬНЫЙ ЛОКАТОР
			IslaMona_ChurchSetHispanos();
		break;
		
		case "Himenes_85":
			dialog.text = "수영 좀 하고 나니, 다 새것처럼 좋아졌어! 우린 살아가고 일할 거야. 내가 최대한 오래 팩토리아를 운영해 보려고 해. 뭐, 수리도 하고, 작은 건축 일도 하겠지. 어쩌면 내 가족이랑 아이도 생각해 볼지도 모르지.";
			link.l1 = "모두들 정말 기쁘다! 아주 긴장되고 돈도 많이 들었지만... 멋진 모험이었지. 우리에게 잘 풀려서 다행이야. 모두에게 행운을 빌고, 특히 다시 항해에 나서는 우리에겐 더 큰 행운이 있길!";
			link.l1.go = "Himenes_86";
		break;
		
		case "Himenes_86":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_Final", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// солдат в бухте
		case "Capral":
			dialog.text = "멈춰라! 하사 "+GetFullName(npchar)+". 전투 지역에 상륙했소! 즉시 신분을 밝히고 여기에 온 목적을 말하시오!";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "상병, 물러서! "+GetFullName(pchar)+", 프랑스 해군의 선장이다. 너희 지휘관에게 나를 호위해 데려가라. 명령을 따르도록!";
				link.l1.go = "Capral_1";
			}
			else
			{
				link.l1 = ""+GetFullName(pchar)+", '라는 이름의 배 선장"+pchar.ship.name+"완전히 우연히 이 섬에 도착했소 – 아마도 수리를 하고 식수를 보충하려고 말이오.";
				link.l1.go = "Capral_3";
			}
		break;
		
		case "Capral_1":
			if(IsUniformEquip())
			{
				dialog.text = "예, 선장 나리! 저를 따라오십시오. 제발 조심해 주십시오! 이 섬에는 도적들이 들끓고 있습니다.";
				link.l1 = "";
			}
			else
			{
				dialog.text = "실례합니다, 선장님. 제복을 입지 않으셨으니, 장교 임명장을 확인해야겠습니다.";
				link.l1 = "봤지? 이제 만족했나? 그럼, 어서 명령을 수행해, 상병!";
			}
			link.l1.go = "Capral_2";
		break;
		
		case "Capral_2":
			DialogExit();
			AddQuestRecord("IslaMona", "16");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 20.0);
		break;
		
		case "Capral_3":
			dialog.text = "저와 함께 가셔야겠습니다, 선장님. 우리 상관께서 당신과 말씀 나누실 겁니다. 지금 이 순간부터 당신의 배는 프랑스 해군의 필요에 의해 임시로 징발된 것으로 간주됩니다.\n즉시 현재 당직자에게 알리고 저를 따라오십시오.";
			link.l1 = "Charles Prince호를 징발하겠다고? 그럴 생각 없어!";
			link.l1.go = "Capral_5";
			link.l2 = "별 수 없군. 네 말대로 하겠다.";
			link.l2.go = "Capral_4";
		break;
		
		case "Capral_4":
			DialogExit();
			AddQuestRecord("IslaMona", "18");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 5.0);
		break;
		
		case "Capral_5":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_DefKillCapral", 1.0);
		break;
		
		case "Capral_6":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "선장님, 적 진영으로 가는 길이 우리 오른쪽에 있습니다. 제가 안내하겠습니다.";
				link.l1 = "물러서게, 상병. 나는 혼자 가는 게 낫겠네.";
			}
			else
			{
				dialog.text = "선장님, 적 진영으로 가는 길은 우리 오른쪽에 있습니다. 길을 잃지 않을 겁니다.";
				link.l1 = "걱정해 주셔서 감사합니다.";
			}
			link.l1.go = "Capral_7";
		break;
		
		case "Capral_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			IslaMona_DefGotoMarch();
			pchar.quest.islamona_def_killslaves.win_condition.l1 = "location";
			pchar.quest.islamona_def_killslaves.win_condition.l1.location = "IslaMona_town";
			pchar.quest.islamona_def_killslaves.function = "IslaMona_DefKillSlaves";
		break;
		
		case "FraOfficer":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Captain "+GetFullName(pchar)+"! 신이시여, 감사합니다! 제 소개를 하겠습니다 - 중위 "+GetFullName(npchar)+". 당신을 정말 존경하는 사람입니다! 이런 초라한 땅에서 뭘 하고 계신지는 모르겠지만, 딱 맞춰 오셨군요!\n말씀드리자면, 선장님, 당신은 우리 장교들 사이에서 아주 유명해지셨습니다. 많은 이들이 당신의... '특별한' 근무 방식에 불만을 갖고 있긴 하지만, 모두가 당신의 임명이 우리 함대를 더 강하게 만든다는 데에는 동의합니다. 현재 우리는 완전히 교착 상태에 있으니, 선장님 같은 분의 도움이 얼마나 소중한지 이루 말할 수 없습니다!";
				link.l1 = "내가 뭘 할 수 있지? 그리고 여기서 무슨 일이 벌어지고 있는 거야?";
				link.l1.go = "FraOfficer_1";
			}
			else
			{
				dialog.text = "Captain "+GetFullName(pchar)+". 함대 보고서에 네 이름이 여러 번 언급됐지. 항상 좀 수상쩍은 평이었어. 하지만 이제 이 불명예스러운 흐름을 끊고 조국을 위해 봉사할 기회가 왔다.";
				link.l1 = "내가 뭘 할 수 있지? 그리고 여기서 무슨 일이 벌어지고 있는 거야?";
				link.l1.go = "FraOfficer_8";
			}
		break;
		
		case "FraOfficer_1":
			dialog.text = "우리는 'Warrior'호에 있었어, 평범한 임무였지 - 특히 대담한 스페인 약탈자들을 사냥하는 일이었어. 사건 자체는 아주 단순해: 첩자가 지역과 목표에 대한 정보를 주면, 우리는 지평선 너머에서 그놈들을 잡는 거지. 특별히 말할 것도 없고, 결국 아주 나쁘게 끝났어: 스페인 놈들이 먼저 우리를 찾아내 공격했거든, 자기들도 코르벳에 타고 있었으면서 말이야. 우리가 좀 더 강한 배를 탔더라면, 그놈들과 같이 바다 밑으로 가지는 않았을 텐데... 그래도 최소한 놈들 선체 전체를 날려버리긴 했지. 내 분대만 살아남았어. 카스티야 놈들도 살아남은 자들이 있었지만, 오래 가진 못했지, 하하!";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "프리깃 '워리어'호? 쇼크 선장이 죽었다고?";
				link.l1.go = "FraOfficer_1_1";
			}
			else
			{
				link.l1 = "";
				link.l1.go = "FraOfficer_2";
			}
		break;
		
		case "FraOfficer_1_1":
			dialog.text = "그 사람에 대해 물어보신 건 놀랍지 않소, 선장님. '알칸타라'를 가로챈 일에 당신이 관여했다는 소문을 들었소. 대단한 업적이었지; 그때 이미 당신의 특허 기반을 다졌다고 할 수 있소! 쇼케 사령관은 죽지 않았소—오히려 반대요! 그는 승진해서, 본인의 요청으로 지중해로 발령받았소. 지금 우리의 처지를 생각하면 그가 부러울 따름이오. 자, 그럼 우리 상황에 대해 말하자면...\n";
			link.l1 = "";
			link.l1.go = "FraOfficer_2";
		break;
		
		case "FraOfficer_2":
			dialog.text = "우리는 섬에서 정착지를 발견했어 – 꽤 인구가 많은 도적 소굴이더군 – 들어봐, 해적이랑 스페인 놈들이 같이 있더라고. 믿기 힘들지! 알다시피, 보통 저놈들은 서로 베고 목 매다는 짓만 하는데, 여기서는 – 봐라: 군도 한가운데서 한 가족처럼 힘을 합쳐 버커니어 목재를 캐내고 있더군. 쟤네가 직접 만든 부두 봤어? 이놈들한테 오는 손님들은 노 젓는 보트 타고 오지 않아. 우리의 임무는 아주 명확해: 네 도움이 있으면, 우리가 정착지를 점령하고, 버커니어 목재랑 포로들을 챙긴 다음, 네가 전부 캡스터버그로 데려가는 거야. 그동안 당국은 자기들끼리 알아서 처리하겠지... 그리고 당국이 머리 싸매고 있는 동안, 우리는 버커니어 목재 처리하고 내 본대 장교들이랑 제대로 한잔할 거다!";
			link.l1 = "지금까지 직접 그 정착지를 차지하지 않은 이유가 뭐지?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_3":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "There are probably many more bandits than us - we saw tents on the shore. And besides tents, they also have a wall, gates, cannon!";
			else sTemp = "There are probably not so many bandits, otherwise they would have kicked us out of here already, but they still have a wall, gates, cannon and plenty of time!";
			dialog.text = "우릴 막은 게 뭐냐고?! 우리는 푸질리에 열둘에 선원 일곱밖에 없어. 모두 지치고 녹초가 됐지. 머스킷 다섯 자루만 간신히 챙겼는데, 그마저도 탄환이 한 발씩밖에 없어! "+sTemp+"";
			link.l1 = "하지만 계획은 있나?";
			link.l1.go = "FraOfficer_4";
		break;
		
		case "FraOfficer_4":
			dialog.text = "들어봐, 우리는 시간 낭비하지 않았어. 우선 이 공장을 점령했고, 식량과 물도 좀 챙겼지. 그리고 가장 중요한 건, 해적용 목재가 가득한 창고 하나와 노예 열몇 명을 손에 넣었어! 어차피 우리가 노예들을 지킬 수는 없었으니, 바로 무장 정찰을 했지. 우리 머스킷 총알을 뒤에 두고, 그 노예들을 옛 주인들에게 공격하라고 보냈어. 그렇게 해서 그 도적놈들이 무기를 비축해뒀다는 걸 알게 된 거야.";
			link.l1 = "내가 제대로 이해한 거냐? 이제 노예들 대신 나랑 내 부하들을 그 무기를 처리하러 보내겠다는 거야?";
			link.l1.go = "FraOfficer_5";
		break;
		
		case "FraOfficer_5":
			dialog.text = "아니, 하지만 휴전기를 들고 산적들에게 갈 수는 있지. 네가 도착했다는 건 그들의 소굴이 드러났다는 뜻이고, 이제 왕의 군사들이 배와 증원군까지 갖췄다는 거다. 좋아, 놈들이 상황을 파악하려고 귀를 쫑긋 세운 사이 네가 최대한 대포 가까이 접근해서, 그 밑에 수류탄을 던져. 그리고 우리 병사들과 네 사람들이 도착할 때까지 절대 죽지 마라. 자신이 없으면 네 부하 중 한 명을 대신 보내 보도록 해.";
			link.l1 = "먼저 폭탄 없이 그들에게 가서 항복할 기회를 주겠어. 주변을 살피고, 놈들의 분위기와 힘을 가늠한 뒤, 마음에 의심을 심어주지. 놈들이 항복하지 않으면, 그땐 폭탄을 들고 다시 찾아가겠어.";
			if (CheckCharacterItem(pchar, "patent_fra")) link.l1.go = "FraOfficer_6";
			else link.l1.go = "FraOfficer_6_1";
		break;
		
		case "FraOfficer_6":
			GiveItem2Character(pchar, "grenade");
			//Log_Info("Вы получили гранату");
			PlaySound("interface\important_item.wav");
			dialog.text = "... 그리고 그때쯤이면 놈들도 이미 너한테 익숙해져 있을 테니, 훨씬 더 쉽게 방해 공작을 할 수 있을 거야! 영리하군! 뭐, 너라면 그 정도는 당연하지, 선장. 준비되면 진행해. 그래도, 이거... 도움이 될지도 몰라.";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_6_1":
			dialog.text = "... 그때쯤이면 놈들도 이미 너한테 익숙해질 테니, 훨씬 쉽게 방해 공작을 할 수 있을 거다. 그렇게 하자. 계속해!";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_7":
			DialogExit();
			AddQuestRecord("IslaMona", "19");
			chrDisableReloadToLocation = false;
			pchar.quest.islamona_def_goout.win_condition.l1 = "location";
			pchar.quest.islamona_def_goout.win_condition.l1.location = "IslaMona_Jungle_01";
			pchar.quest.islamona_def_goout.function = "IslaMona_DefCapralTalk";
		break;
		
		case "FraOfficer_8":
			dialog.text = "이 지역에서 스페인 놈들과 오랜 전투가 있었소. 양쪽 배 모두 침몰했고, 살아남은 자들이 여기까지 흘러왔지. 대부분은 프랑스 놈들이지만, 우리 적들 중에서도 살아남은 자들이 있더군. 더 이상은 알 필요 없소, 미안하오, 선장님. 기밀 사항이니 양해해 주시오.";
			link.l1 = "알겠소.";
			link.l1.go = "FraOfficer_9";
		break;
		
		case "FraOfficer_9":
			dialog.text = "우리가 그 섬에서 정착지를 발견했어. 꽤 인구도 많은 도적 소굴이더군. 들어봐, 해적이랑 스페인 놈들이 같이 있더라고. 믿기 힘들지? 알다시피, 저놈들은 평소엔 서로 죽이고 목 매다는 짓만 하는데, 여기서는 말이야, 군도 한복판에서 한 가족처럼 힘을 합쳐서 버커니어 목재를 캐내고 있어. 자기들끼리 부두까지 만들어 놨더라고. 이놈들한테는 손님이 노 젓는 보트 타고 오지 않아. 우리의 임무는 아주 명확해. 네 도움이 있으면, 우리가 그 정착지를 점령하고, 버커니어 목재와 포로들을 챙긴 다음, 네가 전부 캡스터버그로 데려가는 거야. 그동안 당국은 알아서 처리하겠지... 그리고 당국이 머리 굴리는 동안, 네가 필요하다면 귀한 목재 좀 챙길 기회도 줄 수 있을 것 같군.";
			link.l1 = "지금까지 네가 직접 그 정착지를 차지하지 않은 이유가 뭐지?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_10":
			dialog.text = "여기 있었군! 소식 있나?";
			link.l1 = "이게 근위대인가?";
			link.l1.go = "FraOfficer_11";
		break;
		
		case "FraOfficer_11":
			dialog.text = "분명히 곧 우리의 다음 행동에 대한 결정이 내려질 거요. 새로운 명령을 내리려고 섬 전체를 돌아다니며 내 사람들을 찾아야 하는 상황은 만들고 싶지 않소.";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "훌륭한 결단이야! 곧 명령을 내리겠다. 내가 정찰을 해봤는데, 적은 약하고 대포는 탄약이 다 떨어졌더군. 즉시 산적 소굴을 공격하라고 명령한다, 중위. 손만 만지작거리지 말고. 함대에선 이런 일이 다반사다. 실행해!\n";
				link.l1.go = "FraOfficer_12";
			}
			else
			{
				link.l1 = "내 생각엔, '노예' 정찰 끝나고 바로 힘으로 쳐들어갔어도 됐을 거야. 저놈들 방어는 우습지, 제대로 싸울 만한 놈은 몇 안 돼. 괜히 머리 굴릴 필요 없어 – 지금쯤이면 우리가 철목 더미 위에 앉아서 전리품 와인이나 마시고 있었겠지.";
				link.l1.go = "FraOfficer_14";
			}
		break;
		
		case "FraOfficer_12":
			dialog.text = "알겠습니다, 선장님!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_13";
		break;
		
		case "FraOfficer_13":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -25);
			AddQuestRecord("IslaMona", "22");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_14":
			dialog.text = "이게 자네의 정찰 결과란 말인가? 군인이 아닌 사람에게 너무 많은 걸 기대하는 게 이상할 수도 있다는 건 알지만, 나는 사실이 필요하네! 사실 말이야, 선장, 자네 의견이 아니라!";
			link.l1 = "나를 모욕하는군, 중위. 보고하겠습니다!";
			link.l1.go = "FraOfficer_15";
		break;
		
		case "FraOfficer_15":
			dialog.text = "";
			link.l1 = "지금 우리와 함께 있는 자들 중에 네가 침몰시킨 스페인 배의 살아남은 선장이 있어. 곧 회복할 노련한 지휘관이지. 네가 지체하면, 그는 곧 회복해서 군사학 원칙대로 방어를 조직할 거야. 그러면 우리가 고생하게 되지. 서둘러야 해 - 다시 말하지만, 지금 그들은 약하고 사기가 떨어져 있어.";
			link.l1.go = "FraOfficer_15_1";
			link.l2 = "곧 증원군이 온다 – 버커니어의 목재를 빼앗으려고 말이야. 허세가 아닌 것 같아: 너도 부두랑 공장 창고에 출하 준비된 물건 더미를 직접 봤잖아. 서둘러야 해 – 다시 말하지만, 저놈들은 약하고 사기가 떨어져 있어. 망설이면 해적선이 도착할 때까지 기다리게 될 거야.";
			link.l2.go = "FraOfficer_15_2";
			link.l3 = "이 구멍 같은 곳 주민의 거의 절반이 여자야. 너희가 싸운 건 민병대도 아니었어. 지금까지 너희를 상대한 전투원은 열두 명도 안 됐지. 그들은 약하고, 사기가 완전히 꺾였어.";
			link.l3.go = "FraOfficer_15_3";
			link.l4 = "대포에 탄약이 떨어졌어. 나는 평생 총포를 많이 봐 와서, 선원들이 쏠 준비가 됐는지 아닌지 알 수 있지. 대포 없이는 저놈들은 그냥 한심한 싸움꾼일 뿐이야; 약하고 사기도 떨어졌지.";
			link.l4.go = "FraOfficer_15_4";
			link.l5 = "전리품과 영광을 생각해 보시오, 중위! 스페인 약탈선을 혼자 힘으로 물리치고, 도적 소굴을 점령하며, 해적만이 얻을 수 있는 특별한 목재까지 손에 넣는 것—이 모든 것이 직접 배를 지휘할 자격을 준다오! 다시 말하지만, 놈들은 약하고 사기가 떨어져 있으니, 지금이야말로 박살낼 때요!";
			link.l5.go = "FraOfficer_15_5";
		break;
		
		case "FraOfficer_15_1":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
				dialog.text = "감사합니다, 선장님. 정말 귀중한 정보군요, 그리고 선장님 말씀이 맞습니다. 여기서 지체할 필요가 없겠지요. 내 부하들은 모두 모였고, 우리는 강하고 훈련도 잘 되어 있으며 준비도 끝났습니다. 모든 일은 삼십 분 안에 끝날 겁니다. 선장님, 곧 당신 배로 사람들과 포로, 그리고 화물을 넘길 준비를 해주십시오. 여기 오래 머물진 않을 겁니다.";
				link.l1 = "모든 준비가 끝났습니다, 중위님. 당신만 기다리고 있었죠. 나중에 봅시다!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
				dialog.text = "감사합니다, 선장님. 정말 귀중한 정보군요. 그렇다면 선착장으로 가서 승선팀을 준비하십시오. 우리가 함께, 즉시 산적 소굴을 급습할 것이오. 내 부하들과 당신 부하들 중에서 가장 뛰어난 자들이 선봉을 맡아 문을 점령할 것이오. 병력을 함께 점검한 후에 나머지 이야기는 하도록 합시다. 나나 당신의 조국을 실망시키지 마시오. "+GetFullName(pchar)+".";
				link.l1 = "...그러면 그렇게 하지. 나중에 보세, 중위.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_2":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				Notification_Reputation(true, 42, "low");
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
				dialog.text = "감사합니다, 선장님. 정말 귀중한 정보군요. 그리고 선장님 말이 맞습니다, 여기서 더 지체할 필요는 없습니다. 내 부하들은 모두 모였고, 우리는 강하고 훈련도 잘 되어 있으며 준비도 끝났습니다. 모든 일은 30분 안에 끝날 겁니다. 선장님, 사람들과 포로, 그리고 화물을 배에 받을 준비를 해주십시오. 우리는 여기 오래 머물지 않을 것입니다.";
				link.l1 = "모든 준비가 끝났습니다, 중위님. 당신만 기다리고 있었어요. 나중에 봅시다!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Reputation(false, 42, "low");
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				dialog.text = "감사합니다, 선장님. 정말 귀중한 정보군요. 그렇다면 부두로 가서 승선팀을 준비하십시오.\n함께 즉시 산적 소굴을 습격합시다. 내 최정예 병사들과 당신의 최정예 인원들이 선봉을 맡아 문을 점령할 것입니다.\n병력 점검을 마친 뒤 나머지 이야기는 그때 나누지요. 나와 당신의 조국을 실망시키지 마십시오. "+GetFullName(pchar)+".";
				link.l1 = "...그러면 그렇게 하지. 나중에 보세, 중위.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 70 && sti(pchar.reputation.nobility) > 41)
			{
				Notification_Reputation(true, 42, "low");
				Notification_Skill(true, 70, SKILL_LEADERSHIP);
				dialog.text = "감사합니다, 선장님. 정말 귀중한 정보군요. 그리고 선장님 말씀이 맞습니다, 여기서 지체할 필요 없겠군요. 내 부하들은 모두 모였고, 우리는 강하고, 훈련도 잘 되어 있으며, 준비도 끝났습니다. 모든 일은 삼십 분 안에 끝날 겁니다. 선장님, 선원들과 포로, 그리고 화물을 배에 받을 준비를 해주십시오. 여기 오래 머물지 않을 겁니다.";
				link.l1 = "모든 준비가 끝났습니다, 부관님. 당신만 기다리고 있었죠. 나중에 봅시다!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Reputation(false, 42, "low");
				Notification_Skill(false, 70, SKILL_LEADERSHIP);
				dialog.text = "감사합니다, 선장님. 정말 귀중한 정보군요. 그렇다면 부두로 가서 승선팀을 준비하십시오. 우리가 함께 즉시 도적들의 소굴을 습격할 것이오. 내 부하들과 당신 부하들 중에서 가장 뛰어난 자들이 선봉을 이끌 것이며, 그들이 문을 점령할 거요. 병력을 함께 점검한 뒤 나머지 이야기는 그때 하도록 합시다. 나나 당신의 조국을 실망시키지 마시오. "+GetFullName(pchar)+".";
				link.l1 = "...그러면 그렇게 하지. 나중에 보세, 중위.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_4":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				Notification_Reputation(true, 42, "low");
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
				dialog.text = "감사합니다, 선장님. 정말 귀중한 정보군요. 그리고 선장님 말씀이 맞습니다, 여기서 더 지체할 필요는 없겠지요. 내 부하들은 모두 모였고, 우리는 강하고 훈련도 잘 되어 있습니다. 모든 일이 30분 안에 끝날 겁니다. 선장님, 사람들과 포로, 화물을 배에 받아들일 준비를 해주십시오. 여기 오래 머무르지 않을 테니.";
				link.l1 = "모든 준비가 끝났습니다, 중위님. 당신만 기다리고 있었죠. 나중에 봅시다!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Reputation(false, 42, "low");
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				dialog.text = "감사합니다, 선장님. 귀중한 정보군요. 그렇다면 부두로 가서 승선팀을 준비하십시오.\n함께 즉시 산적 소굴을 습격하겠소. 내 부하들과 당신 부하들 중 가장 뛰어난 자들이 선봉을 이끌 것이며, 그들이 문을 점령할 것이오.\n우리 병력을 함께 점검한 뒤 나머지 이야기는 그때 나누지요. 나나 조국을 실망시키지 마시오. "+GetFullName(pchar)+".";
				link.l1 = "...그러면 그렇게 하지. 나중에 보세, 중위.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_5":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 90)
			{
				Notification_Skill(true, 90, SKILL_LEADERSHIP);
				dialog.text = "감사합니다, 선장님. 정말 귀중한 정보군요, 그리고 선장님 말씀이 맞습니다. 여기서 더 지체할 필요는 없겠지요. 내 부하들은 모두 모였고, 우리는 강하고 훈련도 잘 되어 있으며, 준비도 끝났습니다. 모든 일이 삼십 분 안에 끝날 겁니다. 선장님, 곧 사람들과 포로, 그리고 화물을 배에 받아들일 준비를 해주십시오. 우리는 여기 오래 머물지 않을 겁니다.";
				link.l1 = "모든 준비가 끝났습니다, 중위님. 당신만 기다리고 있었죠. 나중에 봅시다!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				Notification_Skill(false, 90, SKILL_LEADERSHIP);
				dialog.text = "감사합니다, 선장님. 정말 귀중한 정보군요. 그렇다면 곧바로 부두로 가서 승선팀을 준비하십시오. 우리가 함께 산적 소굴을 급습할 것이오, 즉시 말이오. 내 최정예 병사들과 당신의 최정예 인원들이 선봉에 설 것이니, 그들이 문을 점령할 거요. 병력 점검을 마친 뒤에 나머지 이야기는 하도록 합시다. 나나 당신의 조국을 실망시키지 마시오. "+GetFullName(pchar)+".";
				link.l1 = "...그러면 그렇게 하지. 나중에 보세, 중위.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_16": // французы атакуют сами
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			AddQuestRecord("IslaMona", "24");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_17": // совместная атака
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -7);
			AddQuestRecord("IslaMona", "23");
			IslaMona_DefAttackCommon();
		break;
		
		case "FraOfficer_18":
			if (CheckCharacterItem(pchar, "patent_fra")) dialog.text = "그리고 나는, 내가 얼마나 어리석은지, 너를 존경했지! 아-악! 프랑스의 자랑, 선장 "+GetFullName(pchar)+"!! 너는 네 특허증을 가질 자격이 없어!!!";
			else dialog.text = ""+GetFullName(pchar)+", 쓰레기, 배신자, 그리고 저주받은 해적 놈! 이 비참한 소굴이 네 썩은 근거지라는 걸 진작 알아챘어야 했는데! 프랑스는 너 같은 자를 결코 잊지도, 용서하지도 않는다!";
			link.l1 = "";
			link.l1.go = "FraOfficer_19";
		break;
		
		case "FraOfficer_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_75";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FraOfficer_20":
			dialog.text = "준비됐소, 선장? 당신 선원들, 제법 쓸 만해 보이는군!";
			link.l1 = "감사합니다, 중위님. 시작할까요?";
			link.l1.go = "FraOfficer_21";
		break;
		
		case "FraOfficer_21":
			dialog.text = "그래, 바로 진행하자!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_22";
		break;
		
		case "FraOfficer_22":
			DialogExit();
			IslaMona_DefAttackCommonRun();
		break;
		
		// обиженный пират
		case "Pirate":
			dialog.text = "하! "+GetFullName(pchar)+"! 이런 만남이 있나. 이봐, 저놈 잡아! 이 자식이 여기 모든 걸 다 갖고 있어! 이 섬이 바로 이놈 거야!";
			link.l1 = "오늘 정말 대단한 날이군...";
			link.l1.go = "Pirate_1";
		break;
		
		case "Pirate_1":
			DialogExit();
			IslaMona_DefCheckJungleFight();
		break;
		
		// Алонсо
		case "Alonso":
			dialog.text = "선장님, 명령은 무엇입니까? 대기하라는 신호와 승선대를 보내라는 신호가 있습니다.";
			link.l1 = "명령은 그대로다. 얘들아, 따라와라. 우리 집에서 불청객들을 쫓아내야 한다. 전리품은 내 거고, 나머지 보물들은 너희 거다!";
			link.l1.go = "Alonso_1";
		break;
		
		case "Alonso_1":
			dialog.text = "만세!";
			link.l1 = "전투다!";
			link.l1.go = "Alonso_2";
		break;
		
		case "Alonso_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_our_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common"))
			{
				pchar.quest.islamona_attack_common1.win_condition.l1 = "location";
				pchar.quest.islamona_attack_common1.win_condition.l1.location = "IslaMona_Jungle_01";
				pchar.quest.islamona_attack_common1.function = "IslaMona_DefAttackCommonPrepare";
			}
			else
			{
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", true);
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", true);
				pchar.quest.islamona_attack_force.win_condition.l1 = "location";
				pchar.quest.islamona_attack_force.win_condition.l1.location = "IslaMona_factoria";
				pchar.quest.islamona_attack_force.function = "IslaMona_DefAttackForce";
			}
		break;
		
		// испанский офицер
		case "SpaOfficer":
			dialog.text = "인사드리오, 나리. 이 땅의 주인이시오? 내 소개를 하겠소, 나는 '페로 마리노' 코르벳의 전 선장이었던 그란 프란시스코 데 알바요.";
			link.l1 = "그래, 여기가 내 땅이다. 나는 "+GetFullName(pchar)+", ' 선장의"+pchar.ship.name+"'. 대단하군? 이렇게 귀한 손님은 여기 처음이야.";
			link.l1.go = "SpaOfficer_1";
		break;
		
		case "SpaOfficer_1":
			dialog.text = "아, 나리 "+GetFullName(pchar)+"! 네 이름은 이미 유명하지. 요즘 카사 데 콘트라타시온 보고서에 네 이름이 자주 등장해서, 정말로 너를 처리하라는 명령이 떨어질 줄 알았을 정도야.";
			link.l1 = "나랑 한판 뜨겠다고?";
			link.l1.go = "SpaOfficer_2";
		break;
		
		case "SpaOfficer_2":
			dialog.text = "시치미 떼 봐야 소용 없다고 생각하오. 내 임무는 전 세계 모든 바다에서 스페인과 필리프 왕의 적을 찾아내어 소탕하는 것이오.";
			link.l1 = "아직 그런 명령이 내려오지 않은 게 다행이오. 당신은 분명히 아주 유능한 해군 장교구려.";
			link.l1.go = "SpaOfficer_3";
		break;
		
		case "SpaOfficer_3":
			dialog.text = "지금 내가 해적들로 들끓는 작은 섬에서 반쯤 죽은 포로 신세가 되었고, 내 동포들까지 도망 다니고 있다는 사실이 바로 자네 결론을 뒷받침해 주는군, 하하! 정말 위험한 일이었지만, 명령은 명령이지. 거의 성공할 뻔했어! 내 부하들 생각하면 정말 유감이야 - 모두 이름까지 알고 있었고, 수년간 함께 복무했거든. 하지만 우리 조국이 제국의 위신을 지키려면 앞으로도 더 많은 아들들의 피를 흘려야 할 거야. 우리 집안은 그 사실을 누구보다 잘 알고 있지.";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "";
				link.l1.go = "SpaOfficer_4";
			}
			else
			{
				link.l1 = "일단 더 급한 일부터 돌아가자. 그런데, 그랜드, 너를 어떻게 해야 할까?";
				link.l1.go = "SpaOfficer_5";
			}
		break;
		
		case "SpaOfficer_4":
			dialog.text = "그런데 말이오, 드 모르 나리, '워리어'라는 그 작은 배가 익숙했지? 포르토 벨로에서 자네가 벌인 대담한 작전, 눈에 띄지 않을 수가 없었소. 대단하더군, 거의 자살 행위였지. 돈이 몹시 필요했던 거 아니오? 하!";
			link.l1 = "너는 내 이야기를 꽤 잘 아는군, 그랜드. 하지만 이제 네 운명에 대해 이야기해보자.";
			link.l1.go = "SpaOfficer_5";
		break;
		
		case "SpaOfficer_5":
			dialog.text = "생각할 게 뭐가 있지? 모든 좋은 이야기처럼, 선택지는 셋이야. 날 죽이든가, 여기 버려두든가, 아니면 날 풀어주든가. 날 풀어준다면, 데 알바 가문의 명예를 걸고 이곳이나 네가 내 일에 얽힌 사실을 절대 누구에게도 말하지 않겠다고 약속하지. 게다가 네게 빚을 지게 되니, 그 빚을 갚기 전에는 절대 너와 싸우지 않을 거야.";
			link.l1 = "나는 위험을 감수할 수 없어, 할배.";
			link.l1.go = "SpaOfficer_6";
			link.l2 = "여기서 한동안 지내게 될 거야. 동포들과 동등하게 살고 일하게 될 거다.";
			link.l2.go = "SpaOfficer_7";
			link.l3 = "내 배에 탄 걸 환영한다, Grand. 때가 되면 산티아고 등대에 내려주겠다. 약속은 꼭 지켜주길 바란다.";
			link.l3.go = "SpaOfficer_8";
		break;
		
		case "SpaOfficer_6":
			dialog.text = "알겠소, 나리. 뭐, 어쨌든 나는 이미 그 전투에서 내 부하들과 함께 죽은 목숨이오. 좋은 결말이지.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_6_1";
		break;
		
		case "SpaOfficer_6_1":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_KillSpanish", 1.0);
		break;
		
		case "SpaOfficer_7":
			dialog.text = "인정하지, 나는 어정쩡하게 행동하는 걸 좋아하지 않아. 하지만 포로가 되는 것이 부끄러운 일은 아니니, 네가 준 목숨을 받아들이고 이 친절하고, 겉보기엔 아주 행복한 사람들과 평화롭게 살겠어.\n그럼에도 불구하고, 만약 내가 이곳을 떠나게 된다면 너에게 빚진 것은 없을 거야.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_7_1";
		break;
		
		case "SpaOfficer_7_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			AddQuestRecord("IslaMona", "27");
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_8":
			dialog.text = "내가 맹세하네, 그리고 데 알바 가문의 이름도 걸겠소! 배에서 다시 보세!";
			link.l1 = "";
			link.l1.go = "SpaOfficer_8_1";
		break;
		
		case "SpaOfficer_8_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("IslaMona", "28");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			pchar.quest.islamona_final_mayak.win_condition.l1 = "location";
			pchar.quest.islamona_final_mayak.win_condition.l1.location = "Mayak9";
			pchar.quest.islamona_final_mayak.function = "IslaMona_FinalMayakSpanish";
			pchar.questTemp.IslaMona.Mayak = "true";
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_9":
			dialog.text = "Captain "+GetFullName(pchar)+"! 내 목숨을 구해주고 나를 내 집으로 데려다줬군. 그런 위험을 감수하는 게 얼마나 힘든 일이었는지 이해하네 – 나였다면 절대 감히 그렇게 못 했을 거야. 내가 빚을 졌네, 나리. 그 불운했던 전투의 사정에 대해 누구에게도 절대 말하지 않겠다고 맹세하겠네. 자네가 구세계로 돌아가면 꼭 나를 찾아오게. 마드리드에 있는 우리 가문 저택은 언제나 자네를 환영할 걸세. 지금은, 이걸 받아주게...";
			link.l1 = "지도 조각?";
			link.l1.go = "SpaOfficer_10";
		break;
		
		case "SpaOfficer_10":
			AddMapPart();
			dialog.text = "내가 가지고 있던 값진 건 그게 전부야. 나머지 조각은 네가 쉽게 찾을 수 있을 거라 믿어. 잘 가라! 그리고 행운을 빌어, 친구야.";
			link.l1 = "잘 가시오, Grand. 약속 잊지 마시오, 그리고 행운을 빌겠소!";
			link.l1.go = "SpaOfficer_11";
		break;
		
		case "SpaOfficer_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.IslaMona.Mayak = "done";
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			AddQuestRecord("IslaMona", "29");
			CloseQuestHeader("IslaMona");
		break;
		
		// Диалоги обитателей Исламоны
		// мужское население
		case "island_man":
			dialog.text = LinkRandPhrase("안녕하십니까! 잘 지내십니까, 선장님? 우리 쪽은 순조롭습니다.","공동체를 위해 일하는 것이 가장 큰 기쁨이오!","당신의 섬은 정말 멋집니다, 선장님. 번영을 위해 우리가 할 수 있는 모든 것을 하겠습니다.");
			link.l1 = LinkRandPhrase("그 말 들으니 좋군.","모든 게 괜찮다니 다행이군.","네 열정이 대단하군, 친구.");
			link.l1.go = "island_man_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = RandPhraseSimple(RandPhraseSimple("무례하게 들릴지 모르겠지만, 나리, 여기서는 도저히 살 수 없습니다.","이단 심문소 감옥에 앉아 있는 것보단 뭐든 낫지..."),RandPhraseSimple("구해주셔서 감사합니다, 선장님.","이 자들... 해적들이 네 친구들이냐?"));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 1:
						dialog.text = RandPhraseSimple(RandPhraseSimple("여기 나쁘진 않네! 그냥 좀 심심할 뿐이야.","선장님, 반갑습니다. 언제 한 번 들르세요!"),RandPhraseSimple("누가 해변에서 해골을 발견해서 아침 모임에 가져왔어. 여기선 항상 이런 일이 일어나나?","비밀 하나 알려주지, 이봐, Jiménez 나리는 분명히 이곳의 신선한 공기와 안전함 덕을 보고 있어."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 2:
						dialog.text = RandPhraseSimple(RandPhraseSimple("여기 나쁘진 않네! 좀 심심하긴 하지만.","선장님, 반갑습니다. 언제 한 번 들르세요!"),RandPhraseSimple("누가 해변에서 해골을 발견해서 아침 모임에 가져왔어. 여기선 항상 이런 일이 있나?","비밀 하나 알려주지. 이봐, Jimenez 나리는 분명히 이곳의 신선한 공기와 안전함 덕을 보고 있어."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 3:
						dialog.text = RandPhraseSimple(RandPhraseSimple("신의 가호가 함께하길, 선장님!","일주일에 한 번, 우리는 해변과 선술집에서 공연을 해.\n언제 한 번 들러봐."),RandPhraseSimple("네 선원들이 신선한 식량과 바꾸려고 온갖 잡동사니를 자꾸 우리에게 가져오고 있소. 이렇게 장려해 주셔서 감사합니다.","아직 이곳이 발견되지 않은 게 신기하군. 계속 이렇게 남아 있으면 좋겠어."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
				}
			}
		break;
		
		case "island_man_1":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
		break;
		
		case "island_man_2":
			dialog.text = "감사합니다, 나리. 당신 덕분에 진짜 신세계를 보았소. 신의 가호가 함께하길!";
			link.l1 = "";
			link.l1.go = "island_man_3";
			locCameraFromToPos(1.64, 1.58, -5.11, false, 2.66, 0.20, -5.74);
		break;
		
		case "island_man_3":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
			sld = characterFromId("Himenes_companion_12");
			sld.dialog.currentnode = "island_woman_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// женское население
		case "island_woman":
			dialog.text = LinkRandPhrase("안전과 평화, 그게 내가 이곳을 좋아하는 이유지!","멋진 낙원이군! 뭐, 거의 그렇지만...","수많은 고난 끝에 여기서 새로운 보금자리를 찾게 되어 기쁩니다.");
			link.l1 = LinkRandPhrase("너와 네 공동체가 잘 되어 기쁘다.","그래, 나도 이 작은 섬이 마음에 들어.","만족하신다니 다행이군.");
			link.l1.go = "island_woman_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = LinkRandPhrase("오... 안녕.","나리, 저기 있는... 무기를 든 거친 놈들은 누구입니까?","우리를 구해주셔서 감사합니다, 선장님.");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 1:
						dialog.text = LinkRandPhrase("우리 사람들 정말 잘했어 - 집들이 훌륭하군. 하지만 우리도 열심히 일했지!","나리 선장, 걱정 마시오: 우리 작은 씨족의 여자들은 어려움이나 잠깐의 불편쯤은 두려워하지 않소.","여기 공기가 정말 좋아! 그리고 바다도! 신께 더 가까워지는 기분이야!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 2:
						dialog.text = LinkRandPhrase("우리 사람들도 훌륭하게 해냈어 - 집들이 아주 좋아. 하지만 우리도 열심히 일했지!","나리 선장님, 걱정 마십시오. 우리 작은 씨족의 여자들은 어려움이나 잠깐의 불편함 따위는 두려워하지 않습니다.","여기 공기가 정말 좋아! 그리고 바다도! 신께 더 가까워지는 기분이야!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 3:
						dialog.text = LinkRandPhrase("더 자주 오시오, 선장 나리. 나는 항상 그대를 보면 기쁘오.","로드가르 나리는 정말 대단한 이야기꾼이야. 그의 이야기를 영원히 들어도 질리지 않을걸!","헤헤. 우리 일행 중 누군가는 벌써 가족이 늘어날 거라고 하더군. 이슬라 모나에서도 인생은 계속되지!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
				}
			}
		break;
		
		case "island_woman_1":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
		break;
		
		case "island_woman_2":
			dialog.text = "너... 무차스 그라시아스, 나리! 자주 들러줘...";
			link.l1 = "";
			link.l1.go = "island_woman_3";
			locCameraFromToPos(-1.86, 1.18, 4.51, true, -1.49, 0.20, 6.13);
		break;
		
		case "island_woman_3":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// пираты Родгара
		case "fort_pirate":
			if(npchar.location == "islamona_factoria")
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("다 괜찮아요, 선장님!","노예들은 통제되고 있으니 걱정 마."),RandPhraseSimple("걱정할 필요 없어, 반란은 있을 수 없어.","럼 고마워! 이제 일하러 간다!"));
			}
			else
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("스페인 놈들? 너한테서 이런 짓을 기대하진 않았는데.","이제 평화롭게 자려면 해변까지 걸어가야 하잖아!"),RandPhraseSimple("왜 이런 결정을 내린 거야, 응, 선장?","그때 보스가 너를 믿었지 - 그리고 틀리지 않았어. 이번에도 너를 믿을게."));
			}
			link.l1 = "...";
			link.l1.go = "fort_pirate_1";
		break;
		
		case "fort_pirate_1":
			DialogExit();
			npchar.dialog.currentnode = "fort_pirate";
		break;
		
		// посетители таверны
		case "citizen_tavern":
			dialog.text = LinkRandPhrase("고된 노동 끝에는 한두 잔 마시는 것도 죄가 아니지...","거의 다 끝났으니 이제 집에 가야지. 아내가 기다리고 있을 테니까...","아, 일 끝나고 우리 선술집에서 쉬는 건 참 좋지! 모두가 당신께 감사하고 있어요, 선장님!");
			link.l1 = LinkRandPhrase("술이나 즐겨, 친구야, 하하!","진정해, 친구야. 너무 과음하지 마라, 안 그러면 마누라한테 혼날 거야, 하하!","너무 무리하지 마, 친구야. 인생이 일만 있는 건 아니잖아!");
			link.l1.go = "citizen_tavern_1";
		break;
		
		case "citizen_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "citizen_tavern";
		break;
		
		case "sailor_tavern":
			if (GetCharacterIndex("Mirabella") != -1) sTemp = "Who's that pretty mulatto woman living here?";
				else sTemp = "Captain, nice place you got here!";
			dialog.text = RandPhraseSimple(RandPhraseSimple("선장님, 여기 참 멋진 곳이군요!","만약 우리가 갑자기 럼이 다 떨어진다면 어쩌겠냐? 너라면 분명히 더 구해오겠지, 안 그래?"),RandPhraseSimple("이런 휴가를 오랫동안 꿈꿨어. 그래도... 창관 하나 있었으면 좋겠네, 그냥 미친 생각이지, 선장.",sTemp));
			link.l1 = "...";
			link.l1.go = "sailor_tavern_1";
		break;
		
		case "sailor_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_tavern";
		break;
		
		case "sailor_town":
			dialog.text = RandPhraseSimple(RandPhraseSimple("쉬는 시간을 주셔서 감사합니다, 선장님.","여기 참 잘 꾸며놨군. 정돈도 잘하고, 선장답게 솜씨가 있네."),RandPhraseSimple("신선한 음식, 술, 발밑의 단단한 땅. 이게 바로 꿈이지.","여기서 좀 더 머무르고 싶어."));
			link.l1 = "...";
			link.l1.go = "sailor_town_1";
		break;
		
		case "sailor_town_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_town";
		break;
		
		// рабы
		case "slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("너무 피곤해서 거의 서 있을 수도 없겠어.","이렇게는 더 이상 살 힘도 없어!"),RandPhraseSimple("이 일은 나한테 너무 힘들어.","감시관들이 내 피부에 살아 있는 세포 하나도 남기지 않았어!"));				
			link.l1 = "";
			link.l1.go = "slave_1";
		break;
		
		case "slave_1":
			DialogExit();
			npchar.dialog.currentnode = "slave";
		break;
		
		// энкауниеры в домах
		case "HouseMan":
			dialog.text = LinkRandPhrase("무엇을 도와드릴까요, 선장님?","들어와, 여기 현지 빠에야 좀 먹어봐. 제발, 제발 뭘로 만들었는지는 묻지 마!","어서 오시오, 선장님. 여기 마음에 드시오?");
			link.l1 = "...";
			link.l1.go = "HouseMan_1";
		break;
		
		case "HouseMan_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseMan";
		break;
		
		case "HouseWoman":
			dialog.text = LinkRandPhrase("나리, 환영하오!","안녕하시오, 선장님. 머물 생각이오?","나 때문에 오셨나요? 들어오세요, 어질러진 건 신경 쓰지 마시오, 나리.");
			link.l1 = "...";
			link.l1.go = "HouseWoman_1";
		break;
		case "HouseWoman_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseWoman";
		break;
	}
}