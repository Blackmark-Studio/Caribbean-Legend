// Слухи - диалог по типажам

#define MAX_RUMOURS_ABOUT_OWNERS 7

void ProcessCommonDialogRumors(ref NPChar, aref Link, aref NextDiag);
{
    string strum;
    string srum;
	bool bOk1, bOk2;
	switch(Dialog.CurrentNode)
	{
/////////////////////////////////////////////////---слухи мещанок---////////////////////////////////////////////
		case "rumours_towngirl":	
		NextDiag.CurrentNode = "rumours";
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "들었어? 토마스 모리슨의 딸이 벌써 여섯 달째 누워만 지낸다더라. 의사들도 그 병엔 완전히 속수무책이래. 중병도 고친다는 약초술로 유명한 집시 여인만이 도와줄 수 있다는데, 그 여자가 불쌍한 그 아가씨를 위해선 아무것도 안 하겠다고 딱 잘라 거절했다더군.";
			link.l1 = "감사합니다, 이제 가봐야겠소.";
			link.l1.go = "exit";
			DWH_Start();
			break;
        }
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "이틀 전에 항만장 나리를 노린 대담한 암살 시도가 있었대! 암살자는 사무실 문 앞에 숨어 있었는데, 항만장이 다행히 소리쳐 도움을 청했지. 머스킷총수가 급히 달려와 그 악당을 다치게 했지만, 그 자식은 결국 도시 문을 통해 도망쳤다네\n소문에 따르면 항만장 나리가 그 악당의 목에 큰 현상금을 걸었다더라! 하지만 아직까지 감히 나서겠다는 용감한 놈은 아무도 없대.";
			link.l1 = "감사합니다, 이만 물러가겠습니다.";
			link.l1.go = "exit";
			GS_Start();
			break;
        }
		//<-- Грани справедливости
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "소식 들었어?! 이건 완전 말도 안 돼! 선술집에 럼도 와인도 한 방울 안 남았어—이 더위에 대체 어떻게 버티라는 거야? 주점 주인은 술이 곧 다시 들어온다고 일주일째 빈말만 하고 있는데, 아무것도 없어! 우리보고 심판의 날까지 목말라 죽으란 거야?\n";
			link.l1 = "감사합니다, 이제 가봐야겠소.";
			link.l1.go = "exit";
			TPZ_Start();
			break;
        }
		//<-- Торговля по закону
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
		{
			dialog.text = "항구에선 주리 다르마냑, 총독의 조카가 예전의 생기 넘치던 모습은 온데간데없고 그저 그림자처럼 변했다고들 하더라. 한때는 빛나고 활기찼는데, 이제는 얼굴에 슬픔이 가득 새겨진 채 거리만 떠돈다고 해. 마을 사람들은 그녀에게 무슨 일이 있었는지 수군거리며 궁금해하지만, 아무도 진실은 모른다지. 혹시 어느 악당이 그녀의 마음을 짓밟은 걸까?"+GetSexPhrase(" 혹시 그게 당신이었나, 선장?","")+"";
			link.l1 = ""+GetSexPhrase("난 그럴 것 같지 않아 ","")+". 감사합니다, 이만 물러가야겠군요.";
			link.l1.go = "exit";
			UV_Start();
			break;
        }
		//<-- Украденное воспоминание
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "어부 피에르 카르노가 흔적도 없이 사라졌다는 소문이 돌고 있어. 이틀 전 새벽, 그는 바다로 나갔는데 그 뒤로 소식이 없어. 그의 아내 레아는 슬픔에 잠겨 정신을 못 차리고 있지. 낮에도, 등불 아래서도 부두에 앉아 끝없는 바다만 바라보며 사랑하는 이의 돛이 다시 보이길 기도하고 있어.";
			link.l1 = "감사합니다, 이만 물러가야겠군요.";
			link.l1.go = "exit";
			VPVL_Start();
			break;
        }
		//<-- В плену великого улова 
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "선장님, 들으셨소? 우리 선술집에 새로 일하는 여급이 있는데, 꽤 미인이라 하더이다. 사방에서 남정네들이 그녀 얼굴 한번 보려고 몰려들고 있소. 그런데 사흘 전부터 그녀가 일하러 나오지 않아서, 그녀 덕에 큰돈 벌던 선술집 주인이 무척 속상해했다더군. 그 주인이 누가 그 처자를 찾아오면 돈까지 내줄 생각이라 하오.​\n";
			link.l1 = "감사합니다, 이제 가봐야겠군요.";
			link.l1.go = "exit";
			TBP_Start();
			break;
        }
		//<-- Тайна Бетси Прайс
		//--> Оковы азарта
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein";
		if (bOk1 || bOk2)
        {
			dialog.text = "들었어? 우리 대장장이가 하비에르 카스티요랑 카드 치다가 완전히 털렸대. 너무 심하게 져서 아주 값진 걸 걸게 됐다더라. 그 뒤로 대장장이는 아직도 충격에서 못 벗어나서 새 주문도 안 받고, 그냥 제독이 자기 가죽을 벗길 거라며 한탄만 하고 있어. 불쌍한 놈, 이 동네 사람들은 다 알아. 그 사기꾼 카스티요랑은 절대 놀면 안 된다는 걸!";
			link.l1 = "고맙다, 이제 가봐야겠다.";
			link.l1.go = "exit";
			OZ_Start();
			break;
        }
		//<-- Оковы азарта
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "들었어? 'Águila'라는 플루트의 선장이 주점에서 자기 사관을 그렇게 호되게 혼냈다더라, 벽이 흔들릴 정도로 말이야! 알고 보니 선장은 밀물 때 출항할 생각이었는데, 사관이 선원 전부를 육지로 내보낸 거지. 그래서 지금 선원들이 마을 여기저기로 흩어졌고, 제시간에 안 돌아오면 배는 그냥 떠난다더라 – 선장은 절대 기다리지 않는대! 무슨 급한 일이라도 있나? 돈 되는 화물, 이득이 남는 거래, 아니면 총독이 시킨 급한 일?";
			link.l1 = "고맙다, 이제 가봐야겠다"+ GetSexPhrase("","") +".";
			link.l1.go = "exit";
			LFD_Start();
			break;
        }
		//<-- Письмо от покойника
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("towngirl", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        string posrep1, posrep2, answ1, answ2, answ3, answ4;
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Interesting! There is one more question I want to ask...","One more question.");
            answ3 = RandPhraseSimple("Well, anything can happen. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("아이고, 더 이상 할 말이 없으니, 길을 비켜 줘.","너 질문은 이제 지긋지긋해, 미안하지만, 나도 할 일이 아주 많거든."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("고마워, 이제 가봐야겠다.","잘 가라.");
		link.l2.go = "exit";
	break;

/////////////////////////////////////////////////---слухи мещан---////////////////////////////////////////////
	case "rumours_townman":	
		NextDiag.CurrentNode = "rumours";
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "들어봤어? 토마스 모리슨의 딸이 벌써 여섯 달째 누워만 지낸대. 의사들도 그 병에는 완전히 속수무책이래. 중병도 고친다는 약초로 유명한 집시 여인만이 도울 수 있다는데, 그 여자가 불쌍한 그 아가씨를 위해선 아무것도 안 하겠다고 딱 잘라 거절했대.";
			link.l1 = "감사합니다, 이제 가봐야겠소.";
			link.l1.go = "exit";
			DWH_Start();
			break;
        }
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "이틀 전에 항만장 나리의 목숨을 노린 대담한 시도가 있었대! 암살자는 사무실 문 앞에 숨어 있었지만, 항만장이 다행히 소리를 질러 도움을 청했지. 머스킷총병이 급히 달려와 그 악당을 다치게 했지만, 그 놈은 결국 성문 밖으로 도망쳤다더라.\n들리는 말로는 항만장 나리가 그 악당의 목에 걸린 현상금을 두둑이 내건다더군! 아직까지 그 놈을 잡으러 나선 용감한 놈은 없었지. 내 말인데, 아무리 천 두블론을 준다 해도... 내 목숨을 걸고 싶진 않다네.";
			link.l1 = "감사합니다, 이만 물러가겠습니다.";
			link.l1.go = "exit";
			GS_Start();
			break;
        }
		//<-- Грани справедливости
		
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "소식 들었어?! 완전 말도 안 돼! 선술집에 럼도 와인도 한 방울 안 남았다고—이런 지독한 더위에 어떻게 좀 쉬라고? 주점 주인은 술 다시 들어온다고 일주일째 빈말만 하고 있는데, 아무것도 없어! 우리더러 심판의 날까지 목이나 말리라는 거야?\n";
			link.l1 = "감사합니다, 이제 가봐야겠군요.";
			link.l1.go = "exit";
			TPZ_Start();
			break;
        }
		//<-- Торговля по закону
		
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "항구에선 주리 다르마냑, 총독의 조카가 예전의 모습은 온데간데없이 그저 그림자처럼 변했다는 소문이 돌고 있어. 한때는 빛나고 생기 넘쳤는데, 이제는 얼굴에 슬픔이 가득 새겨진 채 거리를 떠돈다고 하더라. 마을 사람들은 그녀에게 무슨 일이 있었는지 수군거리며 궁금해하지만, 아무도 진실은 모른대. 혹시 어떤 악당이 그녀의 마음을 아프게 한 건 아닐까?"+GetSexPhrase(" 혹시 그게 당신이었나, 선장?","")+"";
			link.l1 = ""+GetSexPhrase("난 그럴 것 같지 않아 ","")+". 고맙소, 이만 실례하겠소.";
			link.l1.go = "exit";
			UV_Start();
			break;
        }
		//<-- Украденное воспоминание
		
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "어부 피에르 카르노가 흔적도 없이 사라졌다는 소문이 돌고 있어. 이틀 전 새벽에 바다로 나갔는데, 그 뒤로 소식이 없어. 그의 아내 레아는 슬픔에 잠겨 정신을 못 차리고 있지. 낮에도 등불 아래서도 부두에 앉아, 끝없는 바다만 바라보며 사랑하는 이의 돛이 다시 보이길 기도하고 있대.";
			link.l1 = "고맙소, 이제 가봐야겠군.";
			link.l1.go = "exit";
			VPVL_Start();
			break;
        }
		//<-- В плену великого улова 
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "선장님, 들으셨소? 우리 선술집에 새로 일하는 여급이 있다오. 꽤 미인이라 하더이다. 사방에서 남정네들이 그녀 얼굴 한번 보려고 몰려들고 있다오. 그런데 사흘 전부터 일하러 안 나와서, 그녀 덕에 큰돈 벌던 선술집 주인이 무척 속상해했다오. 들으니, 그 주인이 그 아가씨를 찾아오는 사람에게 돈까지 준다더이다.​";
			link.l1 = "감사합니다, 이만 물러가야겠군요.";
			link.l1.go = "exit";
			TBP_Start();
			break;
        }
		//<-- Тайна Бетси Прайс
		//--> Оковы азарта
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein";
		if (bOk1 || bOk2)
        {
			dialog.text = "들었어? 우리 대장장이가 하비에르 카스티요랑 카드 내기를 했는데, 완전히 털려서 아주 값진 걸 걸게 됐대. 그 뒤로 대장장이는 회복도 못 하고 새 주문도 안 받고 있어 – 그냥 계속 제독이 자기 가죽을 벗길 거라고 한탄만 하지. 불쌍한 놈, 이 동네 사람들은 다 알아. 그 사기꾼 카스티요랑은 절대 내기하면 안 된다는 걸!";
			link.l1 = "고맙다, 이제 가봐야겠다.";
			link.l1.go = "exit";
			OZ_Start();
			break;
        }
		//<-- Оковы азарта
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "들었어? '아길라'라는 플루트의 선장이 선창에서 자기 사관을 그렇게 호되게 혼내서 벽이 다 흔들릴 정도였대! 알고 보니 선장은 조수와 함께 밀물에 맞춰 출항하려고 했는데, 그 사관이 선원 전부를 육지로 내보낸 거야. 그래서 지금 선원들이 마을 여기저기 흩어져 있고, 제시간에 안 돌아오면 배는 그냥 떠난다더라 – 선장은 절대 기다려주지 않을 거래! 대체 왜 이렇게 급한 걸까? 돈 되는 화물이라도 실었나, 이득 볼 만한 거래가 있나, 아니면 총독한테서 급한 임무라도 받은 건가?\n";
			link.l1 = "고맙다, 이제 가봐야겠다"+ GetSexPhrase("","") +".";
			link.l1.go = "exit";
			LFD_Start();
			break;
        }
		//<-- Письмо от покойника
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Interesting! There is one more question I want to ask...","One more question.");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("아이고, 더 이상 할 말 없어. 지나가게 해 줘.","네 질문은 이제 지겹다, 실례하지만, 나한텐 처리해야 할 일이 아주 많거든."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("고마워, 이제 가봐야겠어.","잘 가라.");
		link.l2.go = "exit";
	break;
	
	///////////////////////////////////---слухи тёмных личностей---////////////////////////////////////////////
	case "rumours_marginal":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("안타깝지만 더 할 말이 없어, 지나가게 해 줘.","네 질문은 이제 지긋지긋해, 미안하지만, 나도 할 일이 아주 많거든."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("고마워, 나 가볼게.","잘 가라.");
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---слухи дворян---////////////////////////////////////////////
	case "rumours_nobleman":	
        srum = SelectRumourEx("nobleman", NPChar);
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
			if (bOk1 || bOk2){
				
			dialog.text = "항구에서 들리는 소문인데, 총독의 조카 줄리 다르마냑이 예전의 모습과는 딴판이 되었다더군. 한때는 빛나고 생기 넘쳤는데, 이제는 얼굴에 슬픔이 가득한 채 거리를 떠돈다고 해. 마을 사람들은 그녀에게 무슨 일이 있었는지 수군거리며 궁금해하지만, 아무도 진짜 사정은 모른다지. 혹시 어떤 악당이 그녀의 마음을 아프게 한 건 아닐까?"+GetSexPhrase(" 혹시 그게 당신이었나, 선장?","")+"";
			link.l1 = ""+GetSexPhrase("난 그럴 것 같지 않은데 ","")+". 고맙소, 이제 가봐야겠군.";
			link.l1.go = "exit";
			UV_Start();
			break;
        }
		//<-- Украденное воспоминание
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("내 말이 충분히 전달됐으리라 믿네 - 난 더 할 말 없어.","너 질문은 이제 지겹다, 선장. 딴 데 가서 할 일이나 찾아봐!"),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("고맙다, 이만 가봐야겠다.","잘 가라.");
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---слухи дворянок---////////////////////////////////////////////
	case "rumours_noblegirl":	
        srum = SelectRumourEx("noblegirl", NPChar);
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "항구에선 주인들이 줄리 다르마냑, 총독의 조카가 예전과는 딴사람이 됐다고들 하더군. 한때는 빛나고 생기 넘치던 처자가, 이제는 거리에서 슬픔이 얼굴에 가득한 채 떠돌고 있지. 마을 사람들은 도대체 무슨 일이 있었는지 수군거리지만, 진짜 사연은 아무도 몰라. 어쩌면 누가 그녀의 마음을 산산조각 냈는지도 모르지?"+GetSexPhrase(" 혹시 그게 당신이었나, 선장?","")+"";
			link.l1 = ""+GetSexPhrase("의심스러운데\n ","")+". 고맙소, 이만 실례하겠소.";
			link.l1.go = "exit";
			UV_Start();
			break;
        }
		//<-- Украденное воспоминание
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("내 말이 충분히 전달됐으리라 믿네 - 난 더 할 말 없네.","네 질문은 이제 지겹다, 선장. 딴 일이나 찾아서 해!"),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("고맙소, 이제 가봐야겠군.","잘 가라.");
		link.l2.go = "exit";
	break;
	
	///////////////////////////////////////////---слухи матросов---////////////////////////////////////////////
	case "rumours_sailor":	
		NextDiag.CurrentNode = "rumours";

		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "이틀 전에 항만장 나리의 목숨을 노린 대담한 시도가 있었대! 그 암살자는 사무실 문 앞에서 숨어 기다렸지만, 항만장 나리가 다행히 도움을 청했지. 머스킷총병이 급히 달려와 그 악당을 다치게 했지만, 그 자식은 결국 성문 밖으로 도망쳤다네\n소문에 따르면 항만장 나리가 그 악당의 목에 걸린 현상금을 두둑이 내걸었다더군! 아직까지 감히 나서는 놈은 없었지. 알겠나, 아무리 천 더블룬을 준다 해도... 난 안 할 거야...";
			link.l1 = "감사합니다, 이만 물러가야겠군요.";
			link.l1.go = "exit";
			GS_Start();
			break;
        }
		//<-- Грани справедливости
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "들었어? '아길라'라는 플루트의 선장이 선창에서 자기 사관을 그렇게 호되게 혼내서 벽이 다 흔들릴 정도였대! 알고 보니 선장은 조수 때 출항할 계획이었는데, 사관이 선원 전부를 육지로 내보낸 거야. 이제 선원들은 마을 여기저기로 흩어졌고, 제때 안 돌아오면 배는 그냥 떠난다더라 – 선장은 기다릴 생각이 없대! 대체 왜 이렇게 급한 걸까? 돈 되는 화물이라도 실었나, 이득이 남는 거래가 있나, 아니면 총독이 급한 심부름을 시킨 건가?";
			link.l1 = "고맙다, 이제 가봐야겠다"+ GetSexPhrase("","") +".";
			link.l1.go = "exit";
			LFD_Start();
			break;
        }
		//<-- Письмо от покойника
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2) srum = SelectRumourEx("sailor", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("안타깝게도 더 할 말이 없어, 지나가게 해 줘.","네 질문은 이제 지겹다. 미안한데, 나도 할 일이 많거든."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("고맙소, 이제 가봐야겠군.","잘 가라.");
		link.l2.go = "exit";
	break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		//-->работорговец
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = "(노래) 우린 악당이고 개구쟁이, 악인이며 사기꾼이지; 마셔라, 친구들아, 요호! 우린 악마고 말썽꾸러기, 정말 못된 놈들이야, 마셔라, 친구들아, 요호!! 이봐, 친구, 잘 지내냐? 바다는 어때?";
            link.l1 = "바다? 여전한 계집이지. 짜고 젖어 있잖아. 그런데 내 친구 못 봤어? 얼마 전에 여기서 방을 빌렸던 녀석 말이야. 이름이 프랑수아 곤티에였어.";
            link.l1.go = "Jamaica_ratH_1";
			break;
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "(노래) 예쁜 아가씨야, 나랑 같이 갈래? 예쁜 아가씨야, 내 곁에 누워줄래? 아침이 되면 네 리본을 다 감아줄게, 내가 떠나기 전에!";
            link.l1 = "한잔 해, 친구! 바다는 어때?";
            link.l1.go = "EscapeSlave_Villemstad_H1";
			break;
        }
		//<--работорговец
				
		//Голландский Гамбит, против всех
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "LetterToLucasSent" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "에이, 바다야... 나도 네 자리에 있었으면 좋겠어!";
            link.l1 = "문제 없어, 친구. 언제든 내 선원으로 들어와.";
            link.l1.go = "Lucas_Tavern";
			break;
        }
		//Голландский Гамбит
		
		//--> поиск дезертира
		if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE && !CheckAttribute(npchar, "quest.fugitive"))
        {
			dialog.text = LinkRandPhrase("있잖아, 럼주만 있으면 남자들은 다 친구가 된다니까! 하하!","럼 한 잔만 제대로 마시면 교수형 집행인도 예뻐 보일걸! 하하!","술 마시면 자고, 자면 죄 안 짓지! 럼주랑 에일이 천국으로 데려다줄 거야, 그러니까 마셔, 젠장! 하!");
            link.l1 = "그래, 한잔하자... 이봐, 좋은 사람, 혹시 알아? "+pchar.GenQuest.FindFugitive.Name+"? 그는 내 오랜 동료야. 몇몇 녀석들이 여기로 이사 왔다고 하더군...";
            link.l1.go = "FindFugitiveHb";
			break;
        }
		//<-- поиск дезертира
		
		//--> карибские нравы
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && npchar.location == "Portobello_tavern")
		{
			dialog.text = "뉴스? 하! 아직 못 들었어? 우리 군인들이 프랑스 첩자를 잡았대. 피 묻은 사기꾼이 상인인 척했지, 근데 *딸꾹*... 우리 지휘관은 만만한 놈이 아니거든!";
            link.l1 = "정말이야! 그런데 그 프랑스 놈이 뭘 캐내려고 했는데?";
            link.l1.go = "trial_spy";
			break;
		}
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = "에, "+GetAddress_Form(pchar)+" 우리가 사는 세상 참 기가 막히지... 주위엔 개같은 놈들뿐이야!";
			link.l1 = "무슨 소리야?";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
			break;
		}
		//<-- карибские нравы
		
		//--> Sinistra Длинные тени старых грехов
		if (CheckAttribute(pchar, "questTemp.DTSG_NightIskat") && npchar.city == "SentJons")
        {
			dialog.text = "들었어?! 믿을 수가 없어! 그 유명한 플리트우드 선장이 런던에서 잔인하게 살해당했다더라! 영광을 쫓아 모든 걸 가졌지만 결국 죽음만 남았지... 여기 남아 있었으면 더 안전했을 텐데. 내 말 들어, 가끔은 돈이나 지위를 쫓기보단 가진 걸 소중히 여기는 게 낫다니까, 나리!";
            link.l1 = "이봐, 자네는 이 식민지에 누가 어디 사는지 다 알지?";
            link.l1.go = "DTSG_NightIskat";
			break;
        }
		//<-- Длинные тени старых грехов
		
		//--> Rebbebion, квест "Путеводная звезда"
		if (CheckAttribute(pchar, "questTemp.PZ_Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.PZ_Sotta") && !CheckAttribute(npchar, "questTemp.PZ_Lutter") && npchar.city == "Beliz")
		{
			link.l1 = "그래서 오늘의 영웅, 에드가르도 소타 선장. 사람들이 그에 대해 뭐라고들 하던가? 그리고 자네 생각은 어때? 난 그 사람을 만나기를 고대하고 있었지.";
			link.l1.go = "Sotta1";
			link.l2 = "이봐, 왜 혼자 술 마시고 있냐? 다들 지금 바람쟁이 맷 교수형 보려고 모이고 있는데.";
			link.l2.go = "Lutter1";
			break;
		}
		
		if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(pchar, "questTemp.PZ.TortugaHabitueBlock") && npchar.city == "Tortuga")
		{
			link.l1 = "이봐, 친구, 나 조에프 판 데르 빈크라는 사람을 찾고 있었어. 그에게 전할 메시지가 있거든. 혹시 그 사람이 어떻게 생겼는지나 뭔가 아는 거 있어?";
			link.l1.go = "Sepp1";
			break;
		}
		//<-- квест "Путеводная звезда"
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "들어봤어? 토마스 모리슨의 딸이 벌써 여섯 달째 누워만 지낸대. 의사들도 그 병에는 완전히 속수무책이래. 중병도 고친다는 약초술로 유명한 집시 여인만이 도와줄 수 있다던데, 그 여자가 불쌍한 그 아가씨를 위해선 아무것도 해주지 않겠다고 딱 잘라 거절했다더라.";
			link.l1 = RandPhraseSimple(RandSwear()+"이건 한 잔 더 마실 만하군...","좋아, 한 잔 더 하자.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("고맙다, 이만 가봐야겠다.","에이, 이 럼 진짜 끝내주네. 좋아, 난 가봐야겠다, 여기서 잘 놀아.");
			link.l2.go = "exit_sit";
			DWH_Start();
		break;
		}
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "이틀 전에 항만장 나리의 목숨을 노린 대담한 시도가 있었대! 암살자는 사무실 문 앞에서 숨어 기다렸지만, 항만장이 소리를 질러 도움을 청했지. 머스킷총병이 급히 달려와 그 악당을 다치게 했지만, 그 놈은 결국 성문 밖으로 도망쳤다더군.\n소문에 따르면 항만장 나리가 그 악당의 목에 걸린 현상금을 두둑이 내건다더라! 아직까지 그 놈을 잡겠다고 나선 용감한 자는 없었지. 아무리 천 두블론을 준다 해도, 내 목숨 걸 생각은 없어...";
			link.l1 = RandPhraseSimple(RandSwear()+"이건 한 잔 더 할 만하지...","좋아, 한 잔 더 하자.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("고마워, 이제 가봐야겠어.","에이, 이 럼 진짜 끝내주네. 좋아, 난 가야겠다, 여기서 잘 놀아.");
			link.l2.go = "exit_sit";
			GS_Start();
			break;
        }
		//<-- Грани справедливости
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "소식 들었어?! 이건 완전 말도 안 돼! 선술집에 럼도 와인도 한 방울 안 남았어—이런 지독한 더위에 어떻게 좀 쉬라고? 주점 주인은 술이 곧 다시 들어온다고 일주일째 헛소리만 해대는데, 아무것도 없어! 우리가 심판의 날까지 목말라 죽으란 거야?";
			link.l1 = RandPhraseSimple(RandSwear()+"이건 한 잔 더 할 만한 얘기지...","좋아, 한 잔 더 하자.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("고맙소, 이제 가봐야겠군.","에이, 이 럼 진짜 끝내주네. 좋아, 난 가봐야겠다, 여기서 잘 놀아.");
			link.l2.go = "exit_sit";
			TPZ_Start();
			break;
        }
		//<-- Торговля по закону
		//--> Старые счёты
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		if (bOk1 || bOk2)
        {
			dialog.text = "부두에서 들리는 소문인데, 우리 술집 주인이 큰일 났대! 누가 그의 진을 훔쳐갔거든! 그냥 한 병이 아니라 통째로 한 통을 통째로 말이야 - 이 섬들 어디에서도 구할 수 없는 귀한 거라지! 유럽에서 멀리 실어왔다더라. 그 늙은 여우가 누구를 위해 보관하고 있었는지는 절대 말 안 하지만, 한 가지는 확실해. 그 술통이 곧 돌아오지 않으면, 불쌍한 놈한테 무슨 일이 닥칠지 모른다니까!\n";
			link.l1 = RandPhraseSimple(RandSwear()+"이건 한 잔 더 할 만하군...","좋아, 한 잔 더 하자.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("고맙다, 난 이만 가봐야겠다.","에이, 이 럼 진짜 죽이네. 좋아, 난 가야겠다, 여기서 잘 놀아.");
			link.l2.go = "exit_sit";
			OS_Start();
			break;
        }
		//<-- Старые счёты
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "항구에서 도는 소문에 따르면, 총독의 조카 줄리 다르마냑이 예전의 활기를 잃고 그저 그림자처럼 변했다고 하더군. 한때는 빛나고 생기 넘쳤는데, 이제는 거리마다 슬픔이 얼굴에 선명하게 새겨진 채 떠돌고 있지. 마을 사람들은 무슨 일이 있었는지 수군거리며 궁금해하지만, 진실을 아는 이는 아무도 없어. 혹시 어떤 악당이 그녀의 마음을 아프게 한 건 아닐까?\n"+GetSexPhrase(" 혹시 그게 당신이었나, 선장?","")+"";
			link.l1 = RandPhraseSimple(RandSwear()+"이건 한 잔 더 마실 만한 얘기지...","좋아, 한 잔 더 하자.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("고맙다, 이제 가봐야겠다.","에이, 이 럼 진짜 끝내주네. 좋아, 난 가야겠다, 여기서 잘 놀아.");
			link.l2.go = "exit_sit";
			UV_Start();
			break;
        }
		//<-- Украденное воспоминание
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "어부 피에르 카르노가 흔적도 없이 사라졌다는 소문이 있어. 이틀 전 새벽에 바다로 나갔는데, 그 뒤로 소식이 없어. 그의 아내 레아는 슬픔에 잠겨 정신을 못 차리고 있지. 낮에도 밤에도 부두에서 등불을 켜고 지키며, 끝없는 바다만 바라보면서 사랑하는 남편의 돛이 다시 보이길 기도하고 있대.";
			link.l1 = RandPhraseSimple(RandSwear()+"이건 한 잔 더 할 만한 얘기지...","좋아, 한 잔 더 하자.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("고마워, 이제 가봐야겠다.","에이, 이 럼 진짜 끝내주네. 좋아, 난 가야겠다, 여기서 잘 놀아.");
			link.l2.go = "exit_sit";
			VPVL_Start();
			break;
        }
		//<-- В плену великого улова
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "선장님, 들으셨소? 우리 선술집에 새로 온 여급이 있다는데, 꽤 미인이라 하더이다. 사방에서 남정네들이 그녀 한 번 보려고 몰려들고 있소. 그런데 사흘 전부터 일하러 나오지 않아서, 그녀 덕에 큰돈 벌던 선술집 주인이 무척 속상해했다더군. 그 주인이 지금은 그 아가씨를 찾아주는 사람에게 돈까지 내겠다고 한다오.​\n";
			link.l1 = RandPhraseSimple(RandSwear()+"이건 한 잔 더 마실 만한 얘기지...","좋아, 한 잔 더 하자.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("고마워, 난 가봐야겠어.","에이, 이 럼 진짜 끝내주네. 좋아, 난 가야겠다. 여기서 잘 놀아.");
			link.l2.go = "exit_sit";
			TBP_Start();
			break;
        }
		//<-- Тайна Бетси Прайс
		//--> Оковы азарта
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein";
		if (bOk1 || bOk2)
        {
			dialog.text = "들었어? 우리 대장장이가 하비에르 카스티요랑 카드 내기를 했다가 완전히 털렸대. 너무 심하게 져서 아주 값진 걸 걸 수밖에 없었지. 그 뒤로 대장장이는 아직도 충격에서 못 벗어나고 새 주문도 안 받고 있어 – 그냥 제독이 자기 가죽을 벗길 거라며 한탄만 하고 있지. 불쌍한 놈, 이 동네 사람들은 다 알아. 그 사기꾼 카스티요랑은 절대 놀면 안 된다는 걸!";
			link.l1 = RandPhraseSimple(RandSwear()+"이건 한 잔 더 마실 가치가 있지...","좋아, 한 잔 더 하자.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("고마워, 난 이만 가봐야겠어.","에이, 이 럼주 끝내주네. 좋아, 난 가봐야겠다, 여기서 잘 놀아.");
			link.l2.go = "exit_sit";
			OZ_Start();
			break;
        }
		//<-- Оковы азарта
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "들었어? 'Águila'라는 플루트의 선장이 선창에서 자기 사관을 그렇게 호되게 혼내서 벽이 다 흔들릴 정도였대! 알고 보니 선장은 조수 때 출항할 생각이었는데, 사관이 선원 전부를 육지로 내보냈다는 거야. 그래서 지금 선원들이 마을 여기저기로 흩어졌고, 제때 안 돌아오면 배는 그냥 떠난다더라 – 선장은 기다릴 생각이 없대! 무슨 급한 일이라도 있나? 돈 되는 화물, 이득 볼 장사, 아니면 총독이 시킨 급한 일이라도?";
			link.l1 = RandPhraseSimple(RandSwear()+"이건 한 잔 더 마실 만한 얘기지...","좋아, 한 잔 더 하자.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("고마워, 난 이만 가볼게.","에이, 이 럼 진짜 죽이네. 좋아, 난 가야겠다, 여기서 잘 놀아.");
			link.l2.go = "exit_sit";
			LFD_Start();
			break;
        }
		//<-- Письмо от покойника
		//--> LaEspadaDelRey
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LEDR_Start") && npchar.city == "Pirates";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LEDR_Start") && npchar.city == "Pirates";
		if (bOk1 || bOk2)
        {
			dialog.text = "그 얘기 들었어, "+GetSexPhrase("동료","아가씨")+"? 야, 이 마을에 미친 노인네가 돌아다니고 있거든. 사부-마틸라 만에 처박혀 있는 그 썩은 배에서 살아나온 건 자기 혼자뿐이라고 주장하면서, 이제는 거기로 다시 돌아가려고 안달이야. 근데 겁쟁이라 혼자서는 못 간대. 매일 아침마다 부족 옷 입은 해골이 나타나서 죽을 때까지 싸운다고 계속 중얼거린다니까. 나? *딸꾹* 오백 두블론을 준다 해도 그 노인네랑 같이 안 갈 거야. 저 바보 머릿속에 무슨 귀신이 춤추고 있을지 누가 알겠냐.";
			link.l1 = RandPhraseSimple(RandSwear()+"이건 한 잔 더 마실 만한 얘기지...","좋아, 한 잔 더 하자.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("고맙다, 이제 가봐야겠다.","에이, 이 럼 진짜 끝내주네. 좋아, 난 가야겠다, 여기서 잘 놀아.");
			link.l2.go = "exit_sit";
			LEDR_Start();
			break;
        }
		//<-- LaEspadaDelRey
		
		Dialog.Text = LinkRandPhrase("음... 헉! ","아, 좋은 럼이군! ","음... ")+SelectRumourEx("단골",NPChar);
		link.l1 = RandPhraseSimple(RandSwear()+"이건 한 잔 더 마실 만한 얘기지...","좋아, 한 잔 더 하자.");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("고맙다, 이만 가볼게.","에이, 이 럼 진짜 죽이네. 좋아, 난 가야겠다, 여기서 잘 놀아.");
		link.l2.go = "exit_sit";
	break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
			Dialog.Text = NPCStringReactionRepeat(strum,strum+" 그래. 더 할 말 없어.",strum+" 이제 본론으로 돌아가야겠군.",RandPhraseSimple("이미 말했잖아, 쓸데없는 잡담할 시간 없어!","나는 바쁜 사람이야, 쓸데없는 소문 들을 시간 없어!"),"block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear()+"재밌네! 하지만 본론으로 들어가자","감사합니다, 그리고 한 가지 더 있습니다."),pcharrepphrase(""+GetSexPhrase("젠장","Interesting")+"! 이야기 잘하네. 그런데 나 한 가지 더 물어볼 게 있어.","더 이상 시간 낭비하지 말고 본론이나 얘기하자."),pcharrepphrase(RandSwear()+" 한 가지만 더 말하고 난 갈게.","맞아, 시간은 돈이지."),pcharrepphrase("맨날 자기 이익만 생각하지! 좋아, 정신만은 놓지 마라.","용서해라. 이제 거래 얘기나 하자."),npchar,Dialog.CurrentNode);
			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("잘 가라, 이 늙은 주정뱅이.","잘 가, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("카람바! 너무 멀리 가지 마. 금방 돌아올게.","만나서 반갑군, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"! 잘 가라!")),NPCharRepPhrase(npchar,pcharrepphrase("출항하라!","잘 가라!"),pcharrepphrase("이봐! 거기 뭐 숨기고 있는 거야? 럼주? 아니라고? 뭐, 어차피 내가 알아서 한 잔 마실 거야.","미안하지만, 도시에 중요한 일이 있어.")),NPCharRepPhrase(npchar,pcharrepphrase("헤헷! 또 보자!","나 가봐야겠다. 잘 있어, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("나한테 감히 따지지 마! 나 이런 거 원하지도 않아!","내 배 좀 확인해야겠군. 나중에 보자, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("왜 그래, 친구? 나야 - "+GetFullName(pchar)+"! 좀 자 둬, 나중에 얘기하지.","내가 다시 여기 올 때쯤이면 네 간이 널 먼저 죽일까 두렵구나."),pcharrepphrase("은화 잘 챙겨둬라, 교활한 놈! 나중에 보자.","만나서 반갑군, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("선장",NPChar);
			Link.l1 = RandPhraseSimple(RandSwear()+"흥미롭군! 한 가지 더 묻고 싶은 게 있어...","질문 하나만 더.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("고마워, 이제 가봐야겠어.","잘 가라.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
		
		 case "rumours_landcaptain":
			Dialog.Text = SelectRumourEx("육지 선장",NPChar);
			Link.l1 = RandPhraseSimple(RandSwear()+"재미있군! 한 가지 더 묻고 싶은 게 있어...","질문 하나만 더.");
			Link.l1.go = "question";
			Link.l2 = RandPhraseSimple("고맙다, 이만 가봐야겠다.","잘 가라.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "question";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06
				if(startHeroType == 4)
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("값은 알잖아. 정보도 방이나 음식, 술처럼 값이 있어. 천 페소 내야 해.","값은 알잖아. 정보도 방이나 음식, 술처럼 돈이 들어. 천 페소 내야 해.","값은 알잖아. 정보도 방이나 음식, 술처럼 돈이 들어. 천 페소야."),"여기서 더 할 말은 없어. 이제 실례, 난 가봐야겠어.","","","block",1,npchar,Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple("사실, 내가 왜 이걸 묻고 있는 거지? 다른 사람한테 물어보면 되잖아. 귀찮게 해서 미안해.","사실, 내가 왜 이걸 묻고 있는 거지? 다른 사람한테 물어보면 되잖아. 괜히 귀찮게 해서 미안해."),"","","",npchar,Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000)
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("알고 있지. 자, 내 보수야.","알고 있지. 자, 내 돈이야."),"","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 = HeroStringReactionRepeat("나는 그런 돈 없어.","","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
				}
				else
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("정보는 돈이 드는 법이지. 1000페소만 주면 내가 아는 건 전부 말해주지.","내 기억에 뭔가 문제가 있는데, 1,000에이트만 주면 뭔가 생각날지도 모르겠군.","너에게 정보를 알려주고 싶지. 하지만 1000에이트는 내야 해. 흥정은 없어."),"여기 더 할 말 없어. 이제 실례하겠소, 가봐야 하니까.","","","block",1,npchar,Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear()+"쓸데없는 잡담에 돈 안 낸다.","이 돈을 더 잘 쓸 방법을 생각해 볼게."),"화제를 바꾸자.","화제를 바꾸자.","화제를 바꾸자.",npchar,Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000 )
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("내가 너한테서 쓸만한 정보를 얻으면 그것들을 주지.","가치 있는 걸 주면 내가 돈을 내지."),"","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 = HeroStringReactionRepeat("나는 그런 돈 없어.","","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
				}

		break;
		
		case "rumours_tavern_yes":
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation"))
			{
				bool bOk = (pchar.questTemp.Saga.BarbTemptation == "silk") || (pchar.questTemp.Saga.BarbTemptation == "give_silk");
				if (bOk && npchar.location == "Marigo_tavern" && !CheckAttribute(npchar, "quest.barbtemptation"))
				{
					AddMoneyToCharacter(pchar, -1000);
					Dialog.Text = "우리 순찰대가 최근에 모렐이라는 프랑스 밀수업자의 브리건틴을 격침시켰어. 그 자는 지금 감옥에 갇혀서 사형을 기다리고 있지. 우리 사령관은 그놈 배에 화물이 다 실려 있지 않았다고 생각해서 아직도 그걸 찾으려고 애쓰고 있어... 사령관이 잃어버린 화물을 찾으면 그 프랑스놈은 죽게 될 거야.";
					link.l1 = "흥미롭군... 좋아, 돈 가져가. 더 할 말 있어?";
					link.l1.go = "rumours_tavern";
					Saga_CreateMorelle(); //ставим Мореля
					npchar.quest.barbtemptation = "true";
					pchar.questTemp.Saga.BarbTemptation.Prison = "true";
					break;
				}
			}	
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && npchar.location == "portobello_tavern")
			{
				DelLandQuestMark(npchar);
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "총독 관저에서 큰 연회가 열렸지. 각하의 친구인 돈 카를로스 데 밀리야르가 돌아왔거든. 바다 전투에서 포로가 됐었는데, 프랑스 중위의 도움으로 탈출했다더라. 돈 카를로스는 머리도 좋지만, 아주 인심도 후하신 분이야. 그 덕에 그 중위, 장 드노는 이제 '사리오'의 선장이 됐지. 내가 듣기로는 작은 플랜테이션도 선물 받았다더라. 이제 그 개구리 먹는 놈을 후안이라고 부른대! 참 기막힌 이야기지!";
				link.l1 = "흥미롭군... 좋아, 돈은 네 거다. 이거 가져가라. 더 할 말 있냐?";
				link.l1.go = "rumours_tavern";
				pchar.questTemp.FMQG = "headhunter_juan";
				AddQuestRecord("FMQ_Guadeloupe", "10");
				pchar.quest.FMQG_Juanship.win_condition.l1 = "location";
				pchar.quest.FMQG_Juanship.win_condition.l1.location = "PortoBello";
				pchar.quest.FMQG_Juanship.function = "FMQG_CreateJuanship";
				break;
			}	
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "town" && npchar.location == "Marigo_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "우리 지휘관이 정글을 순찰할 병력을 추가로 보내고, 마을 경비도 늘렸대. 필립스버그에 영국놈들이 침투해서 잡혀 있는 장교들을 풀어주려고 한다는 소문이 돌아.";
				link.l1 = "정말이야! 감히 그런 짓을 저지른다고? 그런데 대체 어떤 장교들 얘기야?";
				link.l1.go = "FMQN_r";
				break;
			}	
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && npchar.location == "Havana_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "얼마 전 온 마을이 벌집 쑤셔놓은 것처럼 뒤집혔지. 군함 소속 장교 하나가 내 선술집에서 만취해서, 유부녀를 거의 겁탈할 뻔했거든. 그 여자를 지키려던 남편을 두들겨 패고, 심지어 칼까지 휘두르며 위협했어. 그것도 마을 경비대 바로 앞에서 말이야! 세상 참, 힘 있는 놈이 이기는 거지 뭐. 군인들은 그 자식이 날뛰는 동안 그냥 못 본 척 고개 돌리더라고\n그런데 말이지, 누가 상상이나 했겠어, 상선 선원 몇 명이 그 악당을 무장 해제시켰다니까. 거의 포박까지 할 뻔했는데, 그 자식이 간신히 도망쳐서 자기 배에 숨었지. 사령관이랑 알칼데는 이 사건을 덮으려고 했지만, 분노한 남편이 마을에서 존경받는 시민이라, 각하 도니에고 데 톨레도에게 직접 호소해서 지역 신사들 사이에 소문이 쫙 퍼졌어\n결국 그 장교 체포 영장이 발부됐지. 그 자식 선장이랑 함께 항구를 떠나 다른 곳으로 보내라는 조언이 있었다는 소문도 돌았고. 하지만 스쿠너 선장 에스베르도 카바냐스는 명예로운 사람이야. 자기 부하가 무슨 짓을 했는지 알자마자 바로 체포해서 육지로 넘겼거든. 그 자식은 당분간 감옥에서 썩게 생겼지, 내 생각엔 거기가 딱 제자리야. 아마 나중엔 평졸병으로 강등당하고, 본보기로 매질까지 당할지도 몰라.";
				link.l1 = "잠깐, 에스베르도 카바냐스 선장이라고 했어? 허... 정말 흥미진진한 이야기구만! 좋아, 네 돈값은 했으니 여기 있다. 또 해줄 말 있나?";
				link.l1.go = "rumours_tavern";
				Mtraxx_CreateOfficer(); // ставим офицера-негодяя
				pchar.questTemp.Mtraxx = "jewelry_4";
				pchar.GenQuest.PrisonQuestLock = "true";
				AddQuestRecord("Roger_1", "7");
				DelLandQuestMark(characterFromId("Havana_tavernkeeper"));
				AddLandQuestMarkToPhantom("havana_prison", "havanaJailOff");
				break;
			}
			// Jason Исла Мона
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "rumours" && rand(2) == 1)
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "어떤 범죄자들이 무인도 중 하나에 버려졌다고 하더라! 얼마나 악랄한 놈들인지, 형리도 신부들도 감히 손을 못 댔다나 봐! 근데 왜 그런 놈들을 맨날 여기로 데려오는 거지?!\n";
				link.l1 = "흠... 재밌는걸! 내가 직접 쫓아가서 그놈들을 내 사람으로 만들어볼까? 절박한 놈들은 언제나 필요하거든... 왜 그렇게 창백해, 친구? 농담이야, 농담... 네 돈은 벌었으니, 여기 받아. 또 들은 소식이라도 있나?\n";
				link.l1.go = "rumours_tavern";
				IslaMona_TerksCreateHimenes();
				break;
			}
			// Гаспар во фриплее 
			if ((SandBoxMode) && npchar.city == "Tortuga" && (sti(pchar.reputation.nobility) < 41))
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "당신의 명성은 이미 자자하군요, 선장님. 자잘한 장신구나 반짝이는 돌들을 어디에 팔아야 할지 고민한 적이 많았겠죠...";
				link.l1 = "그런 걸 도와줄 수 있는 사람을 아는가?";
				link.l1.go = "About_Gaspar";
				break;
			}
            string RumText = SelectRumourEx("tavern", NPChar); //fix
			
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; //fix
				if(startHeroType == 4)
				{
					link.l1 = "결국 너 아무것도 모르는 거였군. 이렇게 날 속일 줄은 몰랐어. 영 똑똑하지도 않네. 뭐, 잘 가라.";
				}
				else
				{
					link.l1 = RandPhraseSimple("쓸모없는 쓰레기군. 한 푼도 안 줄 거야! 잘 가라.","네 정보는 쓸모없으니, 아무것도 못 받아.");
				}
			    link.l1.go = "Exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                AddMoneyToCharacter(pchar, -1000);
                Dialog.Text = RumText;
				if(startHeroType == 4)
				{
					link.l1 = "정말이야? 흥미롭네, 고마워. 자, 난 이만 가봐야겠다. 다음에 보자.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = RandPhraseSimple("고맙다, 돈 가져가라. 더 할 말 있냐?","좋아, 돈 가져가. 더 할 말 있어?");
					link.l1.go = "rumours_tavern";
				}
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;

		case "rumours_tavern_no":
			if(startHeroType == 4)
			{
				Dialog.Text = "동전 좀 보탤 수도 있었잖아. 너랑 달리, 헬렌, 난 해적단 남작이 뒤를 봐주지 않거든.";
				link.l1 = "너는 온전한 가게를 가졌잖아. 나는 내 힘으로 여기까지 왔지. 뭐, 배랑 대포, 선원, 그리고 남작이 준 보급품만 빼면 말이야. 알았어, 됐다.";
				link.l1.go = "exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
			else
			{
				Dialog.Text = "오해하지 마, 나도 가족 먹여 살려야 하거든.";
				link.l1 = "화제를 바꾸자.";
				link.l1.go = "first time";
				NextDiag.CurrentNode = NextDiag.TempNode;
				link.l2 = LinkRandPhrase("고맙소, 이제 가봐야겠군.","잘 가라.","잘 가.");
				link.l2.go = "Exit";
			}
		break;	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("가난한",NPChar);
				Link.l1 = RandPhraseSimple(RandSwear()+"흥미롭군. 한 가지만 더 물어보지...","음, 다른 걸 좀 물어보자...");
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple("그래, 잘 가라.","잘 가라, 친구.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("내가 아는 건 다 말했어.","더 이상 할 말 없어, 미안해...");
				Link.l1 = RandPhraseSimple("알겠어. 잘 가.","잘 가라, 친구...");
				Link.l1.go = "exit";			
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("가난한",NPChar);
				Link.l1 = RandPhraseSimple(RandSwear()+"흥미롭군. 질문 하나만 더 하자...","음, 다른 걸 좀 물어보자...");
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple("그래, 잘 가라.","잘 가라, 친구.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("내가 아는 건 다 말했어.","더 이상 할 말 없어, 미안해...");
				Link.l1 = RandPhraseSimple("알겠어. 잘 가.","알겠어. 잘 가라, 친구...");
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC",NPChar);
				Link.l1 = RandPhraseSimple("알겠어...","그렇군...");
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else  
			{
				Dialog.Text = NPCharSexPhrase(npchar,RandPhraseSimple("내가 아는 건 다 말했어.","새로운 소문은 못 들었어, 미안해..."),RandPhraseSimple("내가 아는 건 다 말했어.","미안하지만, 새로운 소문은 못 들었어..."));
				Link.l1 = RandPhraseSimple("알겠어, 그럼 잘 가.","알겠소. 안녕히 가시오.");
				Link.l1.go = "exit";			
			}
		break;
		
//Jason -------------слухи смотрителей маяков, идентичны таверне, но бесплатны, по 1 шт за день--------------------
		case "rumours_lighthouse": 
			Dialog.Text = NPCStringReactionRepeat(RandPhraseSimple("이봐, 선장! 너랑 얘기하는 건 항상 즐거워. 여기 혼자 있으면 가끔 정말 심심하거든...","나는 혼자 살아서, 찾아오는 사람이 드물지. 그래서 늘 누군가와 이야기하고 싶은 기분이야."),"말하는 거 좋아하시나, 선장님? 음, 내가 또 해줄 얘기가 있을지도 모르지...","다음에 나한테 올 때 럼주 한 병 가져와라. 술이 있어야 얘기가 더 잘 풀리지...","아, 내가 아는 건 전부 말했어. 더 할 말이 없어.","block",1,npchar,Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("그럼 네가 아는 걸 말해 봐. 난 사람들과 얘기하는 걸 좋아하거든...","말해 봐! 그러잖아, 정보를 가진 자가 세상을 가진다지?"),"뭐 같은 거?","물론이지! 또 들려줄 얘기라도 있나?","좋아, 그래도 꽤 재밌게 얘기했잖아.",npchar,Dialog.CurrentNode);
    		link.l1.go = HeroStringReactionRepeat("rumours_lighthouse_yes", "rumours_lighthouse_void", "rumours_lighthouse_void", "exit", npchar, Dialog.CurrentNode);
		break;
		
		case "rumours_lighthouse_yes":
            RumText = SelectRumourEx("tavern", NPChar);
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("고마워! 또 할 말 있어?","아주 흥미롭군! 또 뭐 있어?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("고마워! 꽤 재미있었어...","말해줘서 고마워!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                Dialog.Text = RumText;
    			link.l1 = RandPhraseSimple("고마워! 또 할 말 있어?","아주 흥미로운데! 또 뭐 있어?");
    			link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("고마워! 꽤 재미있었어...","말해줘서 고마워!");
			    link.l2.go = "exit";
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;
		
		case "rumours_lighthouse_void":
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("고마워! 또 뭐 있어?","아주 흥미로운데! 또 뭐 있어?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("고마워! 꽤 재미있었어...","말해줘서 고마워!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
		break;
//Jason ------------------------------------почтовый генератор 2 уровня-------------------------------------------
		case "Postcureer_LevelUp_ForAll":
			//начинаем проверять
			if (!CheckCharacterItem(pchar, pchar.questTemp.WPU.Current.Item))
			{
				dialog.text = "그런데 짐은 어디 있지? 너 그거 안 가지고 있냐?";
	        	link.l1 = "음... 원래는 내가 그걸 당신에게 전달해야 했어. 하지만 그게... 솔직히 말해서, 빼앗겼지. 내가 저항도 못 하고 그놈들에게 직접 소포를 넘겨줬어. ";
	        	link.l1.go = "Postcureer_LevelUp_complete_fail";
				break;
			}
			
			if (sti(pchar.questTemp.WPU.Postcureer.AgentChance) == 4)//раскрыли обман
			{
				dialog.text = "음. 실례지만, 이 꾸러미는 전에 이미 열렸었어! 내 눈엔 너무 뻔해. 봉인이 다시 찍혀 있었거든...";
	        	link.l1 = ""+GetAddress_FormToNPC(NPChar)+", 그건 내가 항구 사무소에서 받은 꾸러미야 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+", 그리고 나는 전혀 모르겠어...";
	        	link.l1.go = "Postcureer_LevelUp_complete_Agentfail";
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				int iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money)/(sti(iTime)+1));//сильно снижаем оплату
				dialog.text = "널 기다리고 있었어. 그런데 너는 "+FindRussianDaysString(iTime)+" 늦었군! 네가 가져온 정보는 이제 훨씬 덜 쓸모가 있어졌어... 물론 아직 약간의 가치는 있으니, 돈은 주겠다\n "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+". 제발, 돈을 받아가고 잘 가시오.";
	        	link.l1 = "고맙다. 그렇겠지.";
	        	link.l1.go = "Postcureer_LevelUp_complete";
				pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Postcureer", "8");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(iTime));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "lost")//опоздали совсем
			{
				dialog.text = "그래, 네가 왔구나! 한참이나 기다렸지, 심지어 그 꾸러미를 되찾으려고 조치까지 했었다. 내놔라. 네가 제때 와 준 덕분에 지금은 꼭 필요하진 않지만, 그래도 내가 갖고 싶군.\n알다시피, 지금은 네게 줄 돈이 없어. 하지만 네 명예는 반드시 회복시켜 주겠다.";
	        	link.l1 = "고맙다... 아마도. 늦어서 미안해, 정말이야. 잘 가.";
	        	link.l1.go = "Postcureer_LevelUp_complete_bad";
				break;
			}
			dialog.text = "기다리고 있었소. 딱 맞춰 왔군, 자네가 가져온 정보가 큰 도움이 될 거야. 자, 수고비로 이 돈을 받아주시오 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+". 때맞춘 방문에 감사하오.";
        	link.l1 = "천만에. 잘 가!";
        	link.l1.go = "Postcureer_LevelUp_complete";
			pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			AddQuestRecord("Postcureer", "10");
		break;
		
		case "Postcureer_LevelUp_complete":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 120);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 120);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_bad":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "9");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 33);
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_fail":
			dialog.text = "에이, 이렇게 될 줄 알았지... 민간 선장이 아니라 군용 연락선이라도 빌렸어야 했는데... 뭐, 어쩔 수 없지, "+GetAddress_Form(NPChar)+", 너는 군인이 아니니 탓할 일도 없어. 잘 가라.";
			link.l1 = "잘 가라, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail":
			dialog.text = "나리, 나는 항만 관리자을 알아 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+" 개인적으로, 그는 정직한 사람이야. 게다가, 그가 그 꾸러미를 열 이유도 없었지. "+GetAddress_Form(NPChar)+", 너 사기꾼이잖아! 나는 너한테 동전 한 푼도 안 줄 거야. 썩 꺼져!";
			link.l1 = "음...";
			link.l1.go = "Postcureer_LevelUp_complete_Agentfail_1";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail_1":
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "17");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.AgentChance");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
// <--почтовый генератор 2 уровня

//Jason --> ---------------------------------генератор Неудачливый вор--------------------------------------------
		case "Device_Common":
			dialog.text = "걸어다니는 쓰레기 같았어. 떠돌이나 거지였지. 어디로 갔는지는 정확히 모르겠어, 따라가고 싶지도 않았고.";
			link.l1 = "없는 것보단 낫지. 고마워! 이제 가봐야겠어.";
			link.l1.go = "Device_Common_1";
		break;
		
		case "Device_Common_1":
			string sNation = pchar.GenQuest.Device.Shipyarder.Nation;
			sld = GetCharacter(NPC_GenerateCharacter("Device_poorman", "panhandler_"+(rand(5)+1), "man", "man", sti(pchar.rank)+5, sNation, 20, true, "quest"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+5, true);         
			GiveItem2Character(sld, "slave_02");
			EquipCharacterbyItem(sld, "slave_02");
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, sNation+"_CITIZENS");
			sld.Dialog.Filename = "Quest\Other_Quests_NPC.c"; 
			sld.dialog.currentnode = "Device_poorman"; 
			sld.greeting = "Gr_poorman";
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance2))
			{
				case 0://в городе
					sld = characterFromId("Device_poorman");
					GetCharacterPos(pchar, &locx, &locy, &locz);
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City +"_town", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
				break;
				case 1://за воротами
					sld = characterFromId("Device_poorman");
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City + "_ExitTown", "goto", "goto1");
				break;
				case 2://в бухте
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
				break;
				case 3://в доме
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Location = GetDeviceLocation(npchar); //определяем локацию
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Location, "goto", "goto1");
					if (pchar.GenQuest.Device.Shipyarder.Location == "none" || CheckAttribute(pchar, "GenQuest.SeekSpy.Location"))//если вдруг мимо или взят поиск шпиона
					{
						pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
					}
				break;
			}
			pchar.GenQuest.Device.Shipyarder = "inSeek";
			DialogExit();
			AddQuestRecord("Device", "9");
		break;
		//<-- генератор Неудачливый вор
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN_r":
			DelLandQuestMark(npchar);
			if (GetNationRelation(SPAIN, ENGLAND) == RELATION_NEUTRAL) {"Not long ago, an English ship was intercepted off the coast of Sint Maarten, and aboard it were several high‑ranking officers. They planned to send them to Willemstad pending investigation, but for the time being they were locked up in prison. There’s word that one of the captured soldiers, in exchange for his freedom, told the commandant that the English intended to send in a sabotage team and stage a jailbreak. They even had their plan ready. So our brave commandant is keeping a sharp lookout. If such important birds fly the coop — he’ll surely be stripped down to a common soldier. That’s not all — we can’t afford another war starting again.";}
			else {Dialog.Text = "얼마 전, 신트마르턴 해역에서 영국 배 한 척이 나포됐어. 그 배에는 고위 장교 몇 명이 타고 있었지. 그들을 빌렘스타드로 보내기로 했지만, 지금은 우리 감옥에서 편안하게(?) 지내고 있대. 들리는 말로는, 잡힌 병사 중 한 명이 우리 사령관에게 영국군이 이 장교들을 구출하려고 습격대를 보낼 계획이라고 말했다더군. 그래서 우리 착한 옛 사령관이 무장하고 준비하고 있는 거야. 안 그러겠어? 죄수들이 도망치면, 사령관도 평범한 병사로 강등될 테니까!";}
			link.l1 = "흥미롭군... 좋아, 돈은 네 거다. 이거 가져가라. 더 할 말 있냐?";
			link.l1.go = "rumours_tavern";
			pchar.questTemp.FMQN = "governor";
			pchar.quest.FMQN_governor.win_condition.l1 = "location";
			pchar.quest.FMQN_governor.win_condition.l1.location = "Marigo_town";
			pchar.quest.FMQN_governor.function = "FMQN_ToGovernor";
			if (Whr_IsDay()) AddDialogExitQuest("FMQN_GetRumoursDay");
			else AddDialogExitQuest("FMQN_GetRumoursNight");
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Квесты мэра, проникновение во враждебный город
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "IntelligenceForAll":
            Dialog.Text = RandPhraseSimple("좋아. 여기 배달할 꾸러미가 준비되어 있어. 가져가라\n이제 여기 오지도 말고 나한테 말도 걸지 마, 너무 위험하니까. 밖에서 조심해...","흠, 좋아. 이 꾸러미를 가져가서 우리가 방금 얘기한 그 남자에게 꼭 전해라\n잘 가라, 그리고 다시는 나한테 말 걸지 마라, 너무 위험하니까.");
            link.l1 = RandPhraseSimple("알겠어. 잘 가...","잘 가라, 행운을 빌지.");
			link.l1.go = "exit";
			pchar.GenQuest.Intelligence = "Execute";
			GiveItem2Character(pchar, "sicretLetter");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			ref rItem = ItemsFromID("sicretLetter");
			rItem.City = XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen")); 
			rItem.Mayor = GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)); 
			AddQuestRecord("MayorsQuestsList", "7");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Voc")); // belamour gen
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)]));			
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Гаспар во фриплее
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "About_Gaspar":
			dialog.text = "알고 있다. 그의 이름은 가스파르 파르망티에지만, 친구들은 그를 골드투스라고 부른다. 그는 신뢰할 수 있는 사람이며, 무엇보다도 어떤 고리대금업자도 상상할 수 없을 만큼 대량으로 구매한다. 너희는 금방 잘 지낼 수 있을 거다. 다만 기억해라, 그는 외지인을 싫어한다. 찾아갈 생각이라면 반드시 내가 보냈다고 말해라. 그의 집은 항만 관리국 근처에 있다.";
			link.l1 = "자, 돈 받을 자격은 충분해 — 받아라. 또 눈에 띄는 소식은 없나?";
			link.l1.go = "rumours_tavern";
			AddDialogExitQuestFunction("CreateGaspar_Sandbox");
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Грабеж среди бела дня, попытка залезть в сундуки
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "Man_FackYou":
			dialog.text = LinkRandPhrase("대낮에 강도질이라고?! 진짜야?! 거기 가만 있어, 이 친구...","이봐, 거기서 뭐 하는 거야?! 누가 나를 털려고 했던 것 같은데. 이제 끝장이야...","잠깐, 어디 가는 거야? 도둑이야! 거기까지다, 이 친구...");
			link.l1 = LinkRandPhrase("젠장!","카라암바!","젠장!");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}

string sRumourAboutOwners_CityRumour(string sCity, string sOwnerType) // Здесь идёт распределение по городам
{
	string sRetRumour = "Oh, seems like you've found a bug. Contact Jason and tell him about it, look for a 'Blackmark'.";
	// флаг - PChar.QuestTemp.RumoursAboutOwners.(sOwner) - для проверок, какой вопрос выпал. Ножно будет юзать для квестов
	switch(sCity)
	{
		case "Tortuga":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 0;
		break;
		
		case "PortRoyal":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 1;
		break;
		
		case "FortOrange":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 2;
		break;
		
		case "Beliz":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 3;
		break;
		
		case "PortoBello":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 4;
		break;
		
		case "Cartahena":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 5;
		break;
		
		case "Maracaibo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 6;
		break;
		
		case "Caracas":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 7;
		break;
		
		case "Cumana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 8;
		break;
		
		case "SantaCatalina":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 9;
		break;
		
		case "SanJuan":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 10;
		break;
		
		case "Marigo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 11;
		break;
		
		case "Charles":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 12;
		break;
		
		case "SentJons":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 13;
		break;
		
		case "FortFrance":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 14;
		break;
		
		case "BasTer":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 15;
		break;
		
		case "Bridgetown":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 16;
		break;
		
		case "PortSpein":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 17;
		break;
		
		case "Havana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 18;
		break;
		
		case "Villemstad":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 19;
		break;
		
		case "Santiago":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 20;
		break;
		
		case "PortPax":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 21;
		break;
		
		case "SantoDomingo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 22;
		break;
	}
	
	return sRetRumour;
}

string sRumourAboutOwners_Init(string sOwnerType, int iRumourNum) // База слухов жителей. Можно менять без новой игры
{
	
	string STR_MAYOR[MAX_RUMOURS_ABOUT_OWNERS]; // Губернаторы
	STR_MAYOR[0] = "Oh, sir governor is an excellent man. He manages our colony with great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is... well... he is quite thrifty. It might be just another virtue though.";
	STR_MAYOR[1] = "Oh, sir governor is an excellent man. He manages our colony with great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is... well... he is quite thrifty. It might be just another virtue though.";
	STR_MAYOR[2] = "Our governor is a good man but he is weak character. If he had a little firmness in his soul, our merchants could've got small tax breaks ... And it's already time to allocate subsidies for repairing the fort.";
	STR_MAYOR[3] = "Hmm ... He's recently become our governor. He is quite young and therefore very initiative. With him our colony is flourishing.";
	STR_MAYOR[4] = "Our governor is still relatively young. They say he is a good-for-nothing younger son of a Spanish count, sent far away from the yard to stop shaming his family. He has been appointed here quite recently, and didn't have time to create anything memorable.";
	STR_MAYOR[5] = "Hmm ... He's recently become our governor. He is quite young and therefore very initiative. With him our colony is flourishing";
	STR_MAYOR[6] = "Well... Nothing... I can't say anything bad about him...";
	
	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // Тавернщики
	STR_TAVERNKEEPER[0] = "Hm, I wouldn't trust my property to this rogue. Don't misunderstand me, but it seems to me that this is the most unreliable person in our town\nI heard he's working with pirates and smugglers whom often can be seen in his tavern.";
	STR_TAVERNKEEPER[1] = "What can we say about him! Cowardly, also not the smartest person I know. Besides, he is greedy for money, which is why he constantly gets into various troubles! But he is always up to date with all the news.";
	STR_TAVERNKEEPER[2] = "Quite a pleasant guy. It is always nice spending time in his tavern, he also got a great sense of humor. The most important thing about him is that he keeps a tavern in order and prevents drunk lowlifes from pestering good citizens.";
	STR_TAVERNKEEPER[3] = "Incredible man. He shouldn't keep a tavern but should be an informant for intelligence office. Sometimes it seems that he knows literally everything that happens in our town. It even scares me.";
	STR_TAVERNKEEPER[4] = "I don't know what to tell you. A man. Keeps a tavern. Knows everything about the town and its citizens.";
	STR_TAVERNKEEPER[5] = "They say that one can rely on it. On the other hand, I heard that he doesn't like unnecessary risk and always careful in doing his business. Yes, and dark affairs is not his type of business.";
	STR_TAVERNKEEPER[6] = "He's got the tavern from his father. His father kept a tavern not far from here, on the island of Highrock on another archipelago. Then his father moved here, built a new tavern here, and now his son runs it..";
	
	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // Верфисты
	STR_SHIPYARDER[0] = "Builds ships. I dunno. He's a quiet and peaceful. I guess, he's a good man.";
	STR_SHIPYARDER[1] = "Builds ships. I dunno. He's a quiet and peaceful. I guess, he's a good man.";
	STR_SHIPYARDER[2] = "A good man, but they say that he is too harsh. Constantly scolds all employees. Therefore, they often leave. Still, in spite of this, he is an excellent shipbuilder.";
	STR_SHIPYARDER[3] = "He is a very educated person. I heard that he studied shipbuilding in England, then in Holland. And in the end, he ended up here - far from the metropolis, in the provincial archipelago\nPeople say that he had troubles with the Holy Inquisition, and he had to flee to the colony.";
	STR_SHIPYARDER[4] = "This old man has to retire already and give the road for some fresh blood. He constantly dreams of past times, and grumbles when someone orders something from him besides caravels or galleons.";
	STR_SHIPYARDER[5] = "Great lad. Always willing to help. I have to say, he builds fine ships for such a shithole like this place.";
	STR_SHIPYARDER[6] = "He was a prisoner, exiled from Europe to our colony until it turned out that he had a talent for shipbuilding. After two magnificent brigs had been built under his leadership at the shipyard of our colony, he was forgiven for his transgressions, and now he is a full member of our society.";
	
	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // Магазинщики
	STR_TRADER[0] = "I can't say anything bad about him. A decent citizen, often visits our chapel. People seem to like him. Never heard of anyone being angry at him.";
	STR_TRADER[1] = "He is the main supplier of our governor, and this gives him a good income. But he conducts his affairs honestly. Well, at least he hasn't been noticed in anything shaming for him.";
	STR_TRADER[2] = "This fat man has a big respect in our city. His goods are always excellent, and I don't remember a single case he has ever cheated someone.";
	STR_TRADER[3] = "He's good-for-nothing, really. Trades, but no sense. Sometimes one good is out of stock, sometimes another, sometimes a half of goods... He can't even get himself out of debts.";
	STR_TRADER[4] = "He is not a good man, monsieur. I heard that he was Piere Thiers's right hand, previous trader, but he ruined his business it and then bought the store. I don't know how about the quality of the goods that he sells, but as a person he is very unpleasant to me.";
	STR_TRADER[5] = "Oh! He is an ugly man, I wouldn't advise you to have any business with him\nHe keeps a half of the inhabitants of our city in debt! And the goods those are sold in his store are always of poor quality.";
	STR_TRADER[6] = "Nobody really knows anything about him. He has recently moved here, and immediately opened his business. Trades honestly, wasn't caught at smuggling.";
	
	string sTempMayor = STR_MAYOR[iRumourNum];
	string sTempTavernkeper = STR_TAVERNKEEPER[iRumourNum];
	string sTempShipyarder = STR_SHIPYARDER[iRumourNum];
	string sTempTrader = STR_TRADER[iRumourNum];
	
	if(sOwnerType == "Mayor") return sTempMayor;
	if(sOwnerType == "TavernKeeper") return sTempTavernkeper;
	if(sOwnerType == "ShipYarder") return sTempShipyarder;
	if(sOwnerType == "Trader") return sTempTrader;
}

string GetDeviceLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId") || CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест по доставке малявы или шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[hrand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}
