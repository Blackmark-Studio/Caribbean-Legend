void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "뭐 필요해?";
			link.l1 = "아무것도 아니야.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Alamida_church":
			dialog.text = "...그리고 성령의 이름으로. 아멘.";
			link.l1 = "나는 교회에서 군인들을 좀처럼 보지 못하지.";
			link.l1.go = "Alamida_church_2";
		break;
		
		case "Alamida_church_2":
			dialog.text = "많은 이들이 신앙과 검이 양립할 수 없다고 믿지. 하지만 외과의사는 치료하기 위해 자르지 않나? 아버지는 보호하기 위해 벌을 주지 않나?";
			link.l1 = "정당화처럼 들리는데.";
			link.l1.go = "Alamida_church_3";
			link.l2 = "그 말에 일리가 있지. 때로는 잔혹함도 필요하다.";
			link.l2.go = "Alamida_church_4";
		break;
		
		case "Alamida_church_3":
			dialog.text = "착각하지 마. 이건 정당화가 아니라 이해야. 내가 처음 복무를 시작했을 때는, 한 명 한 명의 죽음이... 힘들었지. 하지만 그 후에... 내 눈이 열렸어. '잔혹함이야말로 최고의 사랑의 발현이다.'";
			link.l1 = "기도나 계속 하시지.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_4":
			dialog.text = "그래... 그래! 바로 그가 그렇게 말했어, 나를 이 길로 이끈 자가. '힘 없는 자비는 쓸모없다, 손 없는 검처럼.'";
			link.l1 = "기도는 네게 맡기고 가겠다.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_5":
			dialog.text = "우리를 위해 기도해 주시오. 우리가 한 일과... 앞으로 해야 할 일 모두를 위해서.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_guber":
			dialog.text = "7퍼센트 부족이군. 지난번엔 5퍼센트였지. 버려진 정원에 잡초처럼 늘어나고 있어...";
			link.l1 = "이 마을에 새 총독이 왔나?";
			link.l1.go = "Alamida_guber_2";
		break;
		
		case "Alamida_guber_2":
			dialog.text = "뭐라고? 아, 아니오. 각하께서는 저기 구석에 계십니다. 나는 페르난도 데 알라미다 돈, 왕실 감찰관이오.";
			link.l1 = "힘든 일이겠군.";
			link.l1.go = "Alamida_guber_3";
		break;
		
		case "Alamida_guber_3":
			dialog.text = "부패와 싸울 때 가장 힘든 게 뭔지 아나? 죄 지은 자들이 꼭 나쁜 사람인 건 아니지. 그들도 자식이 있고, 가족이 있어. 그리고 매번 스스로에게 되새겨야 해. 금잔에 담긴다 해도, 독은 결국 독이라는 걸.";
			link.l1 = "하지만 그렇게까지 엄하게 판단할 수 있을까? 우리 모두 인간이잖아...";
			link.l1.go = "Alamida_guber_4";
			link.l2 = "너무 물러터졌군. 감옥에나 쳐넣어야 정신 차릴 거야.";
			link.l2.go = "Alamida_guber_5";
		break;
		
		case "Alamida_guber_4":
			dialog.text = "늑대에게 자비를 베푸는 것은 양에게 잔인한 짓이지. 그렇게 말했다네... 현명한 이가. 그리고 날이 갈수록, 그 지혜를 점점 더 깨닫게 되지.";
			link.l1 = "더 이상 일 방해하지 않겠소.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_5":
			dialog.text = "흠. 나도 예전엔 그렇게 생각했지. 하지만 감옥은 너무 단순해. 뭔가 더 필요하지... 정화가.";
			link.l1 = "더 이상 일에 방해하지 않겠소.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_6":
			dialog.text = "그래. 서류는 기다려주지 않지. 하지만 가끔은 여기 적힌 숫자 하나하나 뒤에 누군가의 운명이 숨어 있는 것 같아.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_city":
			dialog.text = "잘 듣고 있어, "+GetAddress_Form(NPChar)+"? 대체 무슨 이유로 이렇게 길에서 나에게 다가온 거지?";
			link.l1 = "너는 다른 놈들과 달라 보여.";
			link.l1.go = "Alamida_city_2";
		break;
		
		case "Alamida_city_2":
			dialog.text = "돈 페르난도 데 알라미다, 왕실 감찰관이오. 오늘은 자네가 처음으로 이렇게 궁금해하는군. 모두가 숨고, 모두가 나를 두려워하지. 하지만 정직한 사람은 두려울 게 없지. 그게 우리에게 무엇을 말해 주는가?";
			link.l1 = "네 명성이 그들을 겁먹게 한다는 거야?";
			link.l1.go = "Alamida_city_3";
			link.l2 = "정직한 사람이 드물다는 건가?";
			link.l2.go = "Alamida_city_4";
		break;
		
		case "Alamida_city_3":
			dialog.text = "재밌군. 나도 그렇게 생각했지. 하지만 깨달았어 - 두려움은 사람을 정화하지. 사람이 두려워할 때 더 정직해져. 본성에 더 가까워지고. 신께도.";
			link.l1 = "흥미로운 생각이군. 나는 가봐야겠어. 좋은 하루 보내시오, 페르난도 돈.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_4":
			dialog.text = "흥미롭군... 네가 아는 어떤 사람과 똑같이 생각하는구나. 안타깝게도 모두가 이 진실을 받아들일 수 있는 건 아니지.";
			link.l1 = "흥미로운 생각이군. 나는 가봐야겠어. 좋은 하루 보내시오, Fernando 돈.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_5":
			dialog.text = "좋은가? 그래, 아마도. 정의롭기만 하다면.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_exit":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_DlgExit");
		break;
		
		case "Alamida_repeat":
			dialog.text = "더 필요한 거 있습니까, 선장님?";
			link.l1 = "아니오, don Fernando 나리, 그냥 인사만 드리는 겁니다, 그 이상은 아닙니다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alamida_repeat";
		break;
		
		case "Alamida_abordage":
			if (startHeroType == 4)
			{
				dialog.text = "칼을 든 아가씨라니? 이런 광경을 내 눈으로 보게 될 줄은 꿈에도 몰랐지. 그런데 대체 누구시길래, 세뇨리타, 감히 '성스러운 자비'를 공격하려 드는 거요?";
				link.l1 = "헬렌 맥아더 선장. 그리고 네 얼굴에 떠오른 그 놀란 표정, 나도 아주 잘 아는 표정이지.";
				link.l1.go = "Alamida_HelenaCaptain";
			}
			else
			{
				dialog.text = "감히 뭐라고?! '성스러운 자비'를 공격하다니?! 왕의 뜻을 실은 배를, 그리고... 좋아. 어차피 여기까지 왔으니 말해 봐라 - 왜지? 왜 이런 미친 짓을 선택한 거냐?";
				link.l1 = "나는 해적이다. 그리고 네 갤리온에는 분명 보물이 가득하겠지.";
				link.l1.go = "Alamida_abordage_Gold";
				link.l2 = "이렇게 아름다운 배라니... 반드시 내 것으로 만들어야겠어.";
				link.l2.go = "Alamida_abordage_Ship";
				link.l3 = "나는 그대 나라의 적이오, 페르난도 돈.";
				link.l3.go = "Alamida_abordage_Hater";
				link.l4 = "그냥. 왜 안 되겠어?";
				link.l4.go = "Alamida_abordage_Prikol";
			}
		break;
		
		case "Alamida_HelenaCaptain":
			dialog.text = "우리 배를 지켜주는 성모 마리아와 참 많이 닮았군... 똑같이 아름답지. 하지만 그분은 의로운 자들을 지키시지만, 너는...";
			link.l1 = "네 배를 가지러 왔다. 그리고 여기서는 칭찬 따위 소용없어, don Fernando.";
			link.l1.go = "Alamida_HelenaCaptain_2";
		break;
		
		case "Alamida_HelenaCaptain_2":
			dialog.text = "참 안됐군. 그럼 내가 겸손이 뭔지 가르쳐줘야겠네. 다른 방법이 없으니 힘으로라도.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Gold":
			dialog.text = "아, 그래. 물론이지. 금. 언제나 금이지. 영혼을 썩게 하는 독이야. 그걸 위해 네가 죽게 될 거다.";
			link.l1 = "그렇게 호들갑 떨지 마. 그냥 일일 뿐이야.";
			link.l1.go = "Alamida_abordage_Gold_2";
		break;
		
		case "Alamida_abordage_Gold_2":
			dialog.text = "창고에 있는 모든 동전은 죄인들이 정화의 대가로 치른 것이네. 그걸 원하나? 그렇다면 그들과 같은 운명을 맞이하게 될 걸세.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Ship":
			dialog.text = "'성스러운 자비'를 탐낸 자들이 많았지. 그 아름다움 때문에 수많은 선장들이 파멸을 맞았어.";
			link.l1 = "그럼 내가 먼저 차지하겠다.";
			link.l1.go = "Alamida_abordage_Ship_2";
		break;
		
		case "Alamida_abordage_Ship_2":
			dialog.text = "힘 없는 자비는 손 없는 검처럼 쓸모없다. 오늘 너는 이 교훈을 뼈저리게 알게 될 것이다.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Hater":
			dialog.text = "그래, 그렇군. 또 한 명 제국의 위대함을 질투하는 자로군.";
			link.l1 = "무슨 위대함? 네 고집스러운 방식이 이 세상을 가로막고 있어.";
			link.l1.go = "Alamida_abordage_Hater_2";
		break;
		
		case "Alamida_abordage_Hater_2":
			dialog.text = "자기 자신에게 거짓말하지 마라. 스페인에 대한 두려움이 너를 더 솔직하게 만들지. 네 본성에 더 가까워지는 거야. 이제 곧 네가 직접 알게 될 거다.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Prikol":
			dialog.text = "미치광이군. 아니면 나를 시험하려고 보낸 건가?";
			link.l1 = "모든 일에 이유가 필요한 건 아니야, 나리.";
			link.l1.go = "Alamida_abordage_Prikol_2";
		break;
		
		case "Alamida_abordage_Prikol_2":
			dialog.text = "너 같은 놈들이 가장 위험하다고 그가 말했지. 하지만 이 일은 내 전투력을 더 강하게 만들어 줄 거다.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_SecondRound":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_Abordage_DlgExit_1");
		break;
		
		case "Alamida_abordage_TrirdRound":
			if (startHeroType == 4)
			{
				dialog.text = "이토록 강한 정신력... 이런 의지라니...";
				link.l1 = "놀랐나?";
			}
			else
			{
				dialog.text = "나쁘지 않군. 이런 만만치 않은 상대는 오랜만이야.";
				link.l1 = "넌 쉴 틈도 주지 않겠다.";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_2";
		break;
		
		case "Alamida_abordage_TrirdRound_2":
			if (startHeroType == 4)
			{
				dialog.text = "나는 경고를 받았지... 이런 시련에 대해. 전사의 신념마저 흔들 수 있는 아름다움에 대해.";
				link.l1 = "단순한 일도 항상 그렇게 복잡하게 만드십니까, don Fernando 나리?";
			}
			else
			{
				dialog.text = "주님께서는 정의로운 대의를 섬기는 자들에게 힘을 주신다네.\n하지만... 가끔은 내가 무엇을 섬기고 있는지 더는 확신이 서지 않아.";
				link.l1 = "의심이 드나?";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_3";
		break;
		
		case "Alamida_abordage_TrirdRound_3":
			if (startHeroType == 4)
			{
				dialog.text = "간단하다고? 아니... 분명 더 깊은 의미가 있을 거야. 이건 시험이야. 내가 틀릴 리 없어.";
			}
			else
			{
				dialog.text = "아니. 그는 나에게 의심하지 말라고 가르쳤어. 절대로.";
			}
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_TrirdRound_4";
		break;
		
		case "Alamida_abordage_TrirdRound_4":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_Abordage_DlgExit_2");
		break;
		
		case "Alamida_abordage_Molitva":
			dialog.text = "잠깐만... 잠깐. 네가 이겼다. 나는 다쳐서 피를 흘리고 있어. 죽기 전에 기도하게 해 줘.";
			link.l1 = "좋소.";
			link.l1.go = "Alamida_abordage_Molitva_2";
		break;
		
		case "Alamida_abordage_Molitva_2":
			if (startHeroType == 4)
			{
				dialog.text = "주님... 제 죄를 용서하시고 이 시련의 시간에 힘을 주소서. 쓰러진 동료들의 영혼을 축복하소서. 신실한 선원들, 그들은 정의를 실었다 믿으며 죽었습니다\n아버지, 저는 당신의 가르침을 따르며 불의와 싸우려 했습니다. 그러나 당신의 아들이 알라미다 가문의 명예를 더럽혔습니다. 용서하소서\n조국이여... 저는 충성스럽고 진실하게 섬기겠다고 맹세했습니다. 하지만 저의 열정과 분노가... 결국 제가 싸우려 했던 존재가 되고 말았습니다\n디에고... 어쩌면 그가 거짓말을 했던 걸까? 이 모든 시간 동안... 만약 그렇다면 나는 참으로 불행하구나\n그리고 이 여인을 축복하소서, 주님. 어쩌면 마지막 자비로 저에게 그녀를 보내주신 것일지도... 제가 얼마나 멀리 벗어났는지 깨닫게 하시려. 아멘.";
			}
			else
			{
				dialog.text = "주여... 제 죄를 용서하시고 이 시련의 시간에 힘을 주소서. 쓰러진 동료들의 영혼을 축복하소서. 충직한 선원들이었으니, 정의를 실었다 믿으며 죽었습니다\n아버지, 저는 당신의 가르침대로 살고, 불의를 물리치려 했습니다. 그러나 당신의 아들이 알라미다 가문의 명예를 더럽혔습니다. 용서하소서\n조국이여... 저는 충성스럽고 진실하게 당신을 섬기겠노라 맹세했습니다. 그러나 저의 열정과 분노가... 제가 싸우려 했던 그 존재가 되어버렸습니다\n디에고... 혹시 그가 거짓말을 했던 걸까? 이 모든 시간 동안... 그렇다면 나는 참으로 불행하구나\n성모 마리아님, 저희를 위해 하느님께 기도해 주시고 자비를 베풀어 주소서. 아멘.";
			}
			link.l1 = "당신을 알아보지 못하겠군, 페르난도 나리. 지금은 완전히 딴사람 같소. 그리고 누구에 대해 이야기하고 있었소?";
			link.l1.go = "Alamida_abordage_Molitva_3";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "Church_Stay_1", "", 5.0);
		break;
		
		case "Alamida_BitvaEnd":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SantaMisericordia_CanLeaveCauta", 5);
		break;
			
		case "Alamida_abordage_Molitva_3":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_Abordage_DlgExit_3");
		break;
		
		//Элен
		case "Alamida_Helena":
			dialog.text = "내 선장님, 축하드립니다! 정말 치열한 전투였어요. 저 선장도 실력자였지, 정말 대단했죠. 하지만 선장님은... 그보다 더 뛰어났어요. 선장님이 정말 자랑스럽습니다...";
			link.l1 = "고마워, 내 사랑. 다친 데는 없어?";
			link.l1.go = "Alamida_Helena_2";
		break;
		
		case "Alamida_Helena_2":
			dialog.text = "아니, 아니야. 몇 번은 정말 아슬아슬했다고 생각했지 - 승선하기 전에도, 승선 중에도 말이야. 그리고 너, 괜찮아?";
			link.l1 = "괜찮아, 다시 한 번 고마워. 선실에 가서 쉬어, 곧 따라갈게.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Мэри
		case "Alamida_Mary":
			dialog.text = "찰스, 괜찮아? 최대한 빨리 왔어, 알겠지.";
			link.l1 = "괜찮아, 고마워, 자기야. 그래도 꽤 힘든 싸움이었어.";
			link.l1.go = "Alamida_Mary_2";
		break;
		
		case "Alamida_Mary_2":
			dialog.text = "기쁘구나! 하지만... 들어봐, Charles? 우리가 왜 이 사람들을 공격한 거지? 주님께서 우리를 용서하지 않으실 거야, 절대. 이 배... 마치 거대한 성전 같아. 내가 이 배를 봤을 때, 내 심장이 떨렸어. 마치 책에서만 보던 진짜 교회를 처음 봤을 때처럼. 그런데 지금은 피를 흘리고 있어!";
			link.l1 = "메리... 겉모습은 속일 수 있다는 거 알지. 경건한 척하는 가면 뒤에는 너처럼 순진한 신도들에게서 돈을 뜯어낸 자들이 있었어. 이해하겠어?";
			link.l1.go = "Alamida_Mary_3";
		break;
		
		case "Alamida_Mary_3":
			dialog.text = "나... 나도 믿어, Charles. 좋아. 다만... 여기서 찾은 금 중 일부라도 정말 필요한 이들에게 기부하자, 응? 그러면 내 마음이 좀 놓일 거야.";
			link.l1 = "그렇게 할게, Mary. 약속할게. 이제 마음을 가다듬고 진정해 봐. 다 끝났으니까.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Томми
		case "Alamida_Tommi":
			dialog.text = "하, 그래, 승리를 축하하네, 선장! 이게 바로 진짜 장사지! 이 갈레온에서 이런 노획이라니!..";
			link.l1 = "오늘은 평소보다도 더 활짝 웃는구나, 토미.";
			link.l1.go = "Alamida_Tommi_2";
		break;
		
		case "Alamida_Tommi_2":
			dialog.text = "당연하지! 이런 전리품이라니. 그리고 그 싸움도 대단했지. 혁명 때가 생각나더군. 그리고 또... 헤헷.";
			link.l1 = "무슨 일이야, Tommy? 어서, 말해 봐.";
			link.l1.go = "Alamida_Tommi_3";
		break;
		
		case "Alamida_Tommi_3":
			dialog.text = "배 전체를 떠다니는 대성당처럼 꾸며 놨군. 온갖 곳에서 금도 잔뜩 긁어모았고. 진짜 가톨릭 광신도들이지! 한심하고 우스워.";
			link.l1 = "여긴 보물선이야, Tommy. 교회 배가 아니라고.";
			link.l1.go = "Alamida_Tommi_4";
		break;
		
		case "Alamida_Tommi_4":
			dialog.text = "우리 입장에선 별 차이 없지. 어쨌든, 그 돈들과 교황쟁이들에게 제대로 본때를 보여줄 수 있어서 속이 다 시원했어! 둘 다 정말 질색이거든. 오늘 하루 정말 통쾌했지, 하하하!";
			link.l1 = "넌 정말 변하지 않는구나! 좋아, 해산해. 여긴 다 통제되고 있어.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Тичингиту
		case "Alamida_Tichingitu":
			if (startHeroType == 1)
			{
				dialog.text = "찰스 선장, 우리가 승리를 거뒀소. 이번 싸움은 힘들었소. 티칭기투조차도 힘들어했으니, 내가 마을에서 손꼽히는 전사 중 하나임에도 말이오.";
				link.l1 = "그래, 친구. 정말 만만치 않은 상대들이었지.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "드 몬토야 나리, 배는 우리 거다.";
				link.l1 = "아주 잘했어, Tichingitu. 나도 여기서 막 끝냈어.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Paterson 선장, 마지막 저항이 배에서 진압되었소.";
				link.l1 = "늦었군, 티치! 다음엔 나랑 같이 다니는 게 좋을 거야. 뭐, 나 혼자서도 충분히 처리할 수 있었지만 말이지...";
			}
			if (startHeroType == 4)
			{
				dialog.text = "McArthur 선장, 괜찮으십니까?";
				link.l1 = "그래, 티칭기투, 나 괜찮아. 물어봐 줘서 고맙다. 그리고 선장을 의심하지 마라 - 나 혼자서도 완벽하게 처리했으니까.";
			}
			link.l1.go = "Alamida_Tichingitu_2";
		break;
		
		case "Alamida_Tichingitu_2":
			if (startHeroType == 1)
			{
				dialog.text = "싸우는 동안 영혼들이 내게 이렇게 말했어. 그리고 왜 내가 그들을 죽이냐고 물었지. 이제 나도 너한테 똑같이 묻겠다.\n티칭이투는 그들의 눈에서 봤어, 그들은 악당이 아니야. 아직은.";
				link.l1 = "아, 내가 뭘 말해 줄 수 있겠어? 답이 없어, 티칭기투.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "나 너한테 물어볼 거 있어, 드 몬토야 선장.";
				link.l1 = "듣고 있다.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "티칭이투가 질문 하나 하고 싶소, 윌리엄 선장, 허락해 주신다면.";
				link.l1 = "허락한다.";
			}
			if (startHeroType == 4)
			{
				dialog.text = "의심은 안 해, 하지만 걱정돼, 선장.";
				link.l1 = "알겠어, 알겠어. 네 눈을 보니 뭔가 더 물어보고 싶은 게 있구나.";
			}
			link.l1.go = "Alamida_Tichingitu_3";
		break;
		
		case "Alamida_Tichingitu_3":
			if (startHeroType == 1)
			{
				dialog.text = "흠, 선장님 말씀대로지. 여기서 끝내는 건가?";
				link.l1 = "그래. 좀 더 둘러보고 나서 다른 사람들과 합류할게.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 2)
			{
				dialog.text = "이 사람들, 너랑 같은 부족 출신 아니지? 스페인 놈들도 아니잖아? 그런데 왜 공격하기로 한 거야?";
				link.l1 = "그건 맞아. 하지만 인디언 부족들도 서로 싸우지 않나? 아니면 한 부족 안에서도 다툼과 불화가 있지 않아?";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 3)
			{
				dialog.text = "이 배가 교회처럼 보이네. 너 교회랑 하얀 신이 싫으냐?";
				link.l1 = "전혀 아니야. 그냥 장식일 뿐이거든? 이건 보물선이야. 하지만 넌 이해 못 하겠지 – 네네들은 세금이 뭔지도 모른다던데. 운 좋은 놈들이지.";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 4)
			{
				dialog.text = "그래. 진실을 말해라. MacArthur 선장, 왜 우리가 이 떠다니는 교회를 공격하는 거지?";
				link.l1 = "떠다니는 교회라니, 하하하! 아니, 아니야. 이건 금고선이야. 흠, 네가 잘 이해 못하는 것 같은데. 음, 그들은 금을 운반하고 있었지. 내가 페르난도 데 알라미다를 쓰러뜨렸다고 얀에게 말하면 얼마나 자랑스러워할지 상상된다!";
				link.l1.go = "Alamida_Tichingitu_4";
			}
		break;
		
		case "Alamida_Tichingitu_4":
			if (startHeroType == 2)
			{
				dialog.text = "흠, 맞아요, 선장. 하지만 인디언들과는 이런 일이 백인들보다 덜 일어나지.";
				link.l1 = "아마도. 뭐, 이 자가... 내 일에 끼어들고 있었거든.";
				link.l1.go = "Alamida_Tichingitu_5";
			}
			if (startHeroType == 3)
			{
				dialog.text = "진실을 말하자면, 마스코기족은 성도 없고 세금도 없어.";
				link.l1 = "맞아. 가도 돼, 어차피 이미 늦었으니까. 나중에 이 멋진 갈레온을 어떻게 할지 정하자고. 난 이런 배는 별로지만, 젠장, 정말 멋지게 생겼군.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 4)
			{
				dialog.text = "티칭이투도 "+pchar.name+" 선장을 자랑스러워해. 그리고 이 힘든 싸움에서의 승리를 축하한대.";
				link.l1 = "고맙다. 이제 전리품을 나누자.";
				link.l1.go = "Alamida_BitvaEnd";
			}
		break;
		
		case "Alamida_Tichingitu_5":
			dialog.text = "방해하는 건가, 몬토야 나리?";
			link.l1 = "정확히 그렇지. 이 군도는 우리 둘이 있기엔 너무 좁아. 그리고 나는 여기서 우리 국가에 훨씬 더 쓸모 있는 사람이야. 코코아 리프를 기억해 봐라 - 그 자는 동료들에게 이익보다 해를 더 끼쳤지. 여기서도 마찬가지야.";
			link.l1.go = "Alamida_Tichingitu_6";
		break;
		
		case "Alamida_Tichingitu_6":
			dialog.text = "이제 나도 알겠어. 티칭기투 가도 돼, 선장?";
			link.l1 = "그래, 가라. 나도 곧 너희한테 합류할 거야.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			dialog.text = LinkRandPhrase("이봐, 왜 그렇게 무기를 휘두르고 있는 거야?! 당장 집어넣어!", "당장 무기를 거두라고 명령한다!", "이봐, " + GetAddress_Form(NPChar) + ", 사람들 그만 놀래켜! 무기 집어넣어.");
			link.l1 = LinkRandPhrase("알겠어, 내가 치워둘게...", "이미 끝났어.", "말씀대로...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("꺼져!", "이걸 써야겠군!", "때가 되면 치워 두겠어.");
			link.l2.go = "fight";
		break;
		
	}
} 