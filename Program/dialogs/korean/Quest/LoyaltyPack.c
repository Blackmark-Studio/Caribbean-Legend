void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
			dialog.text = "무슨 일이야?";
			link.l1 = "아무것도 아니다.";
			link.l1.go = "exit";
		break;
		
		case "Alonso":
			NextDiag.TempNode = "Alonso";
			
			// --> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "...";
				Link.l1 = "알론소, 할 얘기가 있어.";
				Link.l1.go = "SharlieEpilog_Alonso_1";
				break;
			}
			// эпилог <--
			
			if (GetDLCenabled(DLC_APPID_1))
			{
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FirstStage", "ready"))
				{
					dialog.text = "말해도 되겠습니까, 선장?";
					link.l1 = "나중에 보자, Alonso.";
					link.l1.go = "exit";
					link.l2 = "계속해.";
					link.l2.go = "Alonso_1";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.SecondStage", "ready"))
				{
					dialog.text = "말해도 되겠습니까, 선장님?";
					link.l1 = "나중에 보자, Alonso.";
					link.l1.go = "exit";
					link.l2 = "가 보시지.";
					link.l2.go = "Alonso_Lvl_8_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.ThirdStage", "ready"))
				{
					dialog.text = "말해도 되겠습니까, 선장님?";
					link.l1 = "나중에 보자, Alonso.";
					link.l1.go = "exit";
					link.l2 = "진행해.";
					link.l2.go = "Alonso_Lvl_12_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FourthStage", "ready"))
				{
					dialog.text = "말해도 되겠습니까, 선장님?";
					link.l1 = "나중에 보자, Alonso.";
					link.l1.go = "exit";
					link.l2 = "가시지요.";
					link.l2.go = "Alonso_Lvl_16_Start";
					break;
				}
			}
			
			dialog.text = " 보고할 거 없어, 선장.";
			link.l1 = "원래 하던 대로 해, Alonso.";
			link.l1.go = "exit";
		break;
		
		case "Alonso_1":
			DelLandQuestMark(npchar);
			dialog.text = "괜찮아?";
			link.l1 = "무슨 뜻이야?";
			link.l1.go = "Alonso_2";
		break;
		
		// Основная развилка стадии 1
        case "Alonso_2":
            dialog.text = "너는 이 카리브 해역을 몇 달째 항해하고 있지. 어떤 놈들은 여기서 일주일도 못 버티거든. 선원들이 너를 존경하는 건 확실하지만, 나는 말이야? 네 앞날이 걱정돼.\n"+
                          "생각 좀 나눠봐, 선장. 선원들을 위해 한마디 해 줘. 어디 있지\n "+pchar.ship.name+" 어디로 가는 거야?";
                          
            link.l1 = "나는 계획이 없어. 먼저 이 땅을 좀 파악하고 싶어. 모험은 알아서 우리를 찾아올 거야.";
            link.l1.go = "Alonso_Choice_1";
            
            link.l2 = "이 바다에는 포식자들이 득실거려, Alonso. 그리고\n "+pchar.ship.name+" 그들 중에서 가장 작아. 지금은 말이지.";
            link.l2.go = "Alonso_Choice_2";
            
            link.l3 = "나는 돈 버는 게 좋아. 가능하면 합법적으로 말이지. 하지만 어떻게 될지는 두고 봐야겠군.";
            link.l3.go = "Alonso_Choice_3";
			
            if (!SandBoxMode)
            {
                link.l4 = "그 얘기는 알고 있지. 율리시스호에서 그 잊을 수 없는 대화를 나눈 후로, 모든 게 더 복잡해졌어...";
                link.l4.go = "Alonso_Choice_4";
            }
        break;
        
        case "Alonso_Choice_1":
            dialog.text = "이게 바로 자유지! 하지만 배를 유지할 만큼은 챙기고, 비상시에 쓸 돈도 남겨두는 거 잊지 마라.\n"+
                          "네 기분이든, 퀘스트든, 보물 지도가 이끄는 곳이든 상관없지 - 승객 태우기, 화물 운송, 뭐든 눈에 띄는 일거리를 맡아라.\n"+
                          "작은 장사도 해두면 나쁠 거 없지 - 값이 싼 곳에서 사고, 팔 수 있는 데서 팔아라.\n"+
                          "그리고 가는 길에 외로운 상선이라도 보이면... 헤헷. 네가 말한 대로지, 선장. 모험은 반드시 우리를 찾아올 거야.";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50);
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            
            link.l1 = "좋은 조언 고마워, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_2":
            dialog.text = "이익이 되는 장사지, 네 배가 감당할 수 있다면 말이야. 외따로 다니는 상인들을 찾아서 '소탐대실'이 뭔지 제대로 보여줘라.\n"+
                          "불행히도 너한테는 또 다른 속담이 있지. '진실은 드러나게 마련이다.' 선원들 중에는 네가 무슨 짓을 했는지 첫 항구에 닿자마자 떠벌릴 입이 가벼운 녀석이 꼭 있기 마련이거든.\n"+
                          "그러니 모두를 조금씩 털든가, 아니면 평생 적국의 깃발을 고르든가 해라.\n"+
                          "내가 너무 앞서가는 걸지도 모르지. 상황이 정말 꼬이면, 포트 로얄에 있는 변호사가 적당한 값을 받으면 당국과의 문제를 잘 해결해 줄 거야. 해적세라고나 할까, 허허!";
            
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", -1);
            
            link.l1 = "좋은 조언 고마워, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_3":
            dialog.text = "에이, 거기선 별로 도와줄 수 없겠네, 선장. 제대로 된 상선이 필요할 거야—바르크틴이나, 아니면 바르크면 더 좋지. 이런 말 했다가 나중에 후회할지도 모르겠지만, 가벼운 대포를 달거나 아예 포를 다 버리는 게 좋을 거야.\n"+
                          "상점 주인들에게서 화물 계약을 받고, 가는 길에 직접 무역도 하며, 승객들도 태워 주시오.\n"+
                          "돈을 충분히 모으면, 상점이나 은행에 투자해. 내 말 명심해, 선장. 언젠가 네 돈이 돈을 벌기 시작할 거고, 수백 명을 태운 제대로 된 배도 살 수 있을 거야.\n"+
                          "그건 말이지, 네가 아니라 네 사업이 돈을 내게 될 거야.";
            
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            AddCharacterExpToSkill(pchar, SKILL_SAILING, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "좋은 조언 고마워, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_4":
            dialog.text = "내 생각은 달라, 선장. 율리시스호에선 너도 그냥 승객이었지. 그런 불쌍한 자들은 자기 운명을 어찌할 수 없어. 하지만 지금은 네가 선장 모자를 쓸 자격을 얻었으니, 어떤 문제든 해결할 수 있다는 뜻이야. 전에 말했잖아, 우리 세계에서 그보다 높은 자리는 없다고.\n"+
                          "내 촉으로는 네 형제와 얽힌 이 이야기가 몇 년은 더 이어질 것 같으니, 우선 네 몸부터 챙겨라. 미셸 나리는 어디 안 가니까, 허허...\n"+
                          "카리브 해에서 문제를 겪는 건 너만이 아니야. 지금이야말로 남들을 도우면서 돈, 장비, 인맥까지 챙길 절호의 기회지. 이 가족 사업에 필요한 모든 걸 가는 길에 다 배우게 될 거야...";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 100);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "좋은 조언 고마워, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
		
        case "Alonso_Common_End":
            dialog.text = "한 가지 역할에만 자신을 가두지 마, 선장. 하고 싶은 대로, 원하는 때에 해. 다 가져가고 아무것도 돌려주지 마. 그래도 넌 잘 해낼 거야.";
            link.l1 = "지혜도 나눠줘서 고맙다.";
            link.l1.go = "Alonso_Common_End_2";
        break;
        
        case "Alonso_Common_End_2":
            dialog.text = "에이, 그게 바로 내가 돈 받는 이유지, 선장. 선원들이 그 쥐꼬리만 한 월급 때문에 네 명령을 따르는 줄 알아?\n"+
                          "수십 명의 사내들이 좁은 공간에 빽빽이 몰려서, 언제 다시 육지를 볼 수 있을지, 아니면 영영 못 볼지조차 모른 채 지내지. 그리고 배 한 척을 죽이는 일? 너무 쉬운 일이지.";
            link.l1 = "그래, 그래, 그 얘긴 전에 들었어, Alonso. 아까 배에 대해 뭐라고 했지?";
            link.l1.go = "Alonso_Common_End_3";
        break;
        
        case "Alonso_Common_End_3":
            dialog.text = "헤헤! 배란 건 감옥이자, 군대 막사이자, 수도원이 한데 섞인 곳이지. 결국 남자들이 모인 집단이란 말이야. 그러니 문제는 말로 풀거나 채찍으로 해결하지. 자네 경우엔, 헤헤, 채찍질은 안 되니까 이렇게 대화라도 하자고 생각했네. 자네도 좀 편해지라고 말이야.";
            link.l1 = "감옥에 실제로 가본 적 있나? 군대는? 수도원은, 하느님 맙소사? 가만, 알론소, 너에 대해 좀 말해 봐라. 나는 네가 어떤 놈인지 거의 모르겠거든.";
            link.l1.go = "Alonso_Story_1";
        break;
        
        // История Алонсо
        case "Alonso_Story_1":
            dialog.text = "음, 수도원은 피해 다녔지, 거짓말 안 해. 그래도 한때는 성스러운 종교재판소에서 일한 적이 있어...";
            link.l1 = "도대체 어떻게 그런 일이 일어난 거지?";
            link.l1.go = "Alonso_Story_2";
        break;
        
        case "Alonso_Story_2":
            dialog.text = "오! 그랬지. 나는 유럽 전쟁에서 용병으로 내 몫을 다하고 있었어. 어떻게 시작됐는지, 누가 누구랑 싸우는지 악마나 알 일이지. 우리가 아는 건 전쟁이 삼십 년째 계속되고 있다는 거랑, 어느 지휘관이 그나마 꾸준히 돈을 준다는 것뿐이었어. 그게 바로 모험이었지!\n"+
                          "그게 42년이었나... 아니면 41년이었나? 뭐, 상관없지. 두 부대가, 둘 다 황제의 명을 받들고, 숲에서 만났어. 안개 속에서. 그리고 서로를 난도질하기 시작했지! 사흘 동안 학살이 벌어졌어!";
            link.l1 = "그게 어떻게 가능하지?";
            link.l1.go = "Alonso_Story_3";
        break;
        
        case "Alonso_Story_3":
            dialog.text = "저 안개 속에서 누가 아군이고 적군인지 구분해 봐라. 게다가 우리는 석 달째 월급도 못 받아서, 다들 약탈 생각뿐이었지.\n"+
                          "우리는 서로 절반씩 죽였지. 우리가 그걸 깨달았을 땐 이미 늦었어. 그때 내가 이 모스크바 놈을 만났지. 곰만큼 크지만, 마음만은 금덩어리야!";
            link.l1 = "그 다음엔 무슨 일이 있었지?";
            link.l1.go = "Alonso_Story_4";
        break;
        
        case "Alonso_Story_4":
            dialog.text = "전쟁이란 게 어떤지 알지? 제일 먼저 보고하는 놈이 영웅이 되는 법이야. 그래서 우리도 생각했지 - 이 참사를 우리한테 유리하게 써먹자고!\n"+
                          "놈들 모아서 급여 담당관한테 가서 '영광스러운 전투'라고 보고했지. 죽은 자들의 임금은 깎이고, 살아남은 놈들은 돈을 받았고, 나랑 내 친구는 보너스를 챙겼고, 사령관도 자기 몫을 챙겼다.";
            link.l1 = "그럼 너 돈 많구나, 알론소.";
            link.l1.go = "Alonso_Story_5";
        break;
        
        case "Alonso_Story_5":
            dialog.text = "하! 우리는 일주일 내내 포도주를 마시고 카드놀이를 했지. 다행히도, 눈 내리는 모스코비에서 온 내 새 친구가 희귀한 장신구에 약해서, 그렇지 않았으면 난 빚쟁이 감옥에 갇혔을 거야. 내게서 전리품을 샀지 - 멋진 삼연발 권총이었고, 값도 괜찮게 쳐줬어. 내 불운을 이용하지도 않았고.";
            link.l1 = "꽤 그럴듯한 이야기로군, Alonso. 내 생각엔 네가 그냥 지어낸 것 같은데.";
            link.l1.go = "Alonso_Gift";
        break;
        
        // Вручение подарка
        case "Alonso_Gift":
            dialog.text = "나를 상처 입히는군, 선장. 자, 이 작은 선물 받아.";
            link.l1 = "무슨 일이야?";
            link.l1.go = "Alonso_Gift_2";
        break;
        
        case "Alonso_Gift_2":
            // Выдаем Берендейку
            GiveItem2Character(pchar, "talisman20");
			SetAlchemyRecipeKnown("talisman20");
            
            dialog.text = "머스킷 전투용 탄띠야. 내 모스크바 친구 고향에선 모두가 이걸 착용한대. 적어도 그 녀석 말로는 그렇지.\n"+
                          "잘 쓰시길, 선장님. 선원들 모두의 선물이라 생각하시오.";
            link.l1 = "예상치 못했군! 고맙다, Alonso. 그럼 종교재판소에서의 일은 어떻게 됐지?";
            link.l1.go = "Alonso_Escape";
        break;
        
        case "Alonso_Escape":
            PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "에...\n"+
                          "종이 울리고 있어, 선장! 이제 다시 일하러 가야지. 다음에 계속하자.";
            link.l1 = "이 대화는 꼭 계속하자. 선물 고마워!";
            link.l1.go = "exit";
            
			AddDialogExitQuestFunction("LoyaltyPack_FirstStage_DlgExit");
        break;
		
		// (Level 8) - Continuing the story
        case "Alonso_Lvl_8_Start":
			DelLandQuestMark(npchar);
			dialog.text = "우리가 마지막으로 얘기한 이후로 많은 것을 이루었군. 이제는 선원들도, 나도, 더 이상 네 실력을 의심하지 않아.";
			link.l1 = "의심이 있었나?";
			link.l1.go = "Alonso_Lvl_8_1";
        break;

        case "Alonso_Lvl_8_1":
            dialog.text = "당연히 있었지. 우리는 단순한 사람들이라 최악의 상황에 대비하지. 자유를 만끽해, 선장. 이렇게 계속하다 보면 카리브의 완전히 다른 면을 보게 될 거야.";
            link.l1 = "잘 들었네. 이제 종교재판소에서 복무한 이야기를 해보게. 지난번엔 군대 이야기를 시작하더니 끝까지 그 얘기만 하더군.";
            link.l1.go = "Alonso_Lvl_8_2";
        break;

        case "Alonso_Lvl_8_2":
            dialog.text = "뭐 별거 있나? 그 어이없지만 아주 짭짤했던 숲 대학살 이후로, 나랑 그 모스크바 놈은 죽이 척척 맞아서 꽤 많은 꿍꿍이를 벌였지.\n"+
                          "한 번은 우리가 제국의 보급 행렬을 습격하기로 했던 게 기억나. 정찰병들이 전리품이랑 금, 무기 같은 걸 실어 나른다고 했지...";
            link.l1 = "그래서 해냈어?";
            link.l1.go = "Alonso_Lvl_8_3";
        break;

        case "Alonso_Lvl_8_3":
            dialog.text = "식은 죽 먹기였지. 양쪽에서 덮쳐서 경비들을 흩어놓고, 마차 문을 열었더니... 양배추더라고! 썩고 냄새나는 양배추가 주둔군 먹으라고 실려 있었지! 그런데 말이야, 우리 일주일 동안 굶었거든. 그래서 그런 거라도 나와서 진짜 기뻤다니까!";
            link.l1 = "내 배의 음식이 더 낫기라도 하겠냐.";
            link.l1.go = "Alonso_Lvl_8_4";
        break;

        case "Alonso_Lvl_8_4":
            dialog.text = "이제는 익숙해졌지. 하지만 그땐 말이야... 일주일 동안 먹을 걸 찾아다니다 보면 나무껍질까지 씹어 먹게 돼!\n"+
                          "하지만 내 친구는 기죽지 않았지. 자기만의 특별한 술이 담긴 플라스크를 꺼냈어. 모스크바식 비법이라나? 식초만 아니면 뭐든 상관없었지! 몇 모금 들이켜고 나니까, 그 양배추조차 진수성찬처럼 느껴졌거든!";
            link.l1 = "역겨워.";
            link.l1.go = "Alonso_Lvl_8_5";
        break;

        case "Alonso_Lvl_8_5":
            dialog.text = "역겨운 건 우리 물통 상태지. 하지만 그날 내 목숨을 살린 건 그 모스크바산 독한 술이었어.";
            link.l1 = "어째서지?";
            link.l1.go = "Alonso_Lvl_8_6";
        break;

        case "Alonso_Lvl_8_6":
            dialog.text = "우리는 길바닥 진흙탕에서 배추가 둥둥 떠다니는 가운데 눈이 멀도록 술을 마셨지. 뭐, 이러다 저러다 보니 어떤 귀족놈이랑 시비가 붙었어. 독일 놈이었는데, 아주 점잖고 깔끔하더라고. 우리랑 술 마시기엔 너무 고상한 척하면서 그냥 앉아서 머스킷이나 닦고 빈정거리는 소리만 하더라니까.\n"+
                          "그래서 우린 거기 앉아서 양배추에 한탄을 풀고 있었지. 그런데 그 녀석이 갑자기 우리한테 군사적 지혜에 대해 설교를 시작하는 거야. 우리가 믿고 쓰던 검이랑 창은 곧 잊혀질 거라면서, 앞으로는 총검이야말로 미래고 모든 것의 열쇠라고 하더라고.\n"+
                          "그래서 그 놈이랑 말싸움을 하다가, 어쩌다 보니 죽을 때까지 결투하기로 했어. 그것도 총검으로 말이지. 어떻게 그렇게 된 건지 묻지 마, 나도 기억이 안 나니까.\n"+
                          "하지만 우리 중대 전체에 총검이 두 자루밖에 없었지. 하나는 그 조그만 장교가 가지고 있었고, 다른 하나는 영국인인 폭스가 가지고 있었어. 나는 그의 머스킷을 빌려 독일 놈을 두들겨 죽이고는 슬쩍 도망쳤지.";
            link.l1 = "하지만 너는 배고프고 취해 있었지.";
            link.l1.go = "Alonso_Lvl_8_7";
        break;

        case "Alonso_Lvl_8_7":
            dialog.text = "나중에야 알았지. 내 친구가 만든 술이 무거운 머스켓을 휘두를 때 손을 아주 안정시켜 준다는 걸 말이야. 그래서 이제는 죽은 독일 녀석의 생각에 좀 더 동의하게 됐어.";
            link.l1 = "그런데 이것이 자네가 종교재판소에서 일한 것과 무슨 관련이 있지?";
            link.l1.go = "Alonso_Lvl_8_Gift";
        break;

        case "Alonso_Lvl_8_Gift":
            dialog.text = "또 내 말을 안 믿는구나, 선장! 자, 이거 받아.";
            link.l1 = "병 하나랑 종이 한 장?";
            link.l1.go = "Alonso_Lvl_8_Gift_2";
        break;

        case "Alonso_Lvl_8_Gift_2":
            // Даём игроку настойку и рецепт
            GiveItem2Character(pchar, "vodka");
            SetAlchemyRecipeKnown("vodka");

            dialog.text = "이게 내가 말했던 술이야. 그리고 이건 그 레시피지. 혹시 마음에 들면 써먹으라고, 헤헤.";
            link.l1 = "미안하다, 친구야, 하지만 낙서랑 뭔가 흐릿한 혼합물만으론 안 돼...";
            link.l1.go = "Alonso_Lvl_8_Gift_3";
        break;

        case "Alonso_Lvl_8_Gift_3":
            // Даём игроку мушкет с багинетом
            GiveItem2Character(pchar, "mushket10");

            dialog.text = "알았어, 알았어, 선장. 어차피 이걸 줄 생각이었어. 이런 무기는 나랑 안 맞지만, 너한텐 쓸모 있을 거야. 총검은 보기 드문 물건이지. 하지만 한 번 쓰는 법을 익히면, 칼 휘두르는 건 다 잊게 될 거야.";
            link.l1 = "잠깐, 이거 그 제국 장교한테서 나온 머스켓 아니야? 네가 죽인 그 놈 말이야?";
            link.l1.go = "Alonso_Lvl_8_Gift_4";
        break;

        case "Alonso_Lvl_8_Gift_4":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "그래, 바로 나야. 보다시피, 내가 진실만을 말했다니까, 선장.";
            link.l1 = "하지만 내가 물어본 건 그게 아니야.";
            link.l1.go = "Alonso_Lvl_8_Escape";
        break;

        case "Alonso_Lvl_8_Escape":
            dialog.text = "종이 울리고 있어, 선장! 이제 다시 일하러 가야 해. 다음에 계속하자.";
            link.l1 = "이 대화는 꼭 계속하지. 머스킷 고마워!";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_SecondStage_DlgExit");
        break;

        // (Уровень 12)
        case "Alonso_Lvl_12_Start":
			DelLandQuestMark(npchar);
			dialog.text = "선장님, 신병들에 관해서 말씀드리자면...";
			link.l1 = "무슨 일이라도 있었어?";
			link.l1.go = "Alonso_Lvl_12_1";
        break;

        case "Alonso_Lvl_12_1":
            dialog.text = "오늘 저녁 미사에서 신병 중 한 명이 특별히 당신 배에 승선하고 싶다고 말했다는 것을 보고하려고 했소.";
            link.l1 = "그게 정확히 무슨 뜻이지?";
            link.l1.go = "Alonso_Lvl_12_2";
        break;

        case "Alonso_Lvl_12_2":
            dialog.text = "곧 그처럼 되는 자들이 더 생길지도 몰라. 이제 이름이 생겼군, 선장.";
            link.l1 = "아직도 네 이름 뒤에 뭐가 숨겨져 있는지 모른다는 게 웃기네. 너, 종교재판 이야기 끝까지 한 적 없잖아.";
            link.l1.go = "Alonso_Lvl_12_3";
        break;

        case "Alonso_Lvl_12_3":
            dialog.text = "오, 내가 어디까지 말했더라... 맞다! 그리고 우리는 군수업에 뛰어들기로 했지. 전쟁이 끝나가고 있었으니, 미래를 생각해야 했거든. 내 친구는 항상 미래 생각으로 머리가 꽉 차 있었지.";
            link.l1 = "꽤나 출세했군. 얼마 전까지만 해도 약탈당한 양배추 수레 옆에서 술에 취해 있더니.";
            link.l1.go = "Alonso_Lvl_12_4";
        break;

        case "Alonso_Lvl_12_4":
            dialog.text = "기다려, 더 좋은 소식이 있어. 어떤 연대에서 투구 백 개 주문이 들어왔거든. 선금도 두둑하게 받았지. 그래서 우리가 축하했어... 카드도 치고 그랬지.\n"+
                          "아침에 일어나 보니 --- 돈은 사라졌고, 이틀 뒤면 군대가 출정하는데, 우리는 아직 헬멧 백 개를 더 마련해야 해!";
            link.l1 = "그래서 너는 뭘 했어?";
            link.l1.go = "Alonso_Lvl_12_5";
        break;

        case "Alonso_Lvl_12_5":
            dialog.text = "신선한 전장에 가서 죽은 자들한테서 모자를 모았지. 그러고는 온갖 쇳조각을 박고, 판때기를 붙였어... 꼴이 우스꽝스러웠지만, 효과는 있었지! 분명히 군도 한 방은 막아줬다구. 뭐, 적어도 한 번은 확실히. 아무 투구 못지않게 쓸만하지 않아?!";
            link.l1 = "사관장이 네 기지를 알아줬나?";
            link.l1.go = "Alonso_Lvl_12_6";
        break;

        case "Alonso_Lvl_12_6":
            dialog.text = "횡령과 사기로 우리를 재판에 넘겼지. 하지만 그거 알아? 나중에 들으니, 그 모자가 여러 번 사람 목숨을 살렸대. 우리 목숨도, 결국엔.";
            link.l1 = "어째서?";
            link.l1.go = "Alonso_Lvl_12_7";
        break;

        case "Alonso_Lvl_12_7":
            dialog.text = "글쎄, 우리 둘 다 감옥에 갇혔지. 그리고 우리 동료들은 임무에 보내졌어. 어디로, 누구를 상대로 갔는지는 몰라, 아마 그들도 몰랐을 거야. 그들은 돌아오지 않았지.\n"+
                          "...\n"+
                          "미안해, 선장. 다음에 계속하지. 이 모자랑 지침서 받아. 어제 네 기분 풀어주려고 만들었는데... 괜히 나만 우울해졌네.";
            link.l1 = "물론이지, Alonso. 선물 고마워.";
            link.l1.go = "Alonso_Lvl_12_Gift";
        break;

        case "Alonso_Lvl_12_Gift":
            // Даём игроку шляпу
            GiveItem2Character(pchar, "hat10");
            SetAlchemyRecipeKnown("Hat10");

            DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_ThirdStage_DlgExit");
        break;

        // (Уровень 16) - Финальный
        case "Alonso_Lvl_16_Start":
			DelLandQuestMark(npchar);
			dialog.text = "선장님, 이제 선원들이 선술집이랑 사창가에서 귀한 대접을 받고 있다는 걸 보고드리려고 왔습니다.\n요즘은 선장님의 깃발 아래에서 일한다는 게 대단한 의미가 있거든요!";
			link.l1 = "고맙다, 알론소... 아직은 내가 그 왕실 대접을 제대로 못 받고 있는 게 아쉽군.";
			link.l1.go = "Alonso_Lvl_16_1";
        break;

        case "Alonso_Lvl_16_1":
            dialog.text = "곧 알게 될 거야. 카리브 해는 몇십 명의 선장들이 나눠 가진 파이와 같지. 머지않아 너도 그 자리에 앉아 네 몫을 챙기게 될 거다.\n"+
                          "누가 알겠어? 어쩌면 네가 카리브 해에서 모든 걸 차지하는 전설이 될지도 모르지.";
            link.l1 = "그래서 네 이야기를 끝까지 해줄 거야? 우리가 마지막으로 들은 건 네가 감옥에 갇힌 부분이었지.";
            link.l1.go = "Alonso_Lvl_16_2";
        break;

        case "Alonso_Lvl_16_2":
            dialog.text = "하! 위대한 모자 도둑 사건이지. 무스코비아 놈 하나랑 포르투갈 놈 하나가 플랑드르 어딘가의 좁은 감방에 갇혀 있지. 선고를 기다리면서. 당연히 교수형이지.\n"+
                          "어떤 중요한 양반이 우리를 구해줬어 - 알고 보니 모스크바 대사였지! 파데이의 옛 친구라더군. 지나가다가 우리 처지를 듣고, 몸값을 내주고 자유를 사줬어!";
            link.l1 = "파데이? 그 파데이? 그런데 지금까지 아무 말도 안 했다고?!";
            link.l1.go = "Alonso_Lvl_16_3";
        break;

        case "Alonso_Lvl_16_3":
            dialog.text = "그래. 거기서 우리 길이 갈라졌지. 그는 자기 모스크바로 돌아가서 폴란드 놈들이랑 싸우든 큰일을 처리하든 했고, 나는 고향에서 좀 더 떠돌다가 이렇게 여기까지 오게 됐지.";
            link.l1 = "인상적이군, 알론소. 이렇게 오랜 시간 동안 자기 얘기만 빼고 다 말했잖아. 영리한 녀석이 너답지 않게 종교재판소 얘기는 흘려버렸네, 이상하군.";
            link.l1.go = "Alonso_Lvl_16_4";
        break;

        case "Alonso_Lvl_16_4":
            dialog.text = "내가 정말 사실만 말했어, 선장! 못 믿겠으면 파데이한테 직접 물어봐. 바스테르에서 찾기 어렵지 않아.";
            link.l1 = "어쩌면 그럴지도. 그래서 내 선물은 어디 있지?";
            link.l1.go = "Alonso_Lvl_16_5";
        break;

        case "Alonso_Lvl_16_5":
            dialog.text = "엉?";
            link.l1 = "너는 이야기마다 끝날 때마다 내게 선물을 주었지.";
            link.l1.go = "Alonso_Lvl_16_Escape";
        break;

        case "Alonso_Lvl_16_Escape":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "들었어? 종이 울리고 있잖아. 이제 일할 시간이야.";
            link.l1 = "원래 하던 대로 해, Alonso.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_FourthStage_DlgExit");
        break;
		
		// --> Эпилог
		case "SharlieEpilog_Alonso_1":
			dialog.text = "플로랑 얘기야? 이미 그 친구한테 말했는데...";
			link.l1 = "아니, 친구야. 전혀 다른 일이지. 난 유럽으로 떠나기로 했어. 언제 돌아올진 몰라.";
			link.l1.go = "SharlieEpilog_Alonso_2";
		break;

		case "SharlieEpilog_Alonso_2":
			if (GetCompanionQuantity(pchar) <= 1) sStr = "우리 배";
			else sStr = "우리 배들";
			dialog.text = "문제없어요, 선장님. 배는 튼튼하고, 선원들도 노련하죠. 식량만 좀 있으면 돼요...";
			link.l1 = "난 남의 배를 탈 거야. 승객으로. 넌 "+sStr+"을 항구 관리소에 정박시키고 선원들을 해산시켜야 해. 그리고 선택해야지. 여기 남아서 다른 배에 승선할 건지, 아니면 나랑 친구로서 프랑스로 갈 건지.";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;

		case "SharlieEpilog_Alonso_3":
			dialog.text = "...";
			link.l1 = "참, 완전 상관없는 얘긴데 말야… (속삭이며) 보르도에 내가 아는 아가씨들이 몇 명 있어... 이런 마법 같은 애들, 카리브에선 못 봐. 너 같은 스타일에 약하지. 전투 얘기라도 꺼내면 바로 넘어가겠지...";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;

		case "SharlieEpilog_Alonso_4":
			dialog.text = "여자들 때문이라면... 나도 갈게. 헤헤. 근데 왜 우리 배로 안 가? 그리고 왜 승객으로? 애들이야 좀 투덜댈 수도 있겠지만, 당신이라면 천국이든 지옥이든 따라갈 거야.";
			link.l1 = "처음 여기 왔을 땐 내가 뱃사람이 될 거라고는 상상도 못 했어. 그런데 지금은 다른 삶은 생각도 못 하겠어. 내가 더 이상 선장이 아닐 수도 있다는 걸 받아들일 수 있는지... 그리고 바다에서의 삶, 약탈을 떠날 준비가 됐는지 확인하고 싶어.";
			link.l1.go = "SharlieEpilog_Alonso_nothing";
			link.l2 = "긴 얘기야. 선술집에서 럼 한 잔 하면서 말해줄게. 선원들도 불러. 성대한 송별 파티를 열자고. 자, 이거 받아——걔네들한테 한 달치 월급 주라. 퇴직금 대신이야.";
			link.l2.go = "SharlieEpilog_Alonso_salary";
		break;

		case "SharlieEpilog_Alonso_nothing":
			dialog.text = "운명은 피할 수 없어요, 선장님. 당신이 평생 선장으로 살 운명이라면, 그렇게 될 거예요.";
			link.l1 = "두고 보자고, "+npchar.name+"... 일단은 해야 할 일이 있어. 2주 후에 출항한다. 어떤 배인지 절대 못 맞힐걸...";
			link.l1.go = "SharlieEpilog_Alonso_5";
		break;

		case "SharlieEpilog_Alonso_salary":
			dialog.text = "그거 참 좋네요! 이제 걔네들한테 이 얘기 전하기 훨씬 수월하겠어요.";
			link.l1 = "어떤 배인지 절대 못 맞힐걸...";
			link.l1.go = "SharlieEpilog_Alonso_5";
			salary = GetSalaryForShip(PChar);
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;

		case "SharlieEpilog_Alonso_5":
			dialog.text = "안 알려주실 건가요, 선장님?";
			link.l1 = "피나스 '"+GetShipName("Ulysse")+"'호 말이야.";
			link.l1.go = "SharlieEpilog_Alonso_6";
		break;

		case "SharlieEpilog_Alonso_6":
			dialog.text = "설마... 우리가 처음 도착했던 그 배로 떠나는 거예요? 믿기지 않네요...";
			link.l1 = "바로 그 배야, "+npchar.name+"。어떻게 찾았는지는 나중에 얘기해줄게 — 선술집에서, 럼 마시면서. 지금은 할 일이 있어.";
			link.l1.go = "SharlieEpilog_Alonso_7";
		break;

		case "SharlieEpilog_Alonso_7":
			dialog.text = "알겠습니다, 선장님... 아아... 애들과 헤어지기 아쉬워요. 제겐 가족 같은 존재니까요. 그래도 어쩔 수 없네요...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alonso";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			AddDialogExitQuestFunction("SharlieEpilog_Alonso_exit");
		break;

		// эпилог <--
	}
} 