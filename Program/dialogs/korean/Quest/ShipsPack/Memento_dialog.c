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
			dialog.text = "뭘 원하지?";
			link.l1 = "아무것도 아니다.";
			link.l1.go = "exit";
		break;
		
		// Диалог с Алонсо после успешного абордажа
		case "Memento_MortimerGrimDead_Alonso_1":
			dialog.text = "선장님, 오늘은 우리가 이겼습니다. 선봉대가 하층 갑판을 마저 쓸고 있습니다. 포로는 없습니다... 하! 보아하니 선장님도 전혀 봐주지 않으셨군요.";
			link.l1 = "왠지 멋진 연설이라도 할 줄 알았는데, 그냥 들이닥치더군.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_2";
			Achievment_Set("ach_CL_154");
			if (sti(pchar.rank) <= 11) Achievment_Set("ach_CL_156");
		break;

		case "Memento_MortimerGrimDead_Alonso_2":
			dialog.text = "자유롭게 말해도 되겠습니까?";
			link.l1 = "허락한다.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_3";
			link.l2 = "아니, 여기서 할 일은 끝났어.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_end";
		break;

		case "Memento_MortimerGrimDead_Alonso_3":
			dialog.text = "왜 우리가 그들을 공격했지? 저 브리그는 위협도 아니었고, 화물도 싣지 않았어. 물론 그림에 대한 온갖 소문이 돌긴 했지만, 그를 두려워한 건 노예상들뿐이었지. 오늘 많은 사람이 죽었어 — 대체 무엇 때문에?";
			if (sti(pchar.questTemp.ISawDiegoDeLanda) >= 2)
			{
				link.l1 = "...";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_4";
			}
			else
			{
				link.l1 = "이제 선원들 대표로 말하는 거야?";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
			}
		break;

		case "Memento_MortimerGrimDead_Alonso_4":
			dialog.text = "그리고 이게 처음도 아니야...";
			link.l1 = "이제 선원들 대표로 말하는 거냐?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_5":
			dialog.text = "아니. 내 말 믿어라, 만약 선원들이 그런 질문을 한다면 그건 내가 일을 못한다는 뜻이고, 넌 이미 죽은 목숨이라는 거야\n"+
			"운 좋게도, 이놈들이 이번 피비린내 나는 일로 꽤 짭짤하게 벌었지. 이 배에 탄 선원들 전부 주머니에 두블룬을 가득 채웠다니까!\n"+
			"귀한 화물은 없었어 — 그냥 원주민 장신구랑 으스스한 부적뿐이었지. 그래도 선원들은 도둑놈처럼 챙겼어. 그림이 녀석들한테 돈을 두둑이 줬던 모양이야\n"+
			"그 금에서 몫을 챙길 생각은 아니겠지, 선장?";
			link.l1 = "나는 아니야, 알론소. 알려줘서 고마워.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_6";
			link.l2 = "그래. 내 몫은 꼭 내 선실로 가져다줘.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_7";
		break;

		case "Memento_MortimerGrimDead_Alonso_6":
			dialog.text = "언제나 선장 편이지. 그런데, 그 기념품으로 뭘 할 생각이야?";
			link.l1 = "전리품으로 챙겨. 그거 말고 뭐가 있겠어?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "아직 결정하지 않았어"+GetSexPhrase(""," 아직")+" .";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
		break;

		case "Memento_MortimerGrimDead_Alonso_7":
			dialog.text = "항상 선장님 편이죠. 그런데, 그 유품으로 뭘 하실 생각입니까?";
			link.l1 = "전리품으로 챙겨라 — 그거 말고 뭐가 있겠어?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "아직 결정하지 않았어"+GetSexPhrase(""," 아직")+" .";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
			AddCrewMorale(Pchar, -10);
			AddItems(Pchar, "gold_dublon", 500);
		break;

		case "Memento_MortimerGrimDead_Alonso_8":
			dialog.text = "안 하는 게 좋겠어. 뭔가 원주민 기호로 뒤덮여 있거든. 그리고 안 좋은 소문도 돌아 — 한때 끔찍한 역병을 견뎌냈고, 갑판 위가 시체로 춤을 췄다는 말이 있어\n"+
			"선미에 있는 해골에 대해서는 말도 꺼내지 않을 거야. 어느 바보가 재미 삼아 해골을 집어 들 용기를 내기 전까지는, 나 말고는 거기서 감시를 서겠다는 놈이 아무도 없을 거거든.";
			link.l1 = "알겠어, Alonso. 다시 일하자.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_9";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_9":
			dialog.text = "예, 선장.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_end";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_end":
			DialogExit();
			AddDialogExitQuestFunction("Memento_MortimerGrimDead_Alonso_2");
		break;
		
		// Диалог с Алонсо в первую ночь
		case "Memento_Dich_EtapOne_Alonso_1":
			dialog.text = "선장님, 이런 시간에 폐를 끼쳐 죄송합니다.";
			link.l1 = "보고하라, 알론소.";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_2";
			if (CheckAttribute(pchar, "questTemp.Memento_Dich_EtapTwo"))
			{
				dialog.text = "선장? 여기서 뭐 하는 거야? 여기서 자고 있었어?";
				link.l1 = "상관없어.";
				link.l1.go = "Memento_Dich_EtapTwo_Alonso_2";
				link.l2 = "내 선실이... 뭔가 불길하게 느껴져.";
				link.l2.go = "Memento_Dich_EtapTwo_Alonso_2";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_2":
			dialog.text = "상황이 안 좋아. 선원들 사기가 바닥이야! 사람들은 대놓고 배에 저주가 걸렸다고 말하고 있어. 밤마다 이상한 걸 본다고 불평하지.";
			link.l1 = "정확히 뭘 본다는 거지?";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_3";
		break;

		case "Memento_Dich_EtapOne_Alonso_3":
			dialog.text = "악몽이 대부분이야. 하지만 제일 끔찍한 건 우리 중 한 명이 열병으로 죽었다는 거지. 소처럼 힘센 젊은 녀석이었는데, 몇 시간 만에 불타오르듯 죽어버렸어.";
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				link.l1 = "그건 의사가 결정할 일이야. "+sld.name+" 자기 일은 잘 아는 놈이지.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
			else
			{
				link.l1 = "그건 정상 아니야. 선원들 잘 다잡아, 알론소. 그게 네 일이잖아.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
		break;
		
		case "Memento_Dich_EtapOne_Alonso_4":
			dialog.text = "알겠어!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapOne_End");
		break;
		
		// Диалог с Алонсо во вторую ночь
		case "Memento_Dich_EtapTwo_Alonso_2":
			dialog.text = "알겠어. 이제 선원들 중 많은 이들이 무리를 지어 자고 있어 — 혼자 있기가 두려운 거지. 이 배에서 혼자 있는 게 가능하기라도 한 것처럼 말이야...";
			link.l1 = "내가 해낸 것 같진 않은데. 무슨 일이 있었지?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_3";
		break;

		case "Memento_Dich_EtapTwo_Alonso_3":
			dialog.text = "싸움이 벌어졌어 — 호세가 마르셀을 찔렀지. 자기가 "역병을 옮겼다"고 소리치더군.";
			link.l1 = "상황이 더 나빠지고 있나?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_4";
		break;

		case "Memento_Dich_EtapTwo_Alonso_4":
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				dialog.text = sld.name+" 오늘 아침에 이미 보고했습니다. 열한 명이 죽었습니다. 어떻게 해야 합니까?";
			}
			else
			{
				dialog.text = "또 열한 명이 더 죽었어. 이제 어떻게 해야 하지?";
			}
			link.l1 = "내가 신호를 보내겠다.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_5";
		break;

		case "Memento_Dich_EtapTwo_Alonso_5":
			dialog.text = "그러길 바라오, 선장. 호세는 어찌 되었소? 죽이는 건 농담이 아니오.";
			link.l1 = "종이 울린 뒤에 저 놈을 목매달아라. 우리가 이곳을 장악하고 있다는 걸 보여줘.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_6";
			link.l2 = "채찍 삼십 대다. 살아남는다면 — 그건 신의 뜻이지.";
			link.l2.go = "Memento_Dich_EtapTwo_Alonso_7";
		break;

		case "Memento_Dich_EtapTwo_Alonso_6":
			dialog.text = "알겠어!";
			link.l1 = "...";
			link.l1.go = "exit";
			SetCrewQuantity(pchar, GetCrewQuantity(pchar) - 1);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;

		case "Memento_Dich_EtapTwo_Alonso_7":
			dialog.text = "알겠어!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddCrewMorale(Pchar, -10);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;
		
		// Диалог с Алонсо в третью ночь
		case "Memento_Dich_EtapThree_AlonsoPrizrak_1":
			dialog.text = "선장님! 경보입니다!! 지금 바로 포갑판으로 가셔야 합니다!";
			link.l1 = "무슨 일이야?";
			link.l1.go = "Memento_Dich_EtapThree_AlonsoPrizrak_2";
		break;

		case "Memento_Dich_EtapThree_AlonsoPrizrak_2":
			dialog.text = "직접 보는 게 좋을 거야. 어서, 빨리 와!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_4_1");
		break;
		
		// Уже утром
		case "Memento_Dich_EtapThree_Alonso_1":
			dialog.text = "좋은 아침이야, 선장!";
			link.l1 = "어?!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_2";
		break;

		case "Memento_Dich_EtapThree_Alonso_2":
			dialog.text = "어이, 꼴이 말이 아니군. 밤새 힘들었나? 뭐, 좋은 소식이 있어. 역병은 끝났어. 알고 보니—애초에 없었더라고.";
			link.l1 = "무슨 뜻이야?";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_3";
		break;

		case "Memento_Dich_EtapThree_Alonso_3":
			dialog.text = "선원들이 겁을 먹고, 바보 같은 유령선 이야기를 믿기 시작했지. 암시에 휘둘리는 게 얼마나 무서운지 알아? 그 때문에 침몰한 배가 한두 척이 아니야.";
			link.l1 = "하지만 사람들이 죽었잖아!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_4";
		break;

		case "Memento_Dich_EtapThree_Alonso_4":
			dialog.text = "싸움, 더러운 상처, 상한 소금 고기 — 그냥 평범한 선원들의 일상이지. 우리가 저주받은 배에 대한 이야기로 스스로를 들뜨게 만들지 않았다면, 아마 몇 명은 덜 잃었을지도 몰라\n"+
			"선미에 있던 해골도 별 도움이 안 됐지. 다행히도 어떤... 장난꾸러기가 밤새 모자를 훔쳐 갔으니\n"+
			"그런 신성모독을 했는데도 벼락이 우리를 내리치지 않자, 선원들은 기운이 나서 뱃사람 특유의 장난기를 발동하기 시작했지. 예를 들면 말이야...\n";
			link.l1 = "해골 만지지 마라!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_5";
		break;

		case "Memento_Dich_EtapThree_Alonso_5":
			dialog.text = "어... 뭐, 네가 마음에 들었다면 당연히 안 뺏지. 좋은 하루 보내, 선장\n"+
			"그건 그렇고, 모자 멋지네! 너한테 정말 잘 어울린다. 전 주인한테는 분명 안 맞았던 모양이야.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_End");
		break;
		
		// Диалоги с командой Мементо
		case "Memento_Sailor_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "안녕하시오, 선장. 그림 선장과 이야기해 보시오.";
				link.l1 = "미안하지만, 선원. 너 여기서 너무 눈에 띄잖아.";
				link.l1.go = "Memento_Sailor_1_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "더 필요한 거 있습니까, 선장님?";
				link.l1 = "아무것도 아니다.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_1_1":
			dialog.text = "무슨 말인지 알겠소, 선장. 나도 자유 선장 밑에서 일한 적 있지 — 자네랑 비슷한 사람이었어. 보물을 찾아다니고, 무역도 하고, 화물도 실었지. 그러다 상인들을 털기로 마음먹었는데 — 일이 잘 안 풀렸어. 살아남은 자들은 해적으로 몰려 교수형을 선고받았지.";
			link.l1 = "그리고 그림 선장이 널 샀다는 거야?";
			link.l1.go = "Memento_Sailor_1_2";
		break;

		case "Memento_Sailor_1_2":
			dialog.text = "우릴 한꺼번에 짐짝처럼 샀지. 모든 배엔 노련한 선원이 필요하니까, 그림은 선원을 선술집에서 뽑지 않아... 하지만 먹여주고 돈도 잘 줘. 그래서 우린 일하고, 제비도 뽑지.";
			link.l1 = "제비뽑기?";
			link.l1.go = "Memento_Sailor_1_3";
		break;

		case "Memento_Sailor_1_3":
			dialog.text = "미안하지만, 그 얘기는 하지 말아야겠어.";
			link.l1 = "그냥 떠나면 되잖아?";
			link.l1.go = "Memento_Sailor_1_4";
		break;

		case "Memento_Sailor_1_4":
			dialog.text = "어디로 갈 건데? 적어도 여기서는 희망이 있지. 어쩌면 운이 따라줄지도 몰라. 모든 배에는 각자의 운명이 있거든. 그림은 그의 몫이 있고, 너는 너의 몫이 있지. 우리는 사람이 아니라, 그냥 선박 일지에 적힌 숫자일 뿐이야.";
			link.l1 = "내 배에서는 사정이 달라.";
			link.l1.go = "Memento_Sailor_1_5";
		break;
		
		case "Memento_Sailor_1_5":
			dialog.text = "말씀대로 하겠습니다, 선장님. 좋은 하루 되십시오.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_2":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "이 훌륭한 배에 손님이 온 건 정말 오랜만이군!";
				link.l1 = "너 뱃사람이냐? 그렇게 안 보이는데.";
				link.l1.go = "Memento_Sailor_2_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "더 필요한 거 있습니까, 선장님?";
				link.l1 = "아무것도 아니다.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_2_1":
			dialog.text = "하! 선장이 나를 감옥에서 바로 샀지. 원래 포트 로얄에서 교수형 당할 뻔했어 — 시만 읊조리는 멍청한 놈을 찔렀거든. 그 자식, 당해도 싸.";
			link.l1 = "그래서 운이 좋았던 거야?";
			link.l1.go = "Memento_Sailor_2_2";
		break;

		case "Memento_Sailor_2_2":
			dialog.text = "당연하지! 선장님은 인색한 분이 아니야, 하지만 가끔은 그 양반의... 놀이에 끼어들어야 하거든.";
			link.l1 = "무슨 놀이?";
			link.l1.go = "Memento_Sailor_2_3";
		break;
		
		case "Memento_Sailor_2_3":
			dialog.text = "매주 우리는 막대를 뽑아. 짧은 막대가 걸리면 위험한 일을 하거나, 가끔은 그냥 바다에 뛰어들어야 해. 사실 웃긴 일이야. 모두한테 그런 건 아니지만, 선장 말로는 이렇게 무가치한 놈들을 걸러낸다더라.";
			link.l1 = "뭐가 자격이 없다는 거지?";
			link.l1.go = "Memento_Sailor_2_4";
		break;

		case "Memento_Sailor_2_4":
			dialog.text = "내가 어떻게 알아? 선장님은 말하는 걸 좋아하지, 신부처럼 설교도 하고: «죽음을 마주해야만 진짜로 살 수 있다!»\n"+
			"(그가 침을 뱉는다.)";
			link.l1 = "갑판에 침을 뱉으면 채찍질을 당하게 된다. 넌 선원이 아니라 그냥 악당처럼 굴고 있어. 잘 가라.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_3":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "안녕하십니까, 선장님.";
				link.l1 = "어쩌다 여기까지 오게 된 거야?";
				link.l1.go = "Memento_Sailor_3_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "더 필요한 거 있습니까, 선장님?";
				link.l1 = "아무것도 아니다.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_3";
		break;

		case "Memento_Sailor_3_1":
			dialog.text = "그림 선장이 내가 타고 있던 노예선을 빼앗았어. 나는 선창에서 병들어 죽어가고 있었지... 기억이 잘 안 나. \n정신을 차려 보니 여기, 메멘토호에 있었어.";
			link.l1 = "그럼 다른 노예들은 어떻게 됐지?";
			link.l1.go = "Memento_Sailor_3_2";
		break;
		
		case "Memento_Sailor_3_2":
			dialog.text = "모르겠어. 선장님은 모두를 풀어줬다고 했지만, 나만 배에 태워졌지. 나머지는 섬 어딘가로 흩어졌거나 상처 때문에 죽었을 거야. 그날 일은 내게 흐릿하게만 남아 있어.";
			link.l1 = "적어도 이제는 자유로워졌잖아.";
			link.l1.go = "Memento_Sailor_3_3";
		break;

		case "Memento_Sailor_3_3":
			dialog.text = "자유? 여기선 아무도 자유롭지 않아. 선장님이 금화도 주고, 음식도 주고, 옷도 주지만, 그 대가로 절대적인 충성을 요구하지 — 그리고 우리한테 저주받은 제비를 뽑게 하시지.";
			link.l1 = "제비뽑기?";
			link.l1.go = "Memento_Sailor_3_4";
		break;

		case "Memento_Sailor_3_4":
			dialog.text = "매주 누군가 제비를 뽑아 위험한 일을 맡게 되지. 모두가 돌아오는 건 아니야. 선장 말로는, 그게 살아 있는 자와 죽은 자를 가르는 방법이라더군.";
			link.l1 = "그걸 참았다고?";
			link.l1.go = "Memento_Sailor_3_5";
		break;

		case "Memento_Sailor_3_5":
			dialog.text = "모두가 행운이 자기 편이길 바라지. 선장은 각자가 무엇에 이끌리는지 잘 알아. 교수대에 대한 두려움, 금에 대한 탐욕, 목숨을 구해준 빚을 갚으려는 충동. 그런 건 내겐 아무 의미 없어. 난 돈도 필요 없고, 기억나지 않는 일에 무슨 빚을 진다는 거지?";
			link.l1 = "그렇게 대놓고 말하는 게 두렵지 않아?";
			link.l1.go = "Memento_Sailor_3_6";
		break;

		case "Memento_Sailor_3_6":
			dialog.text = "그들이 나한테 뭘 할 수 있겠어? 여긴 죽은 자들의 배야, 선장. 나는 이곳이 내 자리지만, 너는... 너는 아니지.";
			link.l1 = "네가 그렇게 말한다면. 잘 가라.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_3";
		break;
		
		case "Memento_Sailor_4":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "메멘토호에 오신 것을 환영합니다, 선장님.";
				link.l1 = "해적선에 스페인 병사라니? 그런 건 흔히 볼 수 있는 일이 아니지.";
				link.l1.go = "Memento_Sailor_4_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "더 필요한 거 있습니까, 선장님?";
				link.l1 = "아무것도 아니다.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_4";
		break;

		case "Memento_Sailor_4_1":
			dialog.text = "나는 탈영병이야. 그림 선장이 산호세 광장 교수대에서 날 바로 사 갔지. 내 초라한 목숨값으로 금화 자루 하나를 통째로 내줬다니까.";
			link.l1 = "무슨 죄로 교수형을 당했지?";
			link.l1.go = "Memento_Sailor_4_2";
		break;

		case "Memento_Sailor_4_2":
			dialog.text = "살도 장교가 우리를 정글에서 일하는 인부들을 지키라고 보냈지. 거기선 일주일이면 절반이 열병으로 죽어. 내 목숨이 그보다 더 값지다고 생각했어. 이제 내 목숨값을 매긴 놈을 섬기고 있지.";
			link.l1 = "후회 없어?";
			link.l1.go = "Memento_Sailor_4_3";
		break;

		case "Memento_Sailor_4_3":
			dialog.text = "밧줄은 오래도록 꼬일 수 있지... 선장은 자기에게 충성하는 자들에게는 후하신 분이야. 하지만 가끔 우리에게 이상한 시련을 내리시지 — 제비뽑기 같은 거 말이야. 모두가 운이 좋은 건 아니야.";
			link.l1 = "제비뽑기라고?";
			link.l1.go = "Memento_Sailor_4_4";
		break;
		
		case "Memento_Sailor_4_4":
			dialog.text = "알지. 어떤 놈들은 폭풍 속에서 돛대 위로 올라가고, 어떤 놈들은 선두에 내몰리지. 선장 말로는 네가 준비됐는지 시험하는 거라더라. 뭘 준비하는 건지는 모르겠지만, 운이 내 편이길 바랄 뿐이야.";
			link.l1 = "행운을 빌지... 뭐, 그렇지.";
			link.l1.go = "Memento_Sailor_4_5";
		break;

		case "Memento_Sailor_4_5":
			dialog.text = "감사합니다, 선장님. 죽음은 결국 우리 모두에게 찾아오지요, sooner or later.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_4";
		break;
		
		/*case "Memento_Sailor_5":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "대화 5";
				link.l1 = "대화 5";
				link.l1.go = "exit";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "더 필요한 거 있습니까, 선장?";
				link.l1 = "아무것도 아니야.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_5";
		break;*/
		
		case "Memento_MortimerGrim_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "멤멘토호에 탄 걸 환영하지, 동료. 내 이름은 모르티머 그림이야.";
				link.l1 = "Captain "+GetFullName(pchar)+". 초대해 주셔서 감사합니다...";
				link.l1.go = "Memento_MortimerGrim_2";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "또 무슨 이야기를 할까?";
				if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
				{
					link.l1 = "대단한 검이군요, 선장님.";
					link.l1.go = "Memento_MortimerGrim_question_1_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
				{
					link.l2 = "네 망원경이 해골 옆에 잘 어울린다.";
					link.l2.go = "Memento_MortimerGrim_question_2_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
				{
					link.l3 = "한마디 해야겠군, 네 선원들 정말 잡다한 놈들로 모였구나.";
					link.l3.go = "Memento_MortimerGrim_question_3_1";
				}
				link.l4 = "아무것도 아니야... 동료야. 순풍이 불길 바란다.";
				link.l4.go = "exit";
				NextDiag.TempNode = "Memento_MortimerGrim_1";
			}
		break;

		case "Memento_MortimerGrim_2":
			dialog.text = "카리브 해는 교수대로 달려가는 자들에게는 인심이 후하지, 그건 나도 잘 알지.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_3";
		break;
		
		case "Memento_MortimerGrim_3":
			dialog.text = "그래? 물어보고 싶은 게 있었나?";
			link.l1 = "네 등 뒤에 해골이 매달려 있어.";
			link.l1.go = "Memento_MortimerGrim_4";
			link.l2 = "오늘 바람 좋지? 날씨도 끝내주네.";
			link.l2.go = "Memento_MortimerGrim_5";
		break;

		case "Memento_MortimerGrim_4":
			dialog.text = "무슨 해골? 내 뒤에는 푸른 카리브 해뿐이야.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_5":
			dialog.text = "동의해, 동료. 매일 이런 날이면 좋겠는데!";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_6":
			dialog.text = "하하하! 그 농담은 질리지도 않는군! 놀라지 마라. 이 요릭 해골은, 이 배처럼, 내 예전 삶의 유품이지. 정말 말 그대로라니까.";
			link.l1 = "'진짜로?'";
			link.l1.go = "Memento_MortimerGrim_7";
		break;

		case "Memento_MortimerGrim_7":
			dialog.text = "동료야, 죽음이 두렵나? 위협하는 거 아니야, 진심으로 궁금해서 묻는 거야.";
			link.l1 = "물론이지. 다르게 말하는 놈은 거짓말쟁이야.";
			link.l1.go = "Memento_MortimerGrim_8_leadership";
			link.l2 = "아니. 우리 모두 결국 거기로 가게 될 거야.";
			link.l2.go = "Memento_MortimerGrim_8_weapon";
			link.l3 = "그럼 너는?";
			link.l3.go = "Memento_MortimerGrim_8_sneak";
		break;
		
		case "Memento_MortimerGrim_8_leadership":
			dialog.text = "오! 죽음은 모든 두려움의 어머니지. 외로움, 어둠, 형벌 — 이 모든 것은 그녀가 쓴 가면일 뿐이야.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Memento_MortimerGrim_8_weapon":
			dialog.text = "오! 죽음은 모든 두려움의 어머니지. 외로움, 어둠, 벌... 이 모든 건 그녀가 쓴 가면일 뿐이야.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "Memento_MortimerGrim_8_sneak":
			dialog.text = "오! 죽음이야말로 모든 두려움의 어머니지. 외로움, 어둠, 벌 — 이 모든 것은 그녀가 쓰는 가면일 뿐이야.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Memento_MortimerGrim_9":
			dialog.text = "멀리 볼 필요 없어. 옛 요릭을 봐라: 갈비뼈에 등불을 단 뼈더미지 — 그런데도 너처럼 무서운 선장도 덜덜 떨었잖아!";
			if (startHeroType == 4)
			{
				dialog.text = "멀리서 찾을 필요 없어. 옛날 요릭을 봐라. 갈비뼈에 등불을 단 뼈더미지 — 그 위대한 션 맥아더의 딸, 겁 없는 엘렌조차도 질겁했으니까!";
			}
			link.l1 = "말은 잘하는데, 그걸 다 어떻게 할 건지는 말 안 했잖아.";
			link.l1.go = "Memento_MortimerGrim_10";
		break;

		case "Memento_MortimerGrim_10":
			dialog.text = "무엇을 해야 할지는 알고 있지만, 내 치료법이 모두에게 맞는 건 아니야. 언제든 시도해 볼 수는 있지만, 먼저 네 생각을 말해 봐.";
			link.l1 = "성경에는 죽음이 없다고 나와 있다.";
			link.l1.go = "Memento_MortimerGrim_11_1";
			link.l2 = "내가 두려워하기 시작하면, 이 배는 끝장이야.";
			link.l2.go = "Memento_MortimerGrim_11_2";
			link.l3 = "답은 럼주 병 바닥에 가라앉았지.";
			link.l3.go = "Memento_MortimerGrim_11_3";
		break;
		
		case "Memento_MortimerGrim_11_1":
			dialog.text = "맞아. 그 책에서 내가 동의하는 건 그것뿐이야.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_2":
			dialog.text = "감탄스럽군. 하지만 괜한 걱정이야: 죽음은 없어.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_3":
			dialog.text = "요호호! 냉소가로군. 하지만 럼이 없어도 말하겠어: 죽음은 없어.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_12":
			dialog.text = "간단하지: 진짜 삶은 죽음을 정복할 때 비로소 시작된다네. 나도 저 너머, 장막 뒤에 다녀왔지. 믿어, 그 후에야 비로소 진짜로 살기 시작했으니까.";
			link.l1 = "뭐라고?";
			link.l1.go = "Memento_MortimerGrim_13";
		break;

		case "Memento_MortimerGrim_13":
			dialog.text = "신경 쓰지 마, 동료야.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
		break;

		case "Memento_MortimerGrim_question_1_1":
			dialog.text = "눈치챘다니 다행이군, 동료! 내가 자랑하려는 건 아니지만, 무시무시한 커틀라스 하나 없이 해적질을 할 수야 없지 않겠어?";
			link.l1 = "그게 정말 중요한가?";
			link.l1.go = "Memento_MortimerGrim_question_1_2";
		break;
		
		case "Memento_MortimerGrim_question_1_2":
			dialog.text = "정확해! 내가 개인적인 이유로 배의 금고를 눈에 띄게 비운 유일한 때가 바로 이 검 때문이었지. 무려 이천 금 더블룬이야, 동료! 젠장, 내가 한 번 더 무덤에서 일어날 수 있다면, 이 검 값 때문에라도 다시 돌아올 거야!\n"+
			"무기는 정말 훌륭해. 하지만 어쩐지... 뭔가 빠진 느낌이야.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "Memento_MortimerGrim_question_2_1":
			dialog.text = "누군가의 선물이야. 죽음을 누구보다 잘 이해하는, 뛰어난 이야기꾼이지 — 그리고 보다시피 상상력도 대단한 사람이야.";
			link.l1 = "암울해 보이네.";
			link.l1.go = "Memento_MortimerGrim_question_2_2";
		break;

		case "Memento_MortimerGrim_question_2_2":
			dialog.text = "메멘토 모리, 동료야.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_2 = true;
		break;

		case "Memento_MortimerGrim_question_3_1":
			dialog.text = "내 선원들은 네 선원들보다 서로 더 닮았지, 예를 들면... 전부 내가 밧줄과 사슬에서 풀어준 자들이야. 모두가 죽음의 숨결을 느껴봤지. 그런 경험이 피나 깃발보다 사람들을 더 강하게 묶어주거든.";
			link.l1 = "그래서, 너는 선원을 선술집에서 고용하지 않는 거냐?";
			link.l1.go = "Memento_MortimerGrim_question_3_2";
		break;

		case "Memento_MortimerGrim_question_3_2":
			dialog.text = "전 노예였던 자들이나 사형수들이 얼마나 기꺼이 지원하는지 알면 놀랄 거야. 노예선의 감방이나 교수대 대신 메멘토의 갑판을 선택하겠냐고? 지금 내 선원은 178명이나 돼 — 그리고 그들 모두 내게 빚을 졌지.";
			link.l1 = "하지만 여전히 녀석들에게 급여를 주고 배도 관리해야 해. 고마움만으로는 안 돼.";
			link.l1.go = "Memento_MortimerGrim_question_3_3";
		break;

		case "Memento_MortimerGrim_question_3_3":
			dialog.text = "나는 성공한 해적이야, 동료. 진정한 hostis humanitatis지. 인류의 진짜 적들, 즉 노예상들과 왕관 쓴 자들이 나를 그렇게 부르겠지. 그들과 나의 유일한 차이는 칭호뿐이야.\n"+
			"운 좋게도, 저놈들은 금이 아주 많지. 나는 노예상 상자에서 나온 동전으로 왕에게 사형 선고받은 자들을 구하지. 나머지는 전부 내 선원들에게 간다 — 나는 필요 없어. 죽은 자에게 금이 무슨 소용이겠어? 곧 알게 되겠지...\n";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_3 = true;
		break;
		
		// Диалог с Алонсо
		case "Memento_Alonso_phantom_11":
			dialog.text = "이게 우리가 처한 엿 같은 상황이야, 선장.";
			link.l1 = "이게 뭐야?!";
			link.l1.go = "Memento_Alonso_phantom_12";
		break;

		case "Memento_Alonso_phantom_12":
			dialog.text = "너만 남았어. 병이 우리 모두를 덮쳤지. 넌 우리를 저버렸어.";
			link.l1 = "그럴 리가 없어!";
			link.l1.go = "Memento_Alonso_phantom_13";
		break;

		case "Memento_Alonso_phantom_13":
			dialog.text = "너는 우리를 저주받은 배에 태웠어.";
			link.l1 = "...";
			link.l1.go = "Memento_Alonso_phantom_14";
		break;

		case "Memento_Alonso_phantom_14":
			dialog.text = "너 때문에 우리 모두가 망했어!";
			link.l1 = "알론소, 너 왜 이래?!";
			link.l1.go = "Memento_Alonso_phantom_15";
			npchar.model = "skel1";
			npchar.model.animation = "skeleton";
			npchar.sex = "skeleton";
			Characters_RefreshModel(npchar);
			SetMusic("classic_music_retribution_1");
		break;

		case "Memento_Alonso_phantom_15":
			dialog.text = "죽은 자가 산 자를 가르친다.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_6");
		break;
		
		// Диалог с Гримом
		
		case "Memento_MortimerGrim_phantom_11":
			dialog.text = "왜 멈췄어, 동료? 마음이 바뀐 거야? 그럼 애초에 왜 공격했지?";
			link.l1 = "그림? 하지만 너는 죽었잖아!";
			link.l1.go = "Memento_MortimerGrim_phantom_12";
		break;

		case "Memento_MortimerGrim_phantom_12":
			dialog.text = "하! 죽은 것은 결코 죽지 않아. 그리고 넌 너무 앞서가는군: 승선 전투는 이겼을지 몰라도, 살아남을 수 있을까... 자, 한번 두고 보자고!";
			link.l1 = "그 싸움은 몇 주 전에 끝났어! 넌 죽었잖아!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_11");
		break;

		case "Memento_MortimerGrim_phantom_21":
			dialog.text = "이제 끝났군. 승리를 축하한다.";
			link.l1 = "음산해?";
			link.l1.go = "Memento_MortimerGrim_phantom_22";
			LAi_UseAtidoteBottle(pchar);
		break;

		case "Memento_MortimerGrim_phantom_22":
			dialog.text = "있지, 난 기뻐. 정말로 네가 날 죽여서 진심으로 기뻐.";
			link.l1 = "무슨 소리야?";
			link.l1.go = "Memento_MortimerGrim_phantom_23";
		break;

		case "Memento_MortimerGrim_phantom_23":
			dialog.text = "나는 겁쟁이야, 동료. 그저 죽음이 두려웠던 한심한 겁쟁이일 뿐이지 — 나보다 먼저 그런 자들이 수천은 있었지. 선원들이 역병으로 죽었을 때... 그게 내 잘못이었고, 나는 두려움에 미쳐버렸어. 죽은 자들의 배에서 한 달 동안 혼자 표류했지.";
			link.l1 = "무슨 일이 정말로 있었던 거지?";
			link.l1.go = "Memento_MortimerGrim_phantom_24";
		break;

		case "Memento_MortimerGrim_phantom_24":
			dialog.text = "나는 죽음의 시련을 견디지 못했어. 받아들이고, 살아남아, 뭔가를 배워야 했는데 오히려 더 두려워졌지. 그리고 그 두려움을 감추기 위해... 내가 겪었던 일을 남들에게 억지로 겪게 만들기 시작했어.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_25";
		break;
		
		case "Memento_MortimerGrim_phantom_25":
			dialog.text = "고맙네, 동료. 이... 존재로부터 나를 해방시켜 줘서. 이제야 진정으로 죽음이 없다는 걸 알았어. 더 이상 두렵지 않아. 이제는 원망하거나 노예로 삼을 이도 없어.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_26";
		break;

		case "Memento_MortimerGrim_phantom_26":
			dialog.text = "메멘토를 선장과 떼어놓지 마라. 모르티머... 모르티머 선장은 좋은 사람이었지. 도미니카에서 그를 찾아라.\n그리고 그 배... 그 배가 너를 받아들일 거다.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_27";
		break;

		case "Memento_MortimerGrim_phantom_27":
			dialog.text = "Mortui vivos docent, 동료여. 죽은 자가 산 자를 가르치지. 안녕히 가게.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_13");
		break;
		
	}
} 