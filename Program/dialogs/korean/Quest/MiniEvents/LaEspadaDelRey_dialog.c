void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
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
			dialog.text = "뭘 원하지?";
			link.l1 = "아무것도 아니다.";
			link.l1.go = "exit";
		break;
		
		case "LEDR_Gonsalo_1":
			if (pchar.sex == "man")
			{
				dialog.text = "이봐, 꼬마! 너 용감한 뱃사람처럼 보이는데, 싸움도 꽤 할 줄 알겠구나. 어디 잠깐 습격 하나 같이 해줄 수 있겠냐, 응?";
			}
			else
			{
				dialog.text = "이봐, 이쁜이! 여기까지 온 걸 보니 겁 많은 타입은 아니구나. 어때, 나랑 어디 한탕 좀 해볼래?";
			}
			link.l1 = "네가 고대 선박으로 안내해 줄 사람을 찾는 그 노인인가 보군?";
			link.l1.go = "LEDR_Gonsalo_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LEDR_Gonsalo_2":
			dialog.text = "헤... 소문이 바람보다 빠르군. 그래, 나다. 곤살로 페랄타 – '라 에스파다 델 레이' 난파에서 살아남은 유일한 사람이 바로 나지.";
			link.l1 = "그리고 나는 선장이야 "+GetFullName(pchar)+". 네 배를 다시 한 번 살펴볼래?";
			link.l1.go = "LEDR_Gonsalo_3";
		break;

		case "LEDR_Gonsalo_3":
			dialog.text = "그래. 있잖아, 요즘 똑같은 악몽이 자꾸 반복돼서 괴로워. \n그런데 그게 제일 끔찍한 것도 아니야... 믿기 힘들겠지만, 매일 아침 악몽이 끝나자마자 눈을 뜨면... 젠장, 해골이 바로 내 앞에 서 있어...";
			link.l1 = "너 이 이야기를 모두에게 한다고 들었어.";
			link.l1.go = "LEDR_Gonsalo_4";
		break;

		case "LEDR_Gonsalo_4":
			dialog.text = "환상이라고? 흥... 그냥 그런 거였으면 좋겠군. 몇 달 전만 해도, 난 은퇴한 늙은 뱃사람답게 조용히 살고 있었지. 그런데 요즘은 그 해골 자식이 매일 아침마다 나타나서, 날 뚫어지게 쳐다보고, 피가 얼어붙을 듯한 비명을 지르지 뭐야... 젠장, 아무리 뱃사람이라도 간이 얼어붙을 거다... 그리고는 전투를 벌이러 달려들지. 그런데 말이지, 매번 그놈의 공격이 점점 더 거세져. 그래서 난 최대한 빨리 배로 가고 싶은 거야—거기서 꼭 찾아야 할 무언가가 있다는 느낌을 떨칠 수가 없거든.";
			link.l1 = "흠... 꽤나 복잡한 일이군. 그런데 그렇게 오랜 시간이 지난 후에 거기서 뭘 찾으려는 거지?";
			link.l1.go = "LEDR_Gonsalo_5";
		break;
		
		case "LEDR_Gonsalo_5":
			dialog.text = "모르겠어요, 선장님, 정말 모르겠어요... 하지만 저 배에 끌려요, 마치 폭풍 속의 낡은 배처럼요. 제 꿈, 그 해골, 그리고 이 이상한 느낌... 바닷가에서, 뭔가로 이어져 있어요. 도저히 어떻게 연결된 건지 모르겠어요.";
			link.l1 = "네 꿈에서 정확히 무슨 일이 일어나지? 혹시 원주민들과 관련이 있나?";
			link.l1.go = "LEDR_Gonsalo_6";
			link.l2 = "그래서 밤에는 환상을 보고 아침에는 해골이랑 싸운다고? 그게 배 때문이 아니라 그냥 의원한테 가야 하는 거 아냐? 네 허황된 상상에 맞장구쳐 줄 생각 없어. 네 헛소리 믿어줄 다른 바보나 찾아봐.";
			link.l2.go = "LEDR_Gonsalo_6_end";
		break;
		
		case "LEDR_Gonsalo_6_end":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_End");
		break;
		
		case "LEDR_Gonsalo_6":
			dialog.text = "연결됐냐고? 당연하지, 젠장... 그 꿈에서 난 죽은 내 선원들이랑 '라 에스파다 델 레이'에 타 있지. 우리는... 히스파니올라의 카리브 마을들을 습격하면서 길에 있는 모든 사람들을 죽여. 남자, 여자, 아이 할 것 없이. 저항하는 놈들도, 무릎 꿇고 자비를 구걸하는 놈들도 다 마찬가지야. 우리는 그들의 거주지를 하나씩 불태워 버려. 인디언들의 화살과 곤봉 따위는 전함 앞에 새는 타르탄이나 다름없지. 카리브인들은 절박하게 휴전을 애원하고, 그리고 나서...";
			link.l1 = "이런 맙소사! 자네가 그 모든 무법에 가담했다는 건가? 도움이 필요한 게 아니라, 밧줄 목걸이가 필요하겠군!";
			link.l1.go = "LEDR_Gonsalo_7";
		break;
		
		case "LEDR_Gonsalo_7":
			dialog.text = "아니! 아니, 젠장, 그건 사실이 아니야, 알겠어?! 내가 왜 이런 꿈을 꾸는지 전혀 모르겠어... 하지만 맹세코, 나도 내 선원들도 그런 끔찍한 짓에 절대 가담한 적 없어!";
			link.l1 = "그게 사실이길 바라는 게 좋을 거다. 계속해.";
			link.l1.go = "LEDR_Gonsalo_8";
		break;

		case "LEDR_Gonsalo_8":
			dialog.text = "카리브족이 협상을 요청했고, 선장은 동의했지. 그는 그들 모두를 우리가 점령한 오두막 중 하나로 초대했어. 족장들이 왔지—적어도 스무 명은 되었고, 그들의 여왕 아나카오나가 이끌고 있었어. 하지만 선장 자신은 안으로 들어가지 않았고... 우리 중 누구도 들어가지 않았지. 마지막 족장이 들어서자마자 문을 쾅 닫고 들보로 가로막았어. 그리고... 젠장... 불을 질렀지. 여왕만 살아남았지만, 그것도 잠시였어. 그들은 여왕에게 자기 백성이 산 채로 불타는 걸 보게 했고... 그 다음엔 그녀를 나무에 매달아 죽였어.";
			link.l1 = "그리고 이런 일이 매일 밤 일어난다고? 똑같은 꿈을 계속 반복해서 꾸는 거야? 있잖아, 이쯤 되면 그 해골도 네 열에 들뜬 상상 속 허상일지 몰라, 전혀 놀랍지 않군...";
			link.l1.go = "LEDR_Gonsalo_9";
		break;

		case "LEDR_Gonsalo_9":
			dialog.text = "그게 전부가 아니야. 살아남은 카리브인들은 쿠바로 도망쳐서, 현지 부족들의 지원을 받았고 곧 어떤 추장의 지휘 아래 하나의 군대로 뭉쳤지. 아투에이라고 했던 것 같아, 이름이. 그들은 마지막 희망으로 그를 따랐어. 하지만 우리는 별 어려움 없이 그들을 모두 도륙했지. 아투에는 붙잡혀서 처형 준비가 되었어. 그를 십자가에 묶고 불태우려 할 때, 한 수도사가 그에게 진정한 신앙을 권했지—고통을 덜어주고 천국에 들어가게 해주겠다고 말이야. 아투에는 수도사에게 천국이 스페인인들에게도 열려 있는지 물었어. 수도사가 물론 착한 스페인인들에게는 열려 있다고 답하자, 카시크는 주저 없이 그럴 바엔 천국이 아니라 지옥을 원한다고 했지—그렇게 잔인한 인간들과 한집에 살고 싶지 않다고 말이야. 그 뒤로 그는 자기 언어로 몇 마디를 더 하고, 장작더미에 불이 붙었지. 불길이 살을 집어삼킬 때 그는 소리 한 번 내지 않았어. 바다에 맹세코, 난 그런 광경을 실제로 보고 싶지 않아. 내 꿈은 항상 똑같이 끝나. 선장은 꼼짝도 않고 앉아 있고, 옆의 촛불만 연기를 내뿜지. 그는 낡은 일지를 계속 넘기면서, 마치 한 단어 한 단어가 금덩이인 것처럼 천천히, 중얼거리듯 뭔가를 읊조려. 꿈속에서도,\n "+GetSexPhrase("놈","소녀")+", 알겠소 – 이건 신호요. 이제 칼을 뽑을 때가 되었소, 저 자가 이미 공격해 오고 있으니.\n이 악몽을 끝내는 데 도와주시오, 선장. 만에 함께 가주시오. 나 혼자서는 못 가겠소 – 화약도 거의 다 떨어졌으니. 하지만 대답하기 전에 미리 말해두겠소: 보수는 줄 수 없소. 줄 수 있었다면 이미 돕겠다는 자들이 줄을 섰을 거요. 그러니 같은 선원으로서 도와주길 바랄 뿐이오.";
			link.l1 = "좋아, 알겠어. 배에 가는 게 네가 그 꿈이나 환영에서 벗어나는 데 도움이 된다면 도와주지. 타라. 내 볼일만 끝나면 바로 만으로 가자.";
			link.l1.go = "LEDR_Gonsalo_10";
		break;
		
		case "LEDR_Gonsalo_10":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_1");
			AddQuestRecord("LEDR", "2");
			AddQuestUserData("LEDR", "sSex", GetSexPhrase("ся","ась"));
		break;
		
		case "LEDR_Gonsalo_11":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				dialog.text = "여기 있군... 한때는 스페인 상인 함대의 자랑이었지만, 이제는 썩어가는 널빤지 더미가 간신히 형태만 유지하고 있지.";
				link.l1 = "이렇게 거대한 놈이 쓰러져 해변에 누워 있는 건 흔치 않은 일이야. 어떻게 여기까지 오게 된 거지?";
				link.l1.go = "LEDR_Gonsalo_12";
				link.l2 = "그럼 한번 둘러보자. 여기서 뭔가라도 찾을 수 있을지도 모르지.";
				link.l2.go = "LEDR_Gonsalo_20_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "고마움을 모르는 사람이나 겁쟁이처럼 보이고 싶진 않지만... 지금 여기서는 안전하다고 느껴지지 않아. 해가 뜨면 다시 오자.";
				link.l1 = "그래, 친구, 네가 그렇게 말한다면.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LEDR_Gonsalo_11";
			}
		break;
		
		case "LEDR_Gonsalo_12":
			dialog.text = "우리는 산티아고에서 세비야로 향해 출항했어. 화물은 별로 없었지만, 승객이 한 명 있었지—대단한 인물이었어, 주교님이 직접 타셨거든. 솔직히 말해서, 선원들은 이 항해가 영 내키지 않았어... 하지만 우리 의견을 누가 물어본 적이나 있었나?\n우리는 끝내 공해까지 나가지도 못했지. 터크스 근처에서 해적 브리그가 우리를 공격했거든—빠르고, 민첩하고, 무장도 엄청났어. 허름한 잡놈들이 아니라 진짜 바다의 이리들이었지. 처음엔 선장이 도망치려고 했어—주교님의 목숨을 걸고 싶지 않았던 거지. 하지만 바람이 그 모양이라 돌아갈 수도 없었고, 남쪽에서 폭풍까지 몰려오고 있었어. 그래서 선택의 여지가 없었지—싸움이 시작됐어.";
			link.l1 = "두 불 사이에 끼인다는 건 참으로 비참한 운명이야. 그리고 그 다음엔 어떻게 됐지?";
			link.l1.go = "LEDR_Gonsalo_13";
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;

		case "LEDR_Gonsalo_13":
			dialog.text = "싸움은 오래가지 않았어. 우리는 그놈들의 앞돛대를 쓰러뜨리는 데 성공했지만, 해적들도 만만치 않게 맞서더군—날아온 포탄 하나가 우리의 키 밧줄을 끊어버렸고, 마치 악마가 장난친 것처럼 배가 멈춰서, 뱃머리가 다가오는 폭풍을 정면으로 향하게 됐지. 폭풍은 너무 빠르게 다가와서, 해적놈들—그들의 주돛에 체인 샷이 박히길—은 도망치기로 하고, 터키 놈들 소굴 중 하나로 사라져버렸어. 우리는 그저 폭풍이 우리를 삼키길 기다릴 수밖에 없었지. 선장은 돛을 내리고 키 밧줄을 다시 매라고 명령했지만, 이미 너무 늦은 뒤였어.";
			link.l1 = "그래서, 폭풍이 터크스 근처에서 너희를 덮쳤고, 여기까지 끌고 와서 결국 해안에 내던졌다는 거냐?";
			link.l1.go = "LEDR_Gonsalo_14";
		break;

		case "LEDR_Gonsalo_14":
			dialog.text = "정확히 그렇게 됐어. 배는 완전히 아수라장이었지. 바람이 돛줄을 찢어놓고, 돛대들이 하나씩 무너져 갑판을 박살내며 사람들을 깔아뭉갰어. 몸을 묶을 시간이 없으면 바다로 휩쓸려 나갔고, 묶었다면 파편에 깔려 죽었지. 갑판 아래도 다를 게 없었어—대포, 상자, 포탄이 마치 악마처럼 이리저리 날아다니며 닥치는 대로 갈아버렸지. 결국 우리가 해변에 내던져졌을 때, 나는 정신을 잃고 있었어. 정신을 차려보니 모래 위였지. 세르히오 보선이 날 발견했어. 그와 함께 두 명이 더 있었지.";
			link.l1 = "이렇게 큰 배치고는 별로 많지 않군.";
			link.l1.go = "LEDR_Gonsalo_15";
		break;

		case "LEDR_Gonsalo_15":
			dialog.text = "아, 선장님... 시체가 너무 많았어요... 우리는 바로 알았죠: 거기 더는 있을 수 없다는 걸요. 파도가 배를 휩쓸어 갈 수도 있었고, 우리도 함께였을 겁니다. 근처에서 동굴을 발견해서, 지쳐서 땅에 닿자마자 잠이 들었어요. 깨어나 보니, 동굴 안에 세르지오와 다른 두 사람의 흔적이 없었습니다.\n해변 전체를 찾아봤지만, 천둥이라도 칠 듯이 그들은 어디에도 없었어요. 혼자서는 배로 돌아갈 수 없어서, 내륙으로 들어가기로 했죠. 그렇게 해서 샤프타운에 도착했고, 내 어리석음 때문에 일을 망치고 말았어요.\n생존자에 대해 뭔가 알아내고 싶어서, 우리에게 무슨 일이 있었는지 모두에게 말하기 시작했죠. 하지만 그 악당들은 나나 선원들엔 관심도 없었고, 오직 배에서 챙길 수 있는 전리품에만 눈이 멀었어요. 소문은 섬 전체에 빠르게 퍼졌고, 곧 그 라드론 놈들이 떼로 몰려들기 시작했습니다.";
			link.l1 = "그래서, 아직도 그 사람들에게 무슨 일이 있었는지 모른다는 거야?";
			link.l1.go = "LEDR_Gonsalo_16";
		break;

		case "LEDR_Gonsalo_16":
			dialog.text = "배로 돌아가는 건 너무 위험했어. 약탈하러 몰래 들어간 놈들은 전리품을 두고 싸우다 그 근처에 있던 놈한테 총알을 박아버릴 수도 있었지... 실수로 말이야. 아니면, 전혀 실수가 아니었을 수도 있고. 바다를 등지고, 나는 선술집에 박혀서 만 일주일을 보냈어. 만나는 놈마다 만에서 있었던 일을 캐물었지. 하지만 내 선원들이나 그들이 어떻게 됐는지 아는 사람은 아무도 없었어. 결국 받아들일 수밖에 없었지. 젠장할 폭풍에서 살아남은 건 나 혼자인 것 같더라고. 아마 운명이 나만 좀 더 챙겨줬던 걸지도 몰라. 아니면... 언젠가 젊은 선장 에우헤니오 데 라 토레가 내게 준 부적 덕분이었을지도. 나는 항상 그걸 곁에 두고 다녔지. 그리고, 젠장, 진짜로 그게 내게 행운을 가져다준 것 같아.";
			link.l1 = "그럼 지금 그는 어디 있지? 해골들한테는 그게 소용없나 보군, 응...";
			link.l1.go = "LEDR_Gonsalo_17";
		break;

		case "LEDR_Gonsalo_17":
			dialog.text = "내 마당에서 우물 입구를 수리하던 중에 내 목에서 떨어졌어. 통나무가 내 목을 쳐서 부적이 물에 빠졌지. 우물은 이미 가득 차 있었고, 그깟 장신구 하나 때문에 일부러 퍼올릴 사람은 아무도 없었어.";
			link.l1 = "그때부터 악몽을 꾸기 시작했나?";
			link.l1.go = "LEDR_Gonsalo_18";
		break;

		case "LEDR_Gonsalo_18":
			dialog.text = "이런 젠장! 한 번도 생각 못 했는데, 딱 그거였어! 우물이 완성되자마자 악몽이 시작됐지.";
			link.l1 = "재밌는 우연이군. 자, 네가 원하던 대로 이제 여기 있잖아. 그래서, 다음엔 뭘 할 생각이야?";
			link.l1.go = "LEDR_Gonsalo_19";
		break;

		case "LEDR_Gonsalo_19":
			dialog.text = "모르겠어요, 선장님... 정말 모르겠어요. 우선 둘러보죠 – 여기서 꼭 찾아야 할 무언가가 있다는 느낌이 점점 더 강해지고 있어요.";
			link.l1 = "좋아. 괜히 여기 온 건 아니길 바란다.";
			link.l1.go = "LEDR_Gonsalo_20";
		break;
		
		case "LEDR_Gonsalo_20":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
		break;
		
		case "LEDR_Gonsalo_20_1":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
			pchar.questTemp.LEDR_NoStory = true;
		break;
		
		case "LEDR_Gonsalo_21":
			dialog.text = "들어봐... 이 느낌이 점점 더 강해지고 있어. 꼭 내가 찾아야 할 무언가에 한 걸음만 더 다가가면 될 것 같아. 반드시 저 배에 올라타야 해. 바다에 맹세컨대, 저기엔 저 빌어먹을 해골이 왜 나를 가만두지 않는지 설명해 줄 무언가가 있을 거야.";
			link.l1 = "그래서, 여기 오려고 그토록 안달 난 게 헛된 일만은 아니었나 보군? 배에 귀한 걸 숨겨두고 이제 와서 보물을 찾으러 온 거냐?";
			link.l1.go = "LEDR_Gonsalo_22";
		break;

		case "LEDR_Gonsalo_22":
			dialog.text = "무슨 헛소리야? 내가 사십 년이나 지난 뒤에 금화 몇 닢 때문에 군도 전체를 헤매고 다닐 거라고 진짜 생각하는 거야? 네가 그 해골을 한 번이라도 직접 마주쳤다면, 그런 생각은 꿈에도 못 했을 거다.";
			link.l1 = "알겠어, 알겠어, 진정해. 그런데 대체 어떻게 배에 올라탈 생각이야?";
			link.l1.go = "LEDR_Gonsalo_23";
		break;

		case "LEDR_Gonsalo_23":
			dialog.text = "선미에 숨겨진 문이 있어. 선장이 직접 만들어 놨어—만약 적이 배에 올라타면 도망치려고 말이지. 천벌 맞을 노릇이군, 내 늙은 몸뚱이로는 혼자선 거길 못 지나가겠어, 하지만 우리 둘이라면...";
			link.l1 = "좋아, 앞장서. 얼른 끝내자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_5");
		break;
		
		case "LEDR_Gonsalo_24":
			DelLandQuestMark(npchar);
			dialog.text = "목에 포탄이 날아들 뻔했네, 이게 무슨 난리람! 다행히 이번 놈들은 매일 아침 나타나는 그놈만큼 사납진 않았어. 자, 이제 내 말 믿겠어?";
			link.l1 = "저런 걸 보고 나면, 안 그러기가 더 힘들지. 괜찮아?";
			link.l1.go = "LEDR_Gonsalo_24_1";
		break;

		case "LEDR_Gonsalo_24_1":
			dialog.text = "나도 그렇게 생각해. 젠장할 언데드 놈들... 내 다리가 부러진 돛대처럼 풀려버렸어.";
			link.l1 = "그래, 몸이 멀쩡하다면 가만히 앉아 있을 필요 없지. 손 줘 봐, 일으켜 줄게.";
			link.l1.go = "LEDR_Gonsalo_24_2";
		break;

		case "LEDR_Gonsalo_24_2":
			CharacterTurnByChr(npchar, CharacterFromID("blaze"));
			dialog.text = "...";
			link.l1 = "이제 좀 낫군. 우리만 이곳에 들어올 줄 아는 게 아니었던 것 같아.";
			link.l1.go = "LEDR_Gonsalo_25";
			LAi_Fade("LEDR_GonsaloStay", "");
		break;

		case "LEDR_Gonsalo_25":
			dialog.text = "이 녀석들이 내 부하들인 것 같군. 폭풍에서 살아남은 자들 말이야... 세르지오의 조끼를 알아봤어—남아 있는 건 거의 없지만. 결국 이놈들도 돌아왔군—살아남은 자를 찾으려고, 아니면 죽은 자를 묻으려고 말이지. 하지만 결국 그 악마 같은 놈이 이 자들도 끝장냈나 보군.";
			link.l1 = "조끼의 조각만 남아 있다니 이상하군. 다른 건 아무것도 없어.";
			link.l1.go = "LEDR_Gonsalo_26";
		break;

		case "LEDR_Gonsalo_26":
			if(CheckAttribute(pchar, "questTemp.LEDR_NoStory"))
			{
			dialog.text = "우리 승객, 즉 주교의 사제복조차 흔적도 남지 않았어. 저 불쌍한 자의 손에 꼭 쥐어진 열쇠를 보니, 분명 그 사람이겠지. 그 열쇠는 단 한순간도 놓지 않았거든. 다른 사람들보다 운이 더 좋았던 것도 아니었나 봐. 맙소사, 이 언데드들은 그냥 심심해서 돌아다니는 게 아니었어. 뭔가가 이곳에 그들을 붙잡아 두고 있거나, 아니면 뭔가를 지키고 있는 것 같아...";
			DeleteAttribute(pchar, "LEDR_NoStory");
			}
			else
			{
			dialog.text = "주교의 수단 자락조차 흔적도 남지 않았군. 저 불쌍한 자의 손에 꼭 쥐어진 열쇠를 보아하니, 분명 그 사람이겠지. 그 열쇠는 단 한 순간도 놓지 않았던 모양이야. 다른 이들보다 운이 더 좋지는 않았던 것 같군. 바닷가에선 이 언데드들이 그냥 심심해서 돌아다니는 게 아니었어. 뭔가가 이들을 여기 붙잡아 두고 있거나, 아니면 무언가를 지키고 있는 것 같군...";
			}
			link.l1 = "이제 여기서 뭔가를 찾아야 할 것 같은 기분이 들어. 빨리 끝내자 — 더 이상 한순간도 있고 싶지 않으니까.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_8");
		break;
		
		case "LEDR_Gonsalo_27":
			dialog.text = "그래서, 선장님, 뭔가 찾아냈습니까?";
			link.l1 = "이게 주교의 궤짝이었던 것 같아. 안에 뭐가 들어 있더라고. 한번 봐봐.";
			link.l1.go = "LEDR_Gonsalo_28";
		break;

		case "LEDR_Gonsalo_28":
			dialog.text = "벨라스케스... 천둥에 맞아 죽을 일이군... 이 일지를 꿈에서 본 적이 있어! 이게 바로 선장님이 그때 넘겨보고 있던 그 일지야, 그가...";
			link.l1 = "...";
			link.l1.go = "LEDR_Gonsalo_29";
		break;

		case "LEDR_Gonsalo_29":
			dialog.text = "악마야, 이 자식 때문에 손이 타는 것 같아!";
			link.l1 = "손이 데인다고? 에이, 그냥 오래된 일지일 뿐이야. 아니면 정말 그 안에 무슨 어둠의 힘이라도 있다고 믿는 거야?";
			link.l1.go = "LEDR_Gonsalo_30";
		break;

		case "LEDR_Gonsalo_30":
			dialog.text = "모든 성인들을 걸고 맹세하는데, 농담 아니야! 그 빌어먹을 일지, 손에 쥐고 있으면 불타는 것 같아. 반드시 없애야 해! 찢어버리든, 태워버리든, 물에 빠뜨리든—뭐든 해! 아니, 잠깐... 태우는 게 낫겠어. 그래, 태워버려. 재 한 줌도 남지 않게!";
			link.l1 = "원하시는 대로 하겠습니다. 그럼 상륙해서 불을 피우고, 이 악행의 기록을 불 속에 던져버립시다.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_10");
		break;
		
		case "LEDR_Gonsalo_31":
			dialog.text = "그래, 이제 끝났군... 가슴이 한결 가벼워진 기분이야.";
			link.l1 = "이제 다 끝났다고 생각하나?";
			link.l1.go = "LEDR_Gonsalo_32";
			TakeItemFromCharacter(pchar, "LEDR_book");
		break;

		case "LEDR_Gonsalo_32":
			dialog.text = "누가 알겠어... 하지만 맹세컨대, 바다에 걸고 말하는데 이렇게 마음이 가벼운 건 정말 오랜만이야. 마치 오래된 빚이 드디어 탕감된 것 같아. 그래도... 차라리 그 저주받은 일지를 보지 않았더라면, 그 안에 뭐가 적혀 있는지 알지 못했더라면 좋았을 텐데.";
			link.l1 = "그런 꿈을 꾼 것도 당연하지. 네가 이 모든 일에 직접 관여하지는 않았지만, 그 일지와 어떤 식으로든 연관된 살아 있는 사람은 너뿐이니까.";
			link.l1.go = "LEDR_Gonsalo_33";
		break;
		
		case "LEDR_Gonsalo_33":
			dialog.text = "벨라스케스의 지휘 아래 사람들이 저지른 일은 금도 신앙도 정당화할 수 없소. 그리고 그 모든 기억을 떠올리게 할 만한 것들이 다 불타버려서 다행이오.\n그런 것들은 그들의 본보기를 따르고 싶은 유혹을 받을 자들의 손에 절대 넘어가서는 안 되오.";
			link.l1 = "벨라스케스는 그저 많은 사람들 중 하나일 뿐이오. 누가 알겠소, 이런 일지들이 구대륙을 얼마나 더 떠돌며 새로운 정복자들의 탐욕과 무법을 부추기고 있을지? 한 가지는 확실하오—이 일지는 더 이상 아무도 해치지 못할 것이오. 그런데 주교의 궤에는 일지만 있었던 게 아니라, 상당한 양의 두블룬도 들어 있었소—전부 삼백 개였지. 그 중 절반은 당연히 그대의 몫이오.";
			link.l1.go = "LEDR_Gonsalo_34_share";
			link.l2 = "벨라스케스는 자신의 죄값을 치렀다. 그리고 누가 그의 뒤를 따르려 한다면, 똑같은 운명을 맞이하게 될 것이다.\n머지않아 운명은 모두에게 마땅한 대가를 내리게 마련이지.";
			link.l2.go = "LEDR_Gonsalo_34_silence";
		break;
		
		case "LEDR_Gonsalo_34_share":
			dialog.text = "그렇다면 마다할 이유가 없지. 누구나 돈이 필요하고, 나는 지금 그 어느 때보다 절실하네. 이제는 나를 선원으로 받아줄 사람도 없고, 나도 그럴 나이가 지났지. 그러니 고맙네, 선장. 다른 사람들처럼 나를 내치지 않아서.";
			link.l1 = "처음에는 네 이야기가 미친놈의 헛소리처럼 들렸던 건 인정하겠다. 하지만 네가 너무 설득력 있게 말해서, 원하든 원하지 않든 나도 모르게 믿게 되더군. 그래도 그 언데드 원주민들이 나타난 건 정말 예상 못 했어.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "네가 제정신인지 확인하고 싶었을 뿐이야. 그런 이야기는 쉽게 믿기 힘들다는 거 알잖아.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			RemoveDublonsFromPCharTotal(150);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.quest.LEDR_share = true;
		break;
		
		case "LEDR_Gonsalo_34_silence":
			dialog.text = "믿고 싶소... 하지만 바다에서, 나는 너무 많은 자들이 아무리 악행을 저질러도 운이 따라주는 걸 봤지. 언젠가 그들에게도 대가가 오겠지—여기가 아니라, 악마의 솥에서 말이오. 그리고 고맙소, 선장. 외면하지 않고, 내 말을 들어주고, 배웅해줘서. 그게 정말 큰 의미가 있소, 알지?";
			link.l1 = "처음엔 네 이야기가 미친놈의 헛소리처럼 들렸던 건 인정하지. 하지만 네가 너무 그럴듯하게 말해서, 원하든 원하지 않든 믿게 되더라. 그래도 그 언데드 인디언들이 나타난 건 정말 예상 못 했어.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "네가 제정신인가 확인해 보고 싶었을 뿐이야. 그런 이야기는 솔직히 쉽게 믿기 힘들거든.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "LEDR_Gonsalo_35_1":
			dialog.text = "이제 내가 처음 그 언데드들을 봤을 때 어떤 기분이었는지 알겠지. 이제 그놈들이 완전히 사라졌길 바란다... 아니면, 또 그런 일을 겪으면 내가 살아남을 수 있을지 모르겠어.";
			link.l1 = "자, 여기서 할 일은 끝났으니 이제 이곳을 떠나자. 배에 올라타, 샤프타운 항구에 내려줄게.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "LEDR_Gonsalo_35_2":
			dialog.text = "이제 네가 내가 처음 그 언데드들을 봤을 때 어떤 기분이었는지 알겠지.\n이제 그놈들이 완전히 사라졌길 바란다... 그렇지 않으면, 또 그런 일을 겪으면 난 살아남지 못할 것 같아.";
			link.l1 = "자, 여기서 할 일은 끝났으니 이제 이곳을 떠나자. 배에 올라, 샤프타운 항구에 내려줄게.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "LEDR_Gonsalo_36":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_12");
		break;
		
		case "LEDR_Gonsalo_37":
			dialog.text = "다시 한 번 감사드립니다, 선장님 "+GetFullName(pchar)+". 바닷가에 오니 그 이상한 기분도 사라졌고, 그놈의 저주받은 해골 자루도 같이 사라졌으면 좋겠군. 한잔 할까, 어때?";
			link.l1 = "초대해 줘서 고맙네, Gonzalo. 하지만 지금은 내가 너무 바빠. 다음에 기회가 되면 좋겠군. 우리 둘을 위해 한잔해 줘.";
			link.l1.go = "LEDR_Gonsalo_38";
		break;
		
		case "LEDR_Gonsalo_38":
			if (CheckAttribute(npchar, "quest.LEDR_share"))
			{
				dialog.text = "알겠소. 하지만 한마디만 하겠소, 선장. 우리가 함께 겪은 일들을 생각하면, 그냥 감사 인사도 없이 떠날 수는 없소. 그건 도리가 아니지. 자, 이걸 받으시오. 내 젊은 시절엔 보물을 쫓아 여러 번 바다를 헤맸소, 바다에 맹세코. 하지만 이제는 예전 같지 않아서, 허리도 성치 않구려. 하지만 자네는 아직 젊고, 노련한 뱃사람이니 쉽게 찾을 수 있을 거요. 행운을 빌겠소, "+GetFullName(pchar)+", 순풍이 불고 용골 아래 일곱 자 깊은 물길이 있기를.";
				link.l1 = "고맙소, Gonzalo. 그대도 행운이 있기를. 잘 가시오.";
				AddMapPart();
			}
			else
			{
				dialog.text = "그럼, 이제 작별할 시간이군. 순풍과 안전한 항해를 빌겠소, 선장. "+GetFullName(pchar)+"!";
				link.l1 = "잘 가시오, Gonzalo.";
			}
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_14");
		break;
		
		
		
	}
}