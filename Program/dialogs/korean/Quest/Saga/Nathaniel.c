// Натаниэль Хоук - пиратский барон Марун-Тауна
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
			dialog.text = "뭐 필요한 거 있어?";
			link.l1 = "아니, 아무것도 아니야.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "diffindoor":
			PlaySound("Voice\English\saga\Nataniel Hawk-02.wav");
			dialog.text = "아... 너 누구야, 젠장?.. 크흠... (심하게 쉰 목소리로 기침) 젠장, 몸이 왜 이래...";
			link.l1 = "안녕하시오, 네이선리얼. 당신이 네이선리얼 호크 맞지 않소?";
			link.l1.go = "diffindoor_1";
		break;
		
		case "diffindoor_1":
			dialog.text = "그래, 나야. 아직도 그 이름으로 불릴 수 있다면 말이지. 한때는 네이선리얼 호크였지만, 지금은 그냥 초라한 쓰레기 자루일 뿐이야. 저 빌어먹을 조각상 때문에! 내 모든 기운을 빨아가 버렸어.";
			link.l1 = "나도 그 기분을 잘 알지...";
			link.l1.go = "diffindoor_2";
		break;
		
		case "diffindoor_2":
			dialog.text = "어떻게 알겠느냐, 이 녀석아, 내가 무슨 말을 하는지도 모르면서? 크흠... 방금 전까지만 해도 멀쩡하고 힘이 넘쳤는데, 갑자기 반쯤 죽은 노인이 된 기분이 어떤지 아느냐?\n내가 살아오면서 별별 꼴을 다 봤지. 젊었을 때 들렀던 고대 인디언 사원이 내 놀라움을 다 죽여버린 줄 알았는데, 이건... 어째서 미처 눈치채지 못했을까! 그 빌어먹을 조각상이 사원의 문을 열었던 옛 우상과 똑같이 생겼더란 말이다!";
			link.l1 = "좋아, 네이선, 이야기해 보자. 내 소개를 하지, 나는 "+GetFullName(pchar)+". 먼저, 나는 자네를 아주 잘 이해하네. 나 역시 자네처럼 쿠쿨칸 포털을 통해 이곳에 왔으니.";
			link.l1.go = "diffindoor_3";
		break;
		
		case "diffindoor_3":
			dialog.text = "정말이야?! 그런데 왜 너는 멀쩡해 보여? 아니면 그... 쿠쿨칸이 나만 해쳤던 거야?";
			link.l1 = "너를 도와 탈출시킨 미스키토 주술사 스네이크 아이가 나에게 아주 강력한 약을 주었어. 나는 산 아우구스틴에서 깨어나자마자 그걸 마셨지. 완전히 회복됐어. 스네이크 아이도 분명 너를 도와줄 수 있을 거야. 너를 그에게 데려가기만 하면 돼.";
			link.l1.go = "diffindoor_4";
		break;
		
		case "diffindoor_4":
			dialog.text = "아, 그 인디언! 물약이라고? 그런데 왜 나한테는 안 준 거지?";
			link.l1 = "그는 시간이 없다고 했어. 네가 쫓기고 있었고, 그가 할 수 있는 일은 도망칠 길, 즉 포탈을 알려주는 것뿐이었다.";
			link.l1.go = "diffindoor_5";
		break;
		
		case "diffindoor_5":
			PlaySound("Voice\English\saga\Nataniel Hawk-01.wav");
			dialog.text = "도망치냐고? 아... 내가 지금 어떤 상태인지 안 보여? 나는 지금 검도 제대로 쥘 수 없어. 이런 걸 도망이라고 할 수 있겠나? 그래도 세상엔 아직 좋은 사람들이 있구나, 하느님께 감사해야지. 올레, 그 친구도 하느님이 축복해 주시길... 올레를 아나?";
			link.l1 = "그래. 사실 그가 너에 대해 말해줬지. 쥐를 먹인 얘기며, 네가 계속 술을 들이켜는 것까지, 병이 비워질 때마다 또 마신다고 하더군...";
			link.l1.go = "diffindoor_6";
		break;
		
		case "diffindoor_6":
			dialog.text = "럼을 마시지 않으면 켜진 촛불보다도 빨리 죽을 거야. 나를 살게 해주는 건 럼뿐이야. 럼...";
			link.l1 = "아직도 그렇게 상태가 안 좋아? 순간이동 후랑 똑같이?";
			link.l1.go = "diffindoor_7";
		break;
		
		case "diffindoor_7":
			dialog.text = "글쎄, 내 기분이 전과 똑같진 않아... 그렇다고 딱히 나아진 것도 아니고. 이봐, 친구, 왜 네이선 영감을 만나려고 했던 거야? 도대체 무슨 이유로 여기, 이 낡고 썩은 배까지 온 거냐? 나랑 수다나 떨려고?";
			link.l1 = "사실이야. 믿지 않겠지만, 내가 그 모든 순간이동 소동을 겪은 이유는 바로 너를 찾기 위해서였어. 나는 해안의 형제단 소속이고, 얀 스벤손을 대표하고 있지.";
			link.l1.go = "diffindoor_8";
		break;
		
		case "diffindoor_8":
			dialog.text = "젠장... 숲의 악마라고? 으윽... 날 죽이러 온 거냐? 사실, 아니라고? 암살자치곤 말이 많군. 제발 - 고문만은 하지 마라. 뭔가 캐내라는 명령을 받았다면 내가 다 말할게, 숨길 것도 없어.";
			link.l1 = "무슨 말이오? 아-아, 알겠소. 자네도 다니엘처럼 스벤손이 셀바에서 자네를 노린 매복을 꾸몄다고 생각하는군. 하지만 얘기할 수 있소, 얀은 그런 짓을 하지 않았소. 오히려 그는 자네 편이며, 자네가 사라진 걸 무척 걱정하고 있소.";
			link.l1.go = "diffindoor_9";
		break;
		
		case "diffindoor_9":
			dialog.text = "정말이야? 그 말 들으니 진짜 기쁘군. 나도 이미 생각해봤지... 그런데 누가 그런 짓을 한 거지? 내 부대는 순식간에 전멸당했어. 놈들은 우리를 기다리고 있었지. 심지어 배의 대포까지 준비했더군! 산탄으로 내 부하 절반을 쓸어버리고, 남은 자들은 머스킷으로 끝장냈어...";
			link.l1 = "솔직히 말해서, 자세한 내용은 모르지만, 이 모든 일의 뒤에는 분명 잭맨이 있다고 확신해. 우연이 너무 많아, 처음에는 블레이즈, 그리고 이제는 너... 잭맨은 권력을 잡으려고 네 앞길을 막는 모든 사람을 없애고 있어. 이제 마룬 타운은 네가 아니라 잭맨이 다스리고 있지.";
			link.l1.go = "diffindoor_10";
		break;
		
		case "diffindoor_10":
			dialog.text = "잭맨? 그 자식! 에이... 지난 몇 년 사이에 형제단이 갈라졌지, 예전엔 전혀 달랐어. 자카리아는 종교에 미쳐버렸고, 타이렉스는 아무것도 신경 안 쓰고, 바르바존은 오로지 두블룬에만 관심 있어. 이십 년 전만 해도 전부 달랐는데...\n";
			link.l1 = "어떻게 잡힌 거야? 자세히 말해 봐.";
			link.l1.go = "diffindoor_11";
		break;
		
		case "diffindoor_11":
			dialog.text = "재미있게 말할 만한 건 없어! 내가 말했듯이, 그 도적놈들이 전부 계획한 일이었지. 아주 정확하게, 서로 협력해서, 분명 누군가의 명령을 따르며 움직였어. 나를 백 번도 넘게 죽일 수 있었지만, 그러지 않았지. 날 살아 있게 두고 싶었던 거야. 나를 버려진 광산으로 데려가서 오두막 하나에 가둬 놓았어. '두목이 올 때까지'라고 하더군.\n나는 스벤손이 두목인 줄 알았는데, 잭맨이 실질적으로 우두머리인 것 같아. 그가 나한테서 뭘 원했는지는 모르겠지만, 한 가지 확실한 건, 그와 얘기한 뒤 오래 살지는 못했을 거라는 거야.";
			link.l1 = "그 점에 대해서는 의심하지 않소. 스벤손은 잭맨이 블레이즈 샤프를 죽였다고 확신하고 있지... 그런데 어떻게 도망칠 수 있었소?";
			link.l1.go = "diffindoor_12";
		break;
		
		case "diffindoor_12":
			dialog.text = "그 인디언 스네이크 아이가 어떻게든 광산에 몰래 들어왔어. 내가 알기로 미스키토족은 도적들을 싫어하지. 어쨌든, 스네이크 아이가 무슨 이유에서인지 내 탈출을 도와줬어. 나한테 터널을 파고 들어와서, 내 밧줄을 끊고, 우리는 정글로 도망쳤지.\n그는 나를 자기 마을, 미스키토족에게 데려가려고 했어. 하지만 잭맨이 날 아주 원했던 모양이야, 큰 사냥이 벌어졌거든. 놈들은 우리 뒤를 바짝 쫓았지. 스네이크 아이가 놈들을 따돌리려고 애썼지만, 놈들은 항상 우리 흔적을 찾아냈어. 길잡이들이 정말 뛰어났던 게 분명해.\n우리가 스네이크 아이 마을 근처에 다다랐을 때 결국 놈들이 우리를 찾아냈어. 그때쯤 내 배는 이틀째 비어 있었고, 완전히 지쳐 있었지, 게다가 다리도 심하게 다쳤거든. 한밤중이었고, 난 아직도 그 동상 위에 떠 있던 별이 얼마나 밝았는지 기억해... 스네이크 아이가 내 유일한 희망은 우상까지 가서 손을 대는 거라고 했어.\n난 그가 미쳤다고 생각했지만, 지푸라기라도 잡는 심정이 뭔지 알잖아. 나는 절뚝거리며 동상까지 가서 손을 댔지... 그러자 미친 일들이 벌어지기 시작했어!";
			link.l1 = "더 이상 말할 필요 없소, 그 다음에 무슨 일이 있었는지 알고 있소.";
			link.l1.go = "diffindoor_13";
		break;
		
		case "diffindoor_13":
			dialog.text = "난 난파된 배의 축축한 선창에서 정신을 차렸어. 거의 죽을 지경이었지. 걷지도 못하고, 기어서 움직일 수밖에 없었어. 시간이 갈수록 상태는 더 나빠졌지. 올레가 딱 맞춰 나타났어. 그는 역겨운 맛이 나는 카리브 해의 묘한 혼합약을 내 입에 부었어. 해독제와 치료약을 섞은 거였지. 그리고 럼주도 줬어.\n금세 몸이 나아지는 걸 느꼈어. 그 다음엔 오래된 통나무를 찾아서 날 이곳까지 옮겼지. 그 뒤로 한동안 여기서 지내고 있어. 얼마나 됐는지는 정확히 모르겠어—시간 감각을 잃어버렸거든.";
			link.l1 = "괜찮을 거야, 네이선. 스벤손과 나는 큰 계획을 세웠고, 네 역할이 아주 중요해. 마룬 타운에서 네 자리로 돌아가면 우리가 그 쓰레기 잭맨을 처리할 거야.";
			link.l1.go = "diffindoor_14";
		break;
		
		case "diffindoor_14":
			dialog.text = "마룬 타운? 그리고 그게 어떻게 된다고 생각하는 거지? 나 좀 봐, 럼주에 절어 망가진 꼴이잖아! 쓸모없는 놈이지... 아니, 마룬 타운에서 내가 누리던 권위의 세월은 영원히 끝났어. 이 빌어먹을 난파선 무덤에 갇혀버렸으니. 내가 얼마나 더 버틸 수 있을까? 한 달, 두 달, 1년?\n그러다 결국 이 썩은 판자 위에 쓰러져서, 올레가 남은 네이선 호크의 시체를 바다에 던져버리겠지. 제일 괴로운 건 다시는 내 다니를 볼 수 없다는 거야. 에휴, 다 끝났어, 친구.";
			link.l1 = "너무 비관적으로 굴지 마. 내가 너를 여기서 꺼내줄게.";
			link.l1.go = "diffindoor_15";
		break;
		
		case "diffindoor_15":
			dialog.text = "여기서 날 어떻게 데리고 나갈 건데? 그리고 우린 이곳을 어떻게 떠날 거지? 배도 없잖아. 뗏목이라도 만들 생각이야?";
			link.l1 = "아니. 나는 여기 온 것과 똑같이 이곳을 떠날 거야. 동상이 어디 있는지 알아... 대충은. 내가 그걸 찾아서 다시 너랑 샤크 돗슨을 데리러 올게. 그다음에 너를 스네이크 아이에게 데려가겠어. 그가 널 치료해 줄 거야.";
			link.l1.go = "diffindoor_16";
		break;
		
		case "diffindoor_16":
			dialog.text = "뭐라고 했지? 샤크 도드슨? 스티브도 여기 있나? 참 이상한 곳이군...";
			link.l1 = "그래, 그는 여기 있어. 이 섬의 '총독'이라고 할 수 있지. 내가 너에 대해 물어봤지만, 그는 아무것도 모르더군.";
			link.l1.go = "diffindoor_17";
		break;
		
		case "diffindoor_17":
			dialog.text = "그리고 그래서는 안 돼. 내가 이런 꼴인 걸 아버지가 보셨으면 하지 않아. 주술사가 나를 치료해줄 거라고 했지... 아직도 믿기 힘들어. 그리고 너, 대니 얘기도 했잖아... 그녀를 봤어?";
			link.l1 = "그래. 그녀가 직접 블루웰드에서 나를 찾아왔지. 스벤손과 나눈 내 대화를 엿듣고 얀은 너를 죽일 생각이 없으며 잭맨을 적대하고 있다는 걸 알아챘어. 그래서 널 찾는 걸 돕겠다며 내 배에 장교로 합류했지.";
			link.l1.go = "diffindoor_18";
		break;
		
		case "diffindoor_18":
			dialog.text = "에이, 내 사랑하는 대니! 저 여자는 변하지 않았어... 젊었을 때처럼 여전히 무모하지... 지금 얼마나 그녀를 보고 안아주고 싶은지 너는 상상도 못 할 거야! 여기 누워 있으면서 많은 생각을 했지. 있잖아, 친구, 죽음이 가까워지면 세상이 다르게 보이기 시작하더라고. 아내와 함께한 시간이 너무 짧았어! 바다 약탈, 형제단 공식 일, 마룬 타운 통치... 그런데도 그녀는 언제나 나를 지지해줬지. 몇 주씩 혼자 남아 있었고, 내가 없는 동안 다른 해적들과 다투기도 했고, 우리 배를 지휘하기도 했어... 내 대니는 세상에서 가장 멋진 여자야! 그리고 나는... 더 자주 사랑한다고 말해줬어야 했어! 우리가 함께하기로 결심했던 그날이 생각나! 사실, 그날이 내가 처음으로 초자연적인 것들과 맞닥뜨리고 싸웠던 날이었지. 다 저주받은 우상 때문이었어. 그 우상은 꼭 저 조각상들처럼 생겼었지. 내 얘기 들어주는 거 괜찮겠지? 꽤 흥미로운 이야기야.";
			link.l1 = "전혀 아니야! 말해 줘!";
			link.l1.go = "story";
			link.l2 = "네이선, 지금은 추억을 나눌 시간이 없어. 나중에, 미스키토 마을에서 와인 한 병 들고 앉아 있을 때 얘기해 줘.";
			link.l2.go = "diffindoor_19";
		break;
		
		case "story":
			dialog.text = "그건 25년 전 일이었지... 나는 젊고, 열정적이며 안절부절못했어. 카리브 해는 내 놀이터였지. 그때 이미 나는 대니를 알고 있었어. 그녀가 마음에 들었고, 정말로 그랬어. 그녀도 나를 좋아했지. 하지만 우리는 자주 싸우고, 말다툼하고, 서로를 놀리곤 했어. 어리석은 젊음이었지... 그때 존경받는 선원들에게 우리는 꽤나 좋은 구경거리였을 거라 생각해! 아무튼, 어떻게든 대니와 나는 같은 사건에 휘말리게 되었어. 우리는 카엘 로아의 지도를 발견했고, 그곳이 인디언 금을 찾을 수 있는 장소라는 말을 들었지. 또 이상하게 생긴 황금 우상도 발견했어. 그건 조각상 윗부분의 작은 복제품이었지. 그 우상은 위험했어. 소지한 자의 활력을 빼앗았거든. 하지만 신전 안의 금고에 들어가려면 그 저주받은 물건이 꼭 필요했어. 문제는, 우리가 그걸 어떻게 제대로 써야 하는지 전혀 몰랐다는 거야. 대니와 나는 섬으로 항해했어. 그곳엔 고대 신전이 있었고, 풀과 나무에 뒤덮여 있었지. 안으로 들어가자, 우리는 거대한 미로 속에 들어가게 되었어. 우리는 겨우 올바른 길을 찾아 미로의 중심부에 도달했지. 막다른 길이라고 생각했는데, 절망이 밀려오기 시작할 때 이상한 받침대와 작은 구멍, 그리고 그림이 새겨진 걸 발견했어. 나는 그 구멍에 우상을 넣었고...\n";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "idol";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_1";
		break;
		
		case "story_1":
			dialog.text = "돌로 된 단상이 몇 인치쯤 내려앉더니, 벽 하나가 비밀 통로로 드러났네. 우상은 단상 안에 남겨두고 말았지; 다시 꺼내려 했지만 실패했어. 마침내 우리는 거대한 홀에 도착했네. 정말 아름다운 광경이었어! 내가 본 것 중 가장 웅장한 구조물이더군. 벽에는 조각이 새겨져 있고, 거대한 조각상들도 있었지... 우리는 홀 전체를 샅샅이 뒤졌지만, 보물의 흔적은 찾지 못했네.";
			link.l1 = "헤, 우리 같은 놈들한테 그런 일 자주 있지. 애는 많이 쓰는데 결국 남는 게 없더라고...";
			link.l1.go = "story_2";
		break;
		
		case "story_2":
			dialog.text = "헛된 일이 아니었어. 결국 우리는 끝에 거대한 새 조각상이 있는 왕좌의 전당에 들어갔지. 조각상 근처에는 신비로운 빛이 있었고, 자정에 우상 위에 떠오르는 빛과 똑같이 보였어. 우리가 가까이 다가가자 아름다운 구체가 공중에 떠 있었지. 맹세컨대, 정말 사실만을 말하는 거야!\n그건 분명히 실재했지만, 동시에 실재하지 않는 것처럼 느껴졌어. 내가 생각에 잠겨 있을 때, 대니—아, 그 무모한 악동—가 구체를 만졌지. 그러자 구체가 더 밝게 빛나더니 마침내 그녀 손에 작은 물건으로 변했어...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "temple";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_3";
		break;
		
		case "story_3":
			dialog.text = "우리가 신성모독을 저지른 것 같았어. 사원이 살아나더니, 주위 모든 것이 움직이기 시작했고, 벽이 흔들리며 모든 것이 무너져 내렸지. 마치 우리가 모든 인디언 악령을 깨워서, 그들이 온 분노를 우리에게 쏟아붓는 것만 같았어...\n";
			link.l1 = "이런 젠장!";
			link.l1.go = "story_4";
		break;
		
		case "story_4":
			dialog.text = "믿기 어렵다는 것, 나도 알아. 하지만...";
			link.l1 = "반 년 전만 해도 너를 거짓말쟁이라고 했을 거다. 하지만 카리브에서 오래 살다 보니 이제는 너를 의심할 이유가 없다는 걸 알게 됐지. 계속 말해 봐. 어떻게 살아남았지?";
			link.l1.go = "story_5";
		break;
		
		case "story_5":
			dialog.text = "우리는 신전에서 달아나 겨우 제때에 우리 배에 올라탈 수 있었어. 나는 닻을 올리라고 명령했지; 우리는 가능한 한 빨리 그곳을 떠나고 싶었거든.";
			link.l1 = "헤! 결국 보물 대신에 이상한 유물 하나만 찾았단 말이지? 참 멋지고도 동등한 대체품이네, 크크... 그리고 그걸 어떻게 쓰는지 알아냈어? 아니면 쓸모없던 거야?";
			link.l1.go = "story_6";
		break;
		
		case "story_6":
			dialog.text = "잠깐만. 이야기는 아직 끝나지 않았어. 대니가 유물을 가지고 있었고, 우리가 그걸 연구하려고 선실로 가기로 하자마자 하늘이 어두워지고 배 한 척이 나타났지. 오, 맙소사! 그건...\n";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "blackpearl";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_7";
		break;
		
		// вот тут делаем развилку, в зависимости прошёл ли игрок Калеуче
		case "story_7":
			dialog.text = "... 반 데르 데켄 그 자식이 직접 나타났어!!";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "반 데르 데켄? 흠...";
				link.l1.go = "story_8_1";
			}
			else
			{
				link.l1 = "그 사람은 누구요?";
				link.l1.go = "story_8";
			}
		break;
		
		case "story_8":
			dialog.text = "플라잉 더치맨에 대해 들어본 적 없나?";
			link.l1 = "플라잉 더치맨을 모르는 사람이 어디 있겠어! 나는 이미 네덜란드 놈 하나를 만났고, 그 선장은 바다 밑으로 보내 버렸지. 그 자는 그냥 평범한 해적으로, 자기 배를 해초랑 찢어진 돛 같은 가면 무도회 쓰레기로 치장했을 뿐이야.";
			link.l1.go = "story_9";
		break;
		
		case "story_8_1":
			dialog.text = "그래, 하지만 이건 플라잉 더치맨의 선장, 반 데르 데켄 본인이었어!";
			link.l1 = "흥미롭군. 계속 말해 보시오. 어떻게 그 난관을 헤쳐 나갔소?";
			link.l1.go = "story_11";
		break;
		
		case "story_9":
			dialog.text = "에헤, 친구야... 네가 침몰시킨 건 그냥 어릿광대 배고, 내가 말하는 건 진짜 플라잉 더치맨이야. 엄청난 전열함이지. 바다 한가운데서 그 배를 마주치지 않게 신께 빌어라. 선장 반 데르 데켄과 그의 선원들은 한때 저주를 받아 영원히 쉴 새 없이 바다를 떠돌게 되었지.\n나는 그 배의 너덜너덜한 검은 돛, 칼을 뽑고 갑판에 서 있는 죽은 자들의 선원들, 그리고 선장 자신—검은 삼각모를 쓴 소름 끼치는 해골—이 아직도 기억나... 예수여...";
			link.l1 = "진실을 말하는 거요?";
			link.l1.go = "story_10";
		break;
		
		case "story_10":
			dialog.text = "나는 성경에 손을 얹고 맹세할 수 있어, 거짓말이 아니야... '플라잉 더치맨'을 만난다는 건 곧 죽음을 뜻하지. 그 배는 강해, 아주 강하지; 대포 한 번만 쏴도 중형 프리깃과 그 선원들까지 가라앉힐 수 있어... 하지만 더 끔찍한 건, 대체 어떻게 언데드와 싸운다는 거지?";
			link.l1 = "하지만 이 악몽에서 살아남았잖아!";
			link.l1.go = "story_11";
		break;
		
		case "story_11":
			dialog.text = "이 모든 것은 내 사랑스러운 대니와 우리가 신전에서 가져온 인디언 유물 덕분이야. 모두에게 전투 준비를 명령하긴 했지만, 사실 이게 끝이라는 걸 알고 있었지. '플라잉 더치맨'이 우리를 향해 다가오고 있었고, 그 끔찍한 선원들과 반 데르 데켄 본인이 갑판에 있는 게 보였어. 그 배가 우리를 향해 대포를 겨누기 시작했지만...\n";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "artefact";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_12";
		break;
		
		case "story_12":
			dialog.text = "대니가 유물을 들어 올려 던져 버렸다. 왜 그런 짓을 했는지 나는 전혀 알 수 없었다. 그녀는 여자 직감 어쩌고 하며 뭔가를 중얼거렸다... 유물은 다시 빛나는 구체로 변하더니 폭발해 유령선에 치명적인 손상을 입히고 선원들의 사기를 꺾었다. 나는 네덜란드인에게 사격 명령을 내렸다.\n첫 일제 사격에 놈들이 움찔했다. 우리는 다시 공격해, 놈들이 유물의 영향에서 벗어나 반격을 시작하기 직전에 그 썩은 선체를 두 번째로 내리쳤다...";
			link.l1 = "그래서 결국 그놈들과 싸워야 했던 거야?";
			link.l1.go = "story_13";
		break;
		
		case "story_13":
			dialog.text = "정말이지. 내 인생에서 가장 힘든 싸움이었다고 맹세할 수 있지. 그 빌어먹을 배는 겨우 물에 떠 있었는데도, 놈들은 내 선체의 절반을 박살내더군. 우리가 놈들 화약고를 폭파시켜 하늘로 날려버리기 전까지 말이야.";
			link.l1 = "그래서 네가 가라앉혔나? 플라잉 더치맨을 정말 침몰시켰어?";
			link.l1.go = "story_14";
		break;
		
		case "story_14":
			dialog.text = "그래, 젠장! 내가 했어!..";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "ending";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_15";
		break;
		
		case "story_15":
			dialog.text = "그 빌어먹을 배가 가라앉았지. 그러자 다시 해가 비치고 하늘이 맑아졌어. 그리고 마침내 우리는 행복을 느끼기 시작했지... 아, 네가 상상도 못할 만큼 행복했어. 우리는 죽음을 속였으니까. 그런 순간이 사람들을 하나로 묶어주지. 그리고 우리는 그 만남 훨씬 전부터 했어야 할 일을 했어 - 서로를 껴안고, 입맞추고, 사랑을 고백하고, 영원히 함께하겠다고 맹세했지.";
			link.l1 = "그리고 아직도 함께 있군...";
			link.l1.go = "story_16";
		break;
		
		case "story_16":
			dialog.text = "그래, 맞아. 나는 대니와 결혼했고 한 번도 후회한 적 없어. 너는 대니보다 더 좋은 아내이자 동료를 찾지 못할 거야.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "이제야 마침내 '플라잉 더치맨'을 침몰시킨 그 신비로운 선장이 누구인지 알게 되었군... 당신은 진정한 영웅이오!";
				link.l1.go = "story_17_1";
			}
			else
			{
				link.l1 = "그래서, 너희 둘이 진짜 영웅이라는 거냐? 그 유명한 유령선을 침몰시켰다니. 잠깐! '플라잉 더치맨'이 아직도 떠 있다고 했잖아... 그런데 그 배가 바다 밑에 가라앉아 있다면 어떻게 그럴 수 있지?";
				link.l1.go = "story_17";
			}
		break;
		
		case "story_17":
			dialog.text = "이봐, 친구, 너 아무것도 모르는구나... 반 데르 데켄을 침몰시킬 수는 있지만, 그를 죽일 수는 없어. 그와 그의 선원들에게 걸린 저주는 너무 강해, 죽음보다 훨씬 강하지...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_17_1":
			dialog.text = "영웅일 수는 있겠지만, 반 데르 데켄은 죽일 수 없어. 그와 그의 선원, 그리고 그의 배에 드리운 저주는 죽음보다도 강하거든...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_18":
			dialog.text = "네가 그 배를 침몰시킬 때마다, 선원들이 배를 수리하고, 덧대어 고치고, 영원한 항해를 계속하지.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "알고 있네, 네이선리얼. 알고 있어. 그래도 이제 플라잉 더치맨은 더 이상 아무도 괴롭히지 않을 걸세.";
				link.l1.go = "story_22";
			}
			else
			{
				link.l1 = "음, 있잖아, 이건 마치 우화처럼 들리는데. 이미 부서지고 침몰된 배를 수리한다니...";
				link.l1.go = "story_19";
			}
		break;
		
		case "story_19":
			dialog.text = "우리가 그 배를 침몰시킨 후에도 사람들이 여러 번 그 배를 봤다고 하더군... 목격담을 믿을지는 네가 결정해라.";
			link.l1 = "그 사원이 있는 섬은 어디지? 네가 유물을 찾았던 그 섬 말이야?";
			link.l1.go = "story_20";
		break;
		
		case "story_20":
			dialog.text = "그곳은 미지의 땅이며 카리브 해 동쪽 어딘가에 위치해 있소. 나는 마룬 타운에 그 섬의 지도를 남겨두었지만, 알다시피 지금은 거기로 항해할 수 없소. 솔직히 말해, 가고 싶지도 않고. 내가 기억하는 건 이름뿐이오 - 카엘 로아...\n";
			link.l1 = "정말 흥미로운 이야기군. 나도 그 섬을 찾아보고 싶어!";
			link.l1.go = "story_21";
		break;
		
		case "story_21":
			dialog.text = "오, 그건 추천하지 않겠어... 나는 다시 거길 찾아갈 생각이 전혀 없어.";
			link.l1 = "어쨌든 한 번 가보고 싶군... 좋아, 흥미로운 이야기 들려줘서 고마워! 이제 당신 부인에 대해 더 알게 되었어. 두 분 다 살아 있는 전설이구나!";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
			pchar.questTemp.NatanStory = "true";
		break;
		
		case "story_22":
			dialog.text = "무슨 뜻이야, 이봐? 방금 내가 그를 죽일 수 없다고 말하지 않았냐?";
			link.l1 = "네이선리얼, 나는 카엘 로아로 항해했어. 그리고 너, 다니엘, 그리고 어떤 노인이 25년 전에 다녀갔던 차빈 신전을 방문했지. 그때 네가 신전에서 가져온 유물의 이름은 '떠오르는 태양의 구슬'이었어. 그 유물이 바로 '플라잉 더치맨'이 너희에게 관심을 갖게 만든 원인이었지. 그 배의 선장은 차빈 유물을 무척 좋아했거든.";
			link.l1.go = "story_23";
		break;
		
		case "story_23":
			dialog.text = "카엘 로아에 다녀왔다고? 그럴 리가 없잖아! 정말 사실을 말하는 거야?";
			link.l1 = "맹세하네. 자네가 미로와 거대한 새의 석상 이야기를 했을 때, 나는 곧바로 그곳이 어디인지 알아차렸지. 카리브의 주술사 투투아타팍이 자네의 모험담을 내게 들려줬거든. 바로 그가 나를 그 섬으로 이끌었네. 그 섬은 세인트 크리스토퍼의 동쪽에 있어. 아주 작고, 고리 모양이지. 사방이 바위로 둘러싸여 있고, 안쪽에는 작은 만이 있어. 그리고 무성하게 덮인 오솔길 하나만이 피라미드 형태로 지어진 신전으로 이어지지.";
			link.l1.go = "story_24";
		break;
		
		case "story_24":
			dialog.text = "그래! 여기가 카엘 로아야. 그런데 왜 거길 갔지?";
			link.l1 = "칼레우체의 저주를 풀려면... 아니, '플라잉 더치맨'의 저주를 풀려면 말이지. 사실 그 배의 이름은 '플라잉 하트'였고, 선장은 '발타자르 드 코르데스'였어. 오십 년 전에 그는 인디언 죽음의 신, 윰 시밀에게 저주를 받았지. 나는 얼마 전에 발타자르가 신전에서 훔쳐간 윰 시밀의 비취 해골을 가져다가, 그 콘도르 조각상 앞 제단에 다시 올려놓았어...\n";
			link.l1.go = "story_25";
		break;
		
		case "story_25":
			dialog.text = "";
			link.l1 = "...해골을 돌려줌으로써 나는 칼레우체의 저주를 풀었지. 그리고 내가 차빈 부적 두 개를 더 가지고 있었기 때문에, 그녀가 그 섬 근처에서 나를 공격했어, 예전에 네게 그랬던 것처럼. 하지만 저주가 사라지자 발타자르는 더 이상 불멸이 아니었어, 투투아타파크가 말한 대로 말이야. 그래서... '플라잉 더치맨'은 이제 없어. 내가 직접 처리했지.";
			link.l1.go = "story_26";
		break;
		
		case "story_26":
			dialog.text = "천둥 번개야! 정말 깜짝 놀랐군! 너... 너 지금 늙은 네이선을 놀리는 거 아니지? 아니, 네 눈을 보니 진심인 게 분명하군! 너야말로 진정한 영웅이야!";
			link.l1 = "영웅이든 아니든, 나도 자네만큼이나 모험을 많이 겪어봤지. \n뭐, 이제 우리에게 공통의 주제가 생겼으니 앞으로도 지난 이야기를 여러 번 나누게 될 걸세.";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
		break;
		
		case "diffindoor_19":
			dialog.text = "이제 나를 두고 가려는 거야, 친구?";
			link.l1 = "그래, 네이선. 제발, 내가 돌아올 때까지 버텨 줘. 몸조심하고. 무엇보다도, 내가 돌아올 때까지 꼭 살아 있어야 해. 그러면 모든 게 잘 될 거야. 코스트의 형제단도, 다니엘도 네가 필요해.";
			link.l1.go = "diffindoor_20";
		break;
		
		case "diffindoor_20":
			dialog.text = "이제 다니가 당신 선원인가요? 제발, 그녀를 잘 돌봐주십시오. 어릴 때부터 하나도 안 변했어요. 여전히 저돌적이고, 지옥이라도 주저 없이 뛰어들 겁니다. 그녀에게 제가 정말 많이 사랑한다고 전해 주세요...";
			link.l1 = "물론이지. 우리가 함께 널 데리러 올 거야, 네이선. 약속할게. 버텨, 그리고 고개 숙이지 마. 올레가 널 돌봐줄 거야. 곧 보자!";
			link.l1.go = "diffindoor_21";
		break;
		
		case "diffindoor_21":
			DialogExit();
			LAi_SetGroundSitTypeNoGroup(npchar);
			NextDiag.CurrentNode = "diffindoor_wait";
			pchar.questTemp.LSC.NatanTalk = "true"; // атрибут - разговор с Натаном состоялся
			AddQuestRecord("BaronReturn", "10");
			npchar.greeting = "nathaniel_1";
		break;
		
		case "diffindoor_wait":
			dialog.text = "아, 너였군, "+pchar.name+". 아직 섬을 떠나지 않았나?";
			link.l1 = "걱정 마, 네이선, 모든 게 계획대로 되고 있어. 이제 쉬어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "diffindoor_wait";
		break;
		
		case "danny":
			PlaySound("Voice\English\saga\Nataniel Hawk-03.wav");
			dialog.text = "다니엘!.. 대니! 내 대니!..";
			link.l1 = "...";
			link.l1.go = "danny_1";
		break;
		
		case "danny_1": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Nathaniel"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = "danny_2";
		break;
		
		case "danny_2":
			dialog.text = "고맙네, 친구. 모든 것에 감사하고, 특히 내 다니를 위해서 더욱 고맙네...";
			link.l1 = "천만에, Nathan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "danny_2";
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = "누가 방금 들렀나 했더니! 바로 "+GetFullName(pchar)+"  자네로군! 어서 들어오게, 내 친구! 잘 지냈나?";
			link.l1 = "나는 괜찮아. 너는 어때, 네이선? 이제 우울한 기색이 전혀 없구나. 건강해 보여. 스네이크 아이가 정말 잘했어!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "그래, 당신네 주술사는 정말 기적을 행하는 사람이군. 저 빌어먹을 순간이동을 겪기 전보다도 몸이 더 좋아졌소! 마치 열 살은 젊어진 기분이야! "+pchar.name+", 나는 당신에게 큰 빚을 졌소. 그리고 정말 감탄했소: 당신은 완전한 이방인을 도왔고, 저주받은 포탈을 통과해 나를 죽음의 손아귀에서 구해내 아내에게 데려다 주었소!\n그뿐만 아니라, 우리 배와 집까지 돌려주었소. 이제 당신은 우리에게 가장 소중한 친구요. 영원히. 혹시라도 도움이 필요하면 누구에게 찾아가야 할지 알겠지! 마룬 타운은 언제든 당신에게 보호와 지원, 그리고 안식처를 제공할 것이오.\n당신이 위험에 처하면 마을 전체가 당신을 위해 싸울 것이오. 평화로운 시기에는 여기서 우정을, 최고의 럼주와 포근한 침대, 그리고 쉴 만한 좋은 곳을 찾을 수 있을 것이오. 대니와 내가 반드시 그렇게 해주겠소.";
			link.l1 = "감사합니다, 남작 나리! 건강하신 모습을 뵈어 진심으로 기쁩니다, 그리고... 다니와 함께 계시니 더더욱요.";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			dialog.text = "당신이 올 줄 알고 있었소, "+pchar.name+", 그리고 내가 선물을 준비했네 - 희귀하고 강력한 무기지. 언젠가 한 번에 수많은 적을 쓰러뜨려야 할 날이 올지도 모르니, 이 핸드 모르타르가 바로 그때 도움이 될 걸세. '스클로페타'는 특수 수류탄을 발사하니, 내가 그 수류탄 만드는 방법도 함께 준비했네. 자, 받아두게.";
			link.l1 = "정말 훌륭한 무기군! 고마워!";
			link.l1.go = "marun_town_3";
		break;
		
		case "marun_town_3":
			GiveItem2Character(pchar, "grape_mushket"); 
			GiveItem2Character(pchar, "recipe_grenade"); 
			Log_Info("You have received a hand mortar");
			Log_Info("You have received a grenade instruction");
			PlaySound("interface\important_item.wav");
			dialog.text = "자주 들러 줘, "+pchar.name+"! 언제든지 다니와 나는 당신을 반갑게 맞이할 거야.";
			link.l1 = "기꺼이 그러지. 곧 나를 보게 될 것이오!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "marun_town_4":
			dialog.text = "아, 친구여 "+GetFullName(pchar)+"! 들어오시오, 들어오시오, 선장님! 어떻게 지내십니까? 도움이 필요하신가요?";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.NatanInfo"))
			{
				link.l2 = "네이선, 아주 중요한 일로 자네를 찾아왔네. 버려진 배들의 섬에서 자네와 대니가 인디언 사원에 몰래 들어가 '플라잉 더치맨'을 침몰시켰다고 말했던 거 기억하나?";
				link.l2.go = "caleuche";
			}
			link.l1 = "고마워, 난 괜찮아. 그냥 너희 둘을 보고 싶었을 뿐이야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "caleuche":
			dialog.text = "물론이지.";
			link.l1 = "저는 그 신전이 있는 섬에 가야 해요. 반드시 찾아야만 해요. 당신이 그 섬의 지도를 가지고 있다고 했죠. 좌표를 알려줄 수 있나요?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "오, 친구, 이건 정말 위험한 일이야, 알지... 카엘 로아의 신전은 저주받은 곳이거든. 그 복도에 누가 사는지 네가 알기만 한다면...";
			link.l1 = "지금은 그때 네가 봤던 것보다 훨씬 더 무시무시한 괴물들이 그곳에 살고 있지. \n그런데도 나는 여전히 그곳에 갈 거야.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "당신이 거기서 죽는다면 나는 평생 나 자신을 용서하지 못할 거요. "+pchar.name+", 제발 부탁이오: 이 일은 그만두시오! 게다가 그곳이 바로 '플라잉 더치맨'이 가장 자주 목격되는 곳이오...";
			link.l1 = "나는 이미 그것을 마주쳤고, 어떻게 따돌릴 수 있는지도 알고 있어. 네이선, 제발, 카엘 로아의 좌표를 알려주고 그 사원에 대해 네가 아는 모든 것을 말해 줘. 언데드 인디언들이 산다는 사실 말고 말이야.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "어쩔 수 없군... 거절할 수는 없지만... 너는 나랑 대니가 거기서 뭘 겪었는지 전혀 모를 거야! 카엘 로아는 앤티가 동쪽에 있어. 내가 마룬 타운에 돌아왔을 때 그 지도를 찾았지, 위치는... (지도를 보며) 좌표는 북위 19도 32분, 서경 62도 25분이야.";
			link.l1 = "그 위치를 내 일지에 적어둘게... 고마워, 네이선!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "나중에 고맙다고 해도 돼. 이제 세부사항을 말하지. 카엘 로아 섬은 바위로 둘러싸인 고리 모양이고, 그 안에 만이 있어. 바위 틈 사이로 들어가는 통로를 찾아야 해—꽤 깊은 곳이야. 만 안에서 닻을 내리고 해변에 상륙하게. 섬 안쪽으로 이어지는 오래된 길을 찾아. 그 길은 하나뿐이니 헷갈릴 일 없지. 그 길을 따라가면 인디언 피라미드, 그러니까 네가 찾는 신전이 나올 거야.\n섬 자체는 조용하지만, 신전 안에는 온갖 괴물들이 들끓고 있어. 입구는 피라미드 꼭대기에 있어. 안으로 들어가면 세 개의 통로가 있는데, 가운데 통로로 가야 해. 복도를 따라가면 네 개의 입구 또는 출구가 있는 단상이 나와. 내가 처음으로 신전 괴물들에게 습격당한 곳이니 조심해야 해.\n그 다음엔 미로가 있어. 아주 복잡해서, 나도 도저히 올바른 길을 기억 못 하겠어. 미로 안에는 역겨운 괴물들이 잔뜩 있어. 그놈들을 모두 처치하고 나면, 두 개의 입구, 여섯 개의 기둥, 아홉 개의 돌판이 있는 단상이 있는 홀에 도착할 거야. 여기가 바로 성소의 전실이야. 돌벽이 닫혀 있는데, 그걸 어떻게 여는지는 나도 전혀 모르겠어.\n뭔가 장치가 있긴 한데, 맹세코 그게 어떻게 작동하는지 전혀 모르겠어! 나는 우상을 열쇠로 썼지. 중앙 돌판에 우상을 꽂으니 문이 열렸어. 하지만 너에겐 그런 우상이 없으니, 네가 직접 이 장치가 어떻게 작동하는지 알아내야 할 거야.";
			link.l1 = "알겠어요, 최선을 다해 알아볼게요. 성소는 어떻게 할까요?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "성소는 천장이 매우 높고 큰 돌계단이 있는 넓은 홀이다. 하지만 그 계단들은 대부분 너무 낡아 무너져서 사용할 수 없다. 그러나 이 사원을 지은 이들은, 보아하니, 위대한 마법사이기도 했던 것 같다. 쿠쿨칸의 것과 같은 포탈이 있는데, 이 포탈들은 너를 한 장소에서 다른 곳으로 데려다 줄 것이다.\n포탈은 쉽게 알아볼 수 있다 – 색색의 소용돌이처럼 생겼으니. 1층에는 포탈이 두 개 있을 텐데, 그 중 하나는 함정이니 조심해야 한다! 올바른 포탈을 통과하면 2층으로 갈 수 있다. 거기서 또 다른 포탈을 찾아 더 높은 곳으로 올라가야 하고, 그러고 나면 바로 사원의 심장부로 향하게 된다!\n그곳, 거대한 새 조각상 앞에, 내가 다니와 함께 가져온 그 마법 유물이 놓여 있었다. 그리고 그 다음에 무슨 일이 일어났는지는 이미 이야기해 주었지.";
			link.l1 = "방금 해준 말을 기억하겠소. 고맙소, Nathaniel. 큰 도움을 주었소.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "조심해. "+pchar.name+". 미로와 신전의 복도에는 위험이 가득하다네. 한 번만 잘못 움직여도 영원히 거기서 나오지 못할 걸세.";
			link.l1 = "미리 경고받으면 대비할 수 있지, 친구. 나는 미리 들었으니 준비도 되어 있지. 이제 가봐야겠다. 또 보자!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "행운을 빌어요, "+pchar.name+"!";
			link.l1 = "고마워!";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NatanStory");
			DeleteAttribute(pchar, "questTemp.Caleuche.NatanInfo");
			AddQuestRecord("Caleuche", "35");
			NextDiag.CurrentNode = "marun_town_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
