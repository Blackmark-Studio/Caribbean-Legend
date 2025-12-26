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
			dialog.text = "聞いたか？トーマス・モリソンの娘がもう半年も寝たきりだってさ。医者たちも彼女の病にはまるで歯が立たねえらしい。 唯一助けられるのは、重病人さえ治す薬で有名なジプシー女だけだ。でも、 その女は可哀想な娘のために何もしてやろうとしなかったんだとよ。";
			link.l1 = "ありがとう、そろそろ失礼するぜ。";
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
			dialog.text = "二日前、港長の命を狙う大胆な暗殺未遂があったんだ！暗殺者は港長の執務室の前で待ち伏せしてたが、 港長が助けを叫ぶことができたんだ。すぐに銃士が駆けつけて悪党に傷を負わせたが、 そいつはなんとか町の門から逃げちまったらしい\n港長はその悪党の首にかなりの賞金をかけてるって話だぜ！今のところ、名乗りを上げる勇者はいないみたいだな。";
			link.l1 = "ありがとうございます、そろそろお暇します。";
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
			dialog.text = "ニュースを聞いたか！？とんでもねえ話だぜ！酒場にはラムもワインも一滴も残っちゃいねえ――このクソ暑さでどうやって気を紛らわせってんだ？宿屋の親父は一週間も「もうすぐ酒が入る」なんて口ばっかりで、 全然出てこねえ！このまま最後の審判の日まで喉をカラカラにしろってのかよ！？";
			link.l1 = "ありがとうございます、そろそろ失礼します。";
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
			dialog.text = "港で噂になってるんだが、総督の姪ジュリー・ダルマニャックは、昔の面影もなくなっちまったらしいぜ。 かつては輝いてて生き生きしてたのに、今じゃ悲しみを顔に浮かべて、街をさまよってるんだとよ。 町の連中も何があったのかとひそひそ話してるが、真相を知る者はいねえ。もしかして、 誰か悪党に心を砕かれたのかもしれねえな？"+GetSexPhrase(" もしかしてお前だったのか、船長？","")+"";
			link.l1 = ""+GetSexPhrase("疑わしいな ","")+"。ありがとう、そろそろ失礼するぜ。";
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
			dialog.text = "漁師のピエール・カルノが跡形もなく消えちまったって噂だ。\n二日前の夜明けに海へ漕ぎ出したきり、まったく消息がねえ。\n女房のレアは悲しみに暮れてるぜ。昼も夜も桟橋でじっと待ち続け、果てしない海を見つめては、 愛しい旦那の帆が見えるようにと祈ってるんだ。";
			link.l1 = "ありがとうございます、そろそろ失礼します。";
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
			dialog.text = "船長、聞いたか？うちの酒場に新しい給仕娘が入ったんだってよ。かなりの美人らしいぜ。 あちこちから野郎どもが顔を見に押しかけてきてるんだ。\nだが三日前からその娘が店に来なくなってな、酒場の親父は大いに困ってる。あの娘が来てから儲けがすごかったからな。 どうやら、娘を見つけてくれた奴には報酬を出すつもりらしいぜ。";
			link.l1 = "ありがとうございます、これで失礼します。";
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
			dialog.text = "聞いたか？うちの鍛冶屋がハビエル・カスティーリョとカード勝負して、ひどく負けちまったんだ。骨までしゃぶられて、 すごく大事な物まで賭けさせられたらしい。それ以来、鍛冶屋は立ち直れずに新しい注文も受けてねえ。ただ 「提督に生皮を剥がれる」って嘆いてばかりだ。哀れな奴さ、地元の連中はみんな、 あのイカサマ師カスティーリョとは勝負しちゃいけねえって知ってるのによ！";
			link.l1 = "ありがとう、もう行かなくちゃ。";
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
			dialog.text = "聞いたか？フリュート船『アギラ』の船長が、酒場で四等航海士をこっぴどく叱りつけて、壁が揺れるほどだったんだ！ どうやら船長は潮に合わせて出航するつもりだったのに、四等航海士が船員全員を上陸させちまったらしい。 今じゃ水夫たちは町中に散らばっちまって、時間通りに戻らなきゃ船は置いていかれるぞ――船長は待つ気なんてないからな！一体、何をそんなに急いでるんだろうな？儲かる積み荷か、うまい商売か、 総督からの急ぎの用事か？";
			link.l1 = "ありがとう、俺はもう行かなくちゃ"+ GetSexPhrase("","") +".";
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
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("あいにく、もう話すことはねえんだ、通してくれよ。","お前の質問にはもううんざりだ、悪いが他にもやることが山ほどあるんだ。"),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("ありがとう、俺はもう行くぜ。","さらば。");
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
			dialog.text = "聞いたか？トーマス・モリソンの娘がもう半年も寝たきりだそうだ。医者たちもまるで手も足も出ねえ病気らしい。 重い病も治すと評判の薬草使いのジプシー女だけが助けられるって話だが、 あの女は可哀想な娘のために何もする気がねえってさ。";
			link.l1 = "ありがとうございます、そろそろ失礼します。";
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
			dialog.text = "二日前、港長の命を狙う大胆な企てがあったんだ！刺客は港長の執務室の前で待ち伏せしてたが、 港長が助けを呼ぶことに成功したんだよ。すぐに銃士が駆けつけて悪党に傷を負わせたが、 そいつはなんとか城門から逃げちまったらしい。\n噂じゃ、港長はその悪党の首にかなりの賞金をかけてるって話だ！今のところ、名乗り出る勇者はいねえ。 おいらは千ドゥブロン積まれても、命を張る気にはなれねえな……";
			link.l1 = "ありがとうございます、そろそろ失礼します。";
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
			dialog.text = "ニュースを聞いたか！？まったくひでえ話だぜ！酒場にラムもワインも一滴も残っちゃいねえ――このクソ暑さでどうやって気を紛らわせってんだ？宿屋の親父は一週間も前から「もうすぐ酒が入る」って口ばっかりで、 全然出てこねえ！このまま最後の審判の日まで喉を乾かしてろってのかよ！？";
			link.l1 = "ありがとうございます、そろそろ失礼します。";
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
			dialog.text = "港で噂になってるんだが、総督の姪ジュリー・ダルマニャックは、昔の面影もないほどやつれちまったらしいぜ。\nかつては輝くように生き生きしてたのに、今じゃ悲しみを顔に浮かべて町をさまよってるって話だ。\n町の連中も何があったのかとひそひそ話してるが、真相を知る者はいねえ。\nもしかして、どこかの悪党に心を傷つけられたのかもな？"+GetSexPhrase(" もしかしてお前だったのか、船長？","")+"";
			link.l1 = ""+GetSexPhrase("信じられねえな ","")+"。ありがとう、そろそろ失礼するぜ。";
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
			dialog.text = "漁師のピエール・カルノが跡形もなく消えちまったって噂だぜ。二日前の夜明けに沖へ出たきり、 そっから消息がないんだ。女房のレアは悲しみで気が狂いそうだとよ。昼も夜も桟橋で見張り続けて、 果てしない海をじっと見つめながら、愛しい旦那の帆が見えるようにと祈ってるらしいぜ。\n";
			link.l1 = "ありがとうございます、そろそろ失礼します。";
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
			dialog.text = "船長、聞いたか？うちの酒場に新しい給仕娘が入ったんだってよ。すげえ美人らしいぜ。 あちこちから野郎どもが顔を見に押し寄せてるんだ。\nだが三日前からその娘が仕事に来なくなってな、酒場の主人は大いに困ってるらしい。 あの娘が来てから儲けがすごかったからな。どうやら、娘を見つけてくれた奴には報酬を出すつもりらしいぜ。";
			link.l1 = "ありがとうございます、そろそろお暇します。";
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
			dialog.text = "聞いたか？うちの鍛冶屋がハビエル・カスティーリョとカード勝負して、ボロ負けしたんだ。骨までしゃぶられて、 すごく大事な物まで賭けさせられたらしい。それ以来、鍛冶屋は立ち直れず、新しい注文も受けてねえ。ただ 「提督に生皮剥がれる」って嘆いてばかりさ。哀れな奴だよ、地元じゃみんな知ってる――あのイカサマ師カスティーリョと勝負しちゃダメだってな！";
			link.l1 = "ありがとう、もう行かなくちゃ。";
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
			dialog.text = "聞いたか？フリュート船『アギラ』の船長が酒場で四等航海士をこっぴどく叱りつけて、壁が揺れるほどだったんだ！ どうやら船長は潮に合わせて出航するつもりだったのに、四等航海士が乗組員全員を上陸させちまったらしい。 今じゃ水夫たちは町中に散らばってて、時間までに戻らなきゃ船は置いていかれるぞ――船長は待つ気なんてねえ！一体、何をそんなに急いでるんだ？うまい荷物か、儲かる商売か、総督からの急ぎの用か？";
			link.l1 = "ありがとう、もう行かなくちゃ"+ GetSexPhrase("","") +".";
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
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("あいにく、もう話すことはねえ、通してくれ。","お前の質問にはもううんざりだ、失礼するぜ、他にもやることが山ほどあるんだ。"),"ブロック",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("ありがとう、俺はもう行くぜ。","さらば。");
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
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("あいにく、もう話すことはねえんだ、通してくれ。","お前の質問にはもううんざりだ、悪いが他にもやることが山ほどあるんだ。"),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("ありがとう、俺は行くぜ。","さらば。");
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---слухи дворян---////////////////////////////////////////////
	case "rumours_nobleman":	
        srum = SelectRumourEx("nobleman", NPChar);
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
			if (bOk1 || bOk2){
				
			dialog.text = "港で噂になってるんだが、総督の姪ジュリー・ダルマニャックは、昔の面影もないほどやつれちまったらしいぜ。 かつては輝いてて生き生きしてたのに、今じゃ悲しみを顔に浮かべて町をさまよってるって話だ。 町の連中も何があったのかとひそひそ話してるが、真相を知る者はいねえ。ひょっとして、 誰か悪党に心を傷つけられたのかもな？"+GetSexPhrase(" もしかしてお前だったのか、船長？","")+"";
			link.l1 = ""+GetSexPhrase("信じられねえな ","")+"。ありがとう、そろそろ失礼するぜ。";
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
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("俺の言いたいことは伝わったはずだ――もうこれで終わりだ。","お前の質問にはもううんざりだぜ、船長。もっとマシなことでも探してきな！"),"ブロック",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("ありがとう、俺はもう行くぜ。","さらば。");
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
			dialog.text = "港で噂になってるんだが、総督の姪ジュリー・ダルマニャックは、昔の面影もなくなっちまったらしいぜ。\nかつては輝いてて生き生きしてたのに、今じゃ悲しみを顔に浮かべて街をさまよってるって話だ。\n町の連中も何があったのかとひそひそ話してるが、真相を知る者はいねえ。\nもしかして、どこかの悪党に心を傷つけられたのかもな？"+GetSexPhrase(" もしかしてお前だったのか、船長？","")+"";
			link.l1 = ""+GetSexPhrase("信じられねえな ","")+"。ありがとうございます、これで失礼します。";
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
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("俺の言いたいことは伝わったはずだ――もうこれで終わりだ。","もうお前の質問にはうんざりだぜ、船長。もっとマシなことでも探してきな！"),"ブロック",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("ありがとう、そろそろ行くとするよ。","さらば。");
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
			dialog.text = "二日前、港の長官が命を狙われるという大胆な事件があったんだ！刺客は長官の執務室の前で待ち伏せしていたが、 長官が助けを呼ぶことに成功したんだ。銃士が急いで駆けつけて悪党に傷を負わせたものの、 そいつはどうにか城門から逃げちまったらしい\n聞いた話だと、長官はその悪党の首にかなりの賞金をかけてるらしいぜ！でも今のところ、名乗り出る勇者はいねえ。 あんたも知ってるだろ、たとえ千ドゥブロン積まれても……俺はやらねえよ……";
			link.l1 = "ありがとうございます、そろそろ失礼します。";
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
			dialog.text = "聞いたか？フリュート船『アギラ』の船長が酒場で四等航海士をこっぴどく叱りつけて、壁が揺れるほどだったんだ！ どうやら船長は潮に合わせて出航するつもりだったのに、四等航海士が乗組員全員を上陸させちまったらしい。 今じゃ水夫たちは町中に散らばっちまって、時間までに戻らなきゃ船は置いていかれるぞ――船長は待つ気なんてねえからな！一体、何をそんなに急いでるんだろうな？うまい荷物でもあるのか、儲かる商売か、 それとも総督からの急ぎの用事か？";
			link.l1 = "ありがとう、もう行かなくちゃ"+ GetSexPhrase("","") +".";
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
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("あいにく、もう話すことはねえんだ、通してくれ。","お前の質問にはもううんざりだ、悪いが他にもやることが山ほどあるんだ。"),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("ありがとう、そろそろ行くとするよ。","さらば。");
		link.l2.go = "exit";
	break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		//-->работорговец
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = "（歌）俺たちゃ悪党、ろくでなし、悪人にごろつきだぜ。飲めや飲めや、野郎ども、ヨーホー！俺たちゃ悪魔に黒い羊、 本当に腐った卵さ。飲めや飲めや、野郎ども、ヨーホー！！\nおい、相棒、元気か？海の調子はどうだ？";
            link.l1 = "海か？あいつはいつも通りの嫌な女さ。しょっぱくて濡れてるだけだ。なあ、俺の仲間を知らねえか？ ついこの前ここで部屋を借りたやつだ。フランソワ・ゴンティエって名前だったんだが。\n";
            link.l1.go = "Jamaica_ratH_1";
			break;
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "（歌いながら）可愛い娘よ、俺と一緒に来てくれないか、可愛い娘よ、俺のそばで寝てくれないか？朝になったら、 お前のリボンを全部巻き取ってから、俺はお前のもとを去るぜ！";
            link.l1 = "飲めよ、相棒！海の調子はどうだ？";
            link.l1.go = "EscapeSlave_Villemstad_H1";
			break;
        }
		//<--работорговец
				
		//Голландский Гамбит, против всех
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "LetterToLucasSent" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "ああ、海よ……俺もお前の立場だったらよかったのにな！";
            link.l1 = "問題なんて見当たらねえぜ、相棒。いつでも俺の船に乗りなよ。";
            link.l1.go = "Lucas_Tavern";
			break;
        }
		//Голландский Гамбит
		
		//--> поиск дезертира
		if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE && !CheckAttribute(npchar, "quest.fugitive"))
        {
			dialog.text = LinkRandPhrase("知ってるか、ラムを飲めばみんな仲間になるんだぜ！ハハッ！","ラムを一杯やれば、絞首刑執行人でさえ可愛く見えるぜ！ははっ！","酒を飲めば眠くなる、眠れば罪も犯さねえ！ラムとエールは天国へ導いてくれるんだ、だから飲め、くそったれ！ははっ！ ");
            link.l1 = "ああ、一杯やろうぜ……なあ、旦那、知ってるか "+pchar.GenQuest.FindFugitive.Name+"？あいつは俺の昔の仲間なんだ。何人かがここに引っ越してきたって言ってたが…";
            link.l1.go = "FindFugitiveHb";
			break;
        }
		//<-- поиск дезертира
		
		//--> карибские нравы
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && npchar.location == "Portobello_tavern")
		{
			dialog.text = "ニュースだと？はっ！もう聞いてねえのか？うちの兵隊がフランスのスパイを捕まえたんだぜ。くそったれの偽者で、 商人のふりしやがったが、*げっ*…うちの隊長は手強い野郎だからな！";
            link.l1 = "そりゃ驚いたぜ！で、そのカエル野郎は何を探ろうとしてたんだ？";
            link.l1.go = "trial_spy";
			break;
		}
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = "「えっ、」 "+GetAddress_Form(pchar)+" なんて世の中だよ……クソ野郎ばっかりじゃねえか！";
			link.l1 = "どういう意味だ？";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
			break;
		}
		//<-- карибские нравы
		
		//--> Sinistra Длинные тени старых грехов
		if (CheckAttribute(pchar, "questTemp.DTSG_NightIskat") && npchar.city == "SentJons")
        {
			dialog.text = "聞いたか！？信じられねえよ！あの有名なフリートウッド船長がロンドンで無残に殺されたんだ！名声を追い求めて、 すべてを手に入れたはずが、結局は死しかなかった……ここにいればもっと安全だったのによ。俺が言いたいのはな、ときには金や地位を追いかけるより、 今あるものに感謝した方がいいってことだぜ、旦那！";
            link.l1 = "「旦那、この植民地の誰がどこに住んでるか、知ってるよな？」";
            link.l1.go = "DTSG_NightIskat";
			break;
        }
		//<-- Длинные тени старых грехов
		
		//--> Rebbebion, квест "Путеводная звезда"
		if (CheckAttribute(pchar, "questTemp.PZ_Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.PZ_Sotta") && !CheckAttribute(npchar, "questTemp.PZ_Lutter") && npchar.city == "Beliz")
		{
			link.l1 = "さて、本日の英雄、エドガルド・ソッタ船長だな。あいつについて皆は何を言ってる？お前はどう思う？ 俺はずっとあの男に会うのを楽しみにしてたんだぜ。";
			link.l1.go = "Sotta1";
			link.l2 = "おい、なんで一人で飲んでるんだ？今みんな集まってウィンドバッグ・マットの絞首刑を見物してるぜ。";
			link.l2.go = "Lutter1";
			break;
		}
		
		if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(pchar, "questTemp.PZ.TortugaHabitueBlock") && npchar.city == "Tortuga")
		{
			link.l1 = "なあ、相棒、ジョープ・ファン・デル・ヴィンクってやつを探してるんだ。伝言を渡さなきゃならなくてな。 そいつの顔とか、何か知ってるか？";
			link.l1.go = "Sepp1";
			break;
		}
		//<-- квест "Путеводная звезда"
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "聞いたか？トーマス・モリソンの娘がもう半年も寝たきりだってさ。医者たちはまるで手も足も出ねえ病気らしい。 重い病も治すと評判の薬草使いのジプシー女だけが助けられるって話だが、 あの女は可哀想な娘のために何もする気はねえってさ。";
			link.l1 = RandPhraseSimple(RandSwear()+"これはもう一杯いけるな……","よし、もう一杯やろうぜ。");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("ありがとう、俺はもう行くぜ。","へえ、すげえラムだな。よし、俺は行くぜ、ここで楽しんでくれよ。");
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
			dialog.text = "二日前、港長の命を狙う大胆な襲撃があったんだ！刺客は奴の執務室の前で待ち伏せしてたが、 港長が助けを呼ぶことに成功した。銃士が急いで駆けつけて悪党に傷を負わせたものの、 そいつは市門から逃げちまったらしい。\nどうやら港長はその悪党の首にかなりの賞金をかけてるそうだ！今のところ、名乗り出る勇者はいないみたいだぜ。おい、 たとえ千ドゥブロンでも……俺は命を張る気にはなれねえよ…";
			link.l1 = RandPhraseSimple(RandSwear()+"これはもう一杯飲む価値があるな……","よし、もう一杯飲もうぜ。");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("ありがとう、そろそろ行くとするよ。","ああ、すげえラムだな。よし、俺は行くぜ、ここで楽しんでくれ。");
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
			dialog.text = "ニュースを聞いたか！？まったくひでえ話だぜ！酒場にラムもワインも一滴も残っちゃいねえ――このクソ暑さでどうやって癒やせってんだ？宿屋の親父は一週間も「もうすぐ酒が入る」って口ばっかりで、 全然出てこねえ！俺たち、最後の審判の日まで喉を乾かしてろってのか！？";
			link.l1 = RandPhraseSimple(RandSwear()+"これはもう一杯飲む価値があるな……","よし、もう一杯やろうぜ。");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("ありがとう、そろそろ行くとするよ。","へえ、すげえラムだな。まあ、俺は行くぜ、ここで楽しんでくれよ。");
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
			dialog.text = "港の噂じゃ、うちの酒場の親父が大変な目に遭ってるらしいぜ！誰かがあいつのジンを盗みやがったんだ！ しかも一本や二本じゃねえ、まるごと樽一つ分――この島じゃ他に手に入らねえ代物だってよ！ヨーロッパからわざわざ運ばせたらしい。あの老いぼれキツネ、 誰のために取っておいたかは口を割らねえが、一つだけ確かなのは、あの樽が早く見つからなきゃ、 哀れな奴にとんでもねえ災難が降りかかるってことだ！";
			link.l1 = RandPhraseSimple(RandSwear()+"これはもう一杯飲む価値があるな…","よし、もう一杯やろうぜ。");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("ありがとう、俺はもう行くぜ。","ああ、すげえラムだな。よし、俺は行くぜ、ここで楽しんでくれよ。");
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
			dialog.text = "港で噂になってるんだが、総督の姪ジュリー・ダルマニャックはすっかり別人みたいになっちまったらしいぜ。\n昔は輝いてて生き生きしてたのに、今じゃ悲しみを顔に浮かべて町をさまよってるんだとよ。\n町の連中も何があったのかとヒソヒソ話してるが、真相は誰も知らねえ。\nもしかして、どこかの悪党に心を傷つけられたのかもな？"+GetSexPhrase(" もしかしてお前だったのか、船長？","")+"";
			link.l1 = RandPhraseSimple(RandSwear()+"これはもう一杯飲む価値があるな……","よし、もう一杯飲もうぜ。");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("ありがとう、そろそろ行くぜ。","ああ、すげえラムだな。よし、俺は行くぜ、ここで楽しんでくれ。");
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
			dialog.text = "漁師のピエール・カルノが跡形もなく消えたって噂だ。\n二日前の夜明けに海へ出たきり、まったく消息がないらしいぜ。\n女房のレアは悲しみに暮れて、昼も夜も桟橋で待ち続けてる。\n果てしない海をじっと見つめて、愛しい旦那の帆が見えるようにと祈ってるんだとよ。";
			link.l1 = RandPhraseSimple(RandSwear()+"これはもう一杯いく価値があるな……","よし、もう一杯飲もうぜ。");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("ありがとう、俺はもう行くぜ。","ああ、このラムはたまんねえな。よし、俺は行くぜ、ここで楽しんでくれよ。");
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
			dialog.text = "船長、聞いたか？うちの酒場に新しい給仕娘が入ったんだとよ。かなりの美人らしいぜ。 あちこちから男どもが顔を見に押しかけてるって話さ。\nだが三日前からその娘が店に来なくなってな、酒場の親父は大いに困ってるんだ。 あの娘が来てから儲けが跳ね上がったからな。どうやら、娘を見つけてくれた奴には報酬を出すつもりらしいぜ。";
			link.l1 = RandPhraseSimple(RandSwear()+"これはもう一杯いけるな…","よし、もう一杯飲もうぜ。");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("ありがとう、俺はそろそろ行くぜ。","ああ、すげえラムだな。よし、俺は行くぜ、ここで楽しんでくれよ。");
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
			dialog.text = "聞いたか？うちの鍛冶屋がハビエル・カスティーリョとカード勝負して、ひどく負けちまったんだ。 骨の髄まで巻き上げられて、すごく大事な物まで賭けさせられたらしい。それ以来、 鍛冶屋は立ち直れずに新しい注文も受けてねえ。ただ「提督に生皮を剥がれる」って嘆いてばかりだ。哀れな奴さ、 地元の連中はみんな、あのイカサマ野郎カスティーリョと勝負しちゃいけねえって知ってるのによ！";
			link.l1 = RandPhraseSimple(RandSwear()+"これはもう一杯飲む価値があるな……","よし、もう一杯飲もうぜ。");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("ありがとう、俺はもう行くぜ。","ええ、すげえラムだな。よし、俺は行くぜ、ここで楽しんでくれ。");
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
			dialog.text = "聞いたか？フリュート船『アギラ』の船長が、酒場で四等航海士をこっぴどく叱りつけて、壁まで揺れたんだとよ！ どうやら船長は潮に合わせて出航するつもりだったのに、四等航海士が乗組員全員を上陸させちまったらしい。 今じゃ水夫たちは町中に散らばっちまって、時間までに戻らなきゃ船は置いていかれるぞ――船長は待つ気なんてねえからな！一体、何をそんなに急いでるんだろうな？うまい荷物か、儲かる商売か、 総督からの急ぎの用か？";
			link.l1 = RandPhraseSimple(RandSwear()+"これはもう一杯飲む価値があるな……","よし、もう一杯飲もうぜ。");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("ありがとう、俺はもう行くぜ。","ああ、このラムはたまんねえな。よし、俺は行くぜ、ここで楽しんでくれよ。");
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
			dialog.text = "それは聞いたぜ。 "+GetSexPhrase("相棒","お嬢ちゃん")+"？町をうろついてるイカれた爺さんがいるんだよ。サブ＝ マティラ湾に沈んでるあのボロ船の難破から生きて帰ったのは自分だけだって言い張ってて、 今じゃ必死にまたそこへ戻りたがってる。でも一人じゃ怖くて行けねえんだとさ。毎朝部族の格好した骸骨が現れて、 死ぬまで戦いを挑んでくるって、ずっとブツブツ言ってるぜ。俺？*ヒック* 五百ドゥブロン積まれても一緒には行かねえな。あんな阿呆の頭の中でどんな悪魔が踊ってるか、知ったこっちゃねえよ。 ";
			link.l1 = RandPhraseSimple(RandSwear()+"これはもう一杯やる価値があるな……","よし、もう一杯飲もうぜ。");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("ありがとう、俺は行くぜ。","ああ、すげえラムだな。よし、俺は行くぜ、ここで楽しんでくれよ。");
			link.l2.go = "exit_sit";
			LEDR_Start();
			break;
        }
		//<-- LaEspadaDelRey
		
		Dialog.Text = LinkRandPhrase("「うーん……ひっく！」 ","ああ、うまいラム酒だな！ ","「さて……」 ")+SelectRumourEx("常連",NPChar);
		link.l1 = RandPhraseSimple(RandSwear()+"これはもう一杯飲む価値があるな……","よし、もう一杯やろうぜ。");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("ありがとう、俺はもう行くぜ。","ああ、すげえラムだな。よし、俺は行くぜ、ここで楽しんでくれ。");
		link.l2.go = "exit_sit";
	break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
			Dialog.Text = NPCStringReactionRepeat(strum,strum+" ああ。もう話すことはねえよ。",strum+" さて、そろそろ本題に戻るとするか。",RandPhraseSimple("もう言っただろ、暇つぶしの雑談なんかしてる時間はねえんだ！","俺は忙しい男だ、噂話なんかしてる暇はねえ！"),"ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear()+"面白いな！だが本題に入ろうぜ","ありがとうございます、そしてもう一つ伝えたいことがあります。"),pcharrepphrase(""+GetSexPhrase("ちくしょう","Interesting")+"！いい語り手だな。でももう一つ聞きたいことがあるんだ。","これ以上時間を無駄にせず、本題に入ろうぜ。"),pcharrepphrase(RandSwear()+" もう一つだけ言わせてくれ、それが済んだら行くぜ。","おっしゃる通り、時間は金だ。"),pcharrepphrase("自分の儲けばっかり考えてやがるな！まあいい、正気は失うなよ。","許してくれ。さて、本題に入ろう。"),npchar,Dialog.CurrentNode);
			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("さよならだ、酔っ払いのじじい。","「じゃあな」 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("カランバ！あんまり遠くに行くなよ。すぐ戻るからな。","「会えてうれしいぜ」 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"！さらばだ！")),NPCharRepPhrase(npchar,pcharrepphrase("錨を上げろ！","さらばだ！"),pcharrepphrase("おい！そこに何を隠してやがる？ラムか？違うのか！？まあいい、俺は自分で酒を手に入れるぜ。","すまねえ、街で大事な用事があるんだ。")),NPCharRepPhrase(npchar,pcharrepphrase("へっ！また会おうぜ！","俺は行くぜ。じゃあな、 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("俺に口答えするんじゃねえ！こんなの望んじゃいねえんだ！","俺の船の様子を見てくるとするか。じゃあな、 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("どうしたんだよ、相棒？俺だぜ― "+GetFullName(pchar)+"！ちょっと寝てろ、後で話そう。","またここに来る前に、お前の肝臓が先にお前を殺しちまうんじゃねえかと心配だぜ。"),pcharrepphrase("銀貨を数えておけよ、このずる賢い野郎！また後で会おうぜ。","「会えて嬉しいぜ」 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("船長",NPChar);
			Link.l1 = RandPhraseSimple(RandSwear()+"面白いな！もう一つ聞きたいことがあるんだ…","もう一つ聞きたいことがある。");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("ありがとう、俺はもう行くぜ。","さらば。");
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
		
		 case "rumours_landcaptain":
			Dialog.Text = SelectRumourEx("陸の船長",NPChar);
			Link.l1 = RandPhraseSimple(RandSwear()+"面白いな！もう一つ聞きたいことがあるんだ…","「もう一つ質問がある。」");
			Link.l1.go = "question";
			Link.l2 = RandPhraseSimple("ありがとう、そろそろ行くぜ。","さらば。");
			Link.l2.go = "exit";
			NextDiag.TempNode = "question";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06
				if(startHeroType == 4)
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("値段は知ってるだろう。情報ってのは部屋や飯、酒と同じで、タダじゃねえんだ。千ペソだぜ。","値段は知ってるだろう。情報ってのは部屋や飯、酒と同じで、タダじゃねえんだ。千ペソいただくぜ。","値段は知ってるだろう。情報ってのは部屋や飯、酒と同じで、タダじゃねえんだ。千ペソいただくぜ。"),"ここで付け加えることはもうない。では、失礼する、俺は行かなくちゃならねえ。","","","ブロック",1,npchar,Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple("実は、なんで俺がこんなこと聞いてるんだろうな？他の奴にも聞けるしな。邪魔して悪かったな。","実は、なんで俺がこんなこと聞いてるんだろうな？他のやつにも聞けるしな。邪魔して悪かったな。"),"","","",npchar,Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000)
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("知ってるさ、もちろん。ほら、これが俺の支払いだ。","もちろん知ってるさ。ほら、これが俺の支払いだ。"),"","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 = HeroStringReactionRepeat("そんな大金は持ってねえ。","","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
				}
				else
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("情報はタダじゃねえぜ。1000ペソ払えば、知ってること全部教えてやる。","どうも記憶があやふやでな、千ピース・オブ・エイトもらえりゃ何か思い出せるかもしれねえ。","あんたに情報を教えてやりたいんだがな。だが、千エイトかかるぜ。値切りはなしだ。"),"ここで言うことはもうない。さて、失礼するぜ、俺は行かなくちゃな。","","","ブロック",1,npchar,Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear()+"くだらねえおしゃべりに金は払わねえぞ。","この金のもっといい使い道を考えてみるぜ。"),"話題を変えようぜ。","話を変えよう。","話題を変えよう。",npchar,Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000 )
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("お前から何か価値のある話を聞けたら、それを渡してやるぜ。","価値のある物をくれるなら、金は払うぜ。"),"","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 = HeroStringReactionRepeat("そんな大金は持ってねえ。","","","",npchar,Dialog.CurrentNode);
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
					Dialog.Text = "うちの哨戒隊が最近、モレルっていうフランス人密輸業者のブリガンティンを沈めたんだ。 今じゃあいつは地下牢にぶち込まれて、死刑を待ってるぜ。うちの司令官は、 あいつの船にまだ全部の積み荷がなかったと思ってて、今も探してる最中さ……司令官がその隠された積み荷を見つけたら、フランス野郎の命も終わりだな。";
					link.l1 = "面白いな……よし、金を持っていけ。他に言いたいことはあるか？";
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
				Dialog.Text = "総督の館で大きな宴があったんだ。閣下の友人、ドン・カルロス・デ・ミリヤールが戻ってきたんだよ。 海戦で捕まったけど、フランス人の中尉の助けで脱出したらしい。ドン・カルロスは頭が切れるだけじゃなくて、 すごく気前のいい人なんだ。そのおかげで、その中尉ジャン・ドノーは今や「サリオ号」の船長になったんだってさ。 聞いた話じゃ、小さなプランテーションまで贈られたとか。今じゃあのカエル野郎も「フアン」って呼ばれてるぜ！ すげえ話だろう！";
				link.l1 = "面白いな……よし、金はお前のものだ。これを受け取れ。ほかに何か話すことはあるか？";
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
				Dialog.Text = "うちの司令官がジャングルの巡回に増援を送り、町の警備も増やしたらしいぜ。 フィリップスバーグにイギリス野郎どもが潜り込んで、捕まった将校たちを解放しようとしてるって噂があるんだ。\n";
				link.l1 = "そりゃ驚いたぜ！本当にそんな手口を使う度胸があるのか？で、一体どの士官たちのことを言ってるんだ？";
				link.l1.go = "FMQN_r";
				break;
			}	
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && npchar.location == "Havana_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "この前、町中がまるで蜂の巣をつついたように大騒ぎだったんだ。軍のスクーナーの士官が俺の酒場で泥酔して、 人妻を襲いかけたんだよ。そんでもって、妻を守ろうとした旦那を殴りつけて、剣まで抜いて脅したんだぜ。しかも、 これが町の衛兵の目の前で起きたんだ。力こそ正義ってやつさ。兵隊どもは見て見ぬふりで、 あのクズが暴れまわるのを放っておいたんだ\nだがな、意外なことに、あの悪党を取り押さえたのは商船の水夫たちだった。あいつら、 もう少しでリボンで縛り上げるところだったが、クズ野郎は何とか逃げて自分の船に隠れやがった。 司令官とアルカルデは揉み消そうとしたが、怒り心頭の旦那は町でも評判の市民でな、 閣下ドン・ディエゴ・デ・トレドに訴えて、地元の名士たちの間で騒ぎになった\nそれで士官の逮捕状が出されたんだ。噂じゃ、あいつの艦長に港を出て別の場所に移せって助言があったらしい。でもな、 スクーナーの艦長エスベルド・カバナスは名誉ある男だ。部下のやったことを知ると、 すぐに逮捕して陸に送り返したんだよ。あのクズは今、牢屋で腐ってやがる。俺に言わせりゃ当然だ。もしかしたら、 今後は二等兵に格下げされて、見せしめに鞭打たれるかもしれねえな。";
				link.l1 = "待てよ、今「エスベルド・カバナス船長」って言ったか？ふむ……そりゃあ面白い話だな！よし、金はちゃんと払うぜ、ほらよ。\n他に何か知ってることはあるか？";
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
				Dialog.Text = "無人島のどこかに犯罪者が置き去りにされたって話だぜ！処刑人も神父様たちも手を出せねえほどの極悪人らしい！\nでも、なんでいつも奴らをここに連れてくるんだよ！？";
				link.l1 = "ふむ……面白いな！そいつらを探し出して仲間に引き入れるのも悪くねえな――俺はいつだって死に物狂いの奴らを欲してるからな……なんだよ、そんなに青い顔してどうした、相棒？冗談だよ、冗談……報酬はちゃんとやるぜ、ほらよ。他に何か面白い話でも聞いたか？\n";
				link.l1.go = "rumours_tavern";
				IslaMona_TerksCreateHimenes();
				break;
			}
			// Гаспар во фриплее 
			if ((SandBoxMode) && npchar.city == "Tortuga" && (sti(pchar.reputation.nobility) < 41))
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "あなたの評判は既に知れ渡っていますよ、船長。きらびやかな宝石やガラクタをどこで売るか、 悩んだことが何度もあるでしょうね…";
				link.l1 = "それについて助けてくれる人を知っているのか？";
				link.l1.go = "About_Gaspar";
				break;
			}
            string RumText = SelectRumourEx("tavern", NPChar); //fix
			
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; //fix
				if(startHeroType == 4)
				{
					link.l1 = "結局、お前は何も知らなかったんだな。まさかこんなふうに俺を騙すとは思わなかったぜ。あんまり賢くねえな。 じゃあな。";
				}
				else
				{
					link.l1 = RandPhraseSimple("くだらねえガラクタだな。お前には一ペソたりとも払わねえ！じゃあな。","お前の情報なんざ役に立たねえ、だから何もやらねえぞ。");
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
					link.l1 = "本当か？面白いな、ありがとう。さて、そろそろ行くぜ、またな。";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = RandPhraseSimple("ありがとう、金を受け取れ。ほかに言いたいことはあるか？","わかった、金を持ってけ。他に言いたいことはあるか？");
					link.l1.go = "rumours_tavern";
				}
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;

		case "rumours_tavern_no":
			if(startHeroType == 4)
			{
				Dialog.Text = "少しは金を出してくれてもよかったんだぜ。お前と違ってな、ヘレン、 俺にはバラコアのバロンみたいな後ろ盾はいねえんだよ。";
				link.l1 = "お前は店を丸ごと持ってるじゃねえか。俺は自分の力だけでここまで来たんだ。まあ、船とか大砲とか乗組員とか、 バロンがくれた物資は別だけどな。\n……ま、いいや。";
				link.l1.go = "exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
			else
			{
				Dialog.Text = "分かってくれ、家族を養わなきゃならねえんだ。";
				link.l1 = "話を変えよう。";
				link.l1.go = "first time";
				NextDiag.CurrentNode = NextDiag.TempNode;
				link.l2 = LinkRandPhrase("ありがとう、そろそろ行くとするよ。","「さらばだ。」","じゃあな。");
				link.l2.go = "Exit";
			}
		break;	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("貧乏",NPChar);
				Link.l1 = RandPhraseSimple(RandSwear()+"面白いな。もう一つ聞きたいことがあるんだが……","うーん、他のことを聞かせてくれ…");
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple("じゃあな、達者でな。","じゃあな、相棒。");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("俺が知ってることは全部話したぜ。","もうこれ以上話すことはねえんだ、悪いな…");
				Link.l1 = RandPhraseSimple("なるほど。じゃあな。","じゃあな、相棒……");
				Link.l1.go = "exit";			
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("貧乏",NPChar);
				Link.l1 = RandPhraseSimple(RandSwear()+"面白いな。もう一つ聞きたいことがあるんだ…","ふむ、他のことを聞かせてくれ……");
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple("じゃあな、元気でな。","じゃあな、相棒。");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("俺が知ってることは全部話したぜ。","もう話すことはねえんだ、悪いな……");
				Link.l1 = RandPhraseSimple("なるほど。じゃあな。","了解だ。じゃあな、相棒……");
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC",NPChar);
				Link.l1 = RandPhraseSimple("了解した……","なるほど……");
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else  
			{
				Dialog.Text = NPCharSexPhrase(npchar,RandPhraseSimple("俺が知ってることは全部話したぜ。","悪いが、新しい話は何も聞いてねえ……"),RandPhraseSimple("俺が知ってることは全部話したぜ。","悪いが、新しい話は何も聞いてねえんだ…"));
				Link.l1 = RandPhraseSimple("なるほど、それじゃあ、さようなら。","了解だ。じゃあな。");
				Link.l1.go = "exit";			
			}
		break;
		
//Jason -------------слухи смотрителей маяков, идентичны таверне, но бесплатны, по 1 шт за день--------------------
		case "rumours_lighthouse": 
			Dialog.Text = NPCStringReactionRepeat(RandPhraseSimple("おう、船長！あんたと話すのはいつも楽しいぜ。ここで一人だと、たまに退屈しちまうんだよな……","俺は一人で暮らしてるから、訪ねてくる奴なんて滅多にいねえんだ。\nだから、いつでも話し相手が欲しい気分さ。"),"話好きかい、船長？じゃあ、他にも話してやれることがあるぜ……","今度来るときはラム酒を一本持ってきてくれよ。酒があれば話も弾むからな…","ああ、俺の知ってることは全部話したぜ。もう付け加えることはねえ。","block",1,npchar,Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("じゃあ、知ってることを話してくれよ。俺は人と話すのが好きなんだぜ……","教えてくれ！よく言うだろ、情報を握る者が世界を制するってな？"),"「例えば何だ？」","もちろんだぜ！他に話したいことがあるのか？","まあいいさ、どうせ楽しく話せたしな。",npchar,Dialog.CurrentNode);
    		link.l1.go = HeroStringReactionRepeat("rumours_lighthouse_yes", "rumours_lighthouse_void", "rumours_lighthouse_void", "exit", npchar, Dialog.CurrentNode);
		break;
		
		case "rumours_lighthouse_yes":
            RumText = SelectRumourEx("tavern", NPChar);
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("ありがとう！他に何かあるか？","そりゃ面白えな！他に何かあるか？");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("ありがとう！なかなか面白かったぜ……","教えてくれてありがとう！");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                Dialog.Text = RumText;
    			link.l1 = RandPhraseSimple("ありがとう！他に何かあるか？","面白いな！他には何かあるか？");
    			link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("ありがとう！なかなか面白かったぜ……","教えてくれてありがとう！");
			    link.l2.go = "exit";
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;
		
		case "rumours_lighthouse_void":
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("ありがとう！他に何かあるか？","そりゃ面白いな！他に何かあるか？");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("ありがとう！なかなか面白かったぜ……","教えてくれてありがとう！");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
		break;
//Jason ------------------------------------почтовый генератор 2 уровня-------------------------------------------
		case "Postcureer_LevelUp_ForAll":
			//начинаем проверять
			if (!CheckCharacterItem(pchar, pchar.questTemp.WPU.Current.Item))
			{
				dialog.text = "「でも荷物はどこだ？持ってねえのか？」";
	        	link.l1 = "ええと…本当はそれをお前さんに届けるはずだったんだ。だが、それが…正直に言うと、奪われちまったんだ。抵抗できなくて、自分であの襲撃者たちに包みを渡しちまったんだよ。 ";
	        	link.l1.go = "Postcureer_LevelUp_complete_fail";
				break;
			}
			
			if (sti(pchar.questTemp.WPU.Postcureer.AgentChance) == 4)//раскрыли обман
			{
				dialog.text = "ふむ。失礼だが、その包みは前に開けられていたぞ！俺にははっきり分かる。封印が押し直されているんだ…";
	        	link.l1 = ""+GetAddress_FormToNPC(NPChar)+"、それは俺が港の事務所で受け取った包みだ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"……俺にはさっぱり見当もつかねえんだ……";
	        	link.l1.go = "Postcureer_LevelUp_complete_Agentfail";
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				int iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money)/(sti(iTime)+1));//сильно снижаем оплату
				dialog.text = "待っていたんだ。だが、お前は "+FindRussianDaysString(iTime)+" 遅い！お前が持ってきた情報はもうあまり役に立たねえ……まあ、まだ多少の価値はあるから、ちゃんと金は払うぜ "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+"。どうぞ、この金を受け取ってくれ、そして達者でな。";
	        	link.l1 = "ありがとよ。まあな。";
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
				dialog.text = "やっぱりお前か！ずいぶん待ってたんだぜ、荷物を取り戻すために手も打ったんだ。さあ、それを渡せ。 お前が来るタイミングが良かったから、今はもう必要ないんだが、俺の手元に置いておきたいんだ\n分かるだろうが、報酬は払えねえ。ただし、お前の名誉は必ず回復させてやる。";
	        	link.l1 = "ありがとう…だと思うぜ。遅れてすまねえ、本当に申し訳ねえ。じゃあな。";
	        	link.l1.go = "Postcureer_LevelUp_complete_bad";
				break;
			}
			dialog.text = "待っていたぞ。ちょうどいいタイミングだ、お前が持ってきた情報は役に立つぜ。さあ、この金を受け取ってくれ、 お前の働きへの報酬だ― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+"。助かったぜ、いいタイミングだった。";
        	link.l1 = "どういたしまして。じゃあな！";
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
			dialog.text = "ああ、こうなるって分かってたさ……軍用の伝令船を雇うべきだったな、民間の船長なんかじゃなくて……まあ、どうでもいいさ。 "+GetAddress_Form(NPChar)+"、お前は兵士じゃねえから、責めることなんて何もねえよ。じゃあな。";
			link.l1 = "「じゃあな。」 "+GetAddress_FormToNPC(NPChar)+".";
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
			dialog.text = "旦那、俺はここの港長を知ってるぜ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+" 個人的には、彼は正直な男だ。しかも、あの包みを開ける理由はなかったんだ。 "+GetAddress_Form(NPChar)+"「お前は詐欺師だ！一文たりとも払わねえぞ。さっさと失せろ！」";
			link.l1 = "ふむ……";
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
			dialog.text = "歩くゴミみてえだったな。浮浪者か貧乏人だろうよ。どこに行ったかはっきり分かんねえ、 俺は後を追う気にもならなかったぜ。";
			link.l1 = "無いよりはマシだな。ありがとう！行くとするか。";
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
			else {Dialog.Text = "少し前に、シント・マールテン沖でイギリスの船が拿捕されたんだ。乗ってたのは偉い将校たちだったらしい。 ウィレムスタッドに送ることになったが、今はこの町の快適な牢屋に入れられてるんだよ。捕まった兵士の一人が、 イギリスが将校を救い出すために襲撃隊を送り込むつもりだって、うちの司令官に話したって噂だ。それで、 うちの古株司令官は準備万端で武装してるってわけさ。そりゃそうだろ？囚人が逃げたら、 司令官だってただの兵隊に降格されちまうからな！";}
			link.l1 = "面白いな……よし、金はお前のものだ。これを受け取れ。ほかに何か言いたいことはあるか？";
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
            Dialog.Text = RandPhraseSimple("よし、分かった。荷物はここにある、受け取れ\nもうここには来るな、俺にも話しかけるな、危険すぎるんだ。外では気をつけろよ……","ふむ、わかった。包みを持って、さっき話した男に必ず届けろ\nじゃあな、もう俺に話しかけるなよ、危険すぎるんだ。");
            link.l1 = RandPhraseSimple("了解だ。じゃあな…","じゃあな、幸運を祈るぜ。");
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
			dialog.text = "知っている。彼の名前はガスパール・パルマンティエだが、友人たちはゴールドトゥースと呼んでいる。信頼できる男で、 何よりも、金貸しですら想像できないほどの量を買い付けている。きっとすぐに話が合うだろう。ただし覚えておけ、 彼はよそ者が嫌いだ。訪ねるなら、必ず私の紹介だと伝えろ。彼の家は港湾管理局の近くだ。";
			link.l1 = "さて、報酬に値するな — 受け取れ。他に何か気になる話はあるか？";
			link.l1.go = "rumours_tavern";
			AddDialogExitQuestFunction("CreateGaspar_Sandbox");
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Грабеж среди бела дня, попытка залезть в сундуки
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "Man_FackYou":
			dialog.text = LinkRandPhrase("真っ昼間に強盗だと！？本当かよ！？そこを動くな、相棒…","おい、そこで何してやがる！？誰かが俺を盗もうとしてたみてえだな。もう終わりだぜ……","待て、どこへ行くんだ？泥棒だ！ここまでだぜ、相棒…");
			link.l1 = LinkRandPhrase("くそっ！","「カランバ！」","くそっ！");
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
