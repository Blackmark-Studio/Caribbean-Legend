// диалоги персонажей по пиратской линейке // Addon 2016-1 Jason пиратская линейка
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "何の用だ？";
			link.l1 = "俺は行くべきだな……";
			link.l1.go = "exit";
		break;
		
		// Лопе Монторо
		case "Mtr_officer":
			if (pchar.questTemp.Mtraxx != "fail" && pchar.questTemp.Mtraxx == "jewelry_5")
			{
				pchar.quest.Mtraxx_JewelryHavanaOver.over = "yes"; //снять таймер
				dialog.text = "ったく、てめえは一体何者だ！？";
				link.l1 = "ごきげんよう、ロペ旦那。まだお互いに面識はありませんが、今こそご挨拶するのに良い機会でしょう。特に、 今はあなたがこの困難な状況から抜け出すお手伝いをしたくてたまらないのですから……";
				link.l1.go = "Mtr_officer_1";
			}
			else
			{
				dialog.text = "何の用だ？";
				link.l1 = "俺は行くべきだな……";
				link.l1.go = "exit";
			}
		break;
		
		case "Mtr_officer_1":
            dialog.text = "助けてくれる？俺を？なんてこった、状況が一変したな！旦那、一体どこからそんな親切心が湧いてきたのか、 教えてくれないか？";
			link.l1 = "かしこまりました。俺はお前たちの元船長エスベルド・カバナスを探しているんだが、あまり時間がない……できれば、あいつが秘密にしているあの場所で会いたい。できれば、あいつより先にそこへ着きたいんだ。";
			link.l1.go = "Mtr_officer_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_2":
            dialog.text = "ははっ！この哀れな間抜けには黙ってろって言っただろうが！青い琥珀のことだろ、そうじゃねえか？";
			link.l1 = "考え方は正しいぞ、旦那。";
			link.l1.go = "Mtr_officer_3";
		break;
		
		case "Mtr_officer_3":
            dialog.text = "それでは急ごう。ここから俺を助け出してくれたら、細かいことまで全部話してやるよ。 どうして俺がこんな穴蔵にいるか、知ってるか？";
			link.l1 = "全体的には、そうだな。";
			link.l1.go = "Mtr_officer_4";
		break;
		
		case "Mtr_officer_4":
            dialog.text = "あの時は俺、酔い潰れてたんだよ。くそっ、あの忌々しいバーテンダーめ！何も覚えちゃいねえ。全部聞かされたのは、『 カンタヴロ』の船倉で目を覚ました時だった。もし俺たちがさっさと出航してりゃ、 司令官もアルカルデも見逃してくれるつもりだったんだ。だが、 あのドン・エスベルドの野郎が俺を牢にぶち込んだんだよ。お前は“正義のため”にやったと思うか？冗談じゃねえ、あのろくでなしは俺の琥珀の取り分を横取りしたかっただけさ。 浜辺で見つけた以上に水中にもっと琥珀があるかもしれないって言い出したのも、手に入れる方法を見つけたのも俺だぜ。 俺はがっぽり分け前をもらうはずだったのに……くそっ、あの野郎！……まあ、その話はもういい。アルカルデも司令官も、ドン・デ・トレドも、俺がここで腐ってるのを快く思っちゃいねえ。 もしあの百姓と、鳩小屋をかき回したあの牛みてえな女房がいなけりゃ……まあ、どっちにしろ、お前が俺を助けても誰も文句は言わねえさ。総督に話してくれ、 ヨーロッパ時代の古い友人ってことにしてくれ――俺がちゃんと証言する。ところで、お前の名前は何だ？";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "Mtr_officer_5";
		break;
		
		case "Mtr_officer_5":
            dialog.text = ""+GetFullName(pchar)+"、素晴らしい。ドン・ディエゴ・デ・トレドのところへ行って助言を求めな。覚えておけ、猶予は三日だけだ。 それを過ぎて『カンタブロ』を追っても無駄だぜ。俺を解放してくれれば、 カバナスの野郎に対処するために必要なものは全部渡してやる。";
			link.l1 = "すぐに総督に会いに行くぜ、ロペ旦那。この状況をお互いのために解決できるよう全力を尽くす。";
			link.l1.go = "Mtr_officer_6";
		break;
		
		case "Mtr_officer_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_6";
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_1", "8");
			SetFunctionTimerCondition("Mtraxx_TimeclearPrison", 0, 0, 4, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddLandQuestMark(characterFromId("Havana_Mayor"), "questmarkmain");
		break;
		
		case "Mtr_officer_7":
			pchar.quest.Mtraxx_TimeclearPrison.over = "yes"; //снять таймер
            dialog.text = "なるほど、あのペテン師とそのガタガタうるさい雌鶏が復讐を果たしたってわけだな。 これでやっとこの穴蔵ともおさらばだ。感謝するぜ、旦那、あんたは自分の役目を果たした。\n今度は俺の番だ。";
			link.l1 = "聞いてるぜ！";
			link.l1.go = "Mtr_officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_8":
            dialog.text = "よし。前回の哨戒中、嵐に巻き込まれて航路を外れてしまったんだ。仕方なく西インディアスの海岸、 モスキート海岸の近くに上陸して、真水を補給した。そこで青い琥珀の豊かな鉱床を発見したんだ。 俺がちょっと探ってみたら、水中に山ほど埋まっていた。だが、それを集めるにはもっと良い道具が必要だったから、 後で戻ることにしたんだ。\nエスベルドはハバナでインディオたちに潜らせて琥珀を集めるため、ロングボートを五隻買った。あとは知ってるだろう――あの悪党は俺を追い出して、船で逃げやがった。モスキート海岸のブルーウェルドの北でそいつを探せ。急げ――俺の勘じゃ、そこに着くまで七日ほどしかない。あいつが琥珀を集めてる最中に捕まえて、全部奪い取って、 腹を何度も刺してやれ。だが気をつけろよ、俺の元船長は腕の立つ戦士であり船乗りだ。幸運を祈るぜ、旦那。";
			link.l1 = "ロペ、お前もな。じゃあな！";
			link.l1.go = "Mtr_officer_9";
		break;
		
		case "Mtr_officer_9":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_10";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Roger_1", "12");
			SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 7, false); // таймер
			pchar.quest.mtr_jewelry_gulf.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_gulf.win_condition.l1.location = "Santacatalina";
			pchar.quest.mtr_jewelry_gulf.function = "Mtraxx_JewelryGulf";
			DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
			DelMapQuestMarkCity("Havana");
			AddMapQuestMarkShore("Shore53", true);
		break;
		
		// Росарио Гусман
		case "Mtr_rosario":
            dialog.text = "何かお尋ねになりますか、旦那？";
			link.l1 = "ドン・モントロの件だが、俺たちは古い知り合いでな、やつの不運を知ったときは本当に心を痛めたぜ。 ドン・ディエゴ・デ・トレドが俺をお前のもとに寄越したんだ。お前がすでに我々 共通の友人を解放しようとしたと聞いている……";
			link.l1.go = "Mtr_rosario_1";
		break;
		
		case "Mtr_rosario_1":
            dialog.text = "ふむ…旦那、これはちょっと…予想外だが、ロペの友人に会えて嬉しいぜ！あいつはもうしばらく運が悪かったんだが、今度はこれか…";
			link.l1 = "俺たちに何ができる？あんな高貴なイダルゴが社会のクズどもと一緒に朽ち果てるなんて、ありえねえだろう！";
			link.l1.go = "Mtr_rosario_2";
		break;
		
		case "Mtr_rosario_2":
            dialog.text = "商売人か！貧乏なロペを助けるのは簡単なようで難しいんだ。ロペが運悪く口論したあの守銭奴と話をしたんだが、 奴は五百ドゥブロンで手を打つと言ってきた。自分と妻の「苦しみ」のために、かなりの額だよ。残念ながら、 俺が集められたのは必要な額の半分、二百五十ドゥブロンだけなんだ。";
			link.l1 = "「つまり、あと二百五十ドゥブロン持ってくれば、ドン・ロペは解放されるんだな？」";
			link.l1.go = "Mtr_rosario_3";
		break;
		
		case "Mtr_rosario_3":
            dialog.text = "ああ。あの欲深い野郎は、ロペが被害の全額を補償したと皆に言いふらすと約束したんだ。\nそれに、総督に自分の赦免も頼むそうだぜ。";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "今、必要な金は持ってるぜ。ほら、この強欲なブルジョワに喉詰まらせてやれ。";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "できるだけ早く金を用意できるように頑張るぜ。";
			link.l2.go = "Mtr_rosario_5";
		break;
		
		case "Mtr_rosario_4":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "自分の耳が信じられん！旦那、あなたはきっと神様に遣わされたに違いない！";
			link.l1 = "「いつあいつを解放するんだ？」";
			link.l1.go = "Mtr_rosario_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_rosario_5":
            dialog.text = "それは嬉しいぜ、旦那。お前はロペの本当の友であり、真の貴族だ。";
			link.l1 = "じゃあな！";
			link.l1.go = "Mtr_rosario_6";
		break;
		
		case "Mtr_rosario_6":
            DialogExit();
			AddQuestRecord("Roger_1", "10");
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_7":
            dialog.text = "金は持ってきたか？";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "今、必要な金は持ってるぜ。ほら、この強欲なブルジョワに喉を詰まらせてやれ。";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "まだ取り組んでいるところだ。";
			link.l2.go = "Mtr_rosario_7_1";
		break;
		
		case "Mtr_rosario_7_1":
            DialogExit();
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_8":
            dialog.text = "今夜、あのずる賢い野郎に金を持っていくぜ。\n昼までには俺たちの仲間の釈放命令が出るはずだ。\nそれから、みんなで集まって祝えるといいな？";
			link.l1 = "もちろんだ、ロサリオ旦那。そろそろ行くぜ。またな！";
			link.l1.go = "Mtr_rosario_9";
		break;
		
		case "Mtr_rosario_9":
            DialogExit();
			AddQuestRecord("Roger_1", "11");
			npchar.lifeday = 1;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			npchar.dialog.currentnode = "Mtr_rosario_10";
			pchar.quest.mtr_prisoner.win_condition.l1 = "Timer";
			pchar.quest.mtr_prisoner.win_condition.l1.date.hour  = 12;
			pchar.quest.mtr_prisoner.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtr_prisoner.function = "Mtraxx_PrisonerFree";
		break;
		
		case "Mtr_rosario_10":
            dialog.text = "すぐに俺たちの仲間は自由になるぜ！";
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Mtr_rosario_10";
		break;
		
		// Лысый Джеффри
		case "Jeffry":
			pchar.quest.Mtraxx_SilkCPVOver.over = "yes"; //снять прерывание
            dialog.text = "おい、てめえ、俺の船で何してやがるんだ？招いた覚えはねえぞ、ああ？";
			link.l1 = "落ち着け、Geffrey。俺は船の絹取引の件でTyrexから来たんだ。";
			link.l1.go = "Jeffry_1";
		break;
		
		case "Jeffry_1":
            dialog.text = "あ、ああ、まあ、じゃあ話そうか。あいつは何を企んでるんだ？俺はもう密輸業者たちと話をつけてあるぜ。 俺の考えじゃ、あいつらは品物にちゃんとした値をつけてくれるんだがな……";
			link.l1 = "「それで、もし聞いてもいいなら、いくらなんだ？」";
			link.l1.go = "Jeffry_2";
		break;
		
		case "Jeffry_2":
            dialog.text = "1,300ペソで一巻きだ。いい値段だと思うぜ。";
			link.l1 = "ああ、それにな、タイレックスはパン一個につき金貨4枚を要求してるんだ。一枚たりともまけねえってさ。しかもドゥブロン金貨限定だ。 あいつはその値段で買ってくれる相手を探せって仕事を俺に押し付けやがったんだ。";
			link.l1.go = "Jeffry_3";
		break;
		
		case "Jeffry_3":
            dialog.text = "ハハハ、坊主、お前は運がいいじゃねえか！マーカスは食欲旺盛だぜ！まあ、そんな買い手を探してみな、 あんたが苦労するのを見物するのも面白そうだな。";
			link.l1 = "ああ、まったく、すげえおかしくて笑える話だな。俺が嬉しそうに見えるか？見えねえだろ。だから、 さっさと笑うのをやめて手を貸せよ。";
			link.l1.go = "Jeffry_4";
		break;
		
		case "Jeffry_4":
            dialog.text = "わかった、わかったよ、相棒……ったく、お前は冗談が苦手なんだな？まあいいさ、タイレックスの妄想のせいでお前を責める気はねえ、 俺たちみんながこの件で痛い目見るんだ、信じろよ。で、俺に何を手伝えってんだ？店じゃ売れねえし、税関も無理だ、 残るは密輸業者だけだぜ。他に誰が欲しがるんだ？何か考えはあるか？";
			link.l1 = "イスパニョーラの時からずっと考えていたんだ……まあいい。定期的な買い手を見つけるまであと二ヶ月しかねえ。このままじゃまずい。お前たちへの命令は、 最も近い入り江に上陸して修理を行うことだ。\n";
			link.l1.go = "Jeffry_5";
		break;
		
		case "Jeffry_5":
            dialog.text = "二ヶ月だと！？なんだと、くそっ。まあいいや。「スネーク」は修理と掃除が必要だし、 このままじゃバルク船すら追えねえからな。おい、フランスの売女ども！ ハゲのジェフリーの船員たちはカプスターヴィルに二ヶ月滞在だぜ！ハハハハ！…まあ、あんたの無駄な捜し物に幸運を祈るぜ。もしこのクソったれな絹にマーカスの値段を払うバカを見つけたら――俺の居場所は分かってるだろ。";
			link.l1 = "待て！この絹を一反だけくれ。品物を買い手候補に見せる必要があるんだ。";
			link.l1.go = "Jeffry_6";
		break;
		
		case "Jeffry_6":
            dialog.text = "ああ、問題ないぜ。ロングボートで持っていっていいぞ……おい野郎ども！絹の俵を一つ船長の船に積み込め！\n";
			link.l1 = "よし。じゃあ、買い手を見つけたらまた会おうぜ！";
			link.l1.go = "Jeffry_7";
		break;
		
		case "Jeffry_7":
            DialogExit();
			AddQuestRecord("Roger_2", "3");
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
			pchar.questTemp.Mtraxx = "silk_2";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Mtraxx_SilkTimeOver", 0, 0, 61, false); // таймер
		break;
		
		case "Jeffry_8":
            dialog.text = "他に何かあるか、相棒？";
			link.l1 = "今のところ何もない……";
			link.l1.go = "Jeffry_8_1";
		break;
		
		case "Jeffry_8_1":
            DialogExit();
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
		break;
		
		case "Jeffry_9":
			pchar.quest.Mtraxx_SilkTimeOver.over = "yes";
            dialog.text = "調子はどうだ、相棒？";
			link.l1 = "順調だ。買い手を見つけたぜ。1巻につき5ドゥブロンだ。タイレックスも気に入ると思うぜ。";
			link.l1.go = "Jeffry_10";
		break;
		
		case "Jeffry_10":
            dialog.text = "まさか！お前は本当に抜け目のない悪党の息子だな！どうやってそんなことやったんだ、え！？";
			link.l1 = "長い話になるが、ジェフリー。今からよく聞け。ジャマイカのケープ・ネグリルには10日から15日の間に到着しろ。夜にあそこでお前を待っているはずだ。合言葉は「リヨンの商人」だ。わかったか？ もう一度言ってみろ。";
			link.l1.go = "Jeffry_11";
		break;
		
		case "Jeffry_11":
            dialog.text = "リヨンから来た商人か。了解だ。俺の会計係に書き留めさせるとしよう。ここで字が書けるのはあいつだけだからな。 ははっ！";
			link.l1 = "船倉に百個のロールがあるか？";
			link.l1.go = "Jeffry_12";
		break;
		
		case "Jeffry_12":
            dialog.text = "もっとあるぜ。";
			link.l1 = "素晴らしい。さあ、出航の時だ。俺をがっかりさせるなよ！";
			link.l1.go = "Jeffry_13";
		break;
		
		case "Jeffry_13":
            dialog.text = "安心しろよ、相棒、すべてちゃんとやってやるぜ。";
			link.l1 = "ご武運を、Geoffrey。また会えるかもしれねえな。";
			link.l1.go = "Jeffry_14";
		break;
		
		case "Jeffry_14":
            DialogExit();
            AddQuestRecord("Roger_2", "22");
			pchar.questTemp.Mtraxx = "silk_14"; // к Тираксу
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_12";
			pchar.quest.mtraxx_hide_jeffry.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_hide_jeffry.function = "Mtraxx_SilkHideJeffry";
		break;
		
		case "Jeffry_15":
            dialog.text = "ホッホッホ！狡猾なチャーリー・プリンスが直々に現れたか！また会えて嬉しいぜ、相棒！";
			link.l1 = "禿げ頭のジェフリー！チャーリー・プリンスだと？はっ！";
			link.l1.go = "Jeffry_15x";
		break;
		
		case "Jeffry_15x":
            dialog.text = "お前の姓は聞いたことがねえな？今じゃラ・ベガでそう呼ばれてるぜ。";
			link.l1 = "チャーリーがどこから来たかは分かったが、プリンスはなぜなんだ？";
			link.l1.go = "Jeffry_15y";
		break;
		
		case "Jeffry_15y":
            dialog.text = "へっ、お前はラ・ベガで唯一の貴族野郎だな！ハハハ！元気にしてるか？パスクァーレの店に行ったか？ あのクソジジイから物資を買ったのか？";
			link.l1 = "「二度とごめんだ！」";
			link.l1.go = "Jeffry_16";
		break;
		
		case "Jeffry_16":
            dialog.text = "ケッハ！なんだ、あいつが気に入らなかったのか？ラムの値段で塩漬け牛肉を売りつけられたのか？";
			link.l1 = "もっとひどいぜ！あいつからエボニーを積んだオランダの隊商の情報を手に入れたんだ。見つけるのも、 商船に乗り込むのも簡単じゃなかったし、さらにそのクソみたいな木材を何十匹ものネズミどもから守るのも大変だった！ それでどうなったと思う、ゲフリー？あの野郎、一つにつきたったの百五十ペソしか払いやがらねえんだぜ。 クソみたいなエボニー一本につきだぞ、ゲフリー！";
			link.l1.go = "Jeffry_17";
		break;
		
		case "Jeffry_17":
            dialog.text = "よくあることさ、相棒、俺が保証するぜ。ラヴォワジエはお前みたいないい奴をすでに十人は騙してるんだ。 やつが何か払ったって？あいつにしちゃ珍しいことだぜ。俺たちは、どんなに腹が減ってても、あいつの“情報”なんかには手を出さねえよ。";
			link.l1 = "ありがとう、相棒。少なくとも俺が最初で唯一の間抜けじゃなかったってわかったぜ！だが今度ばかりはあの野郎、 自分で墓穴を掘ったんだ。俺が必ず後悔させてやるからな。";
			link.l1.go = "Jeffry_18";
		break;
		
		case "Jeffry_18":
            dialog.text = "おいおいおい！待てよ、プリンス、ちょっと落ち着け。この商人には手を出すな。 こいつを襲えばマーカスが黙っちゃいねえぞ。なあ、ラヴォワジエにお前を送ったのはタイレックスか？";
			link.l1 = "ふむ。そうだな……なぜだ？";
			link.l1.go = "Jeffry_19";
		break;
		
		case "Jeffry_19":
            dialog.text = "聞けよ……（声を潜めて）四つ目はマーカスとつるんでるって話だ。今ならわかるだろ？ だからラヴォワジエの船には誰も手を出さねえ、逆らったら終わりだからな。";
			link.l1 = "了解した。警告ありがとう、Geffrey。じゃあな、幸運を祈るぜ！";
			link.l1.go = "Jeffry_20";
		break;
		
		case "Jeffry_20":
            dialog.text = "「お前もな、相棒。」";
			link.l1 = "...";
			link.l1.go = "Jeffry_21";
		break;
		
		case "Jeffry_21":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Roger_4", "10");
			CloseQuestHeader("Roger_4");
			QuestSetCurrentNode("Terrax", "mtraxx_34"); // релиз-правка
			bDisableFastReload = false;
			pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират
			pchar.questTemp.CharleePrince = true; // атрибут для найма команды 
		break;
		
		case "Jeffry_22":
            dialog.text = "ホーホーホー、王子！誰が花火を上げたのかと思ってたぜ！スペイン野郎かもしれねえから、 マスケット兵の部隊を連れてきたんだ。";
			link.l1 = "「ジェフリー？お前もここにいるのか？でもどうしてだ？お前も宝の地図を買ったのか？」";
			link.l1.go = "Jeffry_23";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
		break;
		
		case "Jeffry_23":
            dialog.text = "相棒、そんなガラクタに金なんて使わねえよ。俺が手に入れたのは、 どこかの旅人がこの地下牢への安全な道について書いた日記だ。";
			link.l1 = "誰がそれを持ってきたんだ？";
			link.l1.go = "Jeffry_24";
		break;
		
		case "Jeffry_24":
            dialog.text = "ただのジャンキーさ。酒を飲むために百ペソ欲しかっただけだ。";
			link.l1 = "トルトゥーガで起こったのか？";
			link.l1.go = "Jeffry_25";
		break;
		
		case "Jeffry_25":
            dialog.text = "いや、違う。バルバドスだったか？旦那、なんでそんなに心配してるんだ？人数が多けりゃ多いほど、 宝を運ぶのも早くなるだろうが！";
			link.l1 = "気に入らねえな。こんな偶然、信じられねえ。これを書いたのはカミラの父親ってことか？";
			link.l1.go = "Jeffry_26";
		break;
		
		case "Jeffry_26":
            dialog.text = "カミラって誰だ？";
			link.l1 = "この場所への地図を二百ペソで俺に売りつけたあの女だ！";
			link.l1.go = "Jeffry_27";
		break;
		
		case "Jeffry_27":
            dialog.text = "へっ…王子、考えすぎだぜ。宝探しに行こうぜ。さあ、行くぞ！";
			link.l1 = "必要ない。もう見つけた……奴らは下の地下牢、鉄格子の向こうにいる。俺たちで助け出さなきゃならねえ。聞けよ、ジェフリー、もう一つある！ カトラスのペリーもここに来てたんだ！\n";
			link.l1.go = "Jeffry_28";
		break;
		
		case "Jeffry_28":
            dialog.text = "カトラスか？そりゃあ運がいい日だぜ！でも、そいつは今どこにいるんだ？";
			link.l1 = "下に……死んでいる。俺は宝の近くであいつに会ったんだ。欲に狂って叫び始めた。そしたら、 あいつと仲間たちが俺を襲ってきたんだ。";
			link.l1.go = "Jeffry_29";
		break;
		
		case "Jeffry_29":
            dialog.text = "ふむ……ペリーはいつも金運が悪かったからな。あの大量の金を見て、きっと正気を失ったんだろう。";
			link.l1 = "そうかもしれねえ……だが、ジェフリー、お前は分かってねえ！俺たち三人全員がここに来たんだぜ！しかも同じ手がかりを掴んでな！ 偶然だと思うのか？誰かが明らかに俺たち全員をここに集めたがってるんだよ、そしてこの場所……まるで墓場みてえじゃねえか。";
			link.l1.go = "Jeffry_30";
		break;
		
		case "Jeffry_30":
            dialog.text = "でも金を見たか？";
			link.l1 = "俺のこの目で見たんだ。巨大な宝箱がいくつもあって、中にはコインや金塊がぎっしり詰まってたぜ。";
			link.l1.go = "Jeffry_31";
		break;
		
		case "Jeffry_31":
            dialog.text = "それなら、なぜ心配するんだ、殿下？案内してくれ、お前の金塊を見せてもらおう。そしたら金を分け合おうじゃねえか。 ";
			link.l1 = "ああ、お前の言う通りかもな、どうでもいいぜ…行こう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionWithJeffry");
		break;
		
		case "Jeffry_32":
            //PlaySound("Voice\English\LE\Jeffry\Jeffry_gold.wav");
			dialog.text = "なんて見ものだ！すごい金貨の山じゃねえか！これじゃカトラスが狂ったのも無理はねえな。俺たちは本当に運がいいぜ、 プリンス！どう思う？ここでどれくらいの金貨が見つかると思う？\n";
			link.l1 = "たっぷりあるさ。この金塊を片付ければ、はっきりするだろうぜ。";
			link.l1.go = "Jeffry_33";
		break;
		
		case "Jeffry_33":
            dialog.text = "ああ、この格子はすごく頑丈だ。素手でも剣でも壊せねえよ。お前の言う通りだ、相棒――道具か大量の火薬を探さなきゃな。おい、見ろよ！あれは何だ！？";
			link.l1 = "...";
			link.l1.go = "Jeffry_34";
		break;
		
		case "Jeffry_34":
            DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionJeffryMushketer", 0.1);
		break;
		
		case "Jeffry_35":
            PlaySound("Voice\English\LE\Jeffry\Jeffry_mozila.wav");
			dialog.text = RandSwear()+"なんて血まみれの間抜けだ！";
			link.l1 = "てめえ、このクソ蛇野郎め！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionJeffryFight");
		break;
		
		// Билли Сипатый
		case "Billy":
			pchar.quest.Mtraxx_BillySeaTimeOver.over = "yes"; //снять таймер
			PlaySound("VOICE\English\LE\Billy\Billy_01.wav");
            dialog.text = "今年「フライフィッシュ号」でこんなことが起きるなんて、サメに食われちまえってんだ……おい野郎ども、客人だぞ！おい、相棒、お前の人生で何がそんなに悪かったんだ、 わざわざ俺のオンボロ船に来るなんてよ？";
			link.l1 = "「よう！お前が“ハスキー・ビリー”って呼ばれてる奴だろ？」";
			link.l1.go = "Billy_1";
		break;
		
		case "Billy_1":
            dialog.text = "俺の声でわからねえのか、船長？昔はこの声でイギリスやスペインの商人どもをビビらせてやったもんだ。 あの頃は栄光の日々だったぜ！…今じゃ、年老いたビリーが大事なロングボートでお気に入りの島の岸辺で人生の終わりを待ってるってわけさ…";
			link.l1 = "ビリー、お前に商売の話があるんだ。ジャマイカ周辺で何が起きてるか全部知ってるって聞いたぜ。本当か？";
			link.l1.go = "Billy_2";
		break;
		
		case "Billy_2":
            dialog.text = "そう言われたんなら、そうなんだろうよ、そう思わねえか？カニのキンタマ引っ張るような真似はやめて、さっさと話せ。 俺に何の用だ？";
			link.l1 = "よし。ポートロイヤルには船大工がいる。あいつは客に特別なサービスを提供していて、 その製造やサービスに船用のシルクが必要なんだ。だが、この品の取引はここじゃ違法だから、 違法な仕入れ先を見つけたらしい。誰がどうやって船用シルクを渡しているのか、俺は知りたいんだ。";
			link.l1.go = "Billy_3";
		break;
		
		case "Billy_3":
            dialog.text = "ホッホッホ、見ろよこれ！ドイル大佐のために働いてるのか、坊や？";
			link.l1 = "またかよ！いや、俺はマーカス・タイレックスと組んでるんだ。あいつは船用の絹市場に手を出したがっててな、 この船大工は“見知らぬ”奴らと関わるのが怖くて仕方ねえんだよ……";
			link.l1.go = "Billy_4";
		break;
		
		case "Billy_4":
            dialog.text = "おお、コードキーパーのために働いてるってわけか！そいつはいい知らせだ……もちろん、嘘じゃなければな。船大工なんざどうでもいい、ひとり捕まえりゃ、また別の奴が出てくるだけだ。だが、 俺の古女房――『フライングフィッシュ』のことは気にかかる。今、あの船はひどい有様なんだ。わかるか？\n新しいロングボートをもう一隻、それとお前が言ってるのと同じ船用シルクの反物を持ってきてくれ。 ビリーがそれでちゃんとした帆を作る、そうすりゃ巡回船なんざ出し抜けるってもんさ、ハハハ！その代わりに、 ビリーが船大工とシルクの仕入れ先について全部教えてやる。信じな、坊主。お前が知りたいことは全部俺が知ってる。 ただ、お前が本物の海賊か、それとも尻舐め野郎の赤服か確かめたいだけだ！";
			link.l1 = "新しいロングボートが欲しいのか？だったら自分で買えるだけの金をやるぜ。おまけもつけてやるよ。";
			link.l1.go = "Billy_5";
		break;
		
		case "Billy_5":
            dialog.text = "へっ、船長、年寄りのビリーはこの街じゃ歓迎されねえんだ。ポートロイヤルじゃ俺のことをよく覚えてやがるし、 あの岩場で昔の仲間と一緒に首を吊られるのはごめんだぜ。だからな、息子よ、 お前が新品のロングボートを持ってきてくれるのを待ってるぜ。ネグリル岬で三日間待ってるからな。 絹のことも忘れるんじゃねえぞ！";
			link.l1 = "よし、ビリー。お前にはロングボートと帆布を一巻きやる。すぐ戻るからな。";
			link.l1.go = "Billy_6";
		break;
		
		case "Billy_6":
            dialog.text = " 承知した、船長。ビリーが岸で待っているぜ。またすぐ会おう！";
			link.l1 = "...";
			link.l1.go = "Billy_7";
		break;
		
		case "Billy_7":
            DialogExit();
			AddQuestRecord("Roger_2", "8");
			npchar.dialog.currentnode = "Billy_8";
			pchar.questTemp.Mtraxx = "silk_7";
			SetFunctionTimerCondition("Mtraxx_BillyTimeOver", 0, 0, 3, false); // таймер
			pchar.quest.mtr_billy_coast.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtr_billy_coast.win_condition.l1.location = pchar.location;
			pchar.quest.mtr_billy_coast.function = "Mtraxx_BillyOnCoast";
			locations[FindLocation("shore35")].DisableEncounters = true; //энкаутеры закрыть
			npchar.DontDeskTalk = true;
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "Billy_8":
			PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
            dialog.text = "何だと？もう俺にロングボートを持ってきたのか？";
			link.l1 = "お前は冗談好きだな、坊や、なあ、ビリー？";
			link.l1.go = "exit";
		break;
		
		case "Billy_9":
            dialog.text = "それで、船長、俺の新品のロングボートはどうなったんだ？";
			if(Companion_CheckShipType(SHIP_TARTANE) && GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0)
			{
				link.l1 = "終わったぜ、ハスキー。あの女は船倉に船用シルクの反物と一緒に届けておいた。 お前の古いポンコツ船は好きに沈めていいぜ。";
				link.l1.go = "Billy_11";
			}
			else
			{
				PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
				link.l1 = "まだ取り組んでいる。待ってくれ。";
				link.l1.go = "Billy_10";
			}
		break;
		
		case "Billy_10":
			DialogExit();
			npchar.dialog.currentnode = "Billy_9";
		break;
		
		case "Billy_11":
			PlaySound("VOICE\English\LE\Billy\Billy_03.wav");
			pchar.quest.Mtraxx_BillyTimeOver.over = "yes"; //снять прерывание
            dialog.text = "ちくしょう！こんなに嬉しい知らせはビリーじいさんにとって五年ぶりだぜ！へっ、この瓶を開けるには最高の理由だな…";
			link.l1 = "俺は遠慮しとくぜ。で、絹の仕入れ先の話はどうなった？";
			link.l1.go = "Billy_12";
		break;
		
		case "Billy_12":
            dialog.text = "残念だな、俺の新しい『フライング・フィッシュ号』で乾杯できたのによ！まあいい……聞けよ、息子よ\n毎月10日から15日の間に、イングランドの旗を掲げたブリガンティンがポートランド・コーブにやって来るんだ。 もし本当にイングランド船なら、俺は死ぬまでラムを飲まねえよ！その船の名は『ユトレヒト』、南西――キュラソーがある方角から来るんだ。明らかにオランダ船の船長だ、見ればわかる\n毎回同じ連中が浜辺で出迎えてるが、あのずる賢い船大工の親方が仕切ってる。 やつがオランダ人が荷下ろしする船絹の受取人さ。間違いなく船絹だ、あんな梱包はオランダ人しかやらねえからな。";
			link.l1 = "「毎月だって言ったのか？」";
			link.l1.go = "Billy_13";
		break;
		
		case "Billy_13":
            dialog.text = "ああ、坊や、去年は一月も欠かさず通ったんだぞ。あの陰気で髭面の連中と話したいなら、毎月10日から15日の夜にポートランド・コーブで待つといい。俺のロングボートの新しい絹の帆に誓って言うぜ！";
			link.l1 = "へっ！どうやら俺の金は無駄じゃなかったようだな。幸運を祈るぜ、ビリー。 巡回の連中から自分の年寄り尻をちゃんと守れよ、でなきゃ本気で怒るからな。";
			link.l1.go = "Billy_14";
		break;
		
		case "Billy_14":
            dialog.text = "ははっ、年寄りのビリーがジャマイカの海岸で本当に面白い騒ぎを起こそうとしてるぜ！\n幸運を祈るぜ、船長！狩りを楽しんでくれよ！";
			link.l1 = "「お前もだぜ、Billy！」";
			link.l1.go = "Billy_15";
		break;
		
		case "Billy_15":
            DialogExit();
			npchar.lifeday = 0;
			pchar.questTemp.Mtraxx = "silk_8";
			chrDisableReloadToLocation = true;//закрыть локацию
			locations[FindLocation("shore35")].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			AddDialogExitQuestFunction("Mtraxx_BillyTakeShip");
			AddQuestRecord("Roger_2", "9");
			//
			if (GetDataDay() >= 1 && GetDataDay() <= 9)
			{
				DoQuestFunctionDelay("Mtraxx_SilkCreateSmuggler", 1.0);
			}
			
			if (GetDataDay() >= 10 && GetDataDay() <= 15)
			{
				int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+2;
				if (iRank > 45) iRank = 45;
				Group_FindOrCreateGroup("Mtr_Utreht");
				sld = GetCharacter(NPC_GenerateCharacter("Cap_Utreht", "mercen_19", "man", "man", iRank, ENGLAND, -1, true, "quest"));
				FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, "Utrecht", CANNON_TYPE_CULVERINE_LBS18, 50, 50, 50);
				FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_13", "pistol5", "bullet", 100);
				sld.name = "Joachim";
				sld.lastname = "Gusen";
				sld.DontRansackCaptain = true;
				sld.AnalizeShips = true;
				sld.Coastal_Captain = true; // правки прогона 3
				DeleteAttribute(sld, "SaveItemsForDead");
				sld.Ship.Mode = "pirate";
				SetSailsColor(sld, 2);
				sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*4;
				if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
				SetCharacterGoods(sld, GOOD_SHIPSILK, 80);

				Group_AddCharacter("Mtr_Utreht", "Cap_Utreht");
				Group_SetGroupCommander("Mtr_Utreht", "Cap_Utreht");
				Group_SetTaskAttackInMap("Mtr_Utreht", PLAYER_GROUP);
				Group_SetAddress("Mtr_Utreht", "Jamaica", "Quest_Ships", "Quest_Ship_4");
				Group_SetTaskRunaway("Mtr_Utreht", PLAYER_GROUP);
				Group_LockTask("Mtr_Utreht");
				
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1 = "Group_Death";
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1.group = "Mtr_Utreht";
				pchar.quest.mtr_silksmuggler_AfterBattle.function = "Mtraxx_SilkSmugglerAfterBattle";
				
				SetTimerFunction("Mtraxx_SilkSmugglerFail", 0, 0, 2);
			}
			
			if (GetDataDay() >= 16 && GetDataDay() <= 20)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 15);
			}
			if (GetDataDay() >= 21 && GetDataDay() <= 26)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 10);
			}
			if (GetDataDay() >= 27 && GetDataDay() <= 31)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 5);
			}
		break;
		
		// мастеровой с верфи Порт-Ройаля
		case "Mtr_acceptor_fight":
            LAi_group_Delete("EnemyFight");
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mtr_acceptor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_SilkWrongTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Mtr_acceptor":
            dialog.text = "おい、水夫、ジャマイカに着いたばかりか？";
			link.l1 = "ふむ。そうだな。どうしたんだ？";
			link.l1.go = "Mtr_acceptor_1";
		break;
		
		case "Mtr_acceptor_1":
            dialog.text = "このあたりの海で何か起きたのを見たか？";
			link.l1 = "ああ、見たぜ。あるブリガンティンがイギリスの哨戒コルベットと戦ってたんだ。イギリス野郎が激しく攻撃して、 オランダ船は逃げようとして積み荷を海に投げ捨てたんだよ。";
			link.l1.go = "Mtr_acceptor_2";
		break;
		
		case "Mtr_acceptor_2":
            dialog.text = "なぜ彼女がオランダ人だとそんなに確信しているんだ？ 正気のオランダ野郎ならポートロイヤルにこんなに近づこうなんて考えもしねえだろう…";
			link.l1 = "あの船はイギリスの旗を掲げていたが、名前は……『ユトレヒト』だ。あまりイギリスらしくねえよな？やつらはオランダ人だったんだ、きっと密輸業者かもしれねえ。 巡回隊もきっとやつらを待ち構えてたはずだぜ。";
			link.l1.go = "Mtr_acceptor_3";
		break;
		
		case "Mtr_acceptor_3":
            dialog.text = "くそっ！";
			link.l1 = "どうやらお前はこれにあまり満足してねえみたいだな……";
			link.l1.go = "Mtr_acceptor_4_1";
			link.l2 = "ここでこのブリガンティンを待っていたのか？";
			link.l2.go = "Mtr_acceptor_7";
		break;
		
		case "Mtr_acceptor_4_1":
            dialog.text = "なんで俺がそうなるんだ？";
			link.l1 = "さあ、知ってるぜ。お前が誰かも分かってる。お前はポートロイヤルの造船所の親方だろう？それに、 ブリガンティンで運ばれてくる特別な積み荷を待ってるんだろ。";
			link.l1.go = "Mtr_acceptor_wrong";
			link.l2 = "顔に全部書いてあるぜ、まさにそこにな！";
			link.l2.go = "Mtr_acceptor_4_2";
		break;
		
		case "Mtr_acceptor_wrong":
            dialog.text = "うおおっ！野郎ども、こいつらは変装した巡回隊だ！ぶっ倒してさっさとずらかるぞ！";
			link.l1 = "くそっ！待て、お前は間違っ…";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_4_2":
            dialog.text = "無礼だな、海の狼め？口の利き方に気をつけろ、さもないと……";
			link.l1 = "さあ、元気出せよ。明らかに落ち込んでるじゃねえか。まさか本当にあのオランダ野郎どもが来るのを待ってたのか？";
			link.l1.go = "Mtr_acceptor_4_3";
			link.l2 = "それともどうする？人生について説教でもするつもりか？";
			link.l2.go = "Mtr_acceptor_6";
		break;
		
		case "Mtr_acceptor_4_3":
            dialog.text = "「だから何だ？お前に関係あるのか？」";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l1 = "俺は別に待ってねえよ。ここで待ってるのはお前だろ、俺じゃない。お前には永遠の時間があるんだ。";
				link.l1.go = "Mtr_acceptor_4_4";
			}
			link.l2 = "ああ、俺には気にする理由が十分にあるんだ。ブリガンティンの貨物室に何があったか知ってるぜ。船の絹さ。 お前がここに来たのも、それが理由だろう？";
			link.l2.go = "Mtr_acceptor_wrong";
		break;
		
		case "Mtr_acceptor_4_4":
            dialog.text = "ふむ……永遠か？";
			link.l1 = "海の底から戻るのは永遠にも感じるぜ。お前のブリガンティンは哨戒コルベットに沈められたんだ、相棒。 あっけないもんさ。それでも戦争ってやつは、戦利品もあれば損失もある。 あの沈んだオランダ船で俺はいい稼ぎをさせてもらうぜ。";
			link.l1.go = "Mtr_acceptor_4_5";
		break;
		
		case "Mtr_acceptor_4_5":
            dialog.text = "「それで一体どうするつもりなんだ？」";
			link.l1 = "奴らが逃げようとして海に投げ捨てた物を俺が売るつもりだ。\nほとんどは失われちまったが、貴重な船用の絹だけはコルクみてえに浮かんでたんだ。\n大半は引き上げたから、明日には街へ行って買い手を探すつもりさ。\nどこで得をして、どこで損をするかなんて分からねえもんだぜ。";
			link.l1.go = "Mtr_acceptor_4_6";
		break;
		
		case "Mtr_acceptor_4_6":
            dialog.text = "「待て！」";
			link.l1 = "カランバ！今度は何だ？";
			link.l1.go = "Mtr_acceptor_4_7";
		break;
		
		case "Mtr_acceptor_4_7":
            dialog.text = "どれだけの絹を集めることができたんだ？";
			link.l1 = "「で、なんでお前が気にするんだ？これは俺の絹だぜ！それとも総督の犬か？お前は死…」";
			link.l1.go = "Mtr_acceptor_4_8";
		break;
		
		case "Mtr_acceptor_4_8":
            dialog.text = "剣を抜くな、水夫。俺は犬でもなけりゃ、密告者でもねえ。俺たちは地元の造船所で働いてるんだ……この絹は本来俺たちのもんで、どうやら今はお前が持ってるらしいな。全部買い取らせてもらうぜ、こいつが必要なんだ、 相棒。";
			link.l1 = "本当か？面白いな……いくらだ？";
			link.l1.go = "Mtr_acceptor_4_9";
		break;
		
		case "Mtr_acceptor_4_9":
			i = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "一巻につき二千五百だ。いい値段だぜ、これ以上は見つからねえよ。";
			link.l1 = "運が良かったみたいだぜ！俺には "+FindRussianQtyString(i)+"「金を見せてくれれば、すぐに陸に届けるよう命じるぜ。」";
			if (i > 80) link.l1.go = "Mtr_acceptor_4_11";
			else link.l1.go = "Mtr_acceptor_4_10";
		break;
		
		case "Mtr_acceptor_4_10":
            dialog.text = "「取引成立だ！」";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilk");
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		case "Mtr_acceptor_4_11":
            dialog.text = "ふん……ヨアヒムは八十巻だけ運ぶはずだった――そんなに回収できるわけがねえ……つまり、てめえは汚い手を使おうとしてるか……あるいは密告者だな！野郎ども、こいつを殺してさっさとずらかれ！";
			link.l1 = "くそっ！";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_5":
            dialog.text = "";
			link.l1 = "素晴らしい取引だぜ、相棒！なんでそんなに浮かない顔してるんだ？海の底に沈んだオランダ野郎のことが気になるのか？ こんなことはよくあるさ、気にすんなよ！";
			link.l1.go = "Mtr_acceptor_5_1";
		break;
		
		case "Mtr_acceptor_5_1":
            dialog.text = "ああ、そうだよ……あいつらはうちの常連の仕入れ先だったんだ。これからどこで絹を手に入れりゃいいんだ？いつも足りなくて、 しかも取引全体がドイル大佐の直轄なんだぜ。ちっ、くそっ……";
			link.l1 = "ふむ……聞けよ、友よ、それなら俺が手を貸してやってもいいぜ。";
			link.l1.go = "Mtr_acceptor_5_2";
		break;
		
		case "Mtr_acceptor_5_2":
            dialog.text = "へえ、本当か？それで、どうやって俺たちを助けるつもりだ？毎月百本のロールを届けてくれるってのか？";
			link.l1 = "俺か？うーん、多分違うが、マーカス・タイレックスなら知ってるはずだ。あいつのこと、聞いたことあるか？";
			link.l1.go = "Mtr_acceptor_5_3";
		break;
		
		case "Mtr_acceptor_5_3":
            dialog.text = "ケッハ！お前、海賊なのか？";
			link.l1 = "いや、俺は特別な時だけあいつらと取引するんだ。マルクスが定期的に船用の絹を仕入れて、 金さえ払える奴なら誰にでも売ってるのは間違いねえ。\nしかも、ここで言ってるのは一反につき2,500ペソなんかじゃねえぞ。一反につき金貨5ドゥブロン払えるなら、あいつは山ほど絹をくれるさ、間違いねえぜ。";
			link.l1.go = "Mtr_acceptor_5_4";
		break;
		
		case "Mtr_acceptor_5_4":
            dialog.text = "それは面白い話だな……マーカス・タイレックスだって？ドゥブロン金貨だけで……？";
			link.l1 = "さあ、相棒、お前がどこから絹を手に入れるかなんて本当に気にするのか？金は金だぜ、 銀行でペソをドブロンに両替すりゃいいだけだろ。それで、どうする？ 暗号係にお前のことをちょっと耳打ちしてやろうか？どうせ俺はラ・ベガに行くつもりだしな。";
			link.l1.go = "Mtr_acceptor_5_5";
		break;
		
		case "Mtr_acceptor_5_5":
            dialog.text = "よし、取引しよう。こちらの条件だ。毎月10日から15日の間にロールパンを100個納品してもらう。俺たちはここで待っている……いや、待て、集合場所を変えよう。ここはもう危険だ。マルーンタウン近くのネグリル岬で待つことにする、 あそこなら安全だろう。合言葉は「リヨンの商人」だ。";
			link.l1 = "取引成立だ、相棒。とんでもない航海だったぜ！タイレックスなら、 こんな買い手にはドゥブロン金貨を一つか二つは払ってくれるだろうな！ははっ！さて、俺は行くとするか。 来月タイレックスの船を待ってな。お前と家族に幸運を祈るぜ！\n";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		break;
		
		case "Mtr_acceptor_6":
            dialog.text = "俺たちが礼儀ってもんを叩き込んでやったら、人生の教訓なんてもう必要ねえだろう。";
			link.l1 = "イキがってるのか、大工？まあいい、お前のブリガンティンを待ってな。だが、しばらくかかるぜ。";
			link.l1.go = "Mtr_acceptor_6_1";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "おい、先生、俺にも教えてやりたいことがいくつかあるぜ！";
				link.l2.go = "Mtr_acceptor_6_2";
			}
		break;
		
		case "Mtr_acceptor_6_1":
            dialog.text = "大工だと？くそっ、なんで知ってやがる！？ケッ、野郎ども、こいつは変装した巡回だ！ぶっ殺してさっさとずらかるぞ！ ";
			link.l1 = "くそっ！";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_6_2":
            dialog.text = "俺たちに構うな、魚のウロコ野郎、てめえにかまってる暇はねえ。消え失せろ！";
			link.l1 = "オランダ船を待っているのか？ご苦労なこったな。これから永遠に待つことになるぜ。";
			link.l1.go = "Mtr_acceptor_4_4";
		break;
		
		case "Mtr_acceptor_7":
            dialog.text = "「何を言ってやがるんだ？」";
			link.l1 = "なるほどな。しかし、万が一お前がそうだとしても、忘れろ。哨戒コルベットのおかげで、あの女は来ねえよ。 望遠鏡で戦いの結末を見たんだ。すぐ近くで、あっという間の出来事だったぜ\n";
			link.l1.go = "Mtr_acceptor_7_1";
		break;
		
		case "Mtr_acceptor_7_1":
            dialog.text = "また、俺たちは何も誰も待っちゃいねえし……";
			link.l1 = "見ろよ、正直どうでもいいんだ。俺は街の巡回隊じゃねえし、お前が何しようが気にしちゃいねえ。 俺だって聖人じゃねえからな。密輸してるなら、それはお前の勝手だ。俺が言いたかったのは、 ただ警告してやるってことだけだ。運が良けりゃいいな、相棒。";
			link.l1.go = "Mtr_acceptor_7_2";
		break;
		
		case "Mtr_acceptor_7_2":
            dialog.text = "待て……「ユトレヒト」が本当に沈んだのか？";
			link.l1 = "まったくだ。彼女は逃げようとしたが、積荷をすべて投げ捨てて、貴重な船用の絹さえ惜しまなかったが、 そんな必死の手段もコルベットの速度の優位には太刀打ちできなかったんだ。";
			link.l1.go = "Mtr_acceptor_7_3";
		break;
		
		case "Mtr_acceptor_7_3":
            dialog.text = "なんてこった……それで俺たちは絹なしでどうしろってんだ？くそっ！";
			link.l1 = "船用の絹が必要か？";
			link.l1.go = "Mtr_acceptor_7_4";
		break;
		
		case "Mtr_acceptor_7_4":
            dialog.text = "なんで聞くんだ、売るつもりか？";
			link.l1 = "俺じゃねえが、心当たりのある男がいるぜ。そいつは気前が良くて、定期的に買ってくれる客を探してるんだ。お前、 条件に合いそうか？";
			link.l1.go = "Mtr_acceptor_7_5";
		break;
		
		case "Mtr_acceptor_7_5":
            dialog.text = "「そいつは誰だ？」";
			link.l1 = "ラ・ベガの男爵、マーカス・タイレックス――通称「コードの守り手」だ。あいつは定期的に船用の絹を仕入れてるから、いつも在庫があるんだぜ。\nお前の値が十分に高けりゃ、きっとあいつも売ってくれるだろうよ。";
			link.l1.go = "Mtr_acceptor_7_6";
		break;
		
		case "Mtr_acceptor_7_6":
            dialog.text = "なるほど、お前は海賊なのか？";
			link.l1 = "なんで気にするんだ？度胸があるなら、お前とタイレックスの間で取引をまとめてやってもいいぜ。\nその気がねえなら――じゃあな。";
			link.l1.go = "Mtr_acceptor_7_7";
		break;
		
		case "Mtr_acceptor_7_7":
            dialog.text = "わかった、わかった、そんなに怒るなよ。ああ、そうだ。俺はタイレックスと取引がしたいんだ。だが、 お前にはどんな得があるんだ？";
			link.l1 = "もし積荷にいい値をつけてくれるなら、俺の助けに対してマーカスからもそこそこの報酬がもらえそうだぜ。\nで、どうするんだ？";
			link.l1.go = "Mtr_acceptor_7_8";
		break;
		
		case "Mtr_acceptor_7_8":
            dialog.text = "1回につき5ドゥブロンだぜ。これ以上の値段はねえ、信じてくれよ。";
			link.l1 = "5枚の金貨か？ふむ、悪くねえな。こんな買い手を連れてきたら、タイレックスも俺に大きな借りができるだろう。よし、 取引成立だ、あいつに伝えてやる。ただし、もし値段について俺に嘘をついてたら、お前の首が飛ぶことになるぜ。";
			link.l1.go = "Mtr_acceptor_7_9";
		break;
		
		case "Mtr_acceptor_7_9":
            dialog.text = "心配するな、俺たちは正直者だ。条件はこうだ――毎月10日から15日の間にロールパンを100個納品してもらう。俺たちはここで待っている……いや、待て、集合場所を変えよう。この場所はもう危険だ。マルーンタウン近くのネグリル岬で待つことにする、 あそこならもっと安全なはずだ。合言葉は「リヨンの商人」だ。\n";
			link.l1 = "了解だ。最初の荷は来月届くぜ。";
			link.l1.go = "Mtr_acceptor_7_10";
		break;
		
		case "Mtr_acceptor_7_10":
            dialog.text = "「今月は絹が切れてしまったから、今回はもっと貨物を持ってきてもいいとタイレックスに伝えてくれ。」";
			link.l1 = "そうするぜ。幸運を祈る、友よ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		// Тесак Пелли
		case "Pelly":
            dialog.text = "おい！何の用で俺の船に乗り込んできたんだ、相棒？";
			link.l1 = "おい、カトラス。マーカス・タイレックスに頼まれて来たんだ。マラカイボへの行軍が俺たちを待ってるぜ。";
			link.l1.go = "Pelly_1";
		break;
		
		case "Pelly_1":
            dialog.text = "あ、ああ、やっと来たか。この航海の新しい雇い主はあんたか。いいだろう。で、俺の新しい提督の名前は何だ？";
			link.l1 = "Captain "+GetFullName(pchar)+".";
			link.l1.go = "Pelly_2";
		break;
		
		case "Pelly_2":
            dialog.text = "ご命令を、提督 "+GetFullName(pchar)+"?";
			link.l1 = "俺たちは別々にマラカイボ湖へ向かうぜ。お前は夜に到着して、こっそりグアヒラ湾に上陸しろ。 そこで俺を待っている間に、小さな野営地を作っておけ。俺はスペインの港に上陸するつもりだ。";
			link.l1.go = "Pelly_3";
		break;
		
		case "Pelly_3":
            dialog.text = "了解だぜ、提督！";
			link.l1 = "そこに着くまでどれくらいかかるんだ？";
			link.l1.go = "Pelly_4";
		break;
		
		case "Pelly_4":
            dialog.text = "ふむ……だいたい一週間くらいだな。風次第で一日早くなるか遅くなるかってところだ。";
			link.l1 = "よし。じゃあ、時間を無駄にしないでおこう。グアヒラ湾で会おうぜ、相棒。";
			link.l1.go = "Pelly_5";
		break;
		
		case "Pelly_5":
            dialog.text = "了解だ、提督！";
			link.l1 = "...";
			link.l1.go = "Pelly_6";
		break;
		
		case "Pelly_6":
            DialogExit();
			AddQuestRecord("Roger_3", "3");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			Mtraxx_PlantContinue();
		break;
		
		case "Pelly_7":
            dialog.text = "ご命令は、提督？";
			link.l1 = "今は何もない。俺たちの作戦で忙しいんだ。";
			link.l1.go = "Pelly_wait";
			if (pchar.questTemp.Mtraxx == "plant_3")
			{
				link.l1 = "岸に大きな箱を用意しろ。そこに囚われた仲間たちのための武器を集めるぞ。";
				link.l1.go = "Pelly_7_1";
			}
			if (pchar.questTemp.Mtraxx == "plant_6" && CheckAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar"))
			{
				dialog.text = "それで、ハンサムの野郎はどうなってるんだ？俺の手がドンの血をぶちまけたくてうずいてるぜ！";
				link.l1 = "思ったより厄介だな。奴が言うには、プランテーションの見張りは警戒が厳しいらしい。武器を忍び込ませるには、 商品に紛れさせるしか手がねえ。急いでコーヒーかコプラ、それかバニラの積荷を手配しなきゃならねえ――あそこの農園主はそれしか扱わねえんだ。";
				link.l1.go = "Pelly_70";
				DelLandQuestMark(npchar);
			}
			if (pchar.questTemp.Mtraxx == "plant_8" && pchar.location.from_sea == "Shore37")
			{
				link.l1 = "野営地を出て嵐部隊を集めろ。\n行進の時だ、闇に紛れて攻撃するぞ。";
				link.l1.go = "Pelly_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Pelly_wait":
             DialogExit();
			 npchar.dialog.currentnode = "Pelly_7";
		break;
		
		case "Pelly_7_1":
            dialog.text = "聞いてくれ、提督。俺、ちょっと考えてたんだ……";
			link.l1 = "なんだよ、カトラス、お前は剣を振るう代わりに頭を使うようテラックスに雇われてるのか？";
			link.l1.go = "Pelly_35";
		break;
		
		case "Pelly_8":
            dialog.text = "おおっ！プランテーションで反乱だな、提督？火の手が上がってるぜ！これで金貨を手に入れるチャンスだ！..";
			link.l1 = "浜辺に箱が必要だ、カトラス。";
			link.l1.go = "Pelly_9";
		break;
		
		case "Pelly_9":
            dialog.text = "「ただちに、提督！」";
			link.l1 = "...";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_10":
            DialogExit();
			npchar.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_4";
			pchar.questTemp.Mtraxx.Chest = "true";
			// подгружаем сундук в локу и меняем локаторы
			int n = Findlocation("Shore37");
			Locations[n].models.always.locators = "shore03_q_locators";
			locations[n].models.always.chest = "chest_quest";
			Locations[n].models.always.chest.locator.group = "box";
			Locations[n].models.always.chest.locator.name = "private1";
			Locations[n].models.always.chest.tech = "DLightModel";
			DoQuestReloadToLocation("Shore37", "goto", "goto5", "Mtraxx_PlantChestReady");
		break;
		
		case "Pelly_11":
            dialog.text = "ただちに、提督！";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantPrepareMarch");
		break;
		
		case "Pelly_12":
            dialog.text = "男たちは準備万端です、提督！";
			link.l1 = "進め！";
			link.l1.go = "Pelly_13";
		break;
		
		case "Pelly_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_14":
            dialog.text = "提督、俺たちが助けるはずだったタイレックスの友人は……どうやら、すでに死んでるみたいだぜ。";
			link.l1 = "ああ、でもあそこではどうしようもなかった。\n衛兵たちを見ただろう、俺たちは生きて帰れただけでも運が良かったんだ。";
			link.l1.go = "Pelly_15";
		break;
		
		case "Pelly_15":
            dialog.text = "提督、マーカスがあなたに怒りますよ。今は彼のところへ行かないでください。私はこれで失礼します。 あなたもそうしたほうがいいです。";
			link.l1 = "ああ……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantFailFinal");
		break;
		
		case "Pelly_16":
            dialog.text = "悪い知らせです、提督。東からスペインの艦隊がこちらに向かってきます。逃げる時間はありません。";
			link.l1 = "何人いるんだ？";
			link.l1.go = "Pelly_17";
		break;
		
		case "Pelly_17":
            dialog.text = "三隻の船だ。大砲も山ほどある。こりゃ終わったな。"; // лесникПОСЛЕДНЕЕ
			link.l1 = "見てみようじゃねえか。";// Жан, ты отправляйся на борт к Тесаку. Тесак, поднимешь испанский флаг и на всех парусах прочь отсюда - глядишь, за торговца сойдёшь. А я пойду прямо на испанцев - отвлеку их от вас. Увидимся в Ла Веге у Тиракса.";
			link.l1.go = "Pelly_181";
		break;
		case "Pelly_181":
	    	DialogExit();
		   sld = characterFromId("Mrt_Rocur");
		   sld.Dialog.currentnode = "Pelly_182";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_182":
		   dialog.text = ""; 
		   link.l1 = "ジャン、お前はカトラスの船に行け。";
		   link.l1.go = "Pelly_183"; 
		break;
		case "Pelly_183":
		     DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_18":
            dialog.text = "";//"Но...";
			link.l1 = "カトラス、スペインの旗を揚げてさっさとここから逃げろ。俺が奴らの注意を引きつけておく。ラ・ベガでまた会おうぜ。 ";//"Отставить! Тесак, за Жана Пикара отвечаешь головой перед Тираксом. Все на борт!";
			link.l1.go = "Pelly_19";
		break;
		
		case "Pelly_19":
            dialog.text = "しかし……";
			link.l1 = "言い訳は無用だ！カトラス、ピカードがタイレックスの所に行けなきゃ、お前の首が飛ぶんだぜ。全員乗り込め！\n";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantSeaEscape");
		break;
		
		case "Pelly_20":
            dialog.text = "ご命令は、提督？";
			link.l1 = "戦う準備をしろ。俺の合図で攻撃開始だ！";
			link.l1.go = "Pelly_21";
		break;
		
		case "Pelly_21":
            dialog.text = "了解だぜ、提督……ご命令通りに！";
			link.l1 = "...";
			link.l1.go = "Pelly_22";
		break;
		
		case "Pelly_22":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_23":
            dialog.text = "ほっほっ！やあ、プリンス。何の用でトルトゥーガに来たんだ？";
			link.l1 = "またマーカスの仕事か。聞けよ、カトラス、この家に住んでるあの野郎はなんで俺を中に入れねえんだ？";
			link.l1.go = "Pelly_24";
		break;
		
		case "Pelly_24":
            dialog.text = "ガスパール・ゴールデンティースか？あいつは信頼できる仲間としか仕事しねえんだ。 他の奴らは紹介がないと取引できねえよ。\nキラキラした小物を売りたいのか？もしよけりゃ、俺があんたの保証人になってやってもいいぜ…";
			link.l1 = "つまり、あいつは高利貸しか？利息はいくらなんだ？";
			link.l1.go = "Pelly_25";
		break;
		
		case "Pelly_25":
            dialog.text = "兄弟、お前は何か見落としてるぜ。ガスパールは高利貸しじゃねえ、行くべきなのは "+GetFullName(characterFromId("Tortuga_usurer"))+" もし必要ならな。ゴールデンティースはあらゆる種類の宝石や装飾品を買い取るぜ。ちなみに、あいつは払いもいいし、 くだらねえ質問もしねえ。どの海賊船長もあいつの客だ。";
			link.l1 = "なるほど……やつに金を預ける者までいると聞いたが……";
			link.l1.go = "Pelly_26";
		break;
		
		case "Pelly_26":
            dialog.text = "ハハハ！そんなことを言った奴は嘘つきだ、行ってその恥知らずの目に唾を吐いてやれ。 ガスパールは宝石だけを扱ってるんだ、昔からな。なんで他人の金で揉め事を起こす必要があるんだよ？";
			link.l1 = "なるほど。ありがとう、カトラス、また海で会おうぜ！";
			link.l1.go = "Pelly_27";
			link.l2 = "ふむ、なるほどな。あいつは小物を買い集めてるのか？面白いじゃねえか……俺のことを推薦してくれるって言うのか？";
			link.l2.go = "Pelly_27z";
		break;
		
		case "Pelly_27":
            dialog.text = "じゃあな、プリンス。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookThird");
		break;
		
		case "Pelly_27z":
            dialog.text = "もちろんだ！お前ももう仲間だぜ、へへっ！ちょっとここで待ってな。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekPellyTalkGems");
		break;
		
		case "Pelly_28z":
            dialog.text = "すべて片付いたぜ！ これでゴールデントゥースはチャーリー・プリンスがガラクタを売りに来るかもしれねえって分かったはずだ。\nただし、あいつの買値は悪くねえが、あのケチな高利貸しどもよりは安いってことは覚えておけよ。\nだが、あいつは何でもトン単位で買い取るんだ！しかも、さっき言った通り、余計な詮索はしねえ。";
			link.l1 = "それでこそ俺のイカした息子だ！よくやったな、ポール！これで戦利品を全部降ろす場所ができたぜ！";
			link.l1.go = "Pelly_29z";
		break;
		
		case "Pelly_29z":
            dialog.text = "いや、ジャン・ピカードは“ハンサム”で、俺は“カトラス”だ、ははっ！じゃあな、プリンス！";
			link.l1 = "ありがとう、カトラス、航海の幸運を祈るぜ！";
			link.l1.go = "Pelly_27";
		break;
		
		case "Pelly_28":
			PlaySound("VOICE\English\LE\Pelly\Pelly_03.wav");
            dialog.text = "お前さんのために三羽の鳥を捕まえたぜ、旦那。タンスの中やベッドの下に隠れていやがった。綺麗なもんだろ？ははは！ ";
			link.l1 = "確かにそうだぜ。しかも、よく手入れされてるじゃねえか。ドン・スタボーンはあいつらを大事にしてるんだな。";
			link.l1.go = "Pelly_29";
		break;
		
		case "Pelly_29":
            DialogExit();
			sld = CharacterFromID("Mtr_CartahenaMayorClone");
			sld.dialog.currentnode = "CartahenaMayor_8";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Pelly_30":
			PlaySound("VOICE\English\LE\Pelly\Pelly_04.wav");
            dialog.text = "おう、万歳だぜ！一体ここで何してやがるんだ、王子？";
			link.l1 = "カトラスか？…声と騒ぎを追ってきたんだが、まさかお前だったとはな。一体どうしてこんな所にいるんだ？";
			link.l1.go = "Pelly_31";
			QuestPointerDelLoc("Judgement_dungeon_01", "reload", "reload2_back");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_05", "quest", "pelly");
		break;
		
		case "Pelly_31":
            dialog.text = "いや、なんでお前がここにいるんだ！いつも現れるじゃねえか！この宝のためにタイレックスが送り込んだんだろ？ カランバ、また遅れちまったな……";
			link.l1 = "タイレックス？いや…俺はどっかの女から地図を買ったんだ。お前にも同じ地図を売りつけたんじゃねえか？トルトゥーガでか？あの女、 なかなか抜け目ねえな。でも嘘はついてなかったぜ――この金の山を見てみろよ！もっと人手を連れて戻ってくるぜ、これ全部運ぶために…";
			link.l1.go = "Pelly_32";
		break;
		
		case "Pelly_32":
            dialog.text = "ああ、そうだ、金貨の山だぜ！だが、それはお前やタイレックスのもんじゃねえ！最初に見つけたのは俺だ！俺のもんだ！ どうやって知ったかなんて関係ねえ！お前には関係ないだろうが！";
			link.l1 = "落ち着けよ、カトラス、なんでそんなに怒ってるんだ？この山を見てみろ――ここには百万はあるぜ。いや、それ以上かもな！俺たち二人に十分すぎるだろう！";
			link.l1.go = "Pelly_33";
		break;
		
		case "Pelly_33":
            dialog.text = "いつもお前が一番いいところを持っていくんだよ、プリンス！だが今回は違うぜ！宝は俺のものだ！ 最初に見つけたのは俺だ！";
			link.l1 = "くそっ、ポール、どうしたんだ？ここで手を打てねえのか？この金の半分でも大金だぜ。お前、 こんな額を手にしたことは今までなかっただろう。それに、 俺がいつか儲かる話を見つけて教えてやることだってできるんだぜ。";
			link.l1.go = "Pelly_34";
		break;
		
		case "Pelly_34":
            dialog.text = "俺を痛めつけたいのか、旦那？冗談じゃねえ！一文たりとも、ギニー一枚たりとも渡さねえぞ！遅かったな！\nああ、何を企んでるか分かったぜ！この金は絶対に渡さねえ！！！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionPellyFight");
		break;
		
		case "Pelly_35": //
            dialog.text = "おかしいな。本当に。提督、あんたは芸人かよ。だが本当の話だ――マーカスはあんたみたいに自分を出し抜こうとする奴が気に入らねえ。でも、賢い男は重宝するんだ。";
			link.l1 = "わかった、わかった。で、何を考えてるんだ？";
			link.l1.go = "Pelly_36";
		break;
		
		case "Pelly_36":
            dialog.text = "お前とハンサムが明らかに考えてなかったことだな。お前たちはプランテーションで反乱を企んでるんだろう。 略奪や混乱を起こすのが目的なら、そりゃあいい考えだ――だが…\n";
			link.l1 = "「でも何だ？反乱に反対なのか？怖じ気づいたのか？」";
			link.l1.go = "Pelly_37";
		break;
		
		case "Pelly_37":
            dialog.text = "俺か？はっ！そんなわけねえだろ。でもよ、もし殺し合いの最中にハンサムがくたばったらどうなると思う？\nマーカスに何て言うんだ？俺が教えてやるよ――何を言ったって無駄だ。どうせあいつは俺たちの皮を剥ぐさ。";
			link.l1 = "ふむ。で、お前の見事な策は何だ？どうにかして奴を外に出さなきゃならねえんだぞ。";
			link.l1.go = "Pelly_38";
		break;
		
		case "Pelly_38":
            dialog.text = "そうだ。だからこそ……奴を買ってしまえばどうだ？正式に、ってことだ。金貨を少しばかり出せば、こいつら野郎どもは誰でも売るぜ――自分の母親だってな。哀れなジャンについては、何を言える？";
			link.l1 = "はっ！カトラス、お前、本気で俺にプランテーションに乗り込んで「ピカールを買いたい」なんて言わせるつもりか？ ついでに誰のために働いてるかも教えてやれってか、冗談だろ？頭でもおかしくなったのか？";
			link.l1.go = "Pelly_39";
		break;
		
		case "Pelly_39":
            dialog.text = "そんなこと言う必要はねえさ。むしろ逆だ――お前は商人のふりをしろ。まあ、その役をやる度胸はねえだろうが、海賊にも見えねえしな。悪く思うなよ、提督、 でも事実だ。堂々とあのプランテーションに乗り込んで、自信満々にジャンを呼べばいい。 あそこの主人はお前が誰か気づくかもしれねえが、顔には出さねえ。言っただろ――金貨を少し握らせりゃ口は閉じるもんさ。";
			link.l1 = "「で、その……黄金の手ってやつはいくらするんだ？山ごと全部か？」";
			link.l1.go = "Pelly_40";
		break;
		
		case "Pelly_40":
            dialog.text = "そうかもしれねえが、首を失うより金を手放す方がマシだぜ。お前が陸に上がってる間、 俺は何もしてなかったわけじゃねえ。海賊らしくない格好に着替えて、 あのプランテーションとそのしがない持ち主について聞き込みをしてきたんだ。";
			link.l1 = "「それで、何を見つけたんだ、カトラス？」";
			link.l1.go = "Pelly_41";
		break;
		
		case "Pelly_41":
            dialog.text = "いわば市場価格ってやつだ。あいつの手に貴重な囚人が転がり込むのはこれが初めてじゃねえ。たいていの場合、 そいつらは絞首台行きか、もっとひどけりゃ異端審問所の地下牢にぶち込まれるんだ。";
			link.l1 = "「それで、彼はそれらをいくらで売っているんだ？」";
			link.l1.go = "Pelly_42";
		break;
		
		case "Pelly_42":
            dialog.text = "偉い人のためか？五百枚のコインだぜ。もちろんドブロン金貨でな。";
			link.l1 = "「五百だと！？」";
			link.l1.go = "Pelly_43";
		break;
		
		case "Pelly_43":
            dialog.text = "「農園主たちよ、何を期待してたんだ？」";
			link.l1 = "その値段なら、小さな軍隊を装備できるじゃねえか！なんで俺は反乱のために船に武器庫を溜め込んでるんだよ？\nそれだけあれば小さな戦争くらいできるぜ。";
			link.l1.go = "Pelly_44";
		break;
		
		case "Pelly_44":
            dialog.text = "その武器は後でお前の船員たちにきっと役立つぜ、どっちにしろな。\nで、どうするんだ？";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "（信頼できる）テラックスの報酬がここで使う金より少なかったら笑えるけどな。だが、お前の言う通り、 俺たちの命の方が大事だ。ドブロン銀貨は俺が持ってるぜ。";
					link.l1.go = "Pelly_45";
				}
				link.l2 = "今はそんな金山なんて持ってねえんだ。";
				link.l2.go = "Pelly_44_1";
				Notification_Perk(true, "Trustworthy");
			}
			else Notification_Perk(false, "Trustworthy");
			link.l3 = "なあ、カトラス、もういいだろ。俺たちは海賊じゃねえのか？それにジャンはどうした？ あいつの取り柄はその綺麗なツラだけか？\n宝箱を用意しろ――最初の計画通りにやるぜ。";
			link.l3.go = "Pelly_62";
		break;
		
		case "Pelly_44_1":
            dialog.text = "もしお前が用意できたら驚きだぜ――とんでもない大金だからな。まあいい、準備ができた時か、もっといい案が浮かんだら、俺のところに来いよ。";
			link.l1 = "了解だ。ここで待ってろ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_44_2":
			dialog.text = "さて、提督、ピカードを救うための金貨は十分にかき集めたか？";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "ああ、ついにやったぞ。これがうまくいくといいが。";
				link.l1.go = "Pelly_45";
			}
			link.l2 = "まだ作業中だ、カトラス。";
			link.l2.go = "exit";
			link.l3 = "俺の苦労して稼いだ金をあの強欲なプランターどもには渡さねえ！\n箱を用意しろ――俺たちは運命の紳士らしく振る舞うんだ。\nそれが俺の決断だ。";
			link.l3.go = "Pelly_9";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_45":
            dialog.text = "おいおい。お前は俺たちの船に入ったばかりなのに、もうそんな大金をばらまくのかよ！";
			link.l1 = "金がすべてじゃねえ。でもテラックスの栄光を浴びるのは……それこそが何物にも代えがたいぜ。";
			link.l1.go = "Pelly_46";
			pchar.questTemp.mtraxx_PlantVykup = true;
		break;
		
		case "Pelly_46":
            dialog.text = "それは否定できねえな。でも、あんたが言った通り、金だけの話じゃねえ――他にも大事なものがあるんだ、提督。";
			link.l1 = "今ちょっと気になるな。何だ？";
			link.l1.go = "Pelly_47";
		break;
		
		case "Pelly_47":
            dialog.text = "俺はこのプランテーションについて全部調べたって言っただろう。どんな商品がここで需要があって、 市場で流通してるかもな。もし本物の商人のふりをしたいなら、 ただプランターの机に金貨の山を叩きつけるんじゃなくて、そういう品を仕入れておいた方がいいぜ。";
			link.l1 = "なるほどな。どんな品物の話なんだ？";
			link.l1.go = "Pelly_48";
		break;
		
		case "Pelly_48":
            dialog.text = "まあ、生きた商品以外だと、へっへっ、地元のプランテーションの旦那がコーヒーやコプラ、バニラを買ったり、 取引したり、転売したりしてるんだ。だからさ…";
			link.l1 = "どこかで急いでそれを補給しないとな。もしくは隊商を襲って、必要な物を運んでることを願うしかねえな。";
			link.l1.go = "Pelly_49";
		break;
		
		case "Pelly_49":
            dialog.text = "ただの隊商じゃねえぜ。手放すのは惜しいが、俺自身のために一つ取っておいたんだ。 お前が必要としてるものを運んでくる隊商がもうすぐ到着する。だが、一つ条件があるんだ……";
			link.l1 = "「ああ、今度は何だ？」";
			link.l1.go = "Pelly_50";
		break;
		
		case "Pelly_50":
            dialog.text = "フランスの旗の下だ。";
			link.l1 = "何だって！？";
			link.l1.go = "Pelly_51";
		break;
		
		case "Pelly_51":
            dialog.text = "お前の苛立ちは分かるぜ、はは。決めるのはあんただ……提督。詳しい話を聞きたいか？";
			link.l1 = "くそっ……よし、話せ。時間がねえ――お前か俺が手を出さなきゃ、他の奴がやるだけだ。";
			link.l1.go = "Pelly_52";
			// link.l2 = "俺はフランス野郎には、どうしても仕方ねえ時以外は手を出さねえ。話はこれで終わりだ。";
			// link.l2.go = "Pelly_51_1";
		break;
		
		case "Pelly_51_1":
            dialog.text = "だったら、自分で全部の品を集め始めたほうがいいぜ、しかも急いでな。プリティボーイが他の誰かに売られる前にな。 俺もここにいつまでもいられるわけじゃねえんだ。";
			link.l1 = "そうだと思ったぜ。";
			link.l1.go = "Pelly_51_2";
		break;
		
		case "Pelly_51_2": // добываем товары сами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		break;
		
		case "Pelly_52":
            dialog.text = "そうこなくっちゃな！やっぱりお前にはその力があると思ってたぜ…提督。さて、本題だが、俺の信頼できる仲間から最近報告があった。約二週間後に、 コーヒーと香辛料を積んだフランスの護送船団がグアドループ沖に現れるらしい。規模も大きく武装も強力だ、 しっかり準備しておけよ。";
			link.l1 = "他にどんな選択肢があるんだ？";
			link.l1.go = "Pelly_53";
		break;
		
		case "Pelly_53": // наводка на караван с нужными товарами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		break;
		
		case "Pelly_54": // провал выкупа Красавчика
            dialog.text = "元気がないな、提督。ハンサムはどこだ？全部パーになっちまったのか？";
			link.l1 = "確かに、そこそこ稼げたが、あの頑固な野郎はピカールを売ってくれなかったんだ――ドゥブロン金貨の山を積んでもな！";
			link.l1.go = "Pelly_55";
		break;
		
		case "Pelly_55":
            dialog.text = "なんて間抜けだ！これからどうする？";
			link.l1 = "もうプランターとは荷下ろしの手配は済んでる。元の計画に戻るしかねえ――今しかねえぞ！";
			link.l1.go = "Pelly_56";
		break;
		
		case "Pelly_56":
            dialog.text = "「でも、ハンサムたちのためにまだ何も用意してねえぜ！」";
			link.l1 = "時間がねえ！船に乗り込め――武器と薬を船倉から荷袋に紛れ込ませるんだ。\nそれと、スペインの旗を揚げるのを忘れるなよ！";
			link.l1.go = "Pelly_57";
		break;
		
		case "Pelly_57":
            dialog.text = "いい考えだな。";
			link.l1 = "とにかく、他に時間はねえ。動け！すぐに荷下ろしが始まるぞ。";
			link.l1.go = "Pelly_58";
		break;
		
		case "Pelly_58":
            DialogExit();
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 1.0);
		break;
		
		case "Pelly_59":
            dialog.text = "おや、誰かと思えば！いい男じゃねえか！顔も無傷で、堂々と歩いてるってことは、うまくいったんだろうな？";
			link.l1 = "順調なんて言葉じゃ足りねえぜ――喧嘩を避けてジャンを買い戻しただけじゃなく、金まで稼げたんだ。お前の作戦は完璧だったぜ、ポール。 水平線の向こうも静かか？";
			link.l1.go = "Pelly_60";
		break;
		
		case "Pelly_60":
            dialog.text = "できるだけ静かにしてるぜ。マーカスのところに戻るのか？";
			link.l1 = "「そうだ。」";
			link.l1.go = "Pelly_61";
		break;
		
		case "Pelly_61":
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_PlantSuccessfulRedemption");
		break;
		
		case "Pelly_62":
            dialog.text = "ふむ、わかりました、提督。でももしハンサムに何かあったら、俺の忠告を無視したことをテラックスに必ず伝えるぜ。 脱走の準備は全部できてるか？";
			link.l1 = "「念のため、俺が持ってる物をこの箱の中で数え直してみるぜ。」";
			link.l1.go = "Pelly_63";
		break;
		
		case "Pelly_63":
            dialog.text = "間違いないぜ。俺の手間賃として、ちょっとした報酬をもらえりゃ手伝ってやるさ、へっへっ。";
			link.l1 = "どうだ？";
			link.l1.go = "Pelly_64";
		break;
		
		case "Pelly_64":
            dialog.text = "俺にはツテがある。マラカイボの武器商人だ。俺が変装してこっそり潜り込み、 あいつに金を払って武器をここに密輸する手はずを整えるぜ。\nだが、タダじゃねえ――金貨のドゥブロンが必要だぜ。";
			link.l1 = "「それで、なぜもっと早くこの男を紹介してくれなかったんだ？俺はいくら払えばいいんだ？」";
			link.l1.go = "Pelly_65";
		break;
		
		case "Pelly_65":
            dialog.text = "俺の情報屋たち全員にも紹介してやろうか？いいぜ。経費やリスク、それに俺の取り分も合わせて……ハンサムの身代金と同じくらいかかるぜ。";
			link.l1 = "カトラスよ、神を畏れよ……";
			link.l1.go = "Pelly_66";
		break;
		
		case "Pelly_66":
            dialog.text = "俺は神もあんたも怖かねえよ、提督。でもな、ジャンを助けられなかった時のマルクスの怒りは別だぜ。\nで、どうする？宝箱の手伝いが要るか？";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "よし、行け――もう十分時間を無駄にしただろう。ほら、これで足りるはずだ。";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "かなりの大金だな、ポール。ちょっと考えさせてくれ。";
			link.l2.go = "Pelly_67";
			link.l3 = "そんな少量の武器にしては高すぎるぜ。卸売りならもっと安く手に入るんだ！\nいらねえ、自分で何とかするさ。";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_67":
            dialog.text = "まあ、好きに考えな。だが覚えておけ――お前が考えてる間にも、ハンサムの顔や体の痣はどんどん増えていくんだぜ、へっへっへ。";
			link.l1 = "ドブロン金貨を用意してやるぜ……";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_67_2";
		break;
		
		case "Pelly_67_1":
            dialog.text = "荷の大きさの問題じゃねえ――大事なのはタイミングとリスクだ。まあ、好きにしな。";
			link.l1 = "俺を信じろ、わかってるさ。とにかく箱を用意してくれ——あとは俺がやる。";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_67_2":
            dialog.text = "準備はいいか、提督？武器のことで手助けが必要か、それともまだ金が足りねえのか？";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "やっと十分集まった！さっさと受け取って、これで終わりにしろよ――イライラしてきたぜ。";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "口の利き方に気をつけろ、カトラス。俺は準備できてるが、金を集めるにはもう少し時間が必要だ。";
			link.l2.go = "Pelly_67";
			link.l3 = "そんな少量の武器にしては高すぎるぜ。まとめて仕入れればもっと安く買えるんだ！\nいらねえ、自分で何とかするさ。";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_68":
            dialog.text = "おお、なんて大量のドゥブロンだ！だが心配するな――この金貨はすべて計画のために使うぜ。そうじゃなきゃ、マーカスが後で墓から俺を掘り起こしに来るだろうな、 へっへっ。さて、行ってくれ、アドミラル。ハンサムのところへ行って、全部準備が整ったと伝えてくれ。";
			link.l1 = "命令するのは俺だ。さあ、動け。";
			link.l1.go = "Pelly_69";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "Pelly_69":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_5";
			AddQuestRecord("Roger_3", "30");
			sld = characterFromId("Mrt_Rocur");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "rocur_wait";
			sld.greeting = "Rocur_02";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Pelly_70":
            dialog.text = "ああ、それは問題だな。どうするつもりだ、提督？";
			link.l1 = "どこかで急いでそれを補給しなきゃならねえな。\nあるいは隊商を襲って、必要な物を運んでることを祈るしかねえ。";
			link.l1.go = "Pelly_49";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar");
		break;
		
		// Жан Пикар
		case "rocur":
            dialog.text = "俺に何の用だ？";
			link.l1 = "旦那、ジャン・ピカードという人物を探しているんだ。その名前に心当たりはあるか？";
			link.l1.go = "rocur_1";
		break;
		
		case "rocur_1":
            dialog.text = "可能性はある。しかし、お前の顔には見覚えがねえな。";
			link.l1 = "あまり荒っぽくするなよ、ジャン。俺はマーカス・タイレックスにここへ送られたんだ。 お前をここから連れ出すのが俺の任務だ。";
			link.l1.go = "rocur_2";
		break;
		
		case "rocur_2":
            dialog.text = "マーカス？しっ…静かに。悪いな、友よ、それは知らなかった。でもここで話すべきじゃねえ、くそったれな衛兵がどこにでもいて、 いつも耳を澄ましてやがる…お前はスペイン人たちに歓迎されてるようだな。夜になったらどこかの小屋で俺を探してくれ、そこで話そう。 待ってるぜ、兄弟。";
			link.l1 = "...";
			link.l1.go = "rocur_3";
		break;
		
		case "rocur_3":
            DialogExit();
			AddQuestRecord("Roger_3", "6");
			LAi_CharacterDisableDialog(npchar);
			Mtraxx_PlantMakeMaxRocurClone();
		break;
		
		case "rocur_4":
            dialog.text = "ここは安全だぜ……お前の名前は何だ、兄弟？";
			link.l1 = "Captain "+GetFullName(pchar)+"。さて、どうしてこんな面倒に巻き込まれたんだ？タイレックスが全部知りたがってるぞ。";
			link.l1.go = "rocur_5";
		break;
		
		case "rocur_5":
            dialog.text = "ウィレムスタッドの酒場で見知らぬ男に声をかけられたんだ……オランダの隊商を襲う仲間にならないかってな。俺はブリガンティン、奴はちょっと変わったポラッカを持ってた。 だからカラカスの近くで隊商を追い詰めて、見事に略奪したんだ……夜だった、戦利品を分けていると、闇の中から巨大なスペインのガレオン船が現れた\n相棒は逃げ出し、俺も後を追った。だが損傷した俺のブリガンティンじゃ、 ガレオンともう二隻から逃げ切れるはずもなかった。奴らは俺たちの船に乗り込んできて、 生き残った者は家畜みたいにこの場所へ売り飛ばされたんだ。";
			link.l1 = "なるほど。事故だったと思うか？ガレオン船のことを言っているんだ。";
			link.l1.go = "rocur_6";
		break;
		
		case "rocur_6":
            dialog.text = "知るかよ。銃撃戦の音を聞いたのかもしれねえ、メインからそんなに遠くなかったしな。";
			link.l1 = "ふむ。あり得るな。お前はその昔の仲間に会ったことがあるのか？そいつは誰だ？";
			link.l1.go = "rocur_7";
		break;
		
		case "rocur_7":
            dialog.text = "今まで会ったことはなかった。自分の名はイグナシオ・マルコ、イングランドに仕える私掠船長だと言っていた。 真面目な男だと感じたからこそ、この計画に参加することにしたんだ。経験豊富な水夫であり、間違いなく船長だ。 背後には精鋭の乗組員が揃っていて、彼のポラッカ船は見事なものさ。あんな船、そうそうお目にかかれるもんじゃねえ。 ";
			link.l1 = "イグナシオ・マルコ？イギリスの私掠船乗りか？スペイン人なのか？";
			link.l1.go = "rocur_8";
		break;
		
		case "rocur_8":
            dialog.text = "あいつはポルトガル人で、スペイン人じゃねえ。\nイギリスの私掠許可証が何か問題か？俺たちの仲間にはスペイン野郎もたくさんいるだろうが。";
			link.l1 = "なるほど。よし、ここからの脱出について話そうか。何か考えはあるか？";
			link.l1.go = "rocur_9";
		break;
		
		case "rocur_9":
            dialog.text = "お前たちの人数はどれくらいだ？";
			link.l1 = "俺の船はバーケンティン、そしてペリー・ザ・カトラスの連中だ。\n俺の船はマラカイボ港に停泊している。カトラスはグアヒラ湾に上陸して、そこで野営しているぜ。";
			link.l1.go = "rocur_10";
		break;
		
		case "rocur_10":
            dialog.text = "ふむ……";
			link.l1 = "なんだよ、タイレックスが戦列艦をここに送ってくるとでも思ったのか？";
			link.l1.go = "rocur_11";
		break;
		
		case "rocur_11":
            dialog.text = "何も期待してなかったさ。実は、マーカスが俺のことを忘れなかったのには驚いたぜ。";
			link.l1 = "当然、彼はやらなかったな。で、何か考えはあるか？";
			link.l1.go = "rocur_12";
		break;
		
		case "rocur_12":
            dialog.text = "ここから逃げ出すのは無理だ――このプランテーションは警備が厳重だし、周りは野生のジャングルばかりだ。\n強行突破にも意味はねえぜ。お前の手勢じゃ足りねえし、すぐ近くに砦もあるんだ。";
			link.l1 = "もしかしたら、あんたと部下たちが中から手を貸してくれるか？やつらの背後から思いきり叩いてくれ。";
			link.l1.go = "rocur_13";
		break;
		
		case "rocur_13":
            dialog.text = "何でだ？素手と錆びたマチェーテでか？";
			link.l1 = "「もし武器を持っていたらどうするんだ？」";
			link.l1.go = "rocur_14";
		break;
		
		case "rocur_14":
            dialog.text = "そうか、だったら俺たちが地獄を見せてやっただろうな。\nだが問題があるんだ。持ち込む物は全部調べられるから、武器を密かに持ち込むなんて無理だぜ。\nだから、この話は忘れた方がいいと思うぜ。";
			link.l1 = "それでも、今のところそれが一番良い選択肢だ。お前や部下たちにどうやって武器を渡すか考えてみる……ところで、戦える者は何人いるんだ？";
			link.l1.go = "rocur_15";
		break;
		
		case "rocur_15":
            dialog.text = "三十人の首だな、俺の見立てじゃ。";
			link.l1 = "じゃあ、三十本のサーベルか……拳銃もあれば違ってくると思うぜ。";
			link.l1.go = "rocur_16";
		break;
		
		case "rocur_16":
            dialog.text = "船長、本気でこれをやるつもりか？";
			link.l1 = "そうだ。わざわざここに来たんだ、ふざけるつもりはねえ。ほかに使えるものはあるか？";
			link.l1.go = "rocur_17";
		break;
		
		case "rocur_17":
            dialog.text = "よし……とにかくやってみようぜ。うちの連中は凝ったレイピアなんか扱えねえ、普通の刃物で十分だ。拳銃も同じで、 一番安いもので構わねえ。もしマスケット銃を一、二丁手に入れてくれたら助かるぜ、 マスケットが得意な奴も何人かいるからな。弾と火薬も必要だ。それから治療薬があれば大歓迎だぜ。";
			link.l1 = "了解だ。剣や斧なら船の武器庫から持ち出せるぜ。残りは手に入れるのがちと厄介だがな。全部揃ったら知らせるぜ。";
			link.l1.go = "rocur_18";
		break;
		
		case "rocur_18":
            dialog.text = "急いでくれよ、兄貴。ここで半年もぐずぐずしてる暇はねえ、 こんなクソみたいな牛の世話で俺たちは一人ずつ死んじまうぜ。\n俺が必要なら、夜に会いに来てくれ。";
			link.l1 = "了解だ、相棒。待たせないようにするぜ。気をつけろよ、まだあいつらに見限られる理由を作るんじゃねえぞ。";
			link.l1.go = "rocur_19";
		break;
		
		case "rocur_19":
            DialogExit();
			AddQuestRecord("Roger_3", "7");
			npchar.dialog.currentnode = "rocur_wait";
			pchar.questTemp.Mtraxx = "plant_3";
			pchar.questTemp.Mtraxx.MagicBox = "Baster";
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			pchar.quest.Mtraxx_PlantPrepareTimeOver.over = "yes"; //снять таймер
			SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false); // таймер
		break;
		
		case "rocur_wait":
            dialog.text = "何か新しい情報はあるか、相棒？武器は集めたか？";
			if (pchar.questTemp.Mtraxx == "plant_5")
			{
				link.l1 = "ああ。弾薬の入った箱はグアヒラ湾にある。あとはそれをどうやってプランテーションにこっそり運び込むかだけだ。";
				link.l1.go = "rocur_20";
			}
			else
			{
				link.l1 = "任せてくれ。待ってろ。";
				link.l1.go = "rocur_wait_1";
			}
		break;
		
		case "rocur_wait_1":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait";
		break;
		
		case "rocur_20":
            dialog.text = "承知しました、船長。どうやってそれを実行するか、すでに考えていました。";
			link.l1 = "それは良かった。どうしたんだ？";
			link.l1.go = "rocur_21";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_21":
            dialog.text = "このプランテーションでは砂糖を生産し、カカオ豆を栽培している。時には責任者自らが商品を売ることもあるが、 その方が儲かるからだ。あいつに取引を持ちかけろ。金じゃなくて、品物で払うんだ。箱詰めできるもの、 たとえばコプラやバニラ、コーヒーなんかがいい。交渉はしっかりやれよ、でもやりすぎるな\n武器を一つか二つの箱に隠して印をつけろ。交換は夕方に手配しろ、そうすれば箱は夜通し外に置かれるはずだ\n夜になったら、お前が印をつけた箱を見つけて武装し、スペイン野郎どもに地獄を見せてやる。もちろん、 お前の協力も必要だぜ。";
			link.l1 = "いい考えだな、兄弟！とてもいい、俺はこの計画が気に入ったぜ。このまま行こう。";
			link.l1.go = "rocur_22";
		break;
		
		case "rocur_22":
            dialog.text = "最後にもう一つ――交換する品物は一種類だけにしろ。種類が多いほど、衛兵に箱を余計に調べられるぞ。";
			link.l1 = "同感だ。じゃあ、一種類だけ選ぶことにするぜ。コーヒー、バニラ、コプラだったな？";
			link.l1.go = "rocur_23";
		break;
		
		case "rocur_23":
            dialog.text = "ああ。これはプランテーションの責任者にとっていい取引に聞こえるだろう。";
			link.l1 = "了解だ。取引がまとまったら知らせるぜ。";
			link.l1.go = "rocur_24";
		break;
		
		case "rocur_24":
            DialogExit();
			AddQuestRecord("Roger_3", "9");
			npchar.dialog.currentnode = "rocur_wait_2";
			pchar.questTemp.Mtraxx = "plant_6";
			pchar.questTemp.mtraxx_PlantInfoTovar = true;
			AddLandQuestMark(characterFromId("Pelly"), "questmarkmain");
		break;
		
		case "rocur_wait_2":
            dialog.text = "行け、友よ、時は金なり、俺たちには時間がないんだ……";
			link.l1 = "";
			link.l1.go = "rocur_wait_3";
		break;
		
		case "rocur_wait_3":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait_2";
		break;
		
		case "rocur_25":
            dialog.text = "...";
			link.l1 = "（小声で）取引は成立した。箱は明日の夕方、プランテーションに届けられる。必要な箱には「W」の文字が記されている。他の箱にはアルファベットの残りの文字が書かれている。部下の準備をしておけ。夜明け前、 三時ごろに攻撃を仕掛けるぞ。";
			link.l1.go = "rocur_25x";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_25x":
            dialog.text = "合図があれば始めるぜ…";
			link.l1 = "";
			link.l1.go = "rocur_26";
		break;
		
		case "rocur_26":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 3.0);
		break;
		
		case "rocur_27":
            dialog.text = "やっとだ！また海を見ることができるとはな！どんな姿で、どんな匂いだったか、もう忘れかけてたぜ。よくやったな、 船長！借りができちまったな。";
			link.l1 = "気にするな、後でケリをつけよう……さあ乗り込んで、ここから出るぞ！";
			link.l1.go = "rocur_28";
		break;
		
		case "rocur_28":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "rocur_29":
            dialog.text = "Greetings "+pchar.name+"。また会えて嬉しいぜ、それにこの冒険でお前が仲間でいてくれるのも心強い。この仕事はきついだろうが、 きっと乗り越えられるさ。";
			link.l1 = "また会えて嬉しいぜ、ピカード。全部聞くぜ、お前の冒険話を聞かせてくれよ。";
			link.l1.go = "rocur_30";
		break;
		
		case "rocur_30":
            dialog.text = "もうマーカスには話したが、今度はお前にも話そう。俺がマラカイボのプランテーションで奴隷だった頃、 スペイン人から色々学んだんだ。あいつら、酔っ払うとよく喋るからな……聞け、マラカイボ湾から南東に小さな村がある。ジャングルの奥、二つの山に挟まれて隠れてるんだ。 とんでもねえ名前だぜ――サンティアゴ・デ・ロス・カバジェロス・デ・メリダ。メリダって呼ぼう\nまだあまり面白そうに聞こえねえか？だがな、その村を囲む山々には宝石が眠ってたんだ。エメラルド、オパール、 そして伝説のファイアオパールまでな\n俺の知る限り、メリダの入植者たちは総督にはこの宝石のことを黙ってる。だが、いずれ総督も知ることになる。 だからこそ、スペインの植民地役人が来る前にメリダへ行くべきなんだ。";
			link.l1 = "この集落を略奪したいのか？";
			link.l1.go = "rocur_31";
		break;
		
		case "rocur_31":
            dialog.text = "その通りだ。あそこは密林と山々に囲まれていて、守備隊も少人数――コルセアの部隊には格好の獲物だぜ。\nそれに、海からも遠く離れているから、槍や弓を持った野蛮人以外に襲われるなんて思っちゃいねえんだ。";
			link.l1 = "その集落に宝石があるって、どれほど確信してるんだ？";
			link.l1.go = "rocur_32";
		break;
		
		case "rocur_32":
            dialog.text = "もしこの冒険が無駄足だったなら、俺自身があんたの船で士官でも水夫でも務めるぜ。甲板掃除もするし、 何度でも白兵戦で戦う。あんたとマーカスへの借りが帳消しになるまでな。";
			link.l1 = "なるほど……よし、メリダへの行き方は知っているか？";
			link.l1.go = "rocur_33";
		break;
		
		case "rocur_33":
            dialog.text = "もちろん、ジャングルの正確な道は分からねえが、現地のインディオから案内人を雇うつもりだ。\nマラカイボ湖の南に上陸して、インディオの村を探し、道を知っている者を探そう。";
			link.l1 = "...";
			link.l1.go = "rocur_34";
		break;
		
		case "rocur_34":
            DialogExit();
			sld = characterFromId("Terrax");
			sld.Dialog.currentnode = "mtraxx_38";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_35":
            dialog.text = "船長、口が悪くて本当にすまねえが、なんで俺たちはまだメリダにいねえんだ？ああ？ 共通の目的をお前は踏みにじったんだぜ！レプラコーンと俺はお前抜きで行く。全部タイレックスに説明してやるから、 お前はもう行け。ほら、マラカイボでの助けの礼だ、五万ペソ持ってけ。仲間から借りたんだ。じゃあな、 まったく情けねえ、もっと信じてたのによ。";
			link.l1 = "うーん……すまねえ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaTimeOverFail");
		break;
		
		case "rocur_36":
            dialog.text = "ここまで来たな。これから先はジャングルだ。まずはインディアンの村を探して、案内人について聞いてみよう。";
			link.l1 = "やろうぜ。ルーク、何か言いたいことはあるか…それとも何か助言でもあるか？";
			link.l1.go = "rocur_37";
		break;
		
		case "rocur_37":
            DialogExit();
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_38":
            dialog.text = "メリダの守備隊は片付いた。村で本格的な抵抗はないだろう。行くぞ！";
			link.l1 = "突撃だぁ！！！";
			link.l1.go = "rocur_39";
		break;
		
		case "rocur_39":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", true);
			pchar.quest.mtraxx_merida_town.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_town.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_town.function = "Mtraxx_MeridaTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "16");
		break;
		
		case "rocur_40":
            dialog.text = "終わったぜ！もう英雄はいねえ。さて、この「街」の総督と話すべきだな。説得できるタイプだといいんだが。";
			link.l1 = "同感だ、やつを“説得”してやろうぜ！…ジャン！ついて来い！";
			link.l1.go = "rocur_41";
		break;
		
		case "rocur_41":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "gate_back", true);
			pchar.quest.mtraxx_merida_townhall.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_townhall.win_condition.l1.location = "Merida_townhall";
			pchar.quest.mtraxx_merida_townhall.function = "Mtraxx_MeridaTownhall";
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Roger_5", "17");
		break;
		
	case "rocur_42": //злой вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			pchar.questTemp.Mtraxx_MeridaZloVariant = true;
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_43": //мирный вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_44":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
            	dialog.text = "「よくやったな」 "+pchar.name+"！取り分を分ける時間だぜ。もう計算はできてる。宝箱にはほぼ2000個の宝石があった：エメラルド1560個、オパール1032個、ファイアオパール363個だ。お前の分は三分の一――エメラルド350個、オパール244個、ファイアオパール63個だ。ほら、受け取れ。";
            }
            else
           	{
           	dialog.text = "「よくやったな。」 "+pchar.name+"！取り分を分ける時間だぜ。もう計算はできてる。宝箱にはほぼ二千個の宝石があった――エメラルドが千五十個、オパールが七百三十二個、ファイアオパールが百八十九個だ。お前の取り分は三分の一――エメラルド三百五十個、オパール二百四十四個、ファイアオパール六十三個だ。ほら、持っていけ。";
           	}
			link.l1 = "「いいね！」";
			link.l1.go = "rocur_45";
		break;
		
		case "rocur_45":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 520);
				TakeNItems(pchar, "jewelry16", 334);
				TakeNItems(pchar, "jewelry14", 121);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 350);
				TakeNItems(pchar, "jewelry16", 244);
				TakeNItems(pchar, "jewelry14", 63);
			}
            dialog.text = "さて、俺を助けてくれた借りについて話そうか。君がかなりの出費をしたのは分かっている。どんな報酬なら納得できる？ 宝石の分け前から払わせてもらうぞ。";
			link.l1 = "お前の取り分の三分の一で十分だ。お前にも金が必要だろう――船を買って装備したり、乗組員に給料を払ったりしなきゃならねえからな……";
			link.l1.go = "rocur_46";
		break;
		
		case "rocur_46":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 173);
				TakeNItems(pchar, "jewelry16", 111);
				TakeNItems(pchar, "jewelry14", 40);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 116);
				TakeNItems(pchar, "jewelry16", 81);
				TakeNItems(pchar, "jewelry14", 21);
			}
            dialog.text = "ありがとう、友よ！半分は要求されるかと思ってたぜ。今は金が必要なんだ。ほら、宝石を持っていけ。";
			link.l1 = "なんて襲撃だ、ジャン！イスパニョーラへ、タイレックスに向かおう。";
			link.l1.go = "rocur_47";
		break;
		
		case "rocur_47":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_gohome";
			AddQuestRecord("Roger_5", "18");
			sld = characterFromId("Mrt_Rocur");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld); // релиз-правка
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Lepricon");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_40";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_merida_lavega.function = "Mtraxx_IgnasioKitty";
			// таймер на доплыть домой 40 дней
			SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
			DeleteAttribute(pchar, "GenQuest.HunterLongPause");
		break;
		
		case "rocur_48":
            dialog.text = "おお、なんて偶然だ！お会いできて嬉しいよ、 "+pchar.name+"。調子はどうだ？";
			link.l1 = "まあまあだぜ。最近レッドウルフの財宝を見つけたばかりさ。 今は共通の知り合いに会うためにマルティニークへ向かってる。\nタイレックスに会いたいのか？";
			link.l1.go = "rocur_49";
		break;
		
		case "rocur_49":
            dialog.text = "ああ。パスカーレ・ラヴォワジエについて彼と話したいんだ。 マーカスが俺をあの半分盗賊で半分商人の野郎のところに送った。言われた通りにやったのに、 奴はガラクタみたいなもんで報酬だと抜かしやがった。あそこでぶっ殺してやろうかと思ったが、 マーカスに礼儀を持てって言われてな……だからこの厄介ごとはマーカスに任せるぜ。";
			link.l1 = "悪いが、マーカスは何もしねえよ。四つ目野郎はあいつと組んでるんだ。";
			link.l1.go = "rocur_50";
		break;
		
		case "rocur_50":
            dialog.text = "なんだと！？";
			link.l1 = "ああ、でもこのことは俺が話したってことにしないでくれよ？ラヴォワジエにも俺は最近やられたんだ。 タイレックスに頼まれて手を貸したのさ、お前と同じようにな。イスラ・テソロで忠告されたんだ――あの四つ目に逆らうのはマーカスに逆らうのと同じだってな。だから、この件は忘れたほうがいいぜ。 お前が最初でも最後でもねえんだからな。\n";
			link.l1.go = "rocur_51";
		break;
		
		case "rocur_51":
            dialog.text = "なるほどな。お前もあの二人にひどい目に遭わされたのか？";
			link.l1 = "ああ、そうだな。俺もあのメガネ野郎にちょっかい出してやろうかと思ってたが、 奴のことをもっと知ってからやめたんだ。やる価値はねえよ。";
			link.l1.go = "rocur_52";
		break;
		
		case "rocur_52":
            dialog.text = "「誰にも絶対にバレないと分かっていたら、その野郎に仕返ししようとするか？」";
			link.l1 = "はっ！もちろんやるさ！だが、どうやるかは分からねえ。ラヴォワジエのフルート船を襲えば、 そのうちお前の船乗りどもが酔っ払って全部しゃべっちまうぜ。どういう仕組みか分かってねえのか？";
			link.l1.go = "rocur_53";
		break;
		
		case "rocur_53":
            dialog.text = "今マルティニークへ向かっているのか？またラ・ベガにはいつ到着するんだ？";
			link.l1 = "マーカスが俺に三週間くれた。";
			link.l1.go = "rocur_54";
		break;
		
		case "rocur_54":
            dialog.text = "二つにまとめてみろ。俺も考えておく……十四日後にゴナイーヴ湾で会おう。まっすぐそこへ向かえ、ラ・ベガには入るな。";
			link.l1 = "何か企んでるのが見えるぜ、はは。よし、やってみるか。";
			link.l1.go = "rocur_55";
		break;
		
		case "rocur_55":
            dialog.text = "そうした方がいいぜ。またな！";
			link.l1 = "...";
			link.l1.go = "rocur_56";
		break;
		
		case "rocur_56":
            DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 10.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ReOpenQuestHeader("Roger_4");
			AddQuestRecord("Roger_4", "11");
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.hour  = 1.0;
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2 = "location";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2.location = "Shore34";
			pchar.quest.mtraxx_pasq_gonaiv.function = "Mtraxx_PasqualeJanGonaiv";
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimer", 0, 0, 10, false); // правки прогона 3
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimeOver", 0, 0, 15, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.questTemp.Mtraxx.Pasquale.Grabbing = "true";
		break;
		
		case "rocur_57":
			if (pchar.location.from_sea != "Shore34")
			{
				dialog.text = RandSwear()+"お前の船はどこだ？ラ・ベガからここに来たのか？くそっ！俺はお前に目立たずこっそり来いと言ったはずだ。 これで俺の計画は台無しだ。ちくしょう…";
				link.l1 = "ふむ……";
				link.l1.go = "rocur_58";
			}
			if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "「そこにいたか、」 "+pchar.name+"。お前がここにいてくれて助かったぜ。仲間たちは船に戻らせろ。これは内緒の話だ。";
				link.l1 = "「よろしい。」";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "「そこにいたか、」 "+pchar.name+"。来てくれてよかった。お前に商売の話があるんだ。聞く気はあるか？";
				link.l1 = "もちろんだぜ！";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_58":
            DialogExit();
			Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
			Group_DeleteGroup("RocurSeaGroup");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("Roger_4", "14");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_59":
            DialogExit();
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "rocur_60";
		break;
		
		case "rocur_60":
            if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "もう言っただろう――お前の士官たちを下がらせろ！";
				link.l1 = "ああ、わかったよ。";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "よし。これで自由に話せるな。お前に商売の話があるんだ。聞く準備はできてるか？";
				link.l1 = "もちろんだぜ！";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_61":
            dialog.text = "ラ・ベガのことをよく知っているか？";
			link.l1 = "そうだな……知ってると思うぜ。なんでそんなこと聞くんだ？";
			link.l1.go = "rocur_62";
			npchar.greeting = "";
		break;
		
		case "rocur_62":
            dialog.text = "地元の店の右にある倉庫に気づいたことがあるか？バラックの中で唯一の大きな家だ。";
			link.l1 = "いつも閉まってるやつか？ああ、見たことがあるぜ。どうしてそんなこと聞くんだ？";
			link.l1.go = "rocur_63";
		break;
		
		case "rocur_63":
            dialog.text = "よく気づいたな――ここはいつも閉まってるんだ。お前がマルティニークで任務にあたっていた間、 俺たちの共通の友人ラヴォワジエが三日間ここに滞在していた。マーカス・タイレックスの客人としてな。 二人はこの屋敷でラムを飲みながら、楽しく過ごしていたぜ。";
			link.l1 = "ふむ……";
			link.l1.go = "rocur_64";
		break;
		
		case "rocur_64":
            dialog.text = "それからラヴォワジエの手下たちがいくつかの箱や包みを家の中に運び込んだ。\nその後、彼は去っていった。\nマーカスについては、毎日何時間もそこに居続けている。";
			link.l1 = "何か提案はあるか？";
			link.l1.go = "rocur_65";
		break;
		
		case "rocur_65":
            dialog.text = "「どんな提案だ？この家はきっとラ・ベガにあるラヴォワジエのアジトに違いねえ。窓越しにあまり見えなかったが、 あそこには品物が保管されてたぜ。あのメガネ野郎なら、俺たちに借りを返す手立てがあるはずだ。」";
			link.l1 = "ほうほう……押し入るつもりか？\n閉まってる扉はどうする？重くて頑丈だ、静かにこじ開けるなんて無理だぜ。";
			link.l1.go = "rocur_66";
		break;
		
		case "rocur_66":
            dialog.text = ""+pchar.name+"、俺を馬鹿にしてるのか？もう全部片付けてあるぜ。錠前の蝋型から鍵を作らせたんだ。かなり金がかかったが、 それは俺の問題だ。";
			link.l1 = "へっ！じゃあ、なんで俺を待ってるんだ？";
			link.l1.go = "rocur_67";
		break;
		
		case "rocur_67":
            dialog.text = "その方が安全だし、それに俺が信頼できるのはお前だけだ。一人より二人、二つの目より四つの目の方がいいからな。";
			link.l1 = "ああ、そうだな、ラヴォワジエを出し抜くには奴の目の数だけ目が必要だぜ、ははは！\nだがタイレックスはどうする？俺たちがパスクァーレの持ち物を調べてる間に、もし奴が家に入ってきたらどうするんだ？ ";
			link.l1.go = "rocur_68";
		break;
		
		case "rocur_68":
            dialog.text = "あいつはしねえよ。必ず真夜中までには自分の家に戻るんだ。\n明日の夜、ラ・ベガに行く準備はできてるか？やつらは誰にやられたか気づきゃしねえ。 お前はまだマルティニークにいるし、俺は一週間前にラ・ベガを出たんだからな。";
			link.l1 = "あの四つ目の野郎をぶちのめしてえぜ。だがよ、ジャン、どうやって家から樽や宝箱を運び出すんだ？";
			link.l1.go = "rocur_69";
		break;
		
		case "rocur_69":
            dialog.text = "きっとあそこでは、宝箱や樽の荷物よりも価値のあるものが見つかるはずだし、しかもずっと軽いぜ。\nどうだ、乗るか？";
			link.l1 = "ああ、そうだぜ！";
			link.l1.go = "rocur_70";
		break;
		
		case "rocur_70":
            dialog.text = "よし、お前を見込んで正解だったぜ。今は休もう、真夜中にラ・ベガへ向かうぞ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNight");
		break;
		
		case "rocur_71":
            dialog.text = "行く時間だ。こいつを襲って、夜明け前にさっさとずらかるぞ。";
			link.l1 = "進め！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightMarch");
			SetLocationCapturedState("LaVega_town", true);
			LAi_LoginInCaptureTown(npchar, true);
		break;
		
		case "rocur_72":
            dialog.text = "静かに……今はパスクワーレの家まで音を立てずに進もう。俺について来い。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightToHouse");
		break;
		
		case "rocur_73":
            dialog.text = "見てみろよ、こんなに物が散らかってるぜ。始めようか。まずはドアのそばの箱を調べてから、 二階に上がって一部屋片付けてくれ。俺はここに残る。ガラクタの中に貴重品を隠すコツは知ってるからな。油断せず、 目と耳をしっかり使って、窓には近づくなよ。\n";
			link.l1 = "「よし……」";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightInHouse");
		break;
		
		case "rocur_74":
            dialog.text = ""+pchar.name+"「で、何を持ってきたんだ？何か面白いものはあるか？」";
			link.l1 = "来て見てみろ。これはすごいぞ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeJanSeeGirl");
		break;
		
		case "rocur_75":
            dialog.text = "くそっ！これでわかったぜ、なぜタイレックスが毎日ここに来るのか。ここは四つ目野郎の倉庫だけじゃなくて、 売春宿でもあるんだな。";
			link.l1 = "ここでは彼女は奴隷みたいだな。";
			link.l1.go = "rocur_76";
		break;
		
		case "rocur_76":
            dialog.text = "ああ、わかったぜ。見てみろよ、あいつはどう見ても港の娼婦じゃねえか……俺たちにとっちゃ運が悪いな。殺すしかねえ。";
			link.l1 = "本当にそうか？";
			link.l1.go = "rocur_77";
		break;
		
		case "rocur_77":
            dialog.text = "あいつは俺たちの顔を見て、お前の名前も聞いた。タイレックスに全部話すだろう。";
			link.l1 = "ふむ……";
			link.l1.go = "rocur_78";
		break;
		
		case "rocur_78":
            dialog.text = "お前の選択だ。あの女の命はお前自身の命と引き換えになるかもしれねえぞ。";
			link.l1 = "";
			link.l1.go = "rocur_79";
		break;
		
		case "rocur_79":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_80":
            dialog.text = "この売女を信用しようなんて考えるな。明日にはタイレックスに全部バレるぜ。お前、黒い印をもらいたいのか？";
			link.l1 = "いや、知らねえよ。それにあの女を殺す気もねえ――使い道があるんだ。あいつは俺と一緒に来るぜ。";
			link.l1.go = "rocur_81";
		break;
		
		case "rocur_81":
            dialog.text = "馬鹿なこと言うな！隙を見せたら、あの女はすぐに逃げるぞ。額を見てみろ、焼き印があるだろ？あいつは盗人だ。";
			link.l1 = "ふむ。おそらくお前の言う通りだな、ジャン。よし、あいつを片付けて、さっさとここを出ようぜ。";
			link.l1.go = "rocur_82";
			link.l2 = "俺はあいつを自分の船に置いておくつもりはねえ。逃げ出せねえ場所を用意してやったし、叫び声を聞く耳もねえんだ。 そこで今まで通りの稼業を続けさせるさ……俺専用の娼婦だ、しかもタダでな、へっへっ！";
			link.l2.go = "rocur_84";
		break;
		
		case "rocur_82":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto6", "", 5);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto7", "Mtraxx_PasqualeJanKillGirl", 5);
		break;
		
		case "rocur_83":
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
            dialog.text = "これで決まりだ、もう彼女がマーカスに何か言うことは絶対にない……";
			link.l1 = "かわいそうな娘だな……はは、まあ、よく言うだろ、運命の女神ってのは気まぐれなあばずれさ……";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_84":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_85":
            dialog.text = "「あなたは親切な男だ」 "+pchar.name+"。なぜお前はあの女に関わりたがるんだ？ああ、もうどうでもいいさ、お前の勝手だ。俺たちが出ていく間、 あいつを黙らせておけよ。";
			link.l1 = "もし彼女がそうならないなら――死んでるってことだ。";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_86":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing.Chest")) sTemp = "A bit. A chest full of doubloons, a handful of rubies, a map of Hispaniola and some rum.";
			else sTemp = "Nothing of value.";
            dialog.text = "何を見つけたんだ？";
			link.l1 = sTemp;
			link.l1.go = "rocur_87";
		break;
		
		case "rocur_87":
			Log_Info("You have received two treasure collections.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 2);
            dialog.text = "また運が俺の味方だな。ほら、お前の取り分だ。こんなにたくさん、一人じゃ浜まで運べねえよ。 あの四つ目の野郎がきっちり支払ってくれたぜ。";
			link.l1 = "素晴らしい！よくやった、ジャン！";
			link.l1.go = "rocur_88";
		break;
		
		case "rocur_88":
            dialog.text = "さあ、行け！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightOutHouse");
		break;
		
		case "rocur_89":
			PlaySound("VOICE\English\LE\Rocur\Rocur_04.wav");
            dialog.text = "よし。終わった。静かに片付いたな。さて、船に戻ろうぜ。";
			link.l1 = "ははっ、いい考えだな。";
			link.l1.go = "rocur_89_1";
			//AddDialogExitQuestFunction("Mtraxx_PasqualeNightGulf");
		break;
		
		case "rocur_89_1":
			DialogExit();
			DoFunctionReloadToLocation("shore34", "goto", "goto13", "Mtraxx_PasqualeFinal");
		break;
		
		case "rocur_90":
			PlaySound("VOICE\English\LE\Rocur\Rocur_05.wav");
            dialog.text = "「さて、」 "+pchar.name+"。そろそろお別れの時だな。もう二度と会えないかもしれねえが、お前と知り合えて本当に楽しかったぜ、友よ。";
			link.l1 = "ああ、まあまあ、ラ・ベガでしょっちゅう会うことになるだろう。";
			link.l1.go = "rocur_91";
			SetLocationCapturedState("LaVega_town", false);
			LAi_LoginInCaptureTown(npchar, false);
		break;
		
		case "rocur_91":
            dialog.text = "いや、もうタイレックスとは関わらない。このラヴォワジエとのゴタゴタが最後の一撃だったんだ。";
			link.l1 = "ふむ……そうか、もう気にするな。俺たちは正当に手に入れるべきものを手に入れたんだ。 タイレックスは儲かる情報をくれるよな？前回はレッドウルフの財宝で五十万以上稼いだぜ。";
			link.l1.go = "rocur_92";
		break;
		
		case "rocur_92":
            dialog.text = "それじゃあ、教えてくれ、見つけるのにずいぶん苦労したのか？";
			link.l1 = "そうだな……簡単じゃなかったぜ。色々考えて、旅して、戦いもした。だが、その価値はあったと思うぜ。";
			link.l1.go = "rocur_93";
		break;
		
		case "rocur_93":
            dialog.text = "「タイレックスにいくら払ったんだ？」";
			link.l1 = "三分の一だ。";
			link.l1.go = "rocur_94";
		break;
		
		case "rocur_94":
            dialog.text = "この件であいつはどんな役割を果たしたんだ？マーカスは一体何をしたんだ？";
			link.l1 = "ふむ……奴は俺にレッドウルフの航海日誌を渡してくれたな……";
			link.l1.go = "rocur_95";
		break;
		
		case "rocur_95":
            dialog.text = "「それで終わりか？そうだろ？」";
			link.l1 = "そうか……じゃなきゃウルフリック船長のことなんて知ることもなかっただろうな……";
			link.l1.go = "rocur_96";
		break;
		
		case "rocur_96":
            dialog.text = ""+pchar.name+"おい、わからねえのか？タイレックスはいつも他人に汚れ仕事をやらせてるんだぜ。 もし自分でその宝を見つけられるなら、お前に探させるわけがねえだろ？絶対に違う！ きっと最初は自分でやろうとしたが、全部台無しにして、お前を呼んで尻拭いさせたんだ。お前が頭を使って、 何週間も海で戦い、命を張ってる間に、あの野郎と気持ち悪い四つ目の仲間はラ・ベガの娼婦と遊んでやがった。 それでいて、奴は二十五万ペソも手に入れたんだ。ただそれだけのことでな\nあいつがレプラコーンって犬をメリダ襲撃の時に俺たちの助けに寄越したと思うか？違う、 奴は自分の利権を守りたかっただけだ。マーカスが自分でできることは全部自分でやる。ひとりで、 あるいはカトラスやハゲ頭、レプラコーン、それに他のくだらねえ連中――奴のために小銭で働くバカども――と一緒にな。お前や俺みたいな奴らは、マーカスが自分じゃ手に負えねえ案件を押し付けられるだけさ\n今まで奴のためにやった仕事を全部思い出してみろ。奴がどれだけお前から搾り取ったか数えてみろよ。もううんざりだ。 今は金もあるし、上等なコルベットもある、忠実な乗組員もいる……これからは俺は自由の身だ。ジャマイカに向かう――もしかしたらそこで私掠免状をもらえるかもしれねえ。";
			link.l1 = "タイレックスについてはお前の言う通りじゃないと思うが……まあ、幸運を祈るぜ、ジャン！ジャマイカでうまくいくといいな。";
			link.l1.go = "rocur_97";
		break;
		
		case "rocur_97":
            dialog.text = "そうするよ。君にも幸運を祈るぜ、それから俺の言ったことをよく考えてくれ。マーカスの手下なんて、 お前には似合わねえ。お前ならもっと大きなことができるはずだ。\nじゃあな、兄弟！幸運を祈るぜ！";
			link.l1 = "いい狩りを、ジャン！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeAddComplete");
		break;
		
		case "rocur_98":
            dialog.text = ""+pchar.name+"なあ、どうして俺たちはこんなに長い時間ジャングルで過ごすことになったんだ？これで俺の計画は台無しだぜ。 ええっと……じゃあな、相棒……";
			link.l1 = "へっ……";
			link.l1.go = "rocur_99";
		break;
		
		case "rocur_99":
            DialogExit();
		    LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			sld.lifeday = 0;
			Group_DeleteGroup("RocurSeaGroup");
			AddQuestRecord("Roger_4", "18");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_100":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				dialog.text = "行く時間だぜ、野郎ども。くそっ、プリンス、お前には驚かされたぜ。町ひとつ焼き払ったくせに、 肝心なときに自分の手は汚さねえとはな。";
				link.l1 = "俺は町を焼き払えなんて命じてねえぞ！";
				link.l1.go = "rocur_101";
			}
			else
			{
				dialog.text = "行く時間だぜ、野郎ども。ルーカス、お前は見逃したな。プリンスが見事にやってのけて、しっかり儲けも出したぜ！";
				link.l1 = "町のことはどうするんだ、イケメン！？俺は約束したんだぞ！";
				link.l1.go = "rocur_102";
			}
			sld = CharacterFromID("Lepricon");
			CharacterTurnToLoc(sld, "reload", "reload3");
		break;
		
		case "rocur_101":
            dialog.text = "少なくとも、お前はそれを守ろうとはしなかったな。そうじゃなきゃ、 うちの連中が真っ先にお前をぶった斬ってただろうさ。今日はあいつらにとっちゃ厳しい一日だったんだ。 少しは鬱憤を晴らす権利があるさ。すぐ慣れるぜ。お前にはその素質があるからな。";
			link.l1 = "忠告はありがたいが、頼んだ覚えはねえぜ。行くぞ。";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_102":
            dialog.text = " 冗談かと思ったぜ。まあ……お前は早まったな。街は終わりだ。コーストの兄弟たちが動き出せば、いつもこうなるんだよ。すぐに慣れるさ。";
			link.l1 = "俺にはできるかどうかわからねえ。まあ、行くとするか。";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_103":
            DialogExit();
			LAi_SetPlayerType(pchar);
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			sld = characterFromId("Tagofa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "12");
		break;
		
		case "rocur_104":
            dialog.text = "「おい…今のは何だったんだ？」";
			link.l1 = "何だ、分からなかったのか？俺はお前を買ったんだぜ。お前は前に、俺がスペイン人にコネがあるって言っただろう？ だから、それを利用させてもらったのさ。";
			link.l1.go = "rocur_105";
		break;
		
		case "rocur_105":
            dialog.text = "分かってるさ、俺はバカじゃねえ。だが、俺たち別の作戦を進めてたんじゃなかったか？";
			link.l1 = "まあな、カトラスと俺で考えたんだが、お前が反乱や追跡の最中に死んじまうのは後味が悪いから、 いっそのことお前を丸ごと買い取ることにしたんだぜ。";
			link.l1.go = "rocur_106";
		break;
		
		case "rocur_106":
            dialog.text = "はっ、俺を侮るなよ。俺はテラックスの船長の一人だぜ。剣の扱いくらい心得てるさ。";
			link.l1 = "それは疑ってねえが、自由になったことを本気で気にしてるのか？";
			link.l1.go = "rocur_107";
		break;
		
		case "rocur_107":
            dialog.text = "いや、いや――感謝してるんだ。ただ……あんなに金貨を使うなんて、ちょっとやりすぎじゃなかったか？考えただけで気分が悪くなるよ。\n一方で、あのプランターは磨き上げた銀のトレイみたいにピカピカだったな。";
			link.l1 = "ああ、「世紀の取引」ってやつだな。本当にちょっと痛いぜ。でもな、ジャン、時間は金よりも貴重なんだ。 お前たち全員のためにピストルや薬を探し回るなんてよ…";
			link.l1.go = "rocur_108";
		break;
		
		case "rocur_108":
            dialog.text = "感謝するぜ、でもな、相棒、お前はバカだな――悪く思うなよ。俺の連中は剣の腕は大したことねえって言っただろう？だが、引き金を引くくらい誰にでもできる。 カトラスや斧みたいに、どんなピストルや薬でも船倉から持ってきゃよかったんだ、あいつらはこだわらねえからな。";
			link.l1 = "ふむ、正直そんなこと考えてなかったな……まあ、とにかく行こうぜ。カトラスもそろそろ我慢できなくなってるだろうし。";
			link.l1.go = "rocur_109";
		break;
		
		case "rocur_109":
			DialogExit();
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_3");
		break;
		
		// Люк Лепрекон
		case "lepricon":
            dialog.text = "ごきげんよう、船長 "+GetFullName(pchar)+"ルーク・ザ・レプラコーン、参上だぜ！俺たちは南部メインのジャングルに向かうって聞いたぜ。";
			link.l1 = "その通りだ。ロングボートに乗り込め、すぐに出発するぞ。";
			link.l1.go = "lepricon_1";
		break;
		
		case "lepricon_1":
            dialog.text = "年寄りのバッカニアから一つ助言をしてやろう、船長。これからセルバに入るんだから、 きっとインディオたちに出会うことになるぜ。やつらへの贈り物を持っていくんだ。 インディオの戦士たちは上等なピストル、特に決闘用のものが大好きだ。 コンパスや望遠鏡も魔法の品として珍重されるぞ。\n女たちは安物の宝飾品や、鏡や櫛みたいな小物を好む。もしやつらと戦闘になったら、 ブランダーバスやアーケバスを使え。ぶどう弾は鎧を着ていない敵には特に効果的だ。集落に攻め入るなら、 紙薬莢が使える銃を勧めるぜ。";
			link.l1 = "よくやった、ルーク。お前の言葉はしっかり覚えておくぜ。乗船を歓迎する。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSail");
		break;
		
		case "lepricon_2":
            dialog.text = "村に着いたらすぐに族長に会え。それと、贈り物を持っていけ、そうでなきゃ意味がない。\n彼の民の中でこの先のジャングルの秘密の通路を知っている者がいないか必ず聞け、 さらに旅を恐れぬ者がいれば紹介してもらえ。\n俺も一緒に行く。困ったことがあれば俺に声をかけろ。";
			link.l1 = "行くぞ！ジャン、リュック、ついて来い！";
			link.l1.go = "exit";
			npchar.greeting = "Lepricon_02";
			AddDialogExitQuestFunction("Mtraxx_MeridaSeekVillage");
		break;
		
		case "lepricon_3":
            dialog.text = "何か質問はあるか、船長？";
			link.l1 = "今のところは何もない、ルーク。";
			link.l1.go = "lepricon_3x";
			if (pchar.questTemp.Mtraxx == "merida_advice")
			{
				link.l1 = "ああ！俺はあいつらの酋長と話して、贈り物も渡したんだ。その後、酋長は仲間を集めて会合を開いた。 何人かはメリダへの行き方を知ってるが、誰も行こうとしねえ――カポング族っていう別の部族を恐れてるんだよ。そのカポング族が地元の連中を震え上がらせてるんだ。あの野郎、 俺たちだけじゃ道を見つけるのは無理だし、雇える案内人もいないって言いやがった。じゃあ、 俺たちはこれからどうすりゃいいんだよ、ああ！？";
				link.l1.go = "lepricon_4";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Potion") && GetCharacterItem(pchar, "potion3") >= 12)
			{
				link.l2 = "俺は解毒剤を持ってるぜ。";
				if (GetCharacterItem(pchar, "potion3") > 42) link.l2.go = "lepricon_7";
				else link.l2.go = "lepricon_6";
			}
		break;
		
		case "lepricon_3x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		break;
		
		case "lepricon_4":
            dialog.text = "ふむ、なるほどな……船長、臆病はしばしば欲に勝てないもんだぜ。たっぷり報酬を約束すりゃ、誰だってその仕事を引き受けるさ……いや、待てよ？もっと狡猾にいこう――女たちを使え。贈り物を渡して、奴らの男について聞き出せば、きっと俺たちが必要とする案内人が見つかるはずだ。 旦那の協力にはビーズや鏡を山ほど約束してやれ。惜しまずに大きく約束して、うまく口説くんだ。";
			link.l1 = "へっ！まあ、やれるだけやってみるさ、うまくいくかどうかはわからねえけどな……";
			link.l1.go = "lepricon_5_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lepricon_5_1":
            dialog.text = "「まあ、もう一つ手はあるが……あまり良い方法じゃねえんだ、分かるだろ？」";
			link.l1 = "他に手があるのか？言ってみろよ！俺はインディアンの女たちのところに行って、 旦那を説得してくれなんて頼む気はねえんだ。";
			link.l1.go = "lepricon_5_2";
		break;
		
		case "lepricon_5_2":
            dialog.text = "この手は昔からあるやり方だ。カポン族よりもお前を恐れるべきだと奴らに思い知らせてやれよ。そうだな……村の女たち、特に酋長の妻や娘たちにお前の海賊どもが何をできるか、酋長に言ってやるのも手だ。 拷問の脅しなんかも混ぜてやればいい。\nまあ、とにかく、どうやったらこのインディアンどもがお前を恐れるかはお前なら考えつくだろう。 俺個人としてはこのやり方は好きじゃねえし、理由もあるんだがな。";
			link.l1 = "理由？例えば何だ？俺に言わせりゃ、かなり効果的で単純明快な解決策だと思うぜ。";
			link.l1.go = "lepricon_5_3";
		break;
		
		case "lepricon_5_3":
            dialog.text = "まず最初に、あれの後じゃ町の人気者にはなれねえだろうな。下手すりゃ罠にかかったり、 他の厄介な目に遭うかもしれねえ。\nそれにもう一つ……どうも気が進まねえ。武装した相手を倒すのと、女を脅すのはまったく別の話だ。\nインディアンたちには、もっと…話し合いでうまくやる方法を探した方がいいと思うぜ。";
			link.l1 = "了解だ、考えてみるぜ。もしかしたらビーズで女を口説いてみるかもな……あるいは酋長の娘たちを面白い方法で困らせてやる手もある、ははっ！";
			link.l1.go = "lepricon_5";
		break;
		
		case "lepricon_5":
            dialog.text = "もう一つ伝えておくぞ、船長。酋長によれば、ジャングルで敵対的なインディアン部族に遭遇するかもしれん。たぶん、 ただの少数の人食い集団だろうが、用心するに越したことはない。もし好戦的な部族なら、やつらは武器に毒を塗るから、 部下たちに解毒剤を用意しておけ。\n俺たちはいつも薬をたっぷり持ち歩いている。お前の海賊どもについては……解毒剤を持ってきてくれれば、俺が部下たちに配ってやる。このためには少なくとも12本の薬が必要だ。自分や士官たちの分も忘れずに持ってくるんだぞ。";
			link.l1 = "わかった。解毒剤を持ってくる。";
			link.l1.go = "lepricon_5x";
		break;
		
		case "lepricon_5x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		   pchar.questTemp.Mtraxx = "merida_advice2";
		   pchar.questTemp.Mtraxx.Merida.Women = "true";
		   pchar.questTemp.Mtraxx.Merida.Potion = "true";
		   AddQuestRecord("Roger_5", "8");
		   sld = characterFromId("Hayamee");
		   LAi_CharacterEnableDialog(sld);
		   AddLandQuestMark(sld, "questmarkmain");
		  // LocatorReloadEnterDisable("Shore_ship3", "boat", false); 
		   bQuestDisableMapEnter = false;
		   DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");// выпустим в море
		   SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "lepricon_6":
			i = GetCharacterItem(pchar, "potion3");
			RemoveItems(pchar, "potion3", i);
			pchar.questTemp.Mtraxx.Merida.Antidote = i;
            dialog.text = "よし、渡せ。あとは俺がやる。";
			link.l1 = "「そこに……」";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_7":
			RemoveItems(pchar, "potion3", 42);
			pchar.questTemp.Mtraxx.Merida.Antidote = 42;
            dialog.text = "四十二本の薬で十分だ。残りは自分で取っておけ。";
			link.l1 = "「よし…」";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_8":
            DialogExit();
		    npchar.dialog.currentnode = "lepricon_3";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		break;
		
		case "lepricon_9":
            dialog.text = "船長、あんたのインディアンたち――ハヤミとタゴファ――は、あんたが約束した贈り物を待ちくたびれて、別の村へカシェーリを飲んで踊りに行っちまったぜ。 あんたのやり方じゃ、俺たちにとっちゃ何の得にもならねえ気がする。悪いが、ここからはあんた抜きだ。 ピカールが遠征隊を率いることになった。";
			link.l1 = "だったら、てめえら全員くたばっちまえ！";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "19");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_10":
            dialog.text = "船長、なんだよこれは？無駄に時間ばかり食っちまったじゃねえか！あんたのやり方じゃ、 俺たちにとって何の得にもならねえ気がするぜ。悪いが、ここでお前はおしまいだ。 ピカードが遠征隊を率いることになった。";
			link.l1 = "だったら、くたばりやがれ！";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_11":
            dialog.text = "船長、なんだってんだ？革と板を探すのに十日もあっただろうが。 ここからそう遠くないところにマラカイボの町があるんだぜ！あんたのやり方じゃ、 俺たちにとって何の得にもならねえ気がする。悪いが、ここでお前はおしまいだ。ピカールが遠征隊を率いる。";
			link.l1 = "じゃあ、くたばりやがれ！";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_12":
            dialog.text = "船長、すまないが、俺は本当ならとっくにラ・ベガにいるはずだったんだ。あんたもそうだったはずだろ。 あんたはマーカスと俺のことを忘れてしまったに違いない。まあいい、俺は行くぜ。 あんたは自分のやることを続ければいいさ、マーカスには全部俺が説明する。じゃあな、残念だよ……もっとあんたを信じてたんだがな。";
			link.l1 = "ふん…";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaReturnFail");
		break;
		
		case "lepricon_13":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_03.wav");
            dialog.text = "つまり、俺の理解だと、お前らはケンカしたってわけだな。戦利品を分けられなかったんだろ、チャーリー・プリンス？";
			link.l1 = "レプラコーンか？お前がここにいるとはな……まあ、別に驚きゃしねえよ。ああ、あの強欲な野郎どもは掟を無視して、俺を殺そうとしやがったんだ。";
			link.l1.go = "lepricon_14";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_01", "quest", "lepricon");
		break;
		
		case "lepricon_14":
            dialog.text = "ああ、ひどくやられたな、坊ちゃん。まるで水浸しのクソみてえな顔してるぜ\nコードについて何か言ったか？教えてやるよ： 俺はそのコードの番人だって言われてるマーカスと一緒に仕事したことがある。 あの紙切れに唾を吐きかける野郎どもを何度も見てきたが、数える気にもならねえ。ひどい目に遭った奴もいれば、 何ともなかった奴もいる\nやりたいことは何でもやれよ、見返りがそれに見合うならな。特に誰も見てねえ時はな";
			link.l1 = "「そうか……お前も宝を狙ってここに来たのか？」";
			link.l1.go = "lepricon_15";
		break;
		
		case "lepricon_15":
            dialog.text = "なんてくだらねえ質問だ。俺がここで何をしてると思うんだよ、ヒスパニョーラの故郷からこんなに離れてさ？まあ、 結局のところ、俺はお前ら全員より賢いんだぜ。お前ら腐った海賊の性根なんざ知り尽くしてる。 だからただ待ってたのさ、お前らネズミどもが互いに食い合って、最後に一人だけ敵が残るようにな。だが、 そいつも傷だらけで疲れ果ててるってわけだ。";
			link.l1 = "敵だと？これがあんたの後ろ盾の掟に従うやり方か！？こんなことで人を殺すのかよ！";
			link.l1.go = "lepricon_16";
		break;
		
		case "lepricon_16":
            dialog.text = "俺はコード・プリンスには従ってねえし、海賊でもねえ。船すら持ってねえから、 ここに来るのにボロ舟を借りる羽目になったんだ。要するに、俺はただのバッカニアにすぎねえよ。俺は狩人だ、 バッファローを狩ってブッカンを作ってる。 俺たちフランスのバッカニアがスペイン野郎どもの生業を台無しにしてるって言いがかりをつけてきやがるから、 マルクスに助けと庇護を求めるしかなかった。だから時々、あいつの仕事を手伝ってやってるってわけさ\n俺は海賊じゃねえが、俺の仲間と俺は腕っぷしには自信がある。お前も俺たちの戦いぶりを見ただろう。";
			link.l1 = "俺たちは一緒に襲撃して戦ったじゃねえか、レプラコーン。命を張ってお互いの背中を守り合ったんだ。全部、 お前にとっては何の意味もねえのか？";
			link.l1.go = "lepricon_17";
		break;
		
		case "lepricon_17":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_04.wav");
            dialog.text = "正直に言うぜ、旦那プリンス。俺はあんたのことが昔から好きじゃなかった。あんたは成り上がり者だ。生意気な若造で、 酒と女に溺れ、タイレックスのためにちょっとばかり儲かる仕事をしたくらいで自分を大海賊気取りだろうが\nそれに、あんたは生まれついての人斬りだ。カルタヘナを落としたからって、 兄弟団の中で重みが増したとでも思ってるのか？ハハッ、冗談じゃねえ、 そんなのはあんたみたいな化け物どもの間だけだぜ。";
			link.l1 = "ああ、こりゃ笑えるぜ！ははは、本物の天使様のお言葉だな！このクソじじいめ！";
			link.l1.go = "lepricon_18";
		break;
		
		case "lepricon_18":
            dialog.text = "もうこれで全て片付いたと思うぜ。そろそろこの茶番も終わりだ。地獄の悪魔どもがお前を長いこと待ってたんだぜ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionLepriconFight");
		break;
		
		case "lepricon_19":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZapugivanieIndeets"))
			{
				dialog.text = "気に入ったか、ん？";
				link.l1 = "引っ込んでろ！";
				link.l1.go = "lepricon_20";
			}
			else
			{
				dialog.text = "さて、どう思う？";
				link.l1 = "ふざけるなよ、レプラコーン。何なんだこれは！？俺は虐殺なんて命じてねえぞ！やりすぎだと思わねえのか！？ テラックスが怒るぞ！";
				link.l1.go = "lepricon_24";
			}
		break;
		
		case "lepricon_20":
            dialog.text = "じゃあ、なんでそんな後ろめたい顔してるんだ？楽しんでないのか？教えてやろう――これからもっとひどくなるだけだぜ。今日の虐殺がたまたま起きたと思ってるのか？はっ、冗談じゃねえ。 こんなの日常茶飯事だ。ピカールなんざ眉ひとつ動かさなかったさ。あいつらにとっちゃ、 好きなことをやるただの一日なんだよ。";
			link.l1 = "で、あんたはどうなんだ？通りすがりってわけか？";
			link.l1.go = "lepricon_21";
		break;
		
		case "lepricon_21":
            dialog.text = "俺は海賊じゃねえ。今日の出来事にも関わりたくなかったんだ。それに……メリダの焼け焦げた大地に女たちの遺体が転がってるのがそんなに気に食わねえなら、王子よ、 なんでインディオたちにはあんなふうに振る舞ったんだ？\n";
			link.l1 = "俺がどうすりゃよかったんだ？全部投げ出してマーカスのところに這いつくばって謝れってのか？";
			link.l1.go = "lepricon_22";
		break;
		
		case "lepricon_22":
            dialog.text = "お前がすっかりその気になって、ティラックスの船長たちみたいに考えたり動いたりし始めたのかと思ったぜ。\nだが違ったな、はは！お前にはこんな仕事は向いてねえ。マーカスに取り分を渡して、 尻尾を巻いて出ていく方が身のためだぜ。\nここはお前の居場所じゃねえよ。";
			link.l1 = "俺のことを決めるのはお前じゃねえ、レプラコーン。それに、俺を侮辱する権利なんてお前にはねえ。 俺の取り分は誰にも渡さねえ。テラックスとはきっちり山分けするぜ。";
			link.l1.go = "lepricon_23";
		break;
		
		case "lepricon_23":
            dialog.text = "ああ、いいぜ。でもお前が気絶する前に出発したほうがいいな。";
			link.l1 = "ふざけんなよ、くそっ。";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_24":
            dialog.text = "それなら、あいつのことをよく知らねえんだな。だが、今日の出来事があんたに喜びをもたらさねえなら、 俺の話を聞いてみな。";
			link.l1 = "これ以上一体何を差し出せるってんだ！？";
			link.l1.go = "lepricon_25";
		break;
		
		case "lepricon_25":
            dialog.text = "ちゃんと耳を傾けたほうがいいぜ、坊主。";
			link.l1 = "ふん、ルーカス、その口の利き方は気に入らねえが、まあいい、やってみろ。";
			link.l1.go = "lepricon_26";
		break;
		
		case "lepricon_26":
            dialog.text = "俺は余裕があるぜ――お前より長く生きてるからな、プリンス。だから射撃だけじゃなくて、目も鋭いんだ。気づいたこと、知りたいか？";
			link.l1 = "「さっさと言え！」";
			link.l1.go = "lepricon_27";
		break;
		
		case "lepricon_27":
            dialog.text = "お前は場違いだ。確かに腕はいいし、成長もしている。だが、それはお前が強い船長だからであって、 本当に天職だからじゃねえ。どうしてテラックスに身を寄せたのか、理由は知らねえが、信じてくれ、 ここがお前の本当の居場所じゃねえんだ。";
			link.l1 = "俺には……目的があるんだ。でも、それが何かは言えねえ。";
			link.l1.go = "lepricon_28";
		break;
		
		case "lepricon_28":
            dialog.text = "「それに少しは近づいたのか？」";
			link.l1 = "「まだだ。」";
			link.l1.go = "lepricon_29";
		break;
		
		case "lepricon_29":
            dialog.text = "さて、今日ですら距離が縮まらなかったなら、ここで得るものはもう何もないな。あんたはいい奴だぜ、プリンス。 インディアンたちを人間として扱ってくれた。皮肉なことに、そんなあんたが俺たちとここにいるとはな。 俺からの助言だが、取り分はテラックスに渡して面倒を避けろ、そしてこの一件から手を引け――今のうちに自分の魂を救うんだ。";
			link.l1 = "考えておくよ。";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_30":
			DialogExit();
			locCameraFromToPos(21.35, 1.54, 0.05, true, 25.55, 0.46, -0.91);
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				PlaySound("People Fight\PistolShot.wav");
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 2.0);
			}
			else
			{
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 0.5);
			}
		break;
		
		// Тагофа - проводник к Мериде
		case "tagofa":
            dialog.text = "海の息子よ、タゴファが挨拶するぜ。山中にあるスペイン人の居留地への道を案内してほしいか？";
			link.l1 = "その通りだ。他の連中と違って、お前は俺たちの言葉がうまいじゃねえか。";
			link.l1.go = "tagofa_1";
		break;
		
		case "tagofa_1":
            dialog.text = "タゴファはよくヤラナウイと取引していた……旅の大半は川を進むことになる。\nお前にはロングボートが必要だ。持っているか？";
			link.l1 = "そうかい？ちょっとの間だけ借りてもいいんじゃねえか…";
			link.l1.go = "tagofa_2";
		break;
		
		case "tagofa_2":
            dialog.text = "我々の村は小さくて、長艇もわずかしかないし、どれも漁にしか使えねえんだ。\n今必要なのは、長い航海にも耐えられる、あんたたちの船にあるような立派な長艇なんだよ。";
			link.l1 = "ふむ……それならロングボートが六隻必要だな。船にはそんなに多くはないぞ。";
			link.l1.go = "tagofa_3";
		break;
		
		case "tagofa_3":
            dialog.text = "なら作ればいいだろう。お前ら白人は陸であんな巨大な船まで修理できるんだ、ロングボートぐらい作れるはずだ。";
			link.l1 = "へっ、どうやらお前の言う通りだな、タゴファ。川まで案内してくれ、ここから遠くないといいが？";
			link.l1.go = "tagofa_4";
		break;
		
		case "tagofa_4":
            dialog.text = "違う。ついて来い。";
			link.l1 = "...";
			link.l1.go = "tagofa_5";
		break;
		
		case "tagofa_5":
           DialogExit();
		   chrDisableReloadToLocation = true;
		   npchar.dialog.currentnode = "tagofa_6";
		   LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_MeridaGotoRiver", 5.0);
		break;
		
		case "tagofa_6":
            dialog.text = "ここが俺が話していた川だ。ここから旅を始めるぜ。お前が船を作ったら、出発するぞ。";
			link.l1 = "了解だ、Tagofa。終わったら知らせるぜ。";
			link.l1.go = "tagofa_7";
		break;
		
		case "tagofa_7":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.dialog.currentnode = "tagofa_8";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.Mtraxx = "merida_boats";
			pchar.questTemp.Mtraxx.Boats = "true";
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
			// Лепрекона - гулять
			sld = characterFromId("Lepricon");
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "tagofa_8":
            dialog.text = "「舟の準備はできてるかい、白い酋長？」";
			link.l1 = "ああ。俺の部下たちがまさにこれから乗り込むところだ。";
			link.l1.go = "tagofa_9";
		break;
		
		case "tagofa_9":
            dialog.text = "よし。俺と一緒に最初の船に乗れ。タゴファが道を案内するぜ。";
			link.l1 = "";
			link.l1.go = "tagofa_10";
		break;
		
		case "tagofa_10":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "Mtraxx_MeridaRiverTrip", -1);
			chrDisableReloadToLocation = true;
		break;
		
		case "tagofa_11":
            dialog.text = "川の部分は終わった。ここからスペイン人の居留地までは遠くない。\nあそこに小道がある、その道に沿って行けば迷わずに済む。\nカポン族の狩人がうようよいる森をうまく避けてきたが、ここもあいつらの縄張りだ。\n油断は禁物だぜ。";
			link.l1 = "心配すんな。あいつらが醜い化粧面を見せた瞬間、俺たちが叩き潰してやるぜ。";
			link.l1.go = "tagofa_12";
		break;
		
		case "tagofa_12":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_warning.win_condition.l1 = "locator";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.location = "Serpentine2";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator = "detector1";
			pchar.quest.mtraxx_merida_warning.function = "Mtraxx_MeridaWarning";
			chrDisableReloadToLocation = false;
		break;
		
		case "tagofa_13":
			StartQuestMovie(true, false, true);
            dialog.text = "";
			link.l1 = "おい！タゴファ！見ろよ！道の真ん中にあるあれは……なんだ？インディアンの何かか。";
			link.l1.go = "tagofa_14";
			locCameraFromToPos(7.63, 9.07, 11.73, true, 2.97, 9.02, 7.70);
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;
		
		case "tagofa_14":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_FadeLong("Mtraxx_MeridaWarningCutscene", "");
			locCameraSleep(true);
		break;
		
		case "tagofa_15":
            dialog.text = "それはカポング族の印だ。警告だぜ。これ以上進むなってことさ。カポング族にはもう見つかってるぞ。";
			link.l1 = "「それで、もし俺たちがさらに進んだらどうなる？奴らは襲ってくるのか？」";
			link.l1.go = "tagofa_16";
		break;
		
		case "tagofa_16":
            dialog.text = "ああ、白人の酋長。お前が威圧的に見えるんだろうな、だからまだ奴らは俺たちを襲ってこないんだ。なのに、 お前のために看板まで立てやがった。";
			link.l1 = "看板なんざくそくらえだ。俺たちは前進するぞ…全員、よく聞け！武器を取れ！準備しろ！油断するな！あの野蛮人どもがツラを出しやがったら、 全員ぶっ殺してやるからな！\n";
			link.l1.go = "tagofa_17";
		break;
		
		case "tagofa_17":
            DialogExit();
			EndQuestMovie();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_capong.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_capong.win_condition.l1.location = "Merida_jungle_01";
			pchar.quest.mtraxx_merida_capong.function = "Mtraxx_MeridaPrepareCapongAttack";
		break;
		
		case "tagofa_18":
            dialog.text = "白い酋長とその仲間たちがカポンガたちを打ち砕いた、タゴファは感心している。\nスペイン人の街は近い。滝の見える谷がある。\nタゴファはスペイン人のところへは行かない。\n滝の近くで待っているぞ。";
			link.l1 = "よし。進むぞ！";
			link.l1.go = "tagofa_19";
		break;
		
		case "tagofa_19":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_merida_exittown.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exittown.win_condition.l1.location = "Merida_ExitTown";
			pchar.quest.mtraxx_merida_exittown.function = "Mtraxx_MeridaExitTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "15");
		break;
		
		case "tagofa_20":
            dialog.text = "戻ったぞ、白い酋長。タゴファは約束通りやったぞ。";
			link.l1 = "ありがとう、Tagofa。よくやったな。";
			link.l1.go = "tagofa_21";
		break;
		
		case "tagofa_21":
            dialog.text = "タゴファは行かねばならん。ハヤミが俺を待っている。さらばだ、海の息子よ。";
			link.l1 = "幸運を祈るぞ、森の息子よ。奥さんによろしく伝えてくれ。そして、助けてくれてありがとう。";
			link.l1.go = "tagofa_22";
		break;
		
		case "tagofa_22":
            DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_final.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_final.win_condition.l1.location = "Shore_ship3";
			pchar.quest.mtraxx_merida_final.function = "Mtraxx_MeridaFinal";
			ChangeIndianRelation(7.0);
		break;
		
		// дозорный у Мериды
		case "merida_guard":
            dialog.text = "おい！お前は誰だ、何の用だ？";
			link.l1 = "メリダに行って、お前たちの総督か、あるいはその代わりの奴と話をしなきゃならねえな…";
			link.l1.go = "merida_guard_1";
		break;
		
		case "merida_guard_1":
            dialog.text = "メリダにはよそ者を入れねえ。出て行け！";
			link.l1 = "相棒、俺たちは二日間も必死に漕いで、それからインディアンの大群と戦ったんだ、 そう簡単に引き下がるわけにはいかねえ。\nもう一度言う、村の頭領と話がしたいんだ！あんたの頭領に…取引の提案がある、そうだ！\nもしお互い納得できれば、あんたたちの村は無傷で済むぜ。";
			link.l1.go = "merida_guard_2";
		break;
		
		case "merida_guard_2":
            dialog.text = "脅してるのか、ラドロン？";
			link.l1 = "どうしてそれが分かったんだ？ああ、そうさ、確かに脅してるぜ。俺たちはここに来た目的を穏便に手に入れるか、 力ずくで奪うかだ。お前にはこの村の運命を決める名誉があるんだぜ。";
			link.l1.go = "merida_guard_3";
		break;
		
		case "merida_guard_3":
            dialog.text = "メリダには絶対に入れさせねえぞ、この血塗られた海賊め！\n警報だ！敵が門にいるぞ！";
			link.l1 = "「なんて理不尽な旦那なんだ……」";
			link.l1.go = "merida_guard_4";
		break;
		
		case "merida_guard_4":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DoQuestFunctionDelay("Mtraxx_MeridaHouseGuards", 5.0);
		break;
		
		// мэр Мериды
		case "merida_head":
            dialog.text = "くそっ、盗賊どもめ！俺たちに何の用だ！？ここは小さくて質素な集落だぞ。金も銀も持っちゃいねえ！ どうやって俺たちのことを知ったんだ！？";
			link.l1 = "おやおや、とぼけたりしらばっくれたりなさらないでくださいませ、閣下。あなたのオパールについての噂は、 もう世界中に広まっておりますわ。";
			link.l1.go = "merida_head_1";
		break;
		
		case "merida_head_1":
            dialog.text = "噂だけでこんな神をも恐れぬ虐殺を引き起こしたのか！？誰一人として容赦しなかった！獣どもめ……よく聞け、鉱床はここから遥か遠くだ。ここにはお前たちの得るものなど何もない。立ち去れ。";
			link.l1 = "お前がこの神も恐れぬ虐殺を始めたんだ。民間人までお前の兵士と一緒に戦った。たった数枚の壁を守るために、 こんな無意味な英雄的行為ができるなんて、俺には絶対に信じられねえ。";
			link.l1.go = "merida_head_2";
		break;
		
		case "merida_head_2":
            dialog.text = "この壁を築くのにどれだけの苦労があったか知ってるか？外部の職人なんて雇わなかった――俺たち自身で、一つ一つレンガを積み上げたんだ。住民全員でな。俺も、この手でやったんだぜ。";
			link.l1 = "なんて感動的な話だな……それで、家具はどうしたんだ？お前たちが自分で作ったのか？見事な彫刻の椅子だな。それにテーブルも。 キャビネットも。これは染色したオークか？それとも黒檀か？『質素な集落』にしては、ちょっと贅沢すぎやしねえか？";
			link.l1.go = "merida_head_3";
		break;
		
		case "merida_head_3":
            dialog.text = "強欲がお前の心を曇らせているな、泥棒野郎。";
			link.l1 = "ややこしくする必要はねえぜ、総督旦那。さもないと後悔することになるぞ。";
			link.l1.go = "merida_head_4";
		break;
		
		case "merida_head_4":
            dialog.text = "俺を拷問するつもりか、この忌々しい海賊め？残念だったな――俺は全能の神を信じている。やりすぎれば、俺は殉教者として天に昇るだけだぞ。";
			link.l1 = "ふむ……";
			link.l1.go = "merida_head_5";
		break;

		case "merida_head_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_6", "Quest\Roger.c");
		break;
		
		case "merida_head_6":
            dialog.text = "旦那、こいつはこんなふうに話す気はねえよ。俺に任せてくれ。";
			link.l1 = "「おや？」";
			link.l1.go = "merida_head_7";
		break;
		
		case "merida_head_7":
            dialog.text = "あの呪われたプランテーションで、あの偉そうなスペイン野郎どもにされたことは全部覚えてるぜ。プリンス、 よかったら見せてやろうか。ついでにいくつか話も聞かせてやるよ。退屈なんてさせねえさ。";
			link.l1 = "「もしお前が調子に乗ったらどうするんだ？」";
			link.l1.go = "merida_head_8";
		break;
		
	case "merida_head_8":
            dialog.text = "あいつは丁寧に話したりしねえよ。ああいう野郎のことは俺もよく知ってるぜ。";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) >= 50 && GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50)
			{
				link.l1 = "（信頼）（名誉）（指導力）今日はもう十分血が流れた、ジャン。ここからは俺が自分でやる。";
				link.l1.go = "merida_head_dobro_1";
				Notification_Perk(true, "Trustworthy");
				Notification_Reputation(true, 50, "low");
				notification("Skill Check Passed", SKILL_Leadership);
			}
			else
			{
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
				if (sti(pchar.reputation.nobility) < 50) Notification_Reputation(false, 50, "low");
				if (GetCharacterSkill(pchar, SKILL_LEADERSHIP) < 50) notification("Skill Check Failed (50)", SKILL_LEADERSHIP);
			}
			link.l2 = "やれよ。俺は関わらねえ。それに見てもいねえからな。";
			link.l2.go = "merida_head_zlo_1";
		break;
		
		case "merida_head_zlo_1":
            dialog.text = "もしお前に借りがなけりゃ、言いたいことをぶちまけてやるところだ…ちくしょう。行け。これからが本番だぜ。";
			link.l1 = "無理はするなよ。";
			link.l1.go = "rocur_42";
		break;
		
		case "merida_head_dobro_1":
            dialog.text = "お望み通りだ、相棒。見物するのも面白そうだぜ。";
			link.l1 = "あまり早くニヤけるんじゃねえぞ。";
			link.l1.go = "merida_head_dobro_2";
		break;
		
		case "merida_head_dobro_2":
			StartInstantDialog("Merida_Head", "merida_head_dobro_3", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_3":
            dialog.text = "自分でやるって言うのか、血を流さずにだと？このクソ野郎め、口先だけで石が湧いてくるわけねえだろうが！";
			link.l1 = "出てきた方がいいぞ、総督。さもなきゃ、この街を焼き払って、お前以外は皆殺しにしてやる。 俺もこんな手段は好かねえが、自分の大義のためなら名誉を犠牲にする覚悟はある。だが、 お前の務めはメリダの民間人や生き残った兵士、労働者たちを守ることだろう。それとも、連中の苦しみを代償に“殉教者として昇天”する方がいいのか？それじゃあ、神の御心とは思えねえな。";
			link.l1.go = "merida_head_dobro_4";
		break;
		
		case "merida_head_dobro_4":
            dialog.text = "くそっ……\nそこだ……あの箱の中だ。町の連中だけは勘弁してくれ！";
			if (GetSummonSkillFromName(pchar, SKILL_Sneak) >= 50)
			{
				link.l1 = "（こっそり）全部宝箱に入ってるか？";
				link.l1.go = "merida_head_dobro_vnimatelnost_1";
				notification("Skill Check Passed", SKILL_Sneak);
			}
			else
			{
				link.l1 = "俺は約束を守るぜ。さらばだ、総督。";
				link.l1.go = "merida_head_dobro_5";
				notification("Skill Check Failed (50)", SKILL_SNEAK);
			}
		break;
		
		case "merida_head_dobro_vnimatelnost_1":
            dialog.text = "地獄に落ちやがれ！\nこの箱にも偽底があるぜ。全部持っていけ！！";
			link.l1 = "...";
			link.l1.go = "merida_head_dobro_vnimatelnost_2";
			pchar.questTemp.Mtraxx_MeridaKamushki = true;
		break;
		
		case "merida_head_dobro_vnimatelnost_2":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "Mtraxx_MeridaOpenChest", -1);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
		break;
		
		case "merida_head_dobro_vnimatelnost_3":
            dialog.text = "見事だな、王子。お前を甘く見てて悪かったぜ。";
			link.l1 = "満足か？";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_dobro_6", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_6":
            dialog.text = "うまいな、王子。";
			link.l1 = "満足か？";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_7":
            dialog.text = "もっとだよ。でも…自分の目で確かめな。\n先に行けよ、俺はもう少し調べてみるぜ。";
			link.l1 = "...";
			link.l1.go = "rocur_43";
		break;
		
		/*case "merida_head_99999":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
		break;*/
		
		case "merida_head_sleep":
            dialog.text = "お前は宝石を手に入れたら町を出ていくと約束したじゃないか……もう手に入れたのに、お前のラドロネスどもが我々の家に火を放った！お前は嘘つきで邪悪な海賊だ！ 地獄の業火がこれほど熱くお前を焼くことを願っているぞ！！！";
			link.l1 = "";
			link.l1.go = "exit";
			locCameraFromToPos(19.18, 1.28, -0.28, true, 24.88, 1.62, -1.19);
			AddDialogExitQuest("Mtraxx_RetributionSleep2");
		break;
		
		// капитан пинаса Китти
		case "kittycap":
            dialog.text = TimeGreeting()+"、旦那。どうしてここに来たんだ？";
			link.l1 = "俺はタイレックスから来た。お前の船をブリッジタウンまで護衛するよう言われてるんだ。準備はいいか？";
			link.l1.go = "kittycap_1";
		break;
		
		case "kittycap_1":
            dialog.text = "やっとか！ああ、俺の船員たちはすぐにでも出航できるぜ！";
			link.l1 = "素晴らしい。帆を上げろ、船長。出航するぞ！";
			link.l1.go = "kittycap_2";
		break;
		
		case "kittycap_2":
		    DialogExit();
            LAi_CharacterDisableDialog(npchar);
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			LAi_SetImmortal(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
		    pchar.quest.mtraxx_ignasio_sail.win_condition.l1 = "location";
			pchar.quest.mtraxx_ignasio_sail.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.mtraxx_ignasio_sail.function = "Mtraxx_IgnasioArrive";
			SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1 = "NPC_Death";
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1.character = "Mtr_KittyCap";
			pchar.quest.mtraxx_ignasio_sinkkitty.function = "Mtraxx_IgnasioKittySink";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "kittycap_3":
            dialog.text = "助けてくれてありがとうございます、船長！あなたがそばにいてくれたおかげで、 まるで砦の壁の内側にいるかのような安心感でした。";
			link.l1 = "ははっ、気にすんな、相棒！全部マーカスのおごりだぜ。幸運を祈るぜ、仲間！";
			link.l1.go = "kittycap_4";
		break;
		
		case "kittycap_4":
            DialogExit();
			npchar.lifeday = 0;
			RemoveCharacterCompanion(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			Mtraxx_IgnasioCreateMarko();
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		// Игнасио Марко
		case "ignasio":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_01.wav");
			dialog.text = "勇敢なる船長にご挨拶を！自己紹介させていただきます――イグナシオ・マルコ・デ・トレロ、イングランドに仕える私掠船乗りでございます。";
			link.l1 = TimeGreeting()+"、友よ。船長 "+GetFullName(pchar)+" お役に立ちますぜ。どうなさいやす？";
			link.l1.go = "ignasio_1";
		break;
		
		case "ignasio_1":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "ああ、知ってるぞ！旦那 "+GetFullName(pchar)+"「お前さんの財力や後ろ盾の噂は、この群島中にまで俺の耳に届いてるぜ。 俺の提案はきっとお前さんにとって面白いものになると思うぜ。」";
			link.l1 = "「どんな申し出だ？」";
			link.l1.go = "ignasio_2";
		break;
		
		case "ignasio_2":
            dialog.text = "酒場に行って一杯やろうぜ。全部話してやる。こんな話、街中でするもんじゃねえ。";
			link.l1 = "よし……行くぞ！";
			link.l1.go = "ignasio_3";
		break;
		
		case "ignasio_3":
            DialogExit();
			FreeSitLocator("Bridgetown_tavern", "sit_front2");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Bridgetown_tavern", "sit", "sit_front2", "Mtraxx_IgnasioInTavern", -1);
		break;
		
		case "ignasio_4":
			LAi_SetSitType(pchar);
            dialog.text = "一杯どうだ、船長？";
			link.l1 = "もちろんだぜ！";
			link.l1.go = "ignasio_5";
		break;
		
		case "ignasio_5":
			LAi_Fade("", "");
            dialog.text = "へっ、ここじゃ本当にラムに水なんて混ぜねえんだな……";
			link.l1 = "「それと、客に腐った魚を出すんじゃねえぞ、いいな。で、どういう話だ？」";
			link.l1.go = "ignasio_6";
		break;
		
		case "ignasio_6":
            dialog.text = "あんたの率直さは気に入ったぜ、旦那。ところで、イングランドとオランダの間で貿易戦争が起きてるのを知ってるか？";
			link.l1 = "そうだ。俺もその件に関わることができて光栄だったぜ。";
			link.l1.go = "ignasio_7";
		break;
		
		case "ignasio_7":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "ならば説明は不要だな。俺はイングランドの私掠船として、この戦争をあいつらの側で戦っている。 お前はほとんど自由な傭兵だから、どっちと戦うかなんて気にしちゃいないだろう…";
			link.l1 = "ほとんどそうだが、フランスは越えないんだ、悪いな。";
			link.l1.go = "ignasio_8";
		break;
		
		case "ignasio_8":
            dialog.text = "もちろんだぜ、船長！じゃあ、単刀直入に言うぞ。キュラソーとトリニダードの間に小さな有人島があるんだが、 地図には載ってねえ……ごく最近、いや本当に最近になって、 オランダ野郎どもがそこを補給と修理のための一時的な寄港地として使い始めたんだ。 どうやら自分たちしかその島を知らねえと思ってるらしいが……それは間違いだ。へっへっへ\n数日前、銀の護送船団が……嵐にやられてな、今オランダの連中はその島で船の修理をしてやがる。旗艦はマストを失っちまったから、 修理にはしばらくかかるだろう。オランダ野郎どもは修理にかかりきりで、乗組員たちもほとんど島中に散らばってるぜ……";
			link.l1 = "「それで突然俺たちが現れて、事態を救うってわけか？」";
			link.l1.go = "ignasio_9";
		break;
		
		case "ignasio_9":
            dialog.text = "その通りだ、船長。俺一人じゃ無理だが、あんたと一緒なら話はまるで違うぜ。やってみるか？俺の船は上等だし、 乗組員も腕利きだ。それに経験もそれなりにある。あんたの腕前も……なかなかのもんだぜ。";
			link.l1 = "「俺たちにどれくらい時間が残ってる？」";
			link.l1.go = "ignasio_10";
		break;
		
		case "ignasio_10":
            dialog.text = "無駄にせずすぐに出航すれば、十分にあるぜ。";
			link.l1 = "それじゃあ、イグナシオ・マルコ船長、弾薬と武器を補給して出航しよう。島の正確な座標はどこだ？";
			link.l1.go = "ignasio_11";
		break;
		
		case "ignasio_11":
            dialog.text = "12度40分北、64度11分西。わかったか？";
			if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche")) link.l1 = "はっ！デジャヴだな……了解だ。";
			else link.l1 = "了解だ。";
			link.l1.go = "ignasio_12";
		break;
		
		case "ignasio_12":
            dialog.text = "『トレロ』へ向かうぜ。"+pchar.name+"船長、待ってるからな！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioAddMarko");
		break;
		
		case "ignasio_13":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_03.wav");
			dialog.text = "すげえ戦いだったな、船長？さて、ここからが楽しいところだぜ。取り分を分けよう。半分は俺と俺の仲間のものだ。";
			link.l1 = "よし、やってやろうじゃねえか……";
			link.l1.go = "ignasio_14";
		break;
		
		case "ignasio_14":
			LAi_Fade("", "");
			WaitDate("", 0, 0, 0, 3, 10); 
			pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER)-sti(pchar.questTemp.Mtraxx.Silver);
			pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY)-sti(pchar.questTemp.Mtraxx.Mahogany);
			if (sti(pchar.questTemp.Mtraxx.Silver) < 100)
			{
				dialog.text = "船長、どうしたんだ？俺たちの銀はどこだ？まさか獲物を沈めちまったのか？";
				if (sti(pchar.questTemp.Mtraxx.Mahogany) < 200) 
				{
					link.l1 = "ふむ……";
					link.l1.go = "ignasio_15_1";
				}
				else
				{
					link.l1 = "どういうわけか銀は無駄になっちまったが、赤木は少し手に入ったぜ。分けようじゃねえか。";
					link.l1.go = "ignasio_15_11";
				}
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 300 && sti(pchar.questTemp.Mtraxx.Silver) > 100)
			{
				dialog.text = "ふむ……これはしょぼいな。もっとあると思ってたぜ。";
				link.l1 = "手に入れたものはこれだけだ。";
				link.l1.go = "ignasio_15_2";
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 700 && sti(pchar.questTemp.Mtraxx.Silver) > 300)
			{
				dialog.text = "悪くないな、悪くない。だが、もっとあると思ってたぜ。";
				link.l1 = "手に入れたものはこれだけだ。";
				link.l1.go = "ignasio_15_3";
				break;
			}
            dialog.text = "見事だな、旦那。これは素晴らしい獲物だ…";
			link.l1 = "これについては反論できねえな、船長。";
			link.l1.go = "ignasio_15_4";
		break;
		
		case "ignasio_15_1":
			dialog.text = "どうやらお前、頭が相当やられてるみたいだな。俺たちは行くぜ！野郎ども！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_11":
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
			dialog.text = "せめてこれで何かは手に入ったな……野郎ども！行くぞ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_2":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "たいしたもんだな。ここでお互い別々の道を行こうぜ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_3":
            RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "まあ、何とかなったな。じゃあ、ここでお別れだ。それにしても、結局うまくいったじゃねえか、へっ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_4":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "とても儲かる取引だったな。たぶん、これが最後の商売じゃねえだろう、船長！";
			link.l1 = "もっと太った商人を見つけたら呼んでくれよ、へへっ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_boarding":
			PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_04.wav");
            dialog.text = "これは偶然じゃないんだろうな、船長？";
			link.l1 = "見抜けなかったら、お前は賢くねえってことだ。仕組んだ分の借りがあるぜ。何の話かわかってるだろう。\nそれに、俺の仲間ジャン・ピカードを罠にかけた分も借りがある。お前の企みのせいで、 あいつはプランテーションに売られちまった……\nイグナシオも失ったな。お前を絞首刑にするつもりだが、罰を軽くする方法はあるぜ……";
			link.l1.go = "ignasio_boarding_1";
		break;
		
		case "ignasio_boarding_1":
            dialog.text = "俺は考えちまうぜ――どうすりゃお前に同情してもらえるんだ？";
			link.l1 = "情報が必要だ。お前を俺の貨物室に連れていくぜ、そこでハバナでの商売について話を聞かせてもらおう…";
			link.l1.go = "ignasio_boarding_2";
		break;
		
		case "ignasio_boarding_2":
            dialog.text = RandSwear()+" こんなことになるなんて思わなかったぜ！\n考えるんじゃねえぞ。\nバルバゾンにはすぐに俺の裏切りがバレちまう。\nあいつを裏切った奴がどうなるか、知らない方が身のためだ。\n俺は見たんだ。";
			link.l1 = "「じゃあ、絞首刑のほうがマシってことか？」";
			link.l1.go = "ignasio_boarding_3";
		break;
		
		case "ignasio_boarding_3":
            dialog.text = "戦って死んだほうがましだぜ！";
			link.l1 = "...";
			link.l1.go = "ignasio_boarding_4";
		break;
		
		case "ignasio_boarding_4":
            DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "spy_sailor":
            dialog.text = "船長！船長！急いでくれ！スペインの軍艦隊が俺たちを追ってきてるぞ！";
			link.l1 = RandSwear()+"こうなると思ってたぜ…ピカードにも同じことが起きたんだ。外にあいつらがどれだけいたか見たか？";
			link.l1.go = "spy_sailor_1";
		break;
		
		case "spy_sailor_1":
            dialog.text = "はい、船長。三隻です。旗艦はガレオンで、俺が今まで見た中で一番でかい船ですし、しかも速いです。 残りの二隻はコルベットとシーベックです。";
			link.l1 = "全員乗り込め。まだ逃げられるかもしれねえぞ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioOurEscape");
		break;
		
		// индей-кариб в гроте Порто-Белло
		case "grot_canib":
            dialog.text = "ハヤ！くそったれヤラナウイめ、俺たちの森に入りやがって！殺せ！ハヤ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekGrotFight");
		break;
		
		// бандит у пещеры Панамы
		case "cave_bandit":
            dialog.text = "おい！てめえ、ここで何してやがる！？あ、ああ、人の物を盗もうってのか？こりゃもう終わりだな！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekCaveFight");
		break;
		
		case "carpenter":
            dialog.text = "おい！みんな、その場で止まれ！さもないと、ぶどう弾でまとめてぶっ飛ばすぞ！ "+RandSwear()+"";
			link.l1 = "今はどこにも行かねえよ。だがな、相棒――お前が一発で俺たち全員を倒せるわけがねえ。お前が銃をリロードしてる間に、何人かはお前をバラバラにしてやるぜ。 今ここで話し合った方がいいんじゃねえか。\n";
			link.l1.go = "carpenter_1";
			locCameraFromToPos(-71.57, 14.57, -130.20, true, -63.78, 11.36, -125.50);
		break;
		
		case "carpenter_1":
            dialog.text = "ここを仕切ってるのはお前か？答えろ！";
			link.l1 = "俺が船長だ "+GetFullName(pchar)+"。それに、ここを離れている間はレッドウルフの副官を務めているのはあんたで間違いないか？";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
            dialog.text = "ここで何してるんだ、船長 "+GetFullName(pchar)+"「？ここでは客なんざ歓迎しねえぞ！」";
			link.l1 = "名前は何だ？誰と話しているのか知りたいんだ。";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
            dialog.text = "名はロドガー・ヤンセンだ。";
			link.l1 = "お前ら、ここで何も分かっちゃいねえようだな。もう船長はいねえし、コルベットも消えちまった。『フレイヤ』 はイスパニョーラの近くでスペイン野郎に地獄へ送られたんだ。乗組員も一人残らず殺された……";
			link.l1.go = "carpenter_4";
		break;
		
		case "carpenter_4":
            dialog.text = RandSwear()+" ウルフリック……ああああああッ！！！……だが、どうやってお前が本当のことを言ってるってわかるんだ？";
			link.l1 = "元船長の航海日誌を手に入れたぜ！フレイヤ号の残骸からいくつか物も拾った。日誌のおかげでこの島と……お前の宝の山を見つけたんだ。";
			link.l1.go = "carpenter_5";
		break;
		
		case "carpenter_5":
            dialog.text = "へっ！まだ答えてもらってねえぜ。なんでこんな未知の土地に来てるんだ？";
			link.l1 = "嘘はつかねえぜ、相棒。レッドウルフはかなりの財宝を持っていたって話だ。その宝を探しに来たんだよ、 奴の船からは何も見つからなかったからな。その財宝は善い人間のものになるべきだと思ってる。 ウルフリックにはもう必要ねえだろうしな。";
			link.l1.go = "carpenter_6";
		break;
		
		case "carpenter_6":
            dialog.text = "はっ！相棒、がっかりさせるが、俺もクルーの誰もウルフの財宝なんて見たことねえよ。 あいつに聞くのは危なすぎたんだ。";
			link.l1 = "それならお前の村で奴らを探すべきだな。銃を下ろす気はあるか、それとも俺が村に突入した方がいいか？ お前に勝ち目はねえぞ、ロドガー。必要なら銃と仲間をもっと連れてくるからな。";
			link.l1.go = "carpenter_7";
		break;
		
		case "carpenter_7":
            dialog.text = "死ぬ前に、てめえら野郎どもをたっぷり道連れにして地獄へ送ってやるぜ！お前もな！";
			link.l1 = "本当にそう思うのか？お前たちには船長もいないし、船もない。助けに来る者もいねえ。俺がただ立ち去ったとしても、 お前ら全員すぐに飢え死にするだけだぜ！";
			link.l1.go = "carpenter_8";
		break;
		
		case "carpenter_8":
            dialog.text = "ふむ……何か提案はあるか？";
			link.l1 = "ああ、そうだ。銃から離れて、部下どもを大人しくさせろ。俺はお前にも部下にも危害は加えねえと誓う。 望むなら俺の船の仲間になってもいいし、嫌なら文明のある場所まで連れていってやる。";
			link.l1.go = "carpenter_9";
		break;
		
		case "carpenter_9":
            dialog.text = "「自分の部下たちの前で、はっきり大声で誓え！」";
			link.l1 = "誓うぜ！俺の言葉だ。お前と部下たちには危害を加えねえ。";
			link.l1.go = "carpenter_10";
		break;
		
		case "carpenter_10":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_11";
			LAi_SetActorType(npchar);
			LAi_ActorDialog(npchar, pchar, "", -1, 0);
			for (i=1; i<=2; i++) // 
			{
				sld = CharacterFromID("Islamona_fort_pirate_"+i);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "carpenter_11":
            dialog.text = "約束を守ってくれるといいな、船長。";
			link.l1 = "いつもそうしてるぜ。お前たちはあと何人残ってるんだ？";
			link.l1.go = "carpenter_12";
		break;
		
		case "carpenter_12":
            dialog.text = "俺たち三人だけだ。他の連中はお前を襲おうとしてジャングルで死んじまった。やめろって言ったのによ、 誰も聞きやしなかったんだ……";
			link.l1 = "なるほど……";
			link.l1.go = "carpenter_13";
		break;
		
		case "carpenter_13":
            dialog.text = "食糧が尽きかけていた。俺たちはオウム狩りを始めた。『フレイヤ』号はあまりにも長く戻ってこなかった。 俺たちの疑念は的中したんだ。";
			link.l1 = "宝探しに行く決心をして本当によかったぜ。どこに奴は宝を隠したと思う？";
			link.l1.go = "carpenter_14";
		break;
		
		case "carpenter_14":
            dialog.text = "もう言っただろう、誰もあいつらを見たことはねえんだ。ウルフリックは自分の取り分を大事にして、 絶対に無駄にしなかった。俺たちには公平だったが、 あいつの隠し場所を探そうとした奴はみんな行方不明になっちまった。村の中を探したいなら、好きにしていいぜ。";
			link.l1 = "それが俺の考えだ。レッドウルフの家はどこだ？";
			link.l1.go = "carpenter_15";
		break;
		
		case "carpenter_15":
            dialog.text = "ここにある唯一の二階建ての建物だ。";
			link.l1 = "よし。ところで、お前の職業は何だ？";
			link.l1.go = "carpenter_16";
		break;
		
		case "carpenter_16":
			worldMap.labels.islamona.icon = 5;
			worldMap.labels.islamona.text = GetIslandNameByID("IslaMona");
            dialog.text = "俺は大工で、この二人は俺の助手だ。前は『フレイヤ』の修理やカリンをやってたんだ。 お前さんの船員として役に立てるぜ。";
			link.l1 = "なるほど。よし、参加を認めよう。詳しい話は後でだ。入口からこの銃を取ってこい。\nそれからロドガー、俺が隠し場所を探している間は村を出るなよ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekInFort");
		break;
		
		case "carpenter_17":
            dialog.text = "ご命令は、船長？";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
			{
				link.l1 = "ああ、あんたの船長の財宝は見つけたぜ。やつはうまく隠してたが、俺のほうが一枚上手だったってわけだ！";
				link.l1.go = "carpenter_18";
				break;
			}
			// Jason Исла Мона -->
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "start")
			{
				link.l1 = "ロドガー、どう思う？この基地で他にできることはあるか？";
				link.l1.go = "IslaMona";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "get_tools")
			{
				link.l1 = "ロドガー、道具を持ってきたぜ。もうお前のところに届けられているはずだ。";
				link.l1.go = "IslaMona_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "himenes")
			{
				link.l1 = "ようこそ！こちらはロドリゴ・ヒメネス、カディス出身の小規模ながらも非常に勤勉な共同体のリーダーだ。\nヒメネス旦那は親切にも我々の土地に一時的に滞在し、建設を手伝ってくれることに同意してくれた。";
				link.l1.go = "IslaMona_12";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "nextday")
			{
				link.l1 = "ロドガー、元気か？俺に何かいい助言はあるか？";
				link.l1.go = "IslaMona_18";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "stalk")
			{
				link.l1 = "「ロドガー、頼みがあるんだ。」";
				link.l1.go = "IslaMona_20";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "dublon_wait" && PCharDublonsTotal() >=600)
			{
				link.l1 = "お前のためにドゥブロン金貨を持ってきたぜ、でも一気に酒で全部使っちまうなよ。";
				link.l1.go = "IslaMona_24";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "storage" && !CheckAttribute(pchar, "questTemp.IslaMona.Food") && IslaMona_CheckFood())
			{
				link.l1 = "ロドガー、倉庫を確認してくれ。薬と食糧を持ってきたぞ。";
				link.l1.go = "IslaMona_30";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "village")
			{
				link.l1 = "やあ、ロドガー、新しい居留地の様子はどうだ？";
				link.l1.go = "IslaMona_32";
				break;
			}
			if (!CheckAttribute(npchar, "quest.stalk")) // ремонт кораблей
			{
				link.l2 = "「ロドガー、俺の船は修理が必要だ。お前と部下たちは準備できてるか？」";
				link.l2.go = "repair";
			}
			link.l3 = "ロドガー、俺の船の一隻をここに置いていきたいんだ。";
			if (CheckAttribute(npchar, "portman.info")) link.l3.go = "shipstock";
			else link.l3.go = "shipstock_info";
			if (CheckAttribute(npchar, "portman") && sti(npchar.portman > 0))
			{
				link.l4 = "ロドガー、俺の船の一隻を取り戻したいんだ。";
				link.l4.go = "shipstockreturn";
			}
			if (!CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "見てくれ、倉庫として使える空き家はあるか？";
				link.l5.go = "storadge";
			}
			if (CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "ロドガー、倉庫を見せてくれ。";
				link.l5.go = "storadge_3";
			}
			if (CheckAttribute(npchar, "crew"))
			{
				link.l6 = "「ロドガー、島に一部の仲間を残しておきたいんだ。」";
				link.l6.go = "crew";
			}
			if (CheckAttribute(npchar, "crew") && sti(npchar.crew.qty) > 0)
			{
				link.l7 = "ロドガー、俺は自分の船員たちを連れてもう一度海に出たいんだ。";
				link.l7.go = "crew_3";
			}// <-- Исла Мона
			link.l99 = "まだ何もない……";
			link.l99.go = "carpenter_exit";
		break;
		
		case "Crew":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchHireCrew();
		break;
		
		case "carpenter_exit":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
		break;
		
		case "carpenter_18":
            dialog.text = "おめでとうございます、船長。次はどうしますか？出発しますか？";
			link.l1 = "ここには長くいるのか？";
			link.l1.go = "carpenter_19";
		break;
		
		case "carpenter_19":
            dialog.text = "あまりにも長すぎた。ウルフリックにここを任されてからもう一年になる。";
			link.l1 = "この秘密基地は無駄にするにはあまりにも価値があると俺は判断した。今やこの村は俺のものだ。 お前と部下たちをここに残してやってもいいぜ、望むならな。ラム酒、食料、薬――全部お前たちのものだ。";
			link.l1.go = "carpenter_20";
		break;
		
		case "carpenter_20":
            dialog.text = "それは素晴らしいことだぜ、船長。俺はこの浜、この島での暮らしにも慣れてきたんだ。";
			link.l1 = "素晴らしい。ところで、その島の名前は何だ？";
			link.l1.go = "carpenter_21";
		break;
		
		case "carpenter_21":
            dialog.text = "イスラ・モナ。";
			link.l1 = "イスラ・モナ……いつかここにもっと家や建物を建てることになるかもしれねえ……だが、それはまた後の話だ。今のところ、お前はここで同じ役目を続けてもらうが、新しい船長の下でな。";
			link.l1.go = "carpenter_22";
		break;
		
		case "carpenter_22":
            dialog.text = "取引成立だ。自分の身はしっかり守ってくれよ、船長。それと、俺たちへの食料の補給も忘れるなよ。";
			link.l1 = "ああ、ロドガー。幸運を祈るぜ、俺はラ・ベガへ出航しなきゃならねえ。";
			link.l1.go = "carpenter_exit";
			npchar.portman = 0;
			AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;
		//------------------------------------------------------------ Исла Мона ------------------------------------
		case "IslaMona":
			sTemp = "";
			if (GetCharacterIndex("Mirabella") != -1) sTemp = ", not accounting for your woman";
            dialog.text = "難しいな、船長。亡くなったウルフリックはここに二十数人以上を残したことはなかった。 今は俺たち三人しかいねえんだ。"+sTemp+"……俺たちにできることはあまりないな。";
			link.l1 = "「つまり、もっと人が住めば、ここを本格的な入植地にできるってことか？」";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
            dialog.text = "島は小さいから植民地を作るのは無理だが、集落なら十分可能だぜ！魚を獲ったり、鳥やヤギを狩ったり、 果物を集めたりできる。自給自足はできるが、これで金持ちにはなれねえな。\nだが一つだけよく分からねえことがあるんだ、船長。なんでこんなものが必要なんだ？";
			link.l1 = "ここは俺の家であり、俺の土地、そして俺の仲間たちだ。\nもし俺が奴らを守らなければ、俺は一体何になるっていうんだ？";
			link.l1.go = "IslaMona_2_1";
			link.l2 = "俺は価値のある商売に金を投資したいんだ。";
			link.l2.go = "IslaMona_2_2";
			link.l3 = "この小さな島はこの地域の中心に位置している。ここを本格的かつ秘密の軍事基地にするのが賢明だろう。";
			link.l3.go = "IslaMona_2_3";
			link.l4 = "お前のことが心配だぜ、ロドガー。お前ら全員、もう完全に手がつけられなくなっちまったじゃねえか。";
			link.l4.go = "IslaMona_2_4";
		break;
		
		case "IslaMona_2_1":
            dialog.text = "お前は変わった奴だな。まあ、いいさ。少なくとも暇つぶしにはなるだろう…";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Defence", 2000);//защита
		break;
		
		case "IslaMona_2_2":
            dialog.text = "お前は変わった奴だな。まあ、いいさ。少なくとも暇つぶしにはなりそうだ……";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Commerce", 1500);//торговля
		break;
		
		case "IslaMona_2_3":
            dialog.text = "お前は変わった奴だな。まあ、いいさ。少なくとも暇つぶしにはなるだろう…";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddComplexSelfExpToScill(250, 250, 250, 250);//оружие
		break;
		
		case "IslaMona_2_4":
            dialog.text = "お前は変わった奴だな。まあ、気にしねえ。少なくとも暇つぶしにはなりそうだ……";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);//авторитет
		break;
		
		case "IslaMona_3":
            dialog.text = "まずは、とても特別な人物たちを探さなきゃならない。この荒野に移り住み、 外の世界から完全に隔絶されたまま何年もここで暮らし、働くことを納得してくれる者たちだ。 そういう並外れた人間を見つける必要があるんだ。できれば一人じゃなく、何人か。そもそも、 今のところは乗組員にここに定住しろと命じるわけにもいかないしな。植民者たちだって、 築き上げた家や安定した仕事を捨てたがらないだろう。それに、流れ者や厄介者なんて俺たちには絶対に必要ない。\nさらに、この島を巡る秘密の問題は常につきまとう。誰かに話せば、 すぐにでも調査しに来る連中が現れる危険があるんだ。";
			link.l1 = "わかった、何か提案はあるか？";
			link.l1.go = "IslaMona_4";
		break;
		
		case "IslaMona_4":
            dialog.text = "いいえ、船長。俺はここにあまりにも長く居すぎて、すっかり文明的な生活から離れてしまったんだ。";
			link.l1 = "素晴らしい、それは助かるぜ！";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
            dialog.text = "俺は木を相手にしてるんであって、人間相手じゃねえんだ。だからこそ、すげえ満足してるんだよ、ははは！\nそれとだな、人手だけじゃなくて、ここには上等な鍛冶と建築用の道具一式も持ってきてもらわなきゃならねえ。 ああいうのは古いヨーロッパでしか作ってねえから、結構な金がかかるぜ。大きな造船所の親方にでも聞いてみな。";
			link.l1 = "すべて理解した。まとめると、もしこの基地をもっと大きくしたいなら、 もっと入植者と道具をここに連れてくればいいんだな？";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            dialog.text = "その通りだ！";
			link.l1 = "できることをやってみるぜ。";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "1");
			pchar.questTemp.IslaMona = "tools";
			IslaMona_SelectShipyard();
		break;
		
		case "IslaMona_8":
            dialog.text = "あいよ、船長！最高の装備だ、これで植民地を築く準備は万端だぜ！高くついたのか？";
			link.l1 = "大金をはたいたんだ、これが価値あるものであってほしいぜ！";
			link.l1.go = "IslaMona_9_1";
			link.l2 = "数年前なら、すごく高いと言っただろうな。\nでも今は……もう分からねえよ。";
			link.l2.go = "IslaMona_9_2";
		break;
		
		case "IslaMona_9_1":
			AddCharacterExpToSkill(pchar, "Commerce", 600);
            dialog.text = "お前はもう持っているもので満足できなかったんだな？まあ、どのみち出費は増える一方だぜ。 入植者たちとの問題は片付いたのか？";
			link.l1 = "いや、ロドガー。まだ奴らをどこで見つければいいか分かっていないんだ。そもそも、 この海域で入植地を作る主権なんて俺にはないからな。";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_9_2":
			AddCharacterExpToSkill(pchar, "Leadership", 300);
            dialog.text = "お前はもう持っていたもので満足できなかったんだな？まあ、どのみち出費は増える一方だと思っておけ。 入植者たちとの問題は片付いたのか？";
			link.l1 = "いや、ロドガー。まだ奴らをどこで見つければいいのか分かっていないんだ。結局のところ、 俺にはこの海域で入植地を作る主権なんてないからな。";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_10":
            dialog.text = "この海域じゃ、船長、毎日が混沌だぜ。人々の噂に耳を傾けてみな、思わぬチャンスが見つかるかもしれねえ。 道具の方は今のところ俺が預かっておくぜ。";
			link.l1 = "よし、そういう情報には気をつけておくぜ。";
			link.l1.go = "IslaMona_11";
		break;
		
		case "IslaMona_11":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "3");
			RemoveItems(pchar, "islamona_toolbox", 1);
			pchar.questTemp.IslaMona = "rumours";
			AddRumor("They say some criminals have been cast out to one of the uninhabited islands! It seems they're such fierce monsters that even the executioner and the holy fathers wouldn't want to deal with them! But why do they always bring such people to us?!", 1, "all", "none", 0, (2022 - STARTGAME_YEAR) * 365, "IslaMona_TerksRumour", "none");
		break;
		
		case "IslaMona_12":
            dialog.text = "スペイン野郎だと？冗談だろう、船長。ル・フランソワから怠け者でも連れてくるのかと思ったが、 まさかこいつらとはな……";
			link.l1 = "";
			link.l1.go = "IslaMona_13";
		break;
		
		case "IslaMona_13":
            DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_14":
            dialog.text = "お前さん、ヨーロッパから来たのか？へへ、すぐにわかるぜ。心配すんな、そのうち慣れるさ。";
			link.l1 = "ヒメネス、お前はしばらく俺の家に滞在してくれ。地下室があるし、十分なスペースもある。ロドガー、 道具も持ってきたし、入植者たちも連れてきた。次はどうする？";
			link.l1.go = "IslaMona_15";
		break;
		
		case "IslaMona_15":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_20";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_16":
            dialog.text = "明日また会おう、船長。これらの…入植者たちが財宝と一緒に落ち着いたら、一日後に話そう。";
			link.l1 = "よし、続きは明日にしよう。";
			link.l1.go = "IslaMona_17";
		break;
		
		case "IslaMona_17":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LAi_SetWarriorType(npchar);
			IslaMona_HimenesWait();
		break;
		
		case "IslaMona_18":
            dialog.text = "船長、スペイン人に話しかけてくれ。もうすっかり仕事に取りかかっているぞ。";
			link.l1 = "了解だ、俺が引き受けるぜ。";
			link.l1.go = "IslaMona_19";
			link.l2 = "何かあったのか？";
			link.l2.go = "IslaMona_18_1";
		break;
		
		case "IslaMona_18_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            dialog.text = "船長、ここで仲間たちと何年もぶらぶらしてきたんだ。だが今や、スペイン野郎どもの騒がしい動きが癪に障るぜ。";
			link.l1 = "争いはなしだ！それから、お前も部下もあいつらの女の方を見ることすら許さん！少なくとも、今はな……もし雰囲気が怪しくなったら、スキッフに乗って数日間……釣りでもしてこい。";
			link.l1.go = "IslaMona_18_2";
		break;
		
		case "IslaMona_18_2":
            dialog.text = "「あいよ、旦那！」";
			link.l1 = "完璧だ。よし、あいつが何をしているか見に行ってくるぜ。";
			link.l1.go = "IslaMona_19";
		break;
		
		case "IslaMona_19":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			IslaMona_SetHimenesNextDay();
		break;
		
		case "IslaMona_20":
            dialog.text = "もう知ってるぜ、船長。スペイン野郎は俺たちに島を探検させたいのか？ 地図持って岩の上をバカみたいに飛び回れってのか？";
			link.l1 = "「その通りだ、ロドガー。」";
			link.l1.go = "IslaMona_21";
		break;
		
		case "IslaMona_21":
            dialog.text = "六百ドゥブロンでやってやるぜ。";
			link.l1 = "気でも狂ったのか？この土地のクモか毒ヘビにでも噛まれたのか？無人島で金貨の詰まった箱をどうするつもりだ？ 埋めるのか？";
			link.l1.go = "IslaMona_22";
		break;
		
		case "IslaMona_22":
            dialog.text = "さあ、船長。いつか俺たちはこの場所を離れるだろうが、金がなきゃ広い世界で誰が俺たちを必要とする？もちろん、 ちょっとした隠し財産はあるが、とても足りねえよ。ウルフリックは最後の冒険の分の借金を、 俺や仲間たちにまだ払ってねえんだ。\n何ヶ月も浜辺でだらだらして、半年に一度お前の艦隊の世話をするのはまあいいさ。でもな、毎日陸で必死に働くなんて、 呪われたバッカニアみてえなもんだ――まるで別の話だぜ！それが仕事ってもんで、仕事には報酬がある。お前はちゃんと船員に給料払ってるよな、船長？";
			link.l1 = "筋は通ってるな。600ドゥブロン用意してやるぜ。まさか前払いを期待してるんじゃねえだろうな？";
			link.l1.go = "IslaMona_23";
			link.l2 = "もう一つ提案がある。お前は陸で働くんだ、海で船のフジツボをこすり落とすんじゃなくてな。今まさに、 そういう仕事が切実に必要なんだぜ。";
			link.l2.go = "IslaMona_25";
		break;
		
		case "IslaMona_23":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddQuestRecord("IslaMona", "7");
            dialog.text = "船長、俺は今すぐにでも始められるぜ。でもな、俺の連中は手にドゥブロン銀貨を握ればもっと張り切るだろう。 約束する、この島で未踏の土地は一つも残さねえよ。";
			if (PCharDublonsTotal() >= 600)
			{
				link.l1 = "わかった。ほら、金だ。だが、すぐに酒で使い果たすんじゃねえぞ。";
				link.l1.go = "IslaMona_24";
			}
			else
			{
				link.l1 = "わかった、お前のドゥブロンを持ってきてやる。";
				link.l1.go = "IslaMona_24_1";
			}
		break;
		
		case "IslaMona_24_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona = "dublon_wait";
		break;
		
		case "IslaMona_24":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You gave away 600 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "ははは！確かにその通りだな、船長！ああ、それともう一つ言い忘れるところだった。 今じゃここに結構な人数が住んでるが、みんな食べるものが必要だ。あの女たちを見ただろ？ あいつらは生き延びたり自給自足したりするのに慣れてねえ。役には立たねえさ。";
			link.l1 = "まさか、またお前のためにバッカニアどもを探してこいなんて言わねえだろうな。";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_25":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			pchar.questTemp.IslaMona.Nodublon = "true"; // дублоны не заплатил
			AddQuestRecord("IslaMona", "8");
            dialog.text = "了解だぜ、船長！陸での作業は準備万端だ！\nああ、それともう一つ、言い忘れるところだった。今じゃここに結構な人数が住んでるが、みんな食べ物が必要なんだ。\nあの女たちを見たか？あいつらは自分で生き延びたり、土地のものだけで暮らすのに慣れてねえ。役には立たねえぜ。";
			link.l1 = "まさか、お前のためにバッカニアどもまで探しに行かなきゃならねえのかよ……";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_26":
            dialog.text = "いや、なぜ俺たちがそんなことをするんだ？俺たちは奴らの中で最も有能な者を訓練し、仕事を与えるつもりだ。だが、 その素晴らしい時が来るまでは、お前が食料を用意しなきゃならねえ。船の備蓄を二千セットほどで十分だ。 それと将来のために薬品を百ポンド分。全部、島の倉庫に船から降ろしておけ。\n";
			link.l1 = "了解だ。偵察任務にはどれくらい時間が必要なんだ？";
			link.l1.go = "IslaMona_27";
		break;
		
		case "IslaMona_27":
            dialog.text = "二、三日で終わるぜ。もう面白いものをいくつか見つけたんだ。";
			link.l1 = "「すごい！」";
			link.l1.go = "IslaMona_28";
		break;
		
		case "IslaMona_28":
            dialog.text = "終わり次第、あの笑っているスペイン野郎のところへ直行しろ。 あの狂人には俺たちの仕事から何か結論を出してもらわねえとな。";
			link.l1 = "もうすでにほとんど友達みたいだな。じゃあ、三日後にあいつのところへ行くとしよう。\nさて、仕事に乾杯だ。俺たち全員の幸運を祈るぜ！";
			link.l1.go = "IslaMona_29";
		break;
		
		case "IslaMona_29":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.quest.stalk = "true";
			AddQuestRecord("IslaMona", "9");
			pchar.questTemp.IslaMona = "storage";
			SetFunctionTimerCondition("IslaMona_StalkFin", 0, 0, 3, false);
		break;
		
		case "IslaMona_30":
            dialog.text = "うわぁ、びっくりだぜ！ありがとう、船長。これで女たちをこの荒くれた生活に備えさせる時間ができたな。";
			link.l1 = "奴らを海賊にしちまわないように気をつけてくれよ！ありがとう、Rodgar";
			link.l1.go = "IslaMona_31";
		break;
		
		case "IslaMona_31":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona.Food = "true";
			AddQuestRecord("IslaMona", "10");
			IslaMona_RemoveFood();
		break;
		
		case "IslaMona_32":
            dialog.text = "船長！正直に言うと、ここで暮らすのがだんだん居心地悪くなってきたんだ。";
			link.l1 = "どうしてだ、ロドガー？貧乏と破滅の魅力が恋しいのか？";
			link.l1.go = "IslaMona_33";
		break;
		
		case "IslaMona_33":
            dialog.text = "そうとも言えるな。今や文明がこんな所にまで押し寄せてきてる。俺みたいな人間の居場所なんて、 もうどこにもねえんだ。";
			link.l1 = "ジャボと杖でも買ってこいよ。そうすりゃ、すっかり馴染めるぜ。";
			link.l1.go = "IslaMona_34";
		break;
		
		case "IslaMona_34":
            dialog.text = "むしろ、お前のスペイン人のところへ行って偵察の結果について話そうぜ。もう一つイカれた考えがあるんだ……";
			link.l1 = "たった今あいつと話したばかりだ！よし、行こうぜ、ロドガー。";
			link.l1.go = "IslaMona_37";
			link.l2 = "「彼と一緒に働くのはどうだ？」";
			link.l2.go = "IslaMona_35";
		break;
		
		case "IslaMona_35":
            dialog.text = "高い教養と勤勉さを持った連中だぜ！それにヒメネスは本当に名人だ。昔なら、 こういう奴らはかなりの金貨で売れたもんさ。しかも、あいつらの女も美人ぞろいでな……";
			link.l1 = "俺はもう聞きたくねえぞ、ロドガー！さあ、あのご主人様に話をしに行こうぜ";
			link.l1.go = "IslaMona_36_1";
			link.l2 = "奴らが仕事をこなせねえなら、売り飛ばしてやるさ。\nだが女たちは残しておけ、ははは！\n親方のところへ行こうぜ… ";
			link.l2.go = "IslaMona_36_2";
		break;
		
		case "IslaMona_36_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
            dialog.text = "本気かよ、船長？冗談だったんだ、行こうぜ…";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_36_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
            dialog.text = "お前が俺を支えてくれるってわかってたぜ、船長！さあ、行こう…";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_37":
            DialogExit();
			DoQuestReloadToLocation("IslaMona_TwoFloorHouse", "goto", "goto5", "IslaMona_HouseDialog");
		break;
		
		case "IslaMona_38":
            dialog.text = "「笑ってねえぞ、船長…」";
			link.l1 = "";
			link.l1.go = "IslaMona_39";
		break;
		
		case "IslaMona_39":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_40":
            dialog.text = "それもだよ、船長。後で話そう……";
			link.l1 = "";
			link.l1.go = "IslaMona_41";
		break;
		
		case "IslaMona_41":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_52";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_42":
            dialog.text = "その旦那の言うことも一理あるぜ、船長。俺たちの誰もジャングルで骨を折るつもりはねえ。仕事は汚いが、 他にやりようがなけりゃ、ここは結局海賊の巣になるしかねえんだ。";
			link.l1 = "";
			link.l1.go = "IslaMona_43";
		break;
		
		case "IslaMona_43":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_58";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_44":
            dialog.text = "船長、工場を建てる時は奴隷たちに護衛が必要だぜ。俺の仲間がその役目を引き受ける。 中には雷神トールみたいに撃つ奴もいるんだ。狩猟用スコープほど仕事のやる気を出させるものはねえ。 銃はもう一丁あるが、あともう一丁必要だ。どんなマスケットでも構わねえ。";
			link.l1 = "";
			link.l1.go = "IslaMona_45";
		break;
		
		case "IslaMona_45":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_60";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_46":
            dialog.text = "そして俺の部下にも同じだけの金貨と、さらに上等なラム酒をもう12本必要だぜ。";
			link.l1 = "一度にどれくらいの木材を用意できるんだ？それと、なぜ金が必要なんだ？";
			link.l1.go = "IslaMona_47";
		break;
		
		case "IslaMona_47":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_62";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_48":
            dialog.text = "まず第一に、娯楽のない人生なんて意味がねえし、そのうち敬虔なカトリックの連中だって、へへ、発狂しちまうぜ。\nそれにだ、島に酒場があれば、乗組員の一部をここに待機させておくこともできる。\n見てみろ、浜辺の小屋で一年も野蛮人みてえな暮らしをタダでやらせるなんて、そう簡単に納得させられるもんじゃねえ。 \nだが、近くに酒場や熱い飯、音楽や娯楽のある集落があれば……陸に上がった水夫に他に何が必要だってんだ？";
			link.l1 = "娼婦か？";
			link.l1.go = "IslaMona_49";
			link.l2 = "飲むか？";
			link.l2.go = "IslaMona_49";
		break;
		
		case "IslaMona_49":
            dialog.text = "お前の言う通りだが、問題は一つずつ解決しよう。まずはお前の家を建て直すんだ…";
			link.l1 = "...";
			link.l1.go = "IslaMona_50";
		break;
		
		case "IslaMona_50":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_65";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_51":
            dialog.text = "そんなこと、あいつは考えもしなかったぜ、船長。";
			link.l1 = "ありがとう、ロドガー。これでこの小さな湾でさらに多くの船にサービスできるようになるってことだな？";
			link.l1.go = "IslaMona_52";
		break;
		
		case "IslaMona_52":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_harbour_4";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_53":
            dialog.text = "ごきげんよう、船長！仕事の話をしに来たのか？";
			link.l1 = "いや、全然そんなことはない。\nただ、お前の北国らしい顔立ちが懐かしくなっただけだ。";
			link.l1.go = "IslaMona_54";
		break;
		
		case "IslaMona_54":
            dialog.text = "歩きましょうか？あなたの工場を案内します。";
			link.l1 = "案内してくれ。";
			link.l1.go = "IslaMona_55";
		break;
		
		case "IslaMona_55":
            DialogExit();
			IslaMona_PlantationGo();
		break;
		
		case "IslaMona_56":
            dialog.text = "ひっく！船長、俺たち祝ってるぜ！";
			link.l1 = "「ロドガー！ロドリゴ！くそっ！」";
			link.l1.go = "IslaMona_57";
		break;
		
		case "IslaMona_57":
            dialog.text = "どうしたんだ、せ、船長？壁の色が気に入らねえのか？";
			link.l1 = "今になってやっと気づいたぜ、お前ら二人、同じ名前じゃねえか！ハハハ！スペイン野郎と海賊が、 同じ名前で無人島に酒場を建てて、まるでインディオの神々がみんなを食い尽くして夜明けに世界が終わるみてえに、 一緒に飲んでやがる！ハハハ！俺も混ぜてくれよ！";
			link.l1.go = "IslaMona_58";
		break;
		
		case "IslaMona_58":
            dialog.text = "ハハハ！まったくだぜ！乾杯！";
			link.l1 = "乾杯！";
			link.l1.go = "IslaMona_59";
		break;
		
		case "IslaMona_59":
            DialogExit();
			npchar.dialog.currentnode = "IslaMona_60";
			IslaMona_ReloadTavern();
		break;
		
		case "IslaMona_60":
            dialog.text = "飲むかい、船長？";
			link.l1 = "ロドガー、お前は酒場の主人にでもなるつもりか？";
			link.l1.go = "IslaMona_61";
		break;
		
		case "IslaMona_61":
            dialog.text = "一時的にな！スペイン人どもは特に、海賊が酒場を仕切ってるのを気に入ってるぜ――やつらにとっちゃ本物の異国情緒と冒険なんだとよ。だが、全体的にはここは居心地がいいぜ。 もしこの集落にお前の仲間を予備として残していきたいなら、俺に言ってくれ――手配してやる。";
			link.l1 = "でも、奴らはどこで暮らすんだ？";
			link.l1.go = "IslaMona_62";
		break;
		
		case "IslaMona_62":
            dialog.text = "簡単さ――浜辺に小屋を建てるんだ。そうすりゃ、連中は酒場から浜まで走り回ることになる。念のため言っておくが、 この島は三百人以上は収容できねえから、今後はそれを覚えておいてくれ。時々 ラムやワインを持ってきてくれって頼むこともあるから、船長、 あんたが前もって倉庫に品を用意しておいてくれると助かるぜ。";
			link.l1 = "覚えておくぜ。さて、相棒よ。スペイン野郎どもを楽しませて、ひと休みしな。だが頼むから、 村全体が燃えちまうほど飲みすぎるなよ――そんな光景、俺は見たくねえからな！\n";
			link.l1.go = "IslaMona_63";
		break;
		
		case "IslaMona_63":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload1", false);
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload3", false);
			npchar.crew = "true"; // можно оставлять матросов
			npchar.crew.qty = 0;
			pchar.questTemp.IslaMona.Tavern = "done"; // флаг - таверна построена и сдана
			// belamour обнулим матросов-->
			ref rTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
			rTown.Ship.crew.quantity = 0;
			rTown.Ship.crew.morale = 0;
			rTown.Ship.Crew.Exp.Sailors   = 0;
			rTown.Ship.Crew.Exp.Cannoners = 0;
			rTown.Ship.Crew.Exp.Soldiers  = 0;
			ChangeCrewExp(rTown, "Sailors", 0);  // приведение к 1-100
			ChangeCrewExp(rTown, "Cannoners", 0);
			ChangeCrewExp(rTown, "Soldiers", 0);
			
		break;
		
		case "IslaMona_64":
            dialog.text = "船長！会えて本当に嬉しいぜ！フレイヤに感謝だ、ちょうどいい時に来てくれたな！";
			link.l1 = "ああ、また厄介なことに巻き込まれちまったな。やあ、ロドリゴ！";
			link.l1.go = "IslaMona_65";
		break;
		
		case "IslaMona_65":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_13";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_66":
            dialog.text = "死者はいない。生き残ったスペイン人たちが最初にこちらへ来て、さらに来客が現れる可能性があると報告してくれた。 それで、ほとんどすべての食料と装備を現場から集落まで運ぶことができたんだ。奴隷たちの件は、 もちろんあまりうまくいかなかったがな。\n";
			link.l1 = "";
			link.l1.go = "IslaMona_67";
		break;
		
		case "IslaMona_67":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_68":
            dialog.text = "奴らが俺たちを引きずり出して、正面から襲いかかってきたらどうするんだ？";
			link.l1 = "じゃあ、銃なしでやるぞ。まるで閲兵みたいに一緒に門まで進んで、後ろからぶちかますんだ。 お前は門を押さえて援護しろ。それだけだ、幸運を祈るぜ！";
			link.l1.go = "IslaMona_69";
		break;
		
		case "IslaMona_69":
            DialogExit();
			AddQuestRecord("IslaMona", "21");
			pchar.quest.islamona_def_jungle1.win_condition.l1 = "locator";
			pchar.quest.islamona_def_jungle1.win_condition.l1.location = "IslaMona_jungle_01";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator_group = "encdetector";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator = "enc04";
			pchar.quest.islamona_def_jungle1.function = "IslaMona_DefSoldiersInJungle"; // встреча с французами
			LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_jungle_01")], true);//запретить драться
		break;
		
		case "IslaMona_70":
            dialog.text = "万歳、船長！";
			link.l1 = "同感だぜ！すごい爆発だったな、俺もぶっ倒れそうだったぜ。おい、お前ら、何を詰め込んだんだ？";
			link.l1.go = "IslaMona_71";
		break;
		
		case "IslaMona_71":
            dialog.text = "二重装填だ、船長。これで一発ぶっ放せば、あいつらももう戦う気が失せるはずだぜ！";
			link.l1 = "そんなに繊細に扱っていて、銃が暴発するんじゃないかと心配しなかったのか？";
			link.l1.go = "IslaMona_72";
		break;
		
		case "IslaMona_72":
            dialog.text = "俺にはウルフリックが残してくれた特別なお守りがある。故郷デンマークの思い出の品さ。\n酒場へ行かねえか、船長？今日はみんな疲れてるぜ。";
			link.l1 = "ああ、それはいいな。カードでもやろうぜ――お前の奇跡の護符を賭けてな。";
			link.l1.go = "IslaMona_73";
		break;
		
		case "IslaMona_73":
            dialog.text = "ははっ、今日のあんな神がかった演奏を見せられたら、船長、俺もその選択肢を考えちまうかもな！";
			link.l1 = "";
			link.l1.go = "IslaMona_74";
		break;
		
		case "IslaMona_74":
            DialogExit();
			sld = characterFromId("IM_fraofficer");
			sld.dialog.currentnode = "FraOfficer_18";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_75":
            dialog.text = "船長、聞こえたか？まだ耳鳴りがしてるぜ。あの悲しげな声は誰のものだ？";
			link.l1 = "それはな、ロドガー、まだ片付いてねえ問題だ。そいつを工場に連れて行って鎖につないでおけ、追加の指示を待て。";
			link.l1.go = "IslaMona_76";
		break;
		
		case "IslaMona_76":
            dialog.text = "あいよ、船長！";
			link.l1 = "";
			link.l1.go = "IslaMona_77";
		break;
		
		case "IslaMona_77":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			sld = characterFromId("IM_fraofficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			for(i=4; i<=7; i++)
			{
				sld = characterFromId("IM_fra_sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_78":
            dialog.text = "船長、囚人の件を解決しに来たのか？ここで見張りしてるのはもううんざりだぜ。";
			link.l1 = "奴を殺すしかねえな。危険がでかすぎる、他に手はねえ。さもなきゃ、フランス植民地には顔を出せねえぜ。";
			link.l1.go = "IslaMona_79";
			link.l2 = "あいつを逃がすわけにはいかねえ、さもなきゃフランス植民地じゃ顔を出せなくなる。 あいつを手錠につないで工場で働かせろ。殺すよりはマシだ。";
			link.l2.go = "IslaMona_80";
		break;
		
		case "IslaMona_79":
            dialog.text = "了解だ！さっさと片付けようぜ。どうぞ、船長。じゃあ、また明日な。";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
		break;
		
		case "IslaMona_80":
            dialog.text = "おいおい、驚いたぜ。お前は相当な悪知恵の持ち主だな。俺はお前を敵に回したくねえよ。さて、 まずはあいつに説明しなきゃならねえな。さあ、船長、頼んだぜ。じゃあ、また明日な。";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
			pchar.questTemp.IslaMona.Fraprisoner = "true";
		break;
		
		case "IslaMona_81":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "IslaMona_DefFraPrisonerFin", 10.0); /// идёт внутрь фактории - УСТАНОВИТЬ ЛОКАТОР
		break;
		
		case "IslaMona_82":
            dialog.text = "なんて惨殺だ！大砲を撃てなかったのは残念だが、奴らはお前の待ち伏せにまっすぐ突っ込んできた――見事な光景だったぜ！";
			link.l1 = "ああ、この地でたくさんの血を流してきた。しかし、どうやらこの世界で家を築くには他に道はないようだ。";
			link.l1.go = "IslaMona_83";
		break;
		
		case "IslaMona_83":
            dialog.text = "あまり気にするなよ、船長。運命そのものが奴らをイスラ・モナに導いたんだぜ。言っとくが、 運命ってのは本当に厄介なもんだぜ！";
			link.l1 = "運命か、それとも島か？";
			link.l1.go = "IslaMona_84";
		break;
		
		case "IslaMona_84":
            dialog.text = "両方とも自分の役割を果たした。";
			link.l1 = "ははっ！どちらも見事だな！よし、勇敢なヴァイキングよ。戦利品を集めて、こいつらの遺体を片付けろ。 ちゃんと弔って埋めてやれ。何しろ俺たちの仲間なんだからな……";
			link.l1.go = "IslaMona_85";
		break;
		
		case "IslaMona_85":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20a";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_86":
            dialog.text = "はい、船長。その通りだぜ！ロドリゴの言葉はあまりにも見事で、思わず涙が出そうになったよ。 聖職者たちがあいつの尻を杭に刺したがる理由もよく分かるってもんだ！";
			link.l1 = "";
			link.l1.go = "IslaMona_87";
			locCameraFromToPos(1.36, 1.32, 0.31, true, 3.44, 0.20, -0.50);
		break;
		
		case "IslaMona_87":
            DialogExit();
			if (GetCharacterIndex("Mirabella") != -1)
			{
				sld = characterFromId("Mirabella");
				sld.dialog.currentnode = "mirabelle_46";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && CheckPassengerInCharacter(pchar, "Mary"))
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
					{
						sld = characterFromId("Helena");
						sld.dialog.currentnode = "IslaMona_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
					else
					{
						sld = characterFromId("Himenes_companion_1");
						sld.dialog.currentnode = "island_man_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
				}
			}
		break;
		
		case "IslaMona_88":
            dialog.text = "ロドリゴ、そして俺はあの聖職者にブドワールでばったり出くわしちまったんだ…それに言わせてもらうが、サンティアゴで一番の店だぜ！";
			link.l1 = "聖職者がお好みなら、ここが一番だぜ。";
			link.l1.go = "IslaMona_89";
		break
		
		case "IslaMona_89":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_90":
            dialog.text = "ああ、あの悪党で異端者のロドリゴを本物の海賊に仕立て上げたんだぜ、まったく。";
			link.l1 = "ところで、教えてくれ、ロドガー。なぜスペイン人の海賊はこんなに少ないんだ？";
			link.l1.go = "IslaMona_91";
		break;
		
		case "IslaMona_91":
            dialog.text = "なぜそんなに少ないんだ？ああ、海賊船長のことか？いや、やつらはたくさんいるぜ。ただ、 ほとんどがセビリアのカサ・デ・コントラタシオンの下で活動してるんだ。\n軍の諜報部みたいなもんだが、なぜか「取引所」って呼ばれてるんだよな……";
			link.l1 = "";
			link.l1.go = "IslaMona_92";
		break;
		
		case "IslaMona_92":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_77";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_93":
            dialog.text = "ああ、まあ、やつらに伝言でも送って呼んでみればいいじゃねえか。みんな特許状を持ってるし、理想家でもあるんだぜ。 普通は仲間同士で盗みはしねえ、襲撃が失敗したときくらいさ、ははっ！プエルト・プリンシペにしか寄りつかねえし、 いつも牧師と揉めてるんだ。\n最近、ひときわ目立つやつがいてな……ディエゴ・デ・モントーヤだ。俺が最後にウルフリックと遠征に出たとき、やつの武勇伝をたくさん聞いたぜ。お前もな、 船長、やつと共通点があるんだ。でも同時に、全然違うところもある……まあ、何言ってんだ俺は。もう一杯やって、カードでもやろうぜ。";
			link.l1 = "お前、金を持ってねえだろう。まさかドゥブロン金貨で賭けてるんじゃねえだろうな？";
			link.l1.go = "IslaMona_94";
		break;
		
		case "IslaMona_94":
            dialog.text = "一人一ペソ賭けよう。二十までやるか？ヒメネス、お前もやるか？";
			link.l1 = "";
			link.l1.go = "IslaMona_95";
		break;
		
		case "IslaMona_95":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_79";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_96":
            dialog.text = "遊ぶかい、船長？";
			if (sti(pchar.money) >= 20)
			{
				link.l1 = "始めろ！";
				link.l1.go = "IslaMona_97";
			}
			link.l2 = "俺も遠慮しておくぜ、ロドガー。ペソがあろうがなかろうが、こうやって船を失う奴はいるもんだ。島ごとな。\nお前はここで楽しんでくれ、俺はもう少し周りを見てくるぜ。";
			link.l2.go = "IslaMona_98";
		break;
		
		case "IslaMona_97": // игра в карты
            DialogExit();
			pchar.questTemp.GoldenGirl.Game.IslaMona = "true"; // атрибут квестовой игры
			npchar.money = 20;
			pchar.questTemp.IslaMona.Money = sti(pchar.money);
			pchar.money = 20;
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1; // ставка
			LaunchCardsGame();
		break;
		
		case "IslaMona_98": // выход из-за стола
            DialogExit();
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_99":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "通れ！ふん、もうお前とは遊ばねえぞ！絶対イカサマしただろ、船長！イカサマ野郎をそのまま逃がすなんて許せねえよ！ ";
				link.l1 = "聞いてるぞ、Rodgar。";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "俺の勝ちだぜ、船長。でもな、手ぶらで帰すわけにはいかねえよ、ははっ！";
					link.l1 = "よし、てめえ、この野郎。これが俺への教訓だな……";
				}
				else
				{
					dialog.text = "俺の勝ちだぜ、船長。でも、あんたを手ぶらで帰すわけにはいかねえよ、ははっ！";
					link.l1 = "よし、てめえ、このことを教訓にするぜ……";
				}
			}
			link.l1.go = "IslaMona_100";
		break;
		
		case "IslaMona_100":
            dialog.text = "ああ、いいじゃねえか！お前さんのおかげで、俺も仲間も、狭苦しい船室や腐った水、 頭に破片が刺さる危険から解放されて、本当の人生を味わえるってもんだ。ほらよ。このお守りは、 遠いデンマークからウルフリックが持ってきて、俺に渡してくれたもんだ――俺があいつの地下室をあまり探らなくて済むようにな。もう俺には必要ねえが、お前さんには……おっと、きっと役に立つぜ。";
			link.l1 = "ありがとう、ロドガー。確かに役に立つ品だな。それに、美しい……";
			link.l1.go = "IslaMona_101_1";
			link.l2 = "取っておけ、ロドガー。お前がいなけりゃ、この場所は存在しなかったんだ。故郷を思い出す品として持っていてくれ。";
			link.l2.go = "IslaMona_101_2";
		break;
		
		case "IslaMona_101_1":
			GiveItem2Character(pchar, "talisman3");
			Log_Info("You received 'Thor's Hammer'");
			PlaySound("interface\important_item.wav");
            dialog.text = "楽しんでいただけて嬉しいです、船長。もう一杯いかがですか？";
			link.l1 = "お前らはここで休んでろ、俺がもう一度あたりを見てくるぜ。";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_101_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Fortune", 2000);
            dialog.text = "かしこまり！じゃあ、幸運の女神にも一杯やるとするか、はは！もう一杯どうだ？";
			link.l1 = "お前らはここにいろ、俺がもう一度辺りを見てくる。";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_102":
            DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			DeleteAttribute(pchar, "GenQuest.Cards");
			pchar.money = sti(pchar.money)+sti(pchar.questTemp.IslaMona.Money);
			DeleteAttribute(pchar, "questTemp.IslaMona.Money");
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_103":
            dialog.text = "さて、船長。スペイン野郎との決着もついたし、宴も済んで、頭痛も少しは引いてきた。人生ってのは悪くねえな！";
			link.l1 = "ロドガー、何をしているんだ？";
			link.l1.go = "IslaMona_104";
		break;
		
		case "IslaMona_104":
			sTemp = "";
            if (CheckAttribute(pchar, "questTemp.IslaMona.MiraRodgar")) sTemp = "I'll get along with the woman. ";
			dialog.text = "いつも通り狩りをして、自分の……いや、俺たちの酒場を見張って、プランテーションで奴隷どもを蹴飛ばすさ。最高の隠居生活だぜ。";
			link.l1 = "お前は俺より五つ年上なだけだぜ、ロドガー。\nそれで、お前はどうだ、ロドリゴ？調子はどうだ？";
			link.l1.go = "IslaMona_105";
		break;
		
		case "IslaMona_105":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		// <-- Исла Мона
		
		case "repair":
			if (CheckSelfRepairConditions())
			{
				dialog.text = "もちろんだぜ、船長！必要なのは板材と帆布だけだ。上陸地点に行って、乗組員に資材の準備を命じてくれ。";
				link.l1 = "向かうぜ。手短にな。";
				link.l1.go = "repair_1";
			}
			else
			{
				dialog.text = "かしこまりました、船長。しかし、俺の見るところ、今のところあなたの船は修理の必要がないようです。";
				link.l1 = "「今聞いたばかりだ…」";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		case "repair_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;
		
		case "shipstock_info":
			npchar.portman.info = "true";
            dialog.text = "可能ですよ、船長。ただし、いくつか制限があります。まず、この島でそれに適した場所は二か所しかありません。 それに、各船ごとに一人の士官しかここに残せません。ここに船員を維持するだけの資源が今はないんです。まだ、 ですが。最後に、一等戦列艦のための場所はありません。";
			link.l1 = "了解だ。ここで船を降りる準備はできてるぜ。";
			link.l1.go = "shipstock";
			link.l2 = "承知した、すぐに彼女を準備する。";
			link.l2.go = "carpenter_exit";
		break;
		
		case "shipstock":
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(npchar.portman) == 3)
				{
					dialog.text = "船長、すでにあなたの船が三隻も桟橋に停泊しています。もうこれ以上停める場所はありません。";
					link.l1 = "お前の言う通りだ、忘れてたぜ。";
					link.l1.go = "carpenter_exit";
					break;
				}
				else
				{
					if(CheckAttribute(npchar,"FstClassInHarbour") && sti(npchar.portman) > 0)
					{
						dialog.text = "船長、すでに一等艦が桟橋に停泊しています。もう空きはありません。";
						link.l1 = "お前の言う通りだ、忘れてたぜ。";
						link.l1.go = "carpenter_exit";
						break;
					}
				}
			}
			else
			{
				if (sti(npchar.portman) == 2)
				{
					dialog.text = "船長、あなたの船がすでに二隻、桟橋に停泊しています。もう空きはありません。";
					link.l1 = "お前の言う通りだ、忘れてたぜ。";
					link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (GetCompanionQuantity(pchar) < 2)
			{
				dialog.text = "船長、あんたの船は一隻だけだ。";
				link.l1 = "ふむ……もう少し酒を控えるべきだな……";
				link.l1.go = "carpenter_exit";
				break;
			}
            dialog.text = "ここに残していきたい船はどれだ？";
			for(i=1; i<COMPANION_MAX; i++)
			{
				int cn = GetCompanionIndex(PChar, i);
				if( cn > 0 )
				{
					ref chref = GetCharacter(cn);
					if (!GetRemovable(chref)) continue;

					attrL = "l"+i;
					Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "ShipStockMan_" + i;
				}
			}
			Link.l9 = "待て、やっぱり気が変わった。";
			Link.l9.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "「さて……」";
			Link.l1 = "「よろしい。」";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "待て、やっぱり気が変わった。";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "「さて……」";
			Link.l1 = "「よろしい。」";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "待て、やっぱり気が変わった。";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "「さて……」";
			Link.l1 = "「よろしい。」";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "待て、やっぱり気が変わった。";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "「さて……」";
			Link.l1 = "「よろしい。」";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "待て、やっぱり考え直した。";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2 && sti(npchar.portman) > 0)
				{
					dialog.text = "船長、前にも申しましたが、我々の停泊地には一等戦列艦は一隻しか停められません。大きすぎて、 空きスペースには収まりません。";
					Link.l1 = "お前の言う通りだ、俺は忘れてた。";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			else
			{
				if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
				{
					dialog.text = "船長、一等戦列艦は俺たちの岸にはデカすぎるんだ。もう言っただろう。";
					Link.l1 = "お前の言う通りだ、忘れてたぜ。";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (sti(chref.Ship.Crew.Quantity) > 0 && !CheckAttributeEqualTo(pchar, "questTemp.IslaMona.Tavern", "complete"))
			{
				dialog.text = "船長、士官を除いて彼女の乗組員全員を旗艦に連れて行ってくれ。";
				Link.l1 = "ああ、そうだな！そうするぜ！";
				Link.l1.go = "carpenter_exit";
				break;
			}
			dialog.Text = "それじゃあ、ここに留まるんだな\n"+XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName+"Acc")+" 『』と名付けられた"+chref.Ship.Name+"「。そうだろ？」";
			Link.l1 = "「そうだ。」";
			Link.l1.go = "ShipStock_3";
			Link.l2 = "待て、やっぱり気が変わった。";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_3":
            LeaveShipIslaMona(&NPChar);
			dialog.text = "よし、彼女を安全な港まで送り届けてやるぜ。";
			Link.l1 = "「素晴らしい！」";
			Link.l1.go = "carpenter_exit";
		break;
		
		case "shipstockreturn":
            if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				dialog.text = "どの船を選ぶんだ、船長？";
				cn = 1;
				for (i=1; i<MAX_CHARACTERS; i++)
				{
					makeref(chref, Characters[i]);
					if (CheckAttribute(chref, "ShipInStockMan"))
					{
						if (chref.ShipInStockMan == NPChar.id)
						{
							attrL = "l"+cn;
							Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockManBack_" + i;
							cn++;
						}
					}
				}
				link.l9 = "待て、やっぱり気が変わった。";
				link.l9.go = "carpenter_exit";
			}
			else
			{
				dialog.text = "船長、あんたの艦隊にはもう一隻入れる余裕はねえぞ。";
				link.l1 = "ふむ。どうやらお前の言う通りだな。";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		 case "ShipStockManBack":
			if (AttributeIsTrue(NPChar, "StoreWithOff") && FindFreeRandomOfficer() < 1 ) {
				dialog.text = "船長、どうやらあなたの乗組員にはもう一人士官を入れる余裕がないみたいだぜ。";
				link.l1 = "お前の言う通りかもしれねえな。後でまた寄るぜ――その間、ここを見張っててくれよ、俺の船に新しい主が現れねえようにな。";
				link.l1.go = "exit";
				break;
			}
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			dialog.Text = "「彼女を連れて行くのか？」";
			link.l1 = "「ああ。」";
			link.l1.go = "ShipStockManBack2";
			link.l2 = "待て、やっぱり気が変わった。";
			link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockManBack2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			if(CheckAttribute(npchar,"FstClassInHarbour")) DeleteAttribute(npchar,"FstClassInHarbour");
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			npchar.portman = sti(npchar.portman)-1;
            pchar.ShipInStock = sti(pchar.ShipInStock)-1;
		break;
		
		case "storadge":
            dialog.text = "ここか？いや、違う。だが、ウルフリックがここからそう遠くない場所にでかい納屋を建てたんだ。しっかりした建物で、 ヤシの葉とタールを塗った帆布で覆われてる。鍵もついてて、貨物室は交易船十隻分は積める広さだぞ\n今は空っぽだが、もし見てみたいなら鍵は俺が持ってる。どうする？";
			link.l1 = "もちろんだ！ところで、この島にはネズミはいるのか？納屋の中の俺の品物を台無しにされたりしねえだろうな？";
			link.l1.go = "storadge_1";
		break;
		
		case "storadge_1":
            dialog.text = "ウルフも抜かりはなかったぜ。本土から猫を二匹連れてきたんだ。ただしオスを忘れちまってな、 あの毛玉のメスどもは発情期になるたびにとんでもねえ騒ぎを起こすんだよ。だが、 ネズミやドブネズミを狩る腕はなかなかのもんだ。心配いらねえよ、船長。あんたの荷物は害獣にも風にもやられねえさ。 ";
			link.l1 = "素晴らしい！有効に使わせてもらうぜ。鍵は自分で持ってろ、この倉庫を見せてくれ。";
			link.l1.go = "storadge_2";
		break;
		
		case "storadge_2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			LaunchStorage(29);
		break;
		
		case "storadge_3":
            dialog.text = "ついて来い、船長。";
			link.l1 = "...";
			link.l1.go = "storadge_4";
		break;
		
		case "storadge_4":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchStorage(29);
		break;
		
		// Мирабель
		case "mirabelle":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "「ああ…」";
			link.l1 = "ほう……女か……こんなところで何してるんだ？";
			link.l1.go = "mirabelle_1";
		break;
		
		case "mirabelle_1":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "「ああ……」";
			link.l1 = "...";
			link.l1.go = "mirabelle_2";
		break;
		
		case "mirabelle_2":
            DialogExit();
			npchar.dialog.currentnode = "mirabelle_3";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_74";
			ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "mirabelle_3":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_01.wav");
            dialog.text = "旦那！旦那 "+pchar.name+" 殺さないでくれ！頼む！タイレックスには何も言わない！あの獣なんて大嫌いだ！お願いだ、ポルファボール！";
			link.l1 = "...";
			link.l1.go = "mirabelle_4";
		break;
		
		case "mirabelle_4":
			DialogExit();
            npchar.dialog.currentnode = "mirabelle_5";
			npchar.greeting = "mirabella_goodgirl";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_80";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "mirabelle_5":
            dialog.text = "";
			link.l1 = "おい、娘っ子！聞こえただろ？お前は俺と来るんだ、さもないとこの野郎がお前を殺すぞ。";
			link.l1.go = "mirabelle_6";
		break;
		
		case "mirabelle_6":
            dialog.text = "どこへ連れて行くつもりでも、俺は一緒に行くぜ、旦那！";
			link.l1 = "よし、それでいい。黙っていろ。叫んだりタイレックスを呼んだりしたら殺すぞ。名前は何だ？";
			link.l1.go = "mirabelle_7";
		break;
		
		case "mirabelle_7":
            dialog.text = "「ミラベル……」";
			link.l1 = "おとなしくしていろ、ミラベル。そうすれば無事に済むからな。俺のそばを離れるな、そして一言もしゃべるな。";
			link.l1.go = "mirabelle_8";
		break;
		
		case "mirabelle_8":
            dialog.text = "誓うよ、旦那。";
			link.l1 = "...";
			link.l1.go = "mirabelle_9";
		break;
		
		case "mirabelle_9":
            DialogExit();
            npchar.dialog.currentnode = "mirabelle_10";
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_85";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
			pchar.questTemp.Mtraxx.Mirabella = "true";
		break;
		
		case "mirabelle_10":
            dialog.text = "旦那？";
			link.l1 = "よくやったな、お嬢ちゃん、その点は気に入ったぜ。さて、これから俺の船に行くぞ。しばらくの間、 お前には小さな船室に入ってもらう。悪いが、タイレックスのところへ駆け込んで何か話されちゃ困るんでな。";
			link.l1.go = "mirabelle_11";
		break;
		
		case "mirabelle_11":
            dialog.text = "ありえねえよ、旦那！俺がタイレックスなんかに行くわけねえだろ、あのバスタードには！あいつが大嫌いなんだ！Lo odio!!!";
			link.l1 = "おい！あいつに何をされたんだ？";
			link.l1.go = "mirabelle_12";
		break;
		
		case "mirabelle_12":
            dialog.text = "たくさん……大嫌いだ、あいつのことが大嫌いだ！";
			link.l1 = "なるほどな。到着したら、お前はかなり立派な屋敷で暮らすことになるぜ。一人きりでな。俺の機嫌を損ねなければ、 誰にも傷つけられることはねえさ。さあ、ロングボートへ行け……ミラベル。";
			link.l1.go = "mirabelle_13";
		break;
		
		case "mirabelle_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1.location = "Shore75";
			pchar.quest.mtraxx_pasq_mirabella.function = "Mtraxx_PasqualeMirabella";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1.location = "Shore77";
			pchar.quest.mtraxx_pasq_mirabella1.function = "Mtraxx_PasqualeMirabella";
			AddPassenger(pchar, npchar, false);//добавить пассажира
			SetCharacterRemovable(npchar, false);
			SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false); // месяц на доплыть до Исла Моны
		break;
		
		case "mirabelle_14":
            dialog.text = "「着いたかい、旦那？」";
			link.l1 = "ああ、可愛い子よ。ここが俺の村で、俺の家だ。この場所は俺の持ち物さ。だが、俺はここには滅多に帰ってこないんだ――外でやることが多すぎてな。お前が住んでいる間、ちゃんと家を綺麗にしておけよ。 そうしないとロドガーとその大工たちにお前を渡すぞ。島の中を自由に歩き回っていいが、とても美しい場所だ。ただし、 どうせここからは逃げられないけどな。";
			link.l1.go = "mirabelle_15";
			// belamour legendary edition -->
			link.l2 = "さて、着いたな。ここが俺の家だ。この島のものは全部俺の所有物だぜ。あまりここには来ないが――結局、俺は船で暮らしてるからな――それでも、誰かが家を見ておく必要がある。ロドガーがありがたくもこの名誉ある役目をお前に譲ってくれたんだ。 好きなだけ歩き回っていいぞ、ジャングルでも浜辺でもな。ただし、必ず誰かを連れて行け――まだ野生動物がいるからな。まあ、船がなければここから出られないんだがな。";
			link.l2.go = "mirabelle_15a";
		break;
		
		case "mirabelle_15a":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
            dialog.text = "俺には逃げ場がねえ、旦那 "+pchar.name+"……私には誰もいないし、誰にも必要とされていない。もしあんたが私を売春宿に売るつもりじゃなければ……";
			link.l1 = "暖炉のそばに地下へ通じるハッチがあるんだ。そこへは行くなよ。洞窟に落ちて骨を折るか、 戻れなくなって飢え死にするかもしれねえ。そうなったら、せっかく助けてやったのが無駄になっちまうじゃねえか。";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_15":
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			// <-- legendary edition
            dialog.text = "俺には行く当てがねえんだ、旦那 "+pchar.name+"。俺には家族も目的もねえ。また娼館に戻ることになるかもしれねえな。";
			link.l1 = "洞窟へ通じるハッチがあるんだ、近づくなよ。\nあそこは暗くて危険だからな。";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_16":
            dialog.text = "俺は離れているぜ、旦那。";
			link.l1 = "二階には寝室もあるぜ。ついて来な。";
			link.l1.go = "mirabelle_17";
		break;
		
		case "mirabelle_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1.location = "IslaMona_TwoFloorRoom";
			pchar.quest.mtraxx_islamona_mirabella1.function = "Mtraxx_PasqualeMirabellaRoom";
		break;
		
		case "mirabelle_18":
            dialog.text = "";
			link.l1 = "ほら、これで家の中を全部案内したぞ。前に住んでいたタイレックスの家より悪くはないだろう。 気に入ってくれるといいがな。";
			link.l1.go = "mirabelle_19";
		break;
		
		case "mirabelle_19":
            dialog.text = "はい、旦那。立派なお屋敷ですね。ご不在の間、しっかりお守りすることをお約束します。";
			link.l1 = "協力的で嬉しいぜ。正直に話してくれてると信じてるが、嘘をついたら後悔することになるぞ。いい子にして、 俺を悲しませるな。そうすれば、俺も優しくしてやる。チャーリー・プリンスは約束を守る男だ！";
			link.l1.go = "mirabelle_20";
			// belamour legendary edition -->
			link.l2 = "信じてるよ、あなた。ここにいた方が、タイレックスに暗い倉庫に縛られていた時よりも安全だと思うんだ。";
			link.l2.go = "mirabelle_20a";
		break;
		
		case "mirabelle_20a":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
            dialog.text = "ありがとうございます、旦那 "+pchar.name+"…。俺をお前の…仲間に殺させなかったこと、感謝するぜ。お前は本当に優しいな…";
			link.l1 = "へっ、お前は面白い奴だな……それに、額に焼き印があっても顔はなかなか綺麗じゃねえか。他の部分もちゃんとしてるといいが……さあ、自分の腕前を船長に見せてみろよ。海の揺れの後で、二、三時間ゆっくりしようぜ。";
			link.l1.go = "mirabelle_21";
			link.l2 = "よし、以上だ。俺はやることが山ほどあるんだ。\nお前はここで落ち着いて、ロドガーや連中と顔を合わせておけ。\n俺が戻ったら、またゆっくり話そうぜ。";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_20":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			// <-- legendary edition
            dialog.text = "ありがとうございます、旦那 "+pchar.name+"。俺を殺させなかったこと、仲間に感謝するぜ。あんたは本当に親切だな。";
			link.l1 = "へへっ、お前は面白い可愛い子だな……その痣があっても、顔もなかなか綺麗じゃねえか。他の部分もちゃんとしてるといいが……さあ、船長様にお前の腕前を見せてみろよ。";
			link.l1.go = "mirabelle_21";
			// belamour legendary edition -->
			link.l2 = "よし、それじゃあ、俺は仕事が山ほどあるんだ。お前はここで落ち着いて、ロドガーや連中と顔を合わせておけ。 俺が戻ったら、またゆっくり話そうぜ。";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_21a":
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 400);
			pchar.questTemp.Mtraxx.MirabellaFirstTimeSex = true;
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_21":
			DialogExit();
			
			pchar.questTemp.Mtraxx.MirabellaFirstTimeKiss = true;
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("IslaMona_MirabelleKiss", "");
		break;
		
		case "mirabelle_22":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Señor "+pchar.name+" あなたは本当に優しい方ですね……本物の紳士ですわ。きっと最近ヨーロッパから来られたのでしょう。";
			link.l1 = "おだてるんじゃねえよ、この小さな嘘つきめ、そんなの信じねえぜ。へっ、やるじゃねえか、ミラベル！ タイレックスの目は確かだな、へっへっ…";
			link.l1.go = "mirabelle_23";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_23":
            dialog.text = "私は違いますわ。あなたは紳士ですもの。でも、何か理由があってわざと無作法に振る舞っているのでしょう。んふふ……とても気に入りましたわ。またお会いできるのを楽しみにしています……";
			link.l1 = "ああ、そうだな、紳士……運に任せる紳士ってやつさ、はは！よし、可愛い子ちゃん、とりあえずここで落ち着いてな。";
			link.l1.go = "mirabelle_24";
		break;
		
		case "mirabelle_24":
            dialog.text = "さようなら、旦那。";
			link.l1 = "...";
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex"))
			{
				link.l1.go = "mirabelle_28";
				DeleteAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex");
			}
			else link.l1.go = "mirabelle_25";
			// <-- legendary edition
		break;
		
		case "mirabelle_25":
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_26":
            dialog.text = TimeGreeting()+"、旦那 "+pchar.name+"！会えて本当に嬉しいよ。元気にしてたか？";
			link.l1 = RandSwear()+""+RandPhraseSimple("「うぉっ、こりゃ驚いたぜ、魂まで震えるじゃねえか！」","おお、俺が掲げる勇ましい黒旗の下で生きて死ぬ方がましだぜ！")+" 「チャーリー・プリンスは無事だよ、可愛い子ちゃん。」";
			link.l1.go = "mirabelle_26x";
			if (!CheckAttribute(pchar, "questTemp.MirabelleBlock")) {
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "お嬢ちゃん、船長をもう少し喜ばせてくれないか？";
					link.l2.go = "mirabelle_sex";
				}
			}
		break;
		
		case "mirabelle_26x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
		break;
		
		case "mirabelle_sex":
            dialog.text = "「あなたのためなら何でもしますぜ、旦那！」";
			link.l1 = RandPhraseSimple("「グラップルを用意しろ！」","乗り込め！");
			link.l1.go = "mirabelle_sex_1";
		break;
		
		case "mirabelle_sex_1":
            DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("", "");
			
			LAi_SetActorType(npchar);
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex")) npchar.dialog.currentnode = "mirabelle_22";
		    else npchar.dialog.currentnode = "mirabelle_27";
			// <-- legendary edition
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_27":
            dialog.text = "んん…旦那、あんたは魔法使いだな！あんたも楽しめたかい？あたしは精一杯やったよ。";
			link.l1 = "よくやったな、可愛い子。";
			link.l1.go = "mirabelle_28";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_28":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_sleep":
            dialog.text = "そんなはずない、違う！旦那 "+pchar.name+" いい人で親切なんだ！悪い海賊のふりをしているだけさ！あなたこそ、旦那\n "+pchar.name+"?";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6_1");
		break;
		
		case "mirabelle_29":
            dialog.text = TimeGreeting()+"、旦那 "+pchar.name+"！会えて本当に嬉しいよ。元気かい？どうしてそんなに元気がなさそうなんだ？";
			link.l1 = "やあ、ミラベル。どうして俺が悲しんでいると思うんだ？";
			link.l1.go = "mirabelle_30";
		break;
		
		case "mirabelle_30":
            dialog.text = "そうか、分かるぜ。お前、いつもの自分じゃねえな。元気づけてやろうか？さあ！ 俺がジャングルで採った甘い果物があるし、ロドガーとその仲間たちが昨日釣った魚も焼いてあって、まだ温かいぜ。";
			link.l1 = "待て。お前と話がしたい。";
			link.l1.go = "mirabelle_31";
		break;
		
		case "mirabelle_31":
            dialog.text = "もちろん、旦那、何でもおっしゃってください。耳を傾けております";
			link.l1 = "教えてくれ、どうしてタイレックスの手に落ちたんだ？それに、なぜお前の額に盗人の印があるんだ？\n怖がることはない、俺は決してお前を傷つけたりしない。\nただ、お前の話を聞きたいだけなんだ。";
			link.l1.go = "mirabelle_32";
		break;
		
		case "mirabelle_32":
            dialog.text = "ああ、旦那！俺の話は短くてつまらないぜ。俺はプエルトリコで生まれた。親父は白人紳士で、 お袋はインディアンだった。親父の顔は一度も見たことがねえ。子供の頃は召使いをやってて、大きくなったら、 馬鹿なことに主人の宝石を盗んじまった。自分の物なんて一つも持ったことがなかったから、 どうしても一日だけでも身につけてみたかったんだ。当然、全部バレたさ\n裁判があって、鞭打たれ、焼き印を押されて、サンファンの牢屋にぶち込まれた。でも、そんなに長くは居なかった。 役人の一人が親分と取引して、俺は金貨数枚でフィリップスバーグの売春宿に売られたんだ\nそこで一年ほど過ごした。ある不運な日に、タイレックスとそのメガネの嫌な友達が俺たちのところにやって来たのさ。";
			link.l1 = "パスカーレ・ラヴォワジエ…";
			link.l1.go = "mirabelle_33";
		break;
		
		case "mirabelle_33":
            dialog.text = "ああ、そうそう、あいつの名前はパスクワーレ・ラヴォワジエ旦那だった。 奴らが俺に何を見出したのかは全く分からねえが、あいつらが来た後すぐに、 タイレックスがジョアンナ女将から俺を買い取って、箱や商品でいっぱいの鍵付きの家に閉じ込めやがった。 あれは人生で最悪の時期だったぜ、サンファンの牢獄で過ごした日々よりもひでえ。 タイレックスは海に出ていない限り毎日俺のところに来やがったし、奴がいない時だけはやっと息ができた。でも、 ラヴォワジエ旦那が来るたびに俺は……俺は……それが一番最悪だったんだ。旦那\n "+pchar.name+"お願いです、このことは話させないでください。\nどれくらいそこにいたのか分かりません。そしてあなたが来て、あのひどい家から私を連れ出してくれました。 あなたがとても親切で、本当に運が良かったです。";
			link.l1 = "優しい？ミラベル、でも俺も同じことをしたじゃねえか。お前を島に連れて行って、家の中に閉じ込めたんだ。";
			link.l1.go = "mirabelle_34";
		break;
		
		case "mirabelle_34":
            dialog.text = "いいえ、旦那、それは違います。私がここに閉じ込められている？毎日島を散歩していますよ。 ここは素晴らしくて静かな場所です。家事をたくさんしなければならないかって？全然そんなことありませんし、 もう慣れました。それに、あなたはタイレックスやあの商人の友達とは違います。あなたに会えるといつも嬉しいです、 あなたはとても若くてハンサムですし、それに紳士ですもの…";
			link.l1 = "ミラベル、どこかの町まで送ってほしいか？十分なお金を渡すよ。どこへ行きたい？好きな植民地を選んでくれ。";
			link.l1.go = "mirabelle_35";
		break;
		
		case "mirabelle_35":
            dialog.text = "旦那、俺を追い払いたいのか？どうかやめてくれ、頼むよ！";
			link.l1 = "そうか……普通の生活に戻りたいんじゃないかと思ってたんだ……";
			link.l1.go = "mirabelle_36";
		break;
		
		case "mirabelle_36":
            dialog.text = "ああ、旦那 "+pchar.name+"、それで私には何があるの？私は印をつけられた混血として、どうやって結婚できるの？また娼館に売られてしまうわ。 お願い、追い出さないで。ここが好きなの、こんなに穏やかで安全だと感じたことは他にないわ。 ロドガーとその仲間たちはいい人たちよ、私たちは友達で、誰も私を傷つけたことがない――みんな私のために命を懸ける覚悟があるのよ。一緒に過ごすのが楽しくて仕方ないの、いつも笑いが絶えないわ！時々 浜辺で焚き火をして、私がサンバを踊るの。お願い、旦那、何でもするから、ここにいさせて！";
			link.l1 = "わかったよ、ミラベル、この場所がそんなに気に入ってるならここにいればいいさ。ただし、 ここで囚われの身じゃないってことは覚えておけよ。いつでも俺に頼めば、ここから連れ出してやるからな。";
			link.l1.go = "mirabelle_37";
		break;
		
		case "mirabelle_37":
            dialog.text = "ああ、親愛なる旦那、ありがとう！ありがとう！ありがとう！もう二度とこんなお願いはしません――私はこの島の囚われの身のままでいたいの……それに、あなたの囚人でも、うふふ……あなたは本当に優しい方。でも今日はとても寂しそう！いつものように歌ったり悪態をついたりしないのね。";
			link.l1 = "歌ってもいいが、もう悪態はつかないよ、ミラベル。あと……もし俺が無礼だったなら、謝るぜ。";
			link.l1.go = "mirabelle_38";
		break;
		
		case "mirabelle_38":
            dialog.text = "あなたもイギリスの貴族みたいに厳しくて堅い人になるのかしら？…ああ…旦那、今夜は私に踊って歌ってほしいの？あなたのためだけに。さあ、こっちに来て！悲しみを癒すには愛が一番よ。 あなたにすごく会いたかったの。";
			link.l1 = "ははっ！いいところに気がついたな、お嬢ちゃん……行こうぜ。";
			link.l1.go = "mirabelle_39";
		break;
		
		case "mirabelle_39":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_40":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "ああ、旦那 "+pchar.name+"、今日はとても優しかったわね、んふ…私のこと、気に入ってくれたかしら、親愛なるカピタン？";
			link.l1 = "すべてが素晴らしかったよ、ミラベル。";
			link.l1.go = "mirabelle_41";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_41":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_42":
			bool bMary = GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer");
			bool bHelena = GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer");
            dialog.text = TimeGreeting()+"、旦那 "+pchar.name+"！会えて本当に嬉しいよ！元気にしてたか？";
			link.l1 = ""+LinkRandPhrase("「あたしも会えて嬉しいよ、お嬢ちゃん。」","やあ、ミラベル。君はいつも変わらず明るくて美しいな、見ていて本当に気持ちがいいよ。","やあ、かわいこちゃん。すごく綺麗だな！")+"俺は元気だぜ。お前も元気だといいな。";
			link.l1.go = "mirabelle_42x";
			if (!bMary && !bHelena && !CheckAttribute(npchar,"quest.rodgar")) // прогона 3
			{
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "ミラベル、もう君と君のイタチが恋しいよ。俺の海のオオカミにキスしてくれるか？";
					link.l2.go = "mirabelle_43";
				}
			}
		break;
		
		case "mirabelle_42x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		case "mirabelle_43":
            dialog.text = "ああ、私の愛しい船長、私もあなたが恋しかったですわ！さあ、もう我慢できませんの！";
			link.l1 = "...";
			link.l1.go = "mirabelle_39";
		break;
		
		// Jason Исла Мона
		case "mirabelle_44":
			dialog.text = "旦那船長！船長 "+pchar.name+"！嬉しい！あなたが私たちを助けてくれるんだね！";
			link.l1 = "俺も会えて嬉しいぜ、ミラベル。で、被害の状況はどうだ？";
			link.l1.go = "mirabelle_45";
		break;
		
		case "mirabelle_45":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_66";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "mirabelle_46":
			dialog.text = "船長、船長、ありがとう！あんたは最高で、一番優しい人だ！俺を怪物から救ってくれただけじゃなく、 新しい人生までくれたんだ！俺たちみんなに乾杯だ！";
			link.l1 = "";
			link.l1.go = "mirabelle_47";
			locCameraFromToPos(1.25, 1.28, 0.71, false, 2.28, -0.20, 1.91);
		break;
		
		case "mirabelle_47":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && CheckPassengerInCharacter(pchar, "Mary"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "IslaMona_2";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
				{
					sld = characterFromId("Helena");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					sld = characterFromId("Himenes_companion_1");
					sld.dialog.currentnode = "island_man_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
			}
		break;
		
		case "mirabelle_48":
			dialog.text = "旦那船長！";
			link.l1 = "あんたもこんにちは、美人さん。退屈してねえだろうな？";
			link.l1.go = "mirabelle_49";
		break;
		
		case "mirabelle_49":
			dialog.text = "ああ、船長！あの恐ろしい屋敷からあなたに助け出されて以来、私の人生は彩りと喜びを取り戻しました。";
			link.l1 = "「幸せか？」";
			link.l1.go = "mirabelle_50";
		break;
		
		case "mirabelle_50":
			dialog.text = "もちろんです！そして、この幸せをあなたと分かち合いたい…あなたの部屋で、二階でお待ちしています。";
			link.l1 = "なんて女なんだ……";
			link.l1.go = "mirabelle_51";
		break;
		
		case "mirabelle_51":
			DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			pchar.questTemp.IslaMona.Mirabelle = "true";
		break;
		
		case "mirabelle_52":
			dialog.text = "旦那船長！";
			link.l1 = "あんたにも挨拶するよ、美人さん。退屈してないだろうな？";
			link.l1.go = "mirabelle_53";
		break;
		
		case "mirabelle_53":
			dialog.text = "ああ、船長！あの恐ろしい屋敷からあなたに救い出されて以来、私の人生は色彩と喜びを取り戻しました。";
			link.l1 = "「幸せか？」";
			link.l1.go = "mirabelle_54";
		break;
		
		case "mirabelle_54":
			dialog.text = "とても！ただし……";
			link.l1 = "なるほど、俺に何か聞きたいことがあるのか？";
			link.l1.go = "mirabelle_55";
		break;
		
		case "mirabelle_55":
			dialog.text = "はい、船長！私……ある男と幸せを分かち合いたいんです……";
			link.l1 = "奴は気にするか？";
			link.l1.go = "mirabelle_56";
		break;
		
		case "mirabelle_56":
			dialog.text = "いや、違うよ、船長。俺たちが一緒にいれば幸せになれるって、俺は確信してるんだ。ただ……許してくれるか？";
			link.l1 = "お前が誰よりもこれにふさわしいさ。だが、俺はお前ら二人を結婚させるつもりはねえからな、頼まれても無駄だぜ！";
			link.l1.go = "mirabelle_57";
		break;
		
		case "mirabelle_57":
			dialog.text = "ハハハ！旦那！ありがとう、船長旦那。世間であんたのことをどう言ってるかは知らねえが、 俺はずっとあんたを一番親切で誠実な人間だと思ってるぜ。";
			link.l1 = "ミラベル、幸運を祈るよ。";
			link.l1.go = "mirabelle_58";
		break;
		
		case "mirabelle_58":
			DialogExit();
			npchar.quest.rodgar = true;
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		// губернатор Картахены
		case "CartahenaMayor":
            dialog.text = "血まみれの盗賊どもめ！まあいい、うちの使者はもうポルトベロへ向かってる。すぐに我々の戦隊が到着して……";
			link.l1 = TimeGreeting()+"、殿下。こんな美しい館でお目にかかれて光栄です。私たちが去った後も、どうかこの館を保っていただきたい。 もし私があなただったら、艦隊には期待しませんし、我々もここに三日以上は滞在しません。貴方もご承知の通り、 ポルトベロの高貴なドンたちがすぐに助けに来ることはないでしょう。では、本題に入りましょうか？";
			link.l1.go = "CartahenaMayor_1";
		break;
		
		case "CartahenaMayor_1":
            dialog.text = "もう商談の話か？窓の外を見てみろ！お前のならず者どもが通りや家の中で何をしているか見てみろ！";
			link.l1 = "ああ、殿下、これなどは、もしご協力いただけなければ、あの者たちがなすことに比べれば何でもございません。 あの男たちが何者か、お分かりいただけますでしょうか…";
			link.l1.go = "CartahenaMayor_2";
		break;
		
		case "CartahenaMayor_2":
            dialog.text = "俺はあの海賊チャーリー・プリンスがどれほど極悪非道な奴か知ってるぜ！そいつの親玉も分かってる！ いずれヒスパニョーラのお前らの盗賊の巣窟を焼き払ってやるからな！いくらだ？";
			link.l1 = "言葉を無駄にするなよ、親愛なる総督殿。さっさと25万ペソ用意してもらおうか。";
			link.l1.go = "CartahenaMayor_3";
		break;
		
		case "CartahenaMayor_3":
            dialog.text = "「なにっ！？お前の無礼さは限度を知らねえな！これは強盗だ！」";
			link.l1 = "もちろん、これは強盗だ。他に何があるってんだ？お前の精鋭や商人どもを集めて、金貨をでかい箱に詰めろ。 さもないと……お前も部下も、もっとひどい目に遭わせてやるぜ。";
			link.l1.go = "CartahenaMayor_4";
		break;
		
		case "CartahenaMayor_4":
            dialog.text = "くそったれ海賊め！バスタード野郎！異端者め！くたばりやがれ！\n";
			link.l1 = "てめえの汚ねえ口のせいで、身代金を三十万に引き上げるぜ。";
			link.l1.go = "CartahenaMayor_5";
		break;
		
		case "CartahenaMayor_5":
            dialog.text = "地獄で焼かれろ、このクソ野郎！！！";
			link.l1 = "３５万だ。続けるか？";
			link.l1.go = "CartahenaMayor_6";
		break;
		
		case "CartahenaMayor_6":
            dialog.text = "この街にそんな金はねえぞ！";
			link.l1 = "嘘だな。それはありえねえ。ここでなら百万くらいは集められるが、残念ながらそんな時間はねえんだ。だから、 俺は親切にしてやるぜ。金額はわかってるだろう。さっさと持ってこい。";
			link.l1.go = "CartahenaMayor_7";
		break;
		
		case "CartahenaMayor_7":
            dialog.text = "もう一度言うぞ、Charlie Prince。カルタヘナにそんな金はねえんだ！";
			link.l1 = "ああ…なんでそんなに鈍いんだ。カトラス！周りを探して、見つけた奴は全員ここに連れてこい。徹底的に探せ！\nそして我々はここで待つとしよう、閣下…";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaInResidence");
		break;
		
		case "CartahenaMayor_8":
            dialog.text = "";
			link.l1 = "おい、頑固者の旦那！カタルヘナの立派な街で金を集めるって考え、まだ変わっちゃいねえのか？…どうした、なんで急にそんなに真剣な顔してんだ！？大丈夫か？水でも持ってこようか？\n";
			link.l1.go = "CartahenaMayor_9";
		break;
		
		case "CartahenaMayor_9":
            dialog.text = "";
			link.l1 = "俺の理解では、この二人のご婦人はあんたの奥さんと娘さんだろう？違うか？三人目の娘は召使いみたいだな。 あんたはどうでもいいと思ってるようだから、こっちは手出ししねえよ。でも、この二人の美人は俺の仲間、 旦那カトラスの目を引くかもしれねえ。どうやら気に入ったようだぜ、旦那。で、どうする？ 身代金の話に応じるつもりか？";
			link.l1.go = "CartahenaMayor_10";
		break;
		
		case "CartahenaMayor_10":
            dialog.text = "俺は……時間が必要だ。";
			link.l1 = "ははっ！やっと本音が出たな！で、ここでのバスタードは誰だ？ 俺の手下がてめえの市民を脅かしても知らん顔だったくせに、女が二人やられると話は別ってわけか？ 俺と取引しようなんて、なめた真似しやがって、この野郎！チャーリー・プリンスを敵に回すってどういうことか、 思い知らせてやるぜ！";
			link.l1.go = "CartahenaMayor_10x";
		break;
		
		case "CartahenaMayor_10x":
            dialog.text = "";
			link.l1 = "さあ、さっさと血まみれの身代金を集めてこい。三十五万、１ペソたりともまけねえぞ。猶予は一日だ。 俺たちはここでワインでも飲みながら、この可愛い女たちと楽しませてもらうぜ……急げよ、旦那、でねえと俺の友達、旦那カトラスと俺があんたの美女たちに惚れちまうかもしれねえ。そしたら、 そいつらの身代金も払う羽目になるぜ。前へ！進め！";
			link.l1.go = "CartahenaMayor_11";
		break;
		
		case "CartahenaMayor_11":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaResidenceWait", 5.0);
		break;
		
		case "CartahenaMayor_12":
			AddMoneyToCharacter(pchar, 350000);
            dialog.text = "血塗られた金を受け取れ、チャーリー・プリンス！";
			link.l1 = "身代金は集めてきたか？素晴らしい！だがな、旦那総督、あんたは一時間遅れたぜ。この余分な一時間で、 俺とカトラス号はよく分かったんだ――こいつらのいない人生なんて、あまりにも退屈すぎるってな。あの美人たちは俺たちにとても親切で、 おしゃべりも楽しませてくれたからな……";
			link.l1.go = "CartahenaMayor_13";
		break;
		
		case "CartahenaMayor_13":
            dialog.text = "お前…お前！";
			link.l1 = "ああ、仕事のせいで緊張しすぎだぜ、友よ。冗談だったんだ……カトラス！行くぞ、出発だ！";
			link.l1.go = "CartahenaMayor_14";
		break;
		
		case "CartahenaMayor_14":
            DialogExit();
			AddQuestRecord("Roger_9", "7");
			AddDialogExitQuestFunction("Mtraxx_CartahenaToFort");
		break;
		
		// Камилла
		case "camilla":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "おお、こいつがあの有名な海賊チャーリー・プリンス、スペイン領南部を震え上がらせた悪名高き奴か！";
			link.l1 = RandSwear()+"へえ、俺がトルトゥーガでそんなに人気者だったとは知らなかったぜ。名前は何だい、お嬢ちゃん？";
			link.l1.go = "camilla_1";
		break;
		
		case "camilla_1":
            dialog.text = "私の名前はカミラです。";
			link.l1 = "カミラ……昔フランスでその名の娘を知っていたことがある。あれはずいぶん昔のことだ！";
			link.l1.go = "camilla_2";
		break;
		
		case "camilla_2":
			PlaySound("ambient\tavern\orijka_003.wav");
            dialog.text = "";
			link.l1 = "（ゲロゲロ）…くそっ…すまねえな、お姫様。でも王子様は今夜かなり酔っ払ってるんだ。で…えっと…俺のところに何の用だ？";
			link.l1.go = "camilla_3";
		break;
		
		case "camilla_3":
            dialog.text = "様々な理由でな。あるいは、理由なんて何もないかもしれねえ。";
			link.l1 = "神よ、これはあまりにも複雑だ。お前は謎めいた娘だな。";
			link.l1.go = "camilla_4";
		break;
		
		case "camilla_4":
            dialog.text = "「女は誰でも謎を持ってるもんさ。」";
			link.l1 = "どうやらこの謎を俺に解いてほしいんだな。違うか？女の謎を解くのは俺の得意分野だぜ、誓ってもいい！\n酒場に行ってワインでも飲まねえか？最高のご馳走を用意してやるぜ！";
			link.l1.go = "camilla_5";
		break;
		
		case "camilla_5":
            dialog.text = "んん…あたし、強い男が好きだよ。でも下の階で酔っ払いの下賤どもと一緒にワインなんて飲まないよ。部屋を取ってきて、 そこで飲みながら話そうよ。";
			link.l1 = RandSwear()+"お前、なかなか魅力的だな！ついて来いよ！";
			link.l1.go = "camilla_6";
		break;
		
		case "camilla_6":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.location = "Tortuga_town";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator = "reload4_back";
			pchar.quest.mtraxx_retribution_tavern.function = "Mtraxx_RetributionToTavern";
		break;
		
		case "camilla_7":
			PlaySound("Voice\English\hambit\Gr_officiant_1.wav");
            dialog.text = "さあ……早く注げよ、お嬢さんを待たせるな！";
			link.l1 = "もちろんだよ、あんた！";
			link.l1.go = "camilla_8";
		break;
		
		case "camilla_8":
			LAi_Fade("", "");
			PlaySound("ambient\tavern\krujki_005.wav");
			PlaySound("ambient\tavern\naliv_003.wav");
			PlaySound("ambient\tavern\glotok_001.wav");
			WaitDate("", 0, 0, 0, 1, 5);
            dialog.text = "んん…考えてみろよ、俺は今チャーリー・プリンスと二人きりで、うまいワインを飲んでるんだぜ…";
			link.l1 = "この航海、俺と一緒に楽しませてやるぜ、約束する！チャーリー・プリンスは自分に従う女には優しくて親切なんだ。 どうだい、お姫様、俺に従う気はあるか？";
			link.l1.go = "camilla_9";
		break;
		
		case "camilla_9":
            dialog.text = "うふふ……もちろんよ、坊や！あなたの約束、とっても魅力的だもの……";
			link.l1 = "じゃあ、時間を無駄にしないでおこうか、美人さん？";
			link.l1.go = "camilla_10";
		break;
		
		case "camilla_10":
            dialog.text = "おお！大好きよ！これぞ本物の男たちね！..";
			link.l1 = "...";
			link.l1.go = "camilla_11";
		break;
		
		case "camilla_11":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 5.1);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			if(bSFW) PlayStereoSound("sex\sex_sfw.wav");
			else PlayStereoSound("sex\sex2.wav");
			LaunchFrameForm();
			if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 6);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 3);
			LAi_SetCurHPMax(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionRoomSex", 5.1);
		break;
		
		case "camilla_12":
            dialog.text = "「んん……」";
			link.l1 = "気に入ったかい、お姫様？";
			link.l1.go = "camilla_13";
		break;
		
		case "camilla_13":
            dialog.text = "もちろんだ！お前も俺のこと気に入ってくれたら嬉しいぜ。";
			link.l1 = "へっ！今じゃ俺の頭までスッキリしたぜ！";
			link.l1.go = "camilla_14";
		break;
		
		case "camilla_14":
            dialog.text = "殿下、お願いがございます。お力を貸していただけますか？";
			link.l1 = "お前のためなら空から星でも取ってきてやるぜ、ははっ！さあ、続けろ。";
			link.l1.go = "camilla_15";
		break;
		
		case "camilla_15":
            dialog.text = "ラ・ベガに行ってタイレックスに会わなきゃならないんだ。あいつが怖いけど、お前は一緒に商売してるだろう。頼む、 あいつのところまで連れて行ってくれ。";
			link.l1 = "これを見てくれ！それにしても、こんな可愛くて繊細な娘がなぜ掟の守り手に会いたがるんだ？";
			link.l1.go = "camilla_16";
		break;
		
		case "camilla_16":
            dialog.text = "この可愛くてか弱い娘が少しでもお金を稼ぎたいんだ。亡くなった父さんや兄さんたちは、 私にあまり財産を残してくれなかったからね。タイレックスならこの状況を何とかできるはずさ。";
			link.l1 = "「へえ、本当か？どうやってだ？スペインのガレオン船の手がかりでも探してるのか？ははっ！」";
			link.l1.go = "camilla_17";
		break;
		
		case "camilla_17":
            dialog.text = "隊商や町を略奪するのは、あんたみたいなタフな男の仕事さ、ハニー。マーカスには別の仕事がある。 あいつは情報の売り買いをしてるんだろ？俺にはちょっとしたネタがある……自分じゃ使えねえが、あいつなら使えるはずだ。俺はほんの少し分け前をもらえりゃ、それで十分さ。";
			link.l1 = "面白いな！もっと聞かせてくれ。";
			link.l1.go = "camilla_18";
		break;
		
		case "camilla_18":
            dialog.text = "うーん……わからねえな……";
			link.l1 = "おいおい、俺をタイレックスの右腕だと思ってくれよ。今まであいつのためにずいぶんと掘り出し物を見つけてきたんだ、 信じてくれ。もしお前の情報が本当に価値あるものなら――俺が自分で買うさ。";
			link.l1.go = "camilla_19";
		break;
		
		case "camilla_19":
            dialog.text = "いいだろう。もっと話してやるが、金を受け取るまでは詳しいことは言わねえぜ。いいかい、坊や？";
			link.l1 = "もちろんだよ、お嬢ちゃん。チャーリー・プリンスは相棒を裏切ったりしねえ……分かるだろ、ははは！さあ、どうぞ、俺は全部聞くぜ。";
			link.l1.go = "camilla_20";
		break;
		
		case "camilla_20":
            dialog.text = "…親父は商船のスクーナーの船長だったんだ。ある日、 どういうわけか本土のジャングル奥深くにある古いスペインの鉱山集落のことを知ったんだ。二十年前、 地震で壊滅して鉱夫たちは去り、秘密の通路も忘れ去られた。ただ一つを除いてな。親父がそれを見つけたんだ\n親父は兄弟たちと案内人を連れてそこへ行き、何年も前に採掘されて精錬された金で満ちた場所を見つけた。大量の金だ。 少なくとも百万ペソはあった。親父は金を運ぶために人手を集めようと船に戻ったが、驚いたことに船が消えていた。 どうやら一等航海士が反乱を起こして、親父と兄弟たちを無人の岸に置き去りにして出航したらしい\n彼らは小舟を作り、岸沿いに住民のいる場所を必死に探して航海したが…（すすり泣き）嵐に襲われて（すすり泣き）兄弟たちは死んだ。親父だけが生き延びて帰ったが、 家に戻っても長くは生きられなかった――兄弟たちの死が日々親父を蝕んでいったんだ。亡くなる前に、親父は地図を作って私に渡してくれた\n結婚したら、夫にそこへ行って金を手に入れ、王様のように暮らせと言われたよ。きっとそうするわ、 でも私はもう二度とあの呪われたジャングルに男を行かせたりしない！百万ペソ、親父はそう言ったけど、 私には分不相応よ。そんな大金、手にできるのはマーカス・タイレックスみたいな一流で屈強な男だけ。だからこそ、 私は彼に会いに行くの。";
			link.l1 = "地図はいくらで売ってくれるんだ？";
			link.l1.go = "camilla_21";
		break;
		
		case "camilla_21":
            dialog.text = "二百枚の金のドゥブロンだ。賞品に比べりゃ大した額じゃねえ。タイレックスならきっと納得するさ。 あいつはクラッスス並みに金持ちだからな。";
			link.l1 = "へっ！もしこれが全部罠だったらどうするんだ？";
			link.l1.go = "camilla_22";
		break;
		
		case "camilla_22":
            dialog.text = "俺が自殺志願者に見えるか？タイレックスに逆らうなんて無謀だろ？\nお嬢ちゃん、生きてるだけで十分なんだ、貧乏でもな。\nそれで、あんたは俺をそこまで連れてってくれるのか？頼むよ……";
			link.l1 = "地図はどこだ？俺に見せてくれるのか？";
			link.l1.go = "camilla_23";
		break;
		
		case "camilla_23":
            dialog.text = "俺の神父がそれを安全に保管してる。200ドゥブロンでお前に見せてやるぜ。";
			link.l1 = "よし！買わせてもらうぜ。酒場の見知らぬ奴らは、ガラクタにもっと高い値をふっかけてくることもあるからな。";
			link.l1.go = "camilla_24";
		break;
		
		case "camilla_24":
            dialog.text = "そうなの？本当なの、あなた？ラ・ベガに行かなくて済むなんて、すごく嬉しいわ！正直に言うと、マルクスが怖いの。 あなたのことも怖いけど……でも、ちょっとだけね。";
			link.l1 = "こんな可愛い娘が俺を怖がる必要はねえよ。金はどこに持っていけばいいんだ？";
			link.l1.go = "camilla_25";
		break;
		
		case "camilla_25":
            dialog.text = "取引をしよう。毎日午前十時から午後一時まで、うちの教会で俺を探してくれ。\nこの聖なる場所の加護の下なら、俺もずっと安心できるからな。\nそこで取引をまとめよう。";
			link.l1 = "まだ俺のことが怖いのか？ははっ！心配するな、カミラ、俺はお前を裏切ったりしねえよ。 チャーリー・プリンスが二百ドゥブロンのためにそんな卑怯な真似をするわけがねえし、それに、 お前を助けてやりたいんだ。";
			link.l1.go = "camilla_26";
		break;
		
		case "camilla_26":
            dialog.text = "素敵ね。いいわよ、イケメンさん、待ってるわ……今夜は一緒に過ごせて本当に楽しかった！あなたに出会えてとても幸せよ！";
			link.l1 = "また会おうぜ、可愛い子ちゃん。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionOutRoom");
		break;
		
		case "camilla_27":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "それで？金は持ってきたのかい、坊や？";
			if (PCharDublonsTotal() >= 200) // belamour legendary edition
			{
				link.l1 = "ああ。これが約束の金だ、さあ地図を渡せ。";
				link.l1.go = "camilla_28";
			}
			else
			{
				link.l1 = "俺はそのすぐ後ろにいる。";
				link.l1.go = "camilla_27x";
			}
		break;
		
		case "camilla_27x":
            DialogExit();
			npchar.dialog.currentnode = "camilla_27";
		break;
		
		case "camilla_28":
			RemoveDublonsFromPCharTotal(200); // belamour legendary edition
			GiveItem2Character(pchar, "mapEnrico"); 
            dialog.text = "ありがとう、あなた……さあ、これを受け取って。父の思い出に誓う――この地図は偽物じゃない、必ず君を必要な場所へ導いてくれる……";
			link.l1 = "いいわよ、坊や。前回みたいに、この取引を祝わない？";
			link.l1.go = "camilla_29";
		break;
		
		case "camilla_29":
            dialog.text = "やりたいのですが、旦那、今は自分の神父の前で告解の準備をしているところなので、 今はあらゆる誘惑から遠ざかっていなければなりません。\n次の機会にしましょう。";
			link.l1 = "おいおい、からかってるのか、お嬢ちゃん。まあいい！ぐずぐずしてる暇はねえ、これから出航だ。 もしあんたの親父の地図が本当に俺を金貨のありかに導いてくれるなら、報酬は倍にしてやると誓うぜ。";
			link.l1.go = "camilla_30";
		break;
		
		case "camilla_30":
            dialog.text = "あなたは本当に気前がいいわ、ダーリン。良い航海を！";
			link.l1 = "「ヨーホーホー！」";
			link.l1.go = "camilla_31";
		break;
		
		case "camilla_31":
            DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_10", "2");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
			pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionCarataska";
			pchar.questTemp.Mtraxx.Retribution = "carataska";
		break;
		
		case "camilla_sleep":
            dialog.text = "貴様らの野郎どもが俺の父と兄弟を殺したんだ。カルタヘナへの襲撃は、あそこのすべての家族に悲しみをもたらした。 今ごろ貴様も怖がっているといいな――俺たちカルタヘナ市民が、貴様らの獣どもが通りや家の中で好き勝手していた時に感じた恐怖と同じくらいにな。 地獄で焼かれるがいい、チャーリー・プリンス。";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep4");
		break;
		
		// дон Энрико - народный мститель
		case "enrico":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_01.wav");
            dialog.text = "この世で俺にこれほどの喜びを与えてくれるものは、箱の中でネズミどもが互いに食い合うのを眺めることくらいだぜ！\n最後に生き残るのは、一番強くて一番醜いネズミだけだ。あとはそいつを絞め殺すだけさ……";
			link.l1 = "うおっ！てめえ、誰だ！？";
			link.l1.go = "enrico_1";
		break;
		
		case "enrico_1":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_02.wav");
            dialog.text = "俺はドン・エンリコだ。イギリスのクズどもは俺をフォックスと呼び、オランダ人はフォス、フランス人はルノーと呼ぶ。 だが、俺はスペインのあだ名――ゾロの方が気に入ってるぜ。俺は弱き民を苦しめ、恐怖に陥れる悪党どもを裁く者だ。\n今日の裁きでは、マーカス・タイレックスの四人の海賊――大胆なジェフリー、カトラスのペリー、レプラコーンのルーク、そしてチャーリー・プリンス――こいつらがメリダとカルタヘナでの虐殺の元凶だ。最後の野郎、ハンサム・ジーンと呼ばれる奴はここに現れなかった。 お前らの中で一番賢い奴なんだろうな。";
			link.l1 = "何だって！？";
			link.l1.go = "enrico_2";
		break;
		
		case "enrico_2":
            dialog.text = "お前はクズ野郎だな、チャーリー・プリンス。でも馬鹿じゃねえ。俺はもう全部見抜いてたぜ。これはな、 俺が仕掛けた罠なんだよ。偽の地図や書類、言葉、金銀の約束を使ってな。俺はお前ら全員をこの地下牢に誘い込み、 お互いを滅ぼさせた。お前らの醜い性質――嫉妬、強欲、卑劣さ、そして良心のなさに駆られてな。本当にこれは天罰だったぜ！";
			link.l1 = "カミラ……あの娘には何かおかしいところがあると気づくべきだったぜ！";
			link.l1.go = "enrico_3";
		break;
		
		case "enrico_3":
            dialog.text = "カミラという名の娘は、父親と兄たちと共にカルタヘナで穏やかな生活を送っていた。結婚を控えていたその時、 お前とその悪党どもが町を襲撃したのだ。お前の海賊どもは彼女の大切な者たちを皆殺しにし、 彼女は復讐のためなら何でもすると誓った。その役目は彼女にとってあまりにも過酷だった。 家族を殺した張本人と寝ることさえ強いられたのだ。その最中、彼女が何を感じていたかなど、 想像するだけでぞっとする。\n哀れな娘は教会で何日も赦しを請い祈り続けた。お前が与えた血塗られたドゥブロン金貨も、 お前の襲撃で最も苦しんだ被害者たちに寄付した。今では修道院にいる、哀れな魂だ。 お前は彼女の人生を台無しにしたんだ、このクズ野郎！よく考えろ！お前が辱め、未亡人にしたカミラやイサベラ、 ロシータが何人いる！？お前ら悪党どもが殺し、拷問したフアンやカルロス、ペドロがどれだけいる！？\nメリダを思い出せ！町の長に火を放たないと約束したくせに、結局町全体を焼き払ったことを思い出せ！";
			link.l1 = "俺はそんなつもりじゃなかったんだ！屋敷を出た時には、もう火の手があちこちに回ってたんだ。 俺が命じたわけじゃねえ……";
			link.l1.go = "enrico_4";
		break;
		
		case "enrico_4":
            dialog.text = "お前は自分の海賊どもの所業に責任があるんだ。死人たちがお前の首にぶら下がっていて、やがて地獄へ引きずり込むぞ！ ";
			link.l1 = "さあ来いよ！ん？俺と勝負しろ！これが望みなんだろ！？だったらやってやるぜ！";
			link.l1.go = "enrico_5";
		break;
		
		case "enrico_5":
            PlaySound("Voice\English\LE\Zorro\Don_Enriko_03.wav");
            if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				dialog.text = "いや、チャーリー・プリンス。武器に手を伸ばすな、無駄だ……お前を殺すのは簡単だが、貴様のようなクズには速い死など生ぬるい。ここで永遠に牢に閉じ込めてやる。 お前が入ってきた扉は外から石で塞がれているし、俺の後ろの扉も今から塞がれる。それに、頑丈な鉄格子が守っている。 これで終わりだ、この二つの扉以外に脱出の道はない\nなんだと……全部の扉に鍵をかけたはずだ！";
				link.l1 = "……何が起きてるんだ……";
				link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag");
			}
			else
			{
				dialog.text = "いや、チャーリー・プリンス。武器に手を伸ばすな、無駄だ……お前を殺すのは簡単だが、そんなクズには速い死など生ぬるい。お前はこの地下牢に永遠に閉じ込められるんだ。 お前が入ってきた扉は外から石で塞がれているし、俺の後ろの扉もすぐに塞がれる。それに、頑丈な鉄格子が守っている。 つまり、この二つの扉以外に出口はない\n下には水があるから、しばらくは生きていられるだろう。その間に自分の所業をじっくり反省するんだな。 ここで一人きり、暗闇の中で、餓死するか狂う前に自分の罪を悔い改めるかもな\n最後に一つ――下の財宝は偽物だ。金塊はただの色付きの鉛だし、ドゥブロン金貨は本物だが、ほんの少しだけで、 宝箱の中の石を隠すためにあるだけだ。海賊にはふさわしい結末だろう？お前たちは偽物の財宝のために殺し合ったんだ、 プリンス。これでお別れだ。自分の罪深い魂のために祈るんだな、チャーリー・プリンス……まだ祈り方を覚えていれば、だがな。";
		// belamour legendary edition -->
				link.l1 = "俺は今、マーカス・タイレックスの先遣隊を全滅させたばかりだぜ！ こんな錆びた鉄格子で俺を止められると思ってんのか？！お前の頭でぶち壊してやるよ！";
				link.l1.go = "enrico_5a";
				link.l2 = "もしかしたら俺が悪かったのかもしれねえ。だが、俺は諦めねえぞ、聞こえるか！？必ず道を見つけてやる、 俺はいつもそうしてきたんだ！";
				link.l2.go = "enrico_5b";
			}
		break;
		
		case "enrico_5a":
			AddCharacterHealth(pchar, 5);
			AddCharacterExpToSkill(pchar, "FencingL", 400);
			AddCharacterExpToSkill(pchar, "FencingS", 400);
			AddCharacterExpToSkill(pchar, "FencingH", 400);
			AddCharacterExpToSkill(pchar, "Pistol", 400);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		
		case "enrico_5b":
			AddCharacterExpToSkill(pchar, "Leadership", 1200);
			ChangeCharacterComplexReputation(pchar, "nobility", 15);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		// <-- legendary edition
		
		case "enrico_Tonzag_1":
			dialog.text = "あんたの言う通りだ、この扉は古くても頼りになる。\n門を下ろさずにいてくれて感謝するぜ――あれを下ろされてたら、ちょっとは足止めされたかもしれねえが、長くはかからなかっただろうな。";
			link.l1 = "エルキュール・トンザグ、ハゲのガストン！お前みたいな奴が王子やその仲間どもに味方するとは思ってたぜ。 ここでお前に会えるとは、俺も運がいいな。";
			link.l1.go = "enrico_Tonzag_2";
			sld = CharacterFromID("Zorro");
			CharacterTurnToLoc(sld, "quest", "door");
		break;
		
		case "enrico_Tonzag_2":
			dialog.text = "運がいいって？死に急いでるなら別だが……まあ、あんたがそうじゃねえと思ってたぜ。だって、あいつと向き合う代わりに飢え死にさせたんだからな。";
			link.l1 = "俺を臆病者呼ばわりか？馬鹿なやつだな。俺は殿下にも言ったが、あいつには死など生ぬるい罰だ。 俺の相手になるような奴じゃねえ。";
			link.l1.go = "enrico_Tonzag_3";
		break;
		
		case "enrico_Tonzag_3":
			dialog.text = "「それに、お前じゃ俺には敵わねえよ、ドン。」";
			link.l1 = "十年前なら？もちろんだ。今は？とても無理だ。さらに……";
			link.l1.go = "enrico_Tonzag_4";
		break;
		
		case "enrico_Tonzag_4":
			dialog.text = "それで何だよ？何をもったいぶってやがる？まあ、その仮面舞踏会みたいな面を見りゃ……俺を諦めるのはまだ早いんじゃねえか？";
			link.l1 = "お前はドアを壊したが、力任せだけじゃ俺には通用しねえぞ。反射神経はどうだ？見えるか？その片目で。 俺はまだ両目があるからな。";
			link.l1.go = "enrico_Tonzag_5";
		break;
		
		case "enrico_Tonzag_5":
			dialog.text = "まあ、とりあえず今のところはな。へっへっ。";
			link.l1 = "ポルトベロのために、お前には王子よりもひどい運命がふさわしいぜ！";
			link.l1.go = "enrico_Tonzag_6";
		break;
		
		case "enrico_Tonzag_6":
			dialog.text = "おお、俺がやったことを聞いたのか？しばらくはお前らの仲間内で噂話が続くだろうな。じゃあ、 俺がどんな目に遭ったかも知ってるわけだな。";
			link.l1 = "お前も年を取ったな、トンザグ。今度こそ、その傲慢さが命取りになるぜ。ああ、ただの噂じゃねえ――カルタヘナもメリダもお前の仕業だろう。ポルトベロと同じようにな。";
			link.l1.go = "enrico_Tonzag_7";
		break;
		
		case "enrico_Tonzag_7":
			dialog.text = "お世辞として受け取ってもよかったが、いや、俺の仕業じゃねえ。遠目には似て見えるかもしれねえが、素人臭すぎる。 とはいえ、ポルトベロでも……事件はあったもんだ。";
			link.l1 = "「事件だと！？あの日、一人が死んだ……そしてあの虐殺を始めたのはお前だ。たとえ全員を自分の手で殺していなくても、俺はお前を責めるぜ。あらゆる『事件』 の責任はお前にあるんだ。」";
			link.l1.go = "enrico_Tonzag_8";
		break;
		
		case "enrico_Tonzag_8":
			dialog.text = "一人だと？あの日は多くの者が死んだんだ。もっと詳しく言え。";
			link.l1 = "本当に、そんなことが言えるなんて、あんたには心がないんだな！\nだが答えてやるよ――あんたが殺してはいけなかった人だ。俺の父親、ドン・デ・ラ・ベガさ。\nもし父が生きていたなら、俺はこんな道を選ばなかったし、あんたたちもまだ生きていただろうよ。";
			link.l1.go = "enrico_Tonzag_9";
		break;
		
		case "enrico_Tonzag_9":
			dialog.text = "黙れ、小僧。俺の愛しい女房も……あそこで死んだんだ。";
			link.l1 = "弔いの言葉が欲しいのか？そんなものはやらねえよ。それがお前への神の罰だ。どうやらお前にも心があるらしいな――ちっぽけで真っ黒なやつがよ。だが俺の剣で、その心を見つけてやるぜ。";
			link.l1.go = "enrico_Tonzag_10";
		break;
		
		case "enrico_Tonzag_10":
			dialog.text = "ああ、俺の心について大げさに言うなよ。俺よりひどい目に遭ったと思ってるなら、それは勘違いだぜ。";
			link.l1 = "俺がただの金持ちの坊ちゃんで、金を無駄遣いしてるだけだと思ってるのか？いいか、 俺は博打や女に一枚たりともドゥブロンを使っちゃいねえ！全部、お前みたいな奴らとの戦いにぶち込んで、 命を賭けてきたんだぜ！";
			link.l1.go = "enrico_Tonzag_11";
		break;
		
		case "enrico_Tonzag_11":
			dialog.text = "それで何になるんだ？あまりうまくいってるようには見えねえな。交易路にはまだ海賊どもがうようよしてるぜ。 お前はたった一人で戦ってるが、あいつらはまるで軍団じゃねえか。";
			link.l1 = "誰かがやらなきゃならないんだ。少なくとも誰かがな。もしかしたら、たった一人の海賊船長を殺すことで、 何人かの命を救えるかもしれない。";
			link.l1.go = "enrico_Tonzag_12";
		break;
		
		case "enrico_Tonzag_12":
			dialog.text = "愚かだな。理想主義者だ。そして……ある意味では高貴だとも言えるが、お前のやり方を見ればそうも言えん。敵と同じく不名誉だ。結局のところ……お前も大して変わらん。";
			link.l1 = "俺に説教するな！名誉なんざ、その掟に従う奴らのもんだ。お前のことは分かってる。俺もお前と同じ考えだ。そして、 俺は裁く。";
			link.l1.go = "enrico_Tonzag_13";
		break;
		
		case "enrico_Tonzag_13":
			dialog.text = "あんたの言う通りだ。お前に教えるなんて無駄だな。だから、穏便には別れられねえ。だが、ドン・エンリコ、 お前なんかに興味はねえよ。俺の時間を割く価値もねえ。";
			link.l1 = "「どういう意味だ…」";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag2");
		break;
		
		case "enrico_Tonzag_14": // после выстрела в Зорро в подземелье
            dialog.text = "大丈夫ですか、船長？気をつけろと警告しましたよ。俺の直感に従うべきでしたね。";
			link.l1 = "ああ、大丈夫だ。ありがとう、エルキュール。ちょっとだけ……";
			link.l1.go = "enrico_Tonzag_15";
		break;
		
		case "enrico_Tonzag_15":
            dialog.text = "…驚いたか？正直に言ってもいいんだぜ――お前くらいの年でこんな状況なら普通のことさ。それに、あのドンはかなりの策士だからな。";
			link.l1 = "ああ。だけど、あいつはお前を怖がってたみたいだな。それには驚いたぜ。けど、そのおかげで俺も正気に戻った。\nところで、あいつはまだ生きてるのか？そうみたいだな。あんた、あいつに背中を向けて立ってる場合じゃねえぞ。";
			link.l1.go = "enrico_Tonzag_16";
		break;
		
		case "enrico_Tonzag_16":
            dialog.text = "生きてはいるが、気絶している。意識を取り戻しつつある。胴じゃなくて頭を狙うべきだったな――どうやらこの貴族のイダルゴ、上着の下に軽いが頑丈な胸甲を着てやがった。へっ、 フリートウッドでさえ普通のプールポワンしか着てなかったのによ。そうじゃなきゃ、ここはもう血の海になってたぜ。";
			link.l1 = "「で、どうしてここに来たんだ？あいつと同じ場所か？」";
			link.l1.go = "enrico_Tonzag_17";
		break;
		
		case "enrico_Tonzag_17":
            dialog.text = "今はそんな暇はねえ。あいつはすぐに立ち直るさ。とにかく、まずこの門を持ち上げるぜ。";
			link.l1 = "俺たち……なんだと？？確かにお前はヘラクレスかもしれねえが……";
			link.l1.go = "enrico_Tonzag_18";
		break;
		
		case "enrico_Tonzag_18":
            dialog.text = "俺の若い頃の連中はみんなタフに鍛えられてたもんだ。こいつの蝶番はピンが短いな。さあ、手を貸してくれ、船長――俺もヘラクレスかもしれねえが、もう歳には勝てねえんだよ。";
			link.l1 = "よし、三つ数えたらだ！せーの、持ち上げろ！";
			link.l1.go = "enrico_Tonzag_19";
		break;
		
		case "enrico_Tonzag_19":
            DialogExit();
			locCameraSleep(true);
			LAi_FadeLong("Mtraxx_RetributionEnricoAndTonzag6", "");
		break;
		
		case "enrico_Tonzag_20": // окружили Зорро
            dialog.text = "俺の計画を全部ぶち壊して勝ったと思ってるのか？それは確かに予想外だったが、まだまだ俺には切り札が残ってるぜ！";
			link.l1 = "その服の下に着てる軽いキュイラス、いいじゃねえか。なんで上に重装備を着ねえんだ？ コートを見せびらかしたいだけか？";
			link.l1.go = "enrico_Tonzag_21";
		break;
		
		case "enrico_Tonzag_21":
            dialog.text = "俺は乙女じゃねえよ、王子。俺の理由は実用的なだけさ――胸当てを全部着けると動きが鈍くなりすぎるんだ。やり方は人それぞれだぜ。";
			link.l1 = "それでも俺はここにいる、フランス人だ。スペイン野郎と違って、鎧を着るのにももう慣れてるぜ。皮肉なもんだな。\nで、これからどうする？俺たちを捕まえることはできなかったな。あんたは何もかも準備してきた……決闘も計画に入ってたのか？それとも剣も鎧も、本当の戦い以外のためのものか？";
			link.l1.go = "enrico_Tonzag_22";
		break;
		
		case "enrico_Tonzag_22":
            dialog.text = "俺のことも臆病者呼ばわりするつもりか？\nさっきも言ったが、お前には決闘で死ぬより長い苦しみがふさわしいんだ。\nここ地上で自分の罪をすべて味わい、理解する時間もないまま死んでどうする？";
			link.l1 = "地獄への道は善意で舗装されている、と言うじゃねえか…\nそれに、犠牲者を苦しめることで自分の魂も汚れちまうんじゃねえのか？";
			link.l1.go = "enrico_Tonzag_23";
		break;
		
		case "enrico_Tonzag_23":
            dialog.text = "決してない。絶対にない。俺は自分自身と信念に忠実であり続けるからだ。";
			link.l1 = "あはは、俺たちとは違うってわけだな。お前は俺たちのことを、名誉のかけらもない卑劣なクズだと散々 言ってきたじゃねえか。だったら、その期待に応えてやろうじゃねえか。俺たち自身でお前を始末するぜ。みんなでな。";
			link.l1.go = "enrico_Tonzag_24";
			link.l2 = "ドン・エンリコ、あなたに提案があります。ここで、今すぐ決闘を申し込みます。貴族同士として。";
			link.l2.go = "enrico_Tonzag_26";
		break;
		
		case "enrico_Tonzag_24":
            dialog.text = "ふむ。そうじゃなきゃ、お前に勝ち目はねえだろう。トンザグは手強いが……まずはお前から片付けてやるぜ。";
			link.l1 = "あいつがそんなことをさせるわけねえだろ。";
			link.l1.go = "enrico_Tonzag_25";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "enrico_Tonzag_25":
            DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, false);
			LAi_SetCheckMinHP(sld, 1, true, "TonzagRanen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_26":
            dialog.text = "お前が？貴族だと？「王子」かもしれねえが、貴族の血なんて一滴も流れてねえだろうよ。";
			link.l1 = "お前は本当の名前を俺に明かしたな。なら、俺も名乗ろう。俺はシャルル・ド・モールだ。\nそして俺たちは互いの名誉を十分に傷つけ合った。どちらにも決闘を求める権利があるはずだ。覚悟しろ、エンリコ旦那。 ";
			link.l1.go = "enrico_Tonzag_27";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "enrico_Tonzag_27":
            dialog.text = "だが、あとで自分の決断を後悔するんじゃねえぞ。";
			link.l1 = "俺はこれまでに何度も自分の決断を後悔してきたが、今回は違うぜ。構えろ！";
			link.l1.go = "enrico_Tonzag_28";
		break;
		
		case "enrico_Tonzag_28":
			DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_29": // после победы над Зорро
            dialog.text = "大丈夫ですか、船長？あの高貴なイダルゴは胸当てだけじゃなく、剣にも毒を塗っていました。さあ、これをどうぞ。 俺はジャングルを歩くとき、いつもこれを何本か持ち歩いてるんです――いつ蛇に噛まれるか、あるいはインディオが毒矢を飛ばしてくるかわかりませんからね。";
			link.l1 = "ありがとう、Hercule。私は大丈夫だ。君がちょうど来てくれたおかげで、気を取り直せたよ。";
			link.l1.go = "enrico_Tonzag_30";
			GiveItem2Character(PChar, "potion3");
			LAi_UseAtidoteBottle(pchar);
			LAi_UseAtidoteBottle(npchar);
		break;
		
		case "enrico_Tonzag_30":
            dialog.text = "気にすんな。行くぞ、ここから出してやるぜ――あいつが入口を石で塞いだって言ってたが、俺は別の抜け道を見つけたんだ、近道だぜ。";
			link.l1 = "教えてくれ、エルキュール……ポルトベロで一体何があったんだ？それに、いつのことだ？";
			link.l1.go = "enrico_Tonzag_31";
		break;
		
		case "enrico_Tonzag_31":
            dialog.text = "今日はその話をする気分じゃねえんだ。だが、いつかワインか、もっと強い酒でも飲みながら話すかもな。 今はここを出よう――あのガキの言う通り、俺も年を取ったもんだ。船で休みたいぜ。";
			link.l1 = "それじゃあ、案内してくれ。";
			link.l1.go = "enrico_Tonzag_32";
		break;
		
		case "enrico_Tonzag_32":
            DoQuestReloadToLocation("Shore10", "goto", "goto2", "Mtraxx_RetributionEnricoAndTonzag8");
		break;
		
		case "mishelle_sleep":
            dialog.text = "教えてくれ、兄弟よ――どうしてそんな化け物になっちまったんだ？俺が「海賊と親しくなれ」と言った時、町を焼き払い、罪もない市民を殺し、 女を拷問しろなんて意味じゃなかった。戦争だって名誉と誇りを持って戦えるはずだろう\nお前は我が家の恥さらしだ。父上がここにいなくてよかったよ――自分の息子が海賊で盗賊になったと知ったら、恥ずかしさで死んじまっただろうからな！";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep5");
		break;
		
		case "mishelle_sleep_1":
            dialog.text = "兄さん！兄さん！\n聞こえるか？\n二つの扉のうち一つの後ろに通路があるんだ。その扉は開けられる。鍵がすぐ近くにあるぞ！\n階段で見つけてくれ。階段だ！..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep7");
		break;
		
		case "terrax_sleep":
            dialog.text = "ハハハ、やあ、俺の勇敢な悪党！なんでそんなにしけた顔してるんだ？海も、金も、ラム酒も、女もある――他に何が足りねえってんだ？最初に会った時のこと、覚えてるか？あの時言っただろ――火薬の匂いも、血の川も恐れねえ奴が欲しいってな。お前は俺の期待を全部超えてくれたぜ！本物の海賊になったな、 チャーリー・プリンス！ハハハ！";
			link.l1 = "";
			link.l1.go = "terrax_sleep_1";
			locCameraSleep(false);
		break;
		
		case "terrax_sleep_1":
            dialog.text = "本物の血塗られた海賊だぜ！あっはっはっは！";
			link.l1 = "";
			link.l1.go = "terrax_sleep_2";
		break;
		
		case "terrax_sleep_2":
			Mtraxx_RetributionSleepSkeletons();
            dialog.text = "ウアハハハハハハ！！！";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6");
		break;

		// belamour legendary edition -->
		case "SlavesTrader":
            dialog.text = "お前は誰だ？ここで何をしている？さっさと答えろ！";
			link.l1 = "俺はファディから来た、黒い骨の一団を受け取りに来たんだ。あいつが前もって知らせておくべきだったろう。";
			link.l1.go = "SlavesTrader_1";
		break;
		
		case "SlavesTrader_1":
            dialog.text = "ははっ！見た目なんて気にするな、友よ。お前のことはちゃんと分かってるぜ。 モスコビトがすごく詳しく特徴を教えてくれたからな。あいつからも、値段に気を悪くしないでくれって頼まれてる。 さて、前金を差し引いて、お前の借りは銀貨一万だ。金貨で払うなら、たった五十ドゥブロンでいい。さあ、どうする？ ぐずぐずするなよ！\n";
			if(PCharDublonsTotal() >= 50)
			{
				link.l1 = "俺は50ドゥブロン払うぜ。そっちの方が儲かるからな。";
				link.l1.go = "SlavesTrader_Dub";
			}
			if(sti(Pchar.money) >= 10000)
			{
				link.l2 = "一万ペソ払うぜ。";
				link.l2.go = "SlavesTrader_P";
			}
			link.l3 = "すまないが、今は奴隷を買う余裕がないんだ。";
			link.l3.go = "SlavesTrader_X";
		break;
		
		case "SlavesTrader_Dub":
			RemoveDublonsFromPCharTotal(50);
            dialog.text = "それは素晴らしい。部下に合図して荷を運ばせろ。";
			link.l1 = "かしこまりました。";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_P":
			AddMoneyToCharacter(pchar, -10000);
            dialog.text = "それは素晴らしい。部下に合図して品物を運ばせろ。";
			link.l1 = "かしこまりました。";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_End":
			DialogExit();
			AddQuestRecord("Roger_3", "25");
            pchar.questTemp.Mtraxx.GiveMeSlaves = "Deal";
			SetCharacterGoods(pchar, GOOD_SLAVES, (GetCargoGoods(pchar, GOOD_SLAVES) + 50));
			Log_Info("Fifty slaves shipped to "+PChar.Ship.Name);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		
		case "SlavesTrader_X":
            dialog.text = "まあ、好きにしな。こんな品には必ず買い手がつくもんだぜ。じゃあな、友よ。";
			link.l1 = "さようなら。";
			link.l1.go = "SlavesTrader_EndX";
		break;
		
		case "SlavesTrader_EndX":
			DialogExit();
			AddQuestRecord("Roger_3", "26");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		// диалог Гаспара Златозубого Xenon
		case "GasparGold_meeting":
            dialog.text = "ごきげんよう、船長。君はチャーリー・プリンスだろう？間違っていなければな。\n心配するな、俺の部屋の壁には耳なんてついてねえよ。\n正直、君の名前なんてどうでもいい。\n大事なのは、君が俺に推薦されたってことだ。それなら商売ができるってわけだ。";
			link.l1 = "あんたにも挨拶するぜ、ガスパール“金歯”。まあ、正直あんたの呼び名なんざどうでもいいがな。ところで、小物を買いたいって話を聞いたんだが？";
			link.l1.go = "GasparGold_meeting_01";
		break;
		
		// ---> andre39966, Фриплейный Гаспарито
		case "GasparGold_meeting_sandbox":
			dialog.text = "ようこそ。私はガスパール・パルマンティエです。ご用件は何でしょうか？";
			link.l1 = "やあ、ガスパール。私は船長 " + GetFullName(pchar) + " だ。地元の酒場の主人から来た。君がガラクタを買い取っているって噂を聞いたんだ。";
			link.l1.go = "GasparGold_meeting_01";
			link.l2 = "やあ、金歯さん。君は光るものなら何でも買い取るって聞いたよ。雷に誓って、俺たち気が合いそうだな。";
			link.l2.go = "GasparGold_meeting_wrong";
		break;

		case "GasparGold_meeting_wrong":
			dialog.text = "失礼ですが、人違いではありませんか？警備を呼ぶ前にここを立ち去ってください。";
			link.l1 = "…くそっ、わかったよ…";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gaspar_sandbox_repeat";
		break;

		case "Gaspar_sandbox_repeat":
			dialog.text = RandPhraseSimple("先ほど退室をお願いしましたよね？", "無駄話に付き合っている時間はありません。放っておいてください。", "あなたの無礼には驚きました。まだ私を煩わせるつもりですか？");
			link.l1 = "落ち着けよ、友よ。酒場の主人の紹介だ。";
			link.l1.go = "Gaspar_Alternative";
			link.l2 = "もうごまかすな！お前が宝石を買ってるのは知ってるぞ！";
			link.l2.go = "Gaspar_Angry";
		break;

		case "Gaspar_Angry":
			dialog.text = "そのようなことはしていないと申し上げたはずです。追い出される前にお引き取りください。";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gaspar_sandbox_repeat";
		break;

		case "Gaspar_Alternative":
			dialog.text = "それなら話は別ですな、船長。お目当ての場所はここで間違いありません。さて、宝石をいくつか売りたいのですか？";
			link.l1 = "まあ、“俺の”ってのは早計だったな。へっへっへ。";
			link.l1.go = "GasparGold_01";
			NextDiag.TempNode = "GasparGold";
		break;
		// <--- andre39966, Фриплейный Гаспарито
		
		case "GasparGold_meeting_01":
            dialog.text = "その通りだ。他の誰よりもいい値で買い取ってやるぜ。まあ、質屋くらいだな、俺より高く買うのは。 でもあいつらはあまり買わねえしな。お前が売りたい物は全部買う用意があるぜ。 貴重品をわざわざ俺のところまで持ってこなくてもいいんだ。裏口から人目につかねえ桟橋に出られるようになってる。 船の宝箱にしまってあるガラクタも、遠慮なく全部俺に売ってくれよ。\n";
			link.l1 = "おお、それは素晴らしい！お前と知り合えて嬉しいぜ。";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold_story":
			npchar.mtraxx.story = true;
            dialog.text = "それは俺の個人的な事情だ。詮索しないでもらいたい。全部ちゃんと管理してるから、安心して俺と取引してくれ。 他のことはお前には関係ないぜ。";
			link.l1 = "まあ、危険がないのが一番大事だぜ！もう一つ聞きたいことがあるんだが…";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold":
			NextDiag.TempNode = "GasparGold";
            dialog.text = "どうした？何か手伝えるか？余った真珠や宝石を処分したいのか？それとも金や銀、宝飾品か？全部買い取るぜ。";
			if(!CheckAttribute(npchar,"mtraxx.story"))
			{
				link.l1 = "なあ、お前、盗品の買い手ってどんな気分だ？役人にビビったりしねえのか？";
				link.l1.go = "GasparGold_story";
			}
			link.l2 = "ここにちょっとした物があるんだ……現金と交換したいんだぜ。";
			link.l2.go = "GasparGold_01";
		break;
		
		case "GasparGold_01":
            dialog.text = "さて、取引をしようか。ドゥブロンか、それともペソか？";
			link.l1 = "ペソで行こうぜ――ドゥブロンは要らねえ。普通の金ならどこでも通用するんだ。";
			link.l1.go = "GasparGold_peso";
			link.l2 = "その通りだぜ――俺が欲しいのはドゥブロン金貨だけさ。だから、それ以外じゃ売らねえぞ。";
			link.l2.go = "GasparGold_dub";
			link.l3 = "今は売る物は何もないんだ。\nただ、俺が貴重な品を手に入れた時に、あんたが買う気でいるか確かめたかっただけさ。\nまた今度な！";
			link.l3.go = "exit";
		break;
		
		// окно торговли
		case "GasparGold_peso":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "GasparGold_dub":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		// Диалоги после угроз вождю индейцев Кумване
		case "MeridaObsuzhdenie_Bad_1":
            dialog.text = "まだ脅しに頼ってるのかい、船長？外にいてもお前の脅しが聞こえてきたぜ。";
			link.l1 = "奴らには選択肢を残さなかった。俺はこのタゴファの助けを得るために、奴の女房に贈り物までしたんだが、 あいつは話す耳すら持たなかった。今度は酋長に任せてみるさ。もしあの頑固者どもを説得できなかったら、 俺が自分の手で酋長の心臓を引き裂いてやる。\nところで、ヤハフって誰だ？";
			link.l1.go = "MeridaObsuzhdenie_Bad_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Bad_2":
            dialog.text = "インディアンたちとの関係を悪くするべきじゃなかったんだぜ。俺たち海賊の味方は剣と船だけだ。\nだが、これはお前の決断だから、仕方ねえな。それにヤハフは悪しき悪魔だ。そいつについては他に何も知らねえ。";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_3";
		break;
		
		case "MeridaObsuzhdenie_Bad_3":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Bad_4", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_4":
            dialog.text = "説得なんぞに時間を使うのは愚かだぜ、レプラコーン。\nそれとも、お宝を諦めてインディアンたちと仲良くしたいってのか？";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_5";
		break;
		
		case "MeridaObsuzhdenie_Bad_5":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Bad_6", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_6":
            dialog.text = "俺は両方欲しいぜ。";
			link.l1 = "両陣営にいい顔をするのはもう通用しない。今回はそうはいかん。議論はもう十分だ、すべてはすでに決まっている。 明日、酋長がタゴファの決断を伝えてくれるだろう、俺を失望させないことを願うぜ。もしそうでなければ……俺は極端な手段を取らざるを得なくなる。それはできれば避けたいがな、もちろん。";
			link.l1.go = "MeridaObsuzhdenie_Bad_7";
		break;
		
		case "MeridaObsuzhdenie_Bad_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait"); //разрешить отдыхать
			ChangeShowIntarface();
			
            sld = characterFromId("Lepricon");
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "MeridaObsuzhdenie_Good_1":
            dialog.text = "さて、どうなってる？案内人はつくのか？";
			link.l1 = "いいや、ジャン、無理だ。酋長も部族全員もカポン族を悪魔が香を恐れるように怖がってるんだ。\nどうやら俺たちの計画は諦めるしかなさそうだぜ。";
			link.l1.go = "MeridaObsuzhdenie_Good_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Good_2":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Good_3", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_3":
            dialog.text = "この展開にはTerraxも喜ばねえだろうな。";
			link.l1 = "俺がこんな結末になってめちゃくちゃ嬉しいと思ってるのか？臆病なロコノ族はカポング族と関わりたがらねえ。 説得にも報酬にも全然乗ってこないんだ。";
			link.l1.go = "MeridaObsuzhdenie_Good_4";
		break;
		
		case "MeridaObsuzhdenie_Good_4":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Good_5", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_5":
            dialog.text = "ならば脅しを使うしかねえな。あいつらにこう言え――「てめえらのクソ村を焼き払って、生き残った奴は誰かが案内するまで拷問してやる」ってな。";
			link.l1 = "ジャン、お前は完全に正気を失ったのか？俺は罪のない人々の家を焼き払ったりしないぜ。 ましてや拷問なんて絶対にしない。";
			link.l1.go = "MeridaObsuzhdenie_Good_6";
		break;
		
		case "MeridaObsuzhdenie_Good_6":
            dialog.text = "チャールズ・プリンスは模範的な恩人だ。お前からそんな優しさがあふれ出るとは思わなかったぜ。";
			link.l1 = "これは優しさじゃねえよ、イケメン。まあ、インディアンを半殺しにして拷問すりゃ、 復讐心で俺たちをカポン族の手に導いて、その後は自分しか知らねえ道を使って消えちまうだろう。 そんなことで仲間の命を危険にさらす気はねえ。";
			link.l1.go = "MeridaObsuzhdenie_Good_7";
		break;
		
		case "MeridaObsuzhdenie_Good_7":
            dialog.text = "その場合は、レプラコーンと俺は行くぜ。これはマラカイボのプランテーションから助けてくれた礼の五万銀貨だ。 新しい船のために貯めてたんだ。\nそれと忠告だが、しばらくはマーカスの目に触れないようにしとけ。\nじゃあな、チャールズ・プリンス。";
			link.l1 = "さようなら、Jean。";
			link.l1.go = "MeridaObsuzhdenie_Good_8";
			AddMoneyToCharacter(pchar, 50000);
		break;
		
		case "MeridaObsuzhdenie_Good_8":
            DialogExit();
			chrDisableReloadToLocation = false;
			ChangeShowIntarface();
			AddQuestRecord("Roger_5", "8b");
			CloseQuestHeader("Roger_5");
			
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_type_actor_Reset(sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "First time";
		break;
		
		// Немезида. Диалоги с офицерами после взрыва бочонков с порохом
		// Тонзаг
		case "Nemezida_Tonzag_1":
            dialog.text = "「この辺りの連中が今すぐ押し寄せてくるぞ！あの木を爆破したのは本当に良かったのか、船長？」";
			link.l1 = "くそっ！みんなが斧で働いてた方がよかったかもしれねえな……だが、今さら遅いぜ。";
			link.l1.go = "Nemezida_Tonzag_2";
		break;
		
		case "Nemezida_Tonzag_2":
            dialog.text = "そうだな。今あるもので何とかするしかねえ。準備しろ。";
			link.l1 = "お前もだ、エルキュール。";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tonzag_3":
            dialog.text = "まだこっちに向かってきてるな。じゃあ、こいつらも片付けるか？\n";
			link.l1 = "奴らに終わりがなかったらどうするんだ？俺たちはこんな厄介ごとのために来たんじゃねえ。";
			link.l1.go = "Nemezida_Tonzag_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_4":
            dialog.text = "そうだな、すべてには終わりがある……だが、お前の言う通りだ。退却しよう。しかも急いでな。";
			link.l1 = "急ごうぜ！";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tonzag_5":
            dialog.text = "しつこい連中だ、とうとう追いつかれちまったな。ここに小道がある、入ってみるか？ここなら踏ん張りやすいぜ。";
			link.l1 = "待て、エルキュール。聞こえるか？中に誰かいるぞ。お前と仲間たちはここを頼む。 俺は中に入って宝を取られる前に動く。偶然入り込んだ奴なんているとは思えねえからな。";
			link.l1.go = "Nemezida_Tonzag_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_6":
            dialog.text = "わかった。でも気をつけろよ、なんだか嫌な予感がするんだ。";
			link.l1 = "お前もな！俺はあっちに行くぜ。";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Tonzag_7": // на берегу
            dialog.text = "何か言いたいことがあるのか、船長？船まで歩いてくる間ずっと考え込んでいたじゃねえか。";
			link.l1 = "そうだ。最近自分がしてきたことについて考えていたんだ。テラックスのこと、そして……それが俺をどこへ導いたのかも。兄弟を救うことに近づけたのか？それとも故郷に帰ることに……？";
			link.l1.go = "Nemezida_Tonzag_8";
		break;
		
		case "Nemezida_Tonzag_8":
            dialog.text = "ふむ。いい質問だな。で、お前の答えはどうなんだ？";
			link.l1 = "もう一つだけ質問だ。前に無駄だったなら、また無駄になるのか？テラックスは俺を助けてくれねえ。兄貴のことも、 トルトゥーガのこともな。";
			link.l1.go = "Nemezida_Tonzag_9";
		break;
		
		case "Nemezida_Tonzag_9":
            dialog.text = "たぶん違うな。あいつにはそんなもの必要ねえよ。今さら気づいたとは驚きだぜ。で、次は何を聞きたいんだ？";
			link.l1 = "なんで俺は今までずっとテラックスのために、まるで飼い犬みたいに後を追いかけて、火中の栗を拾ってやってたんだよ！ ？";
			link.l1.go = "Nemezida_Tonzag_10";
		break;
		
		case "Nemezida_Tonzag_10":
            dialog.text = "さて、それはいい質問だな。ちゃんとしたやつだ。今度こそ答えはあるのか？";
			link.l1 = "どちらかと言えば決意だな。今日は運が良かった。でも次も運が味方するとは限らねえ。引き際を知るのは大事だ。 そして……自分を大切にすることもな。もう十分だ。";
			link.l1.go = "Nemezida_Tonzag_11";
		break;
		
		case "Nemezida_Tonzag_11":
            dialog.text = "テラックスとの協力関係を終わらせることにしたのか？";
			link.l1 = "ああ。俺にはもっと大事なことがある。家族や仲間たちだ。奴らと一緒なら、俺は自分の目的を果たせる。 こんなやり方じゃない。たとえやったとしても……マーカスとは一緒じゃない。俺は自分自身の主人になる。自分で決めていくんだ。";
			link.l1.go = "Nemezida_Tonzag_12";
		break;
		
		case "Nemezida_Tonzag_12":
            dialog.text = "かつて俺が従っていた男が、また話し始めた。\nまた変な奴らに関わるんじゃねえぞ。\nかつて俺を惹きつけたその可能性を、無駄にするなよ。";
			link.l1 = "わかった、エルキュール。それと、改めて礼を言うぜ。今回は、本当に気づかせてくれてありがとう。 俺はもう王子の腰巾着じゃない。俺はシャルル・ド・モール、誇り高き貴族だ。さあ、船に乗ろう――お互い疲れてるだろうしな。";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Tonzag");
		break;
		
		// Книппель
		case "Nemezida_Knippel_1":
            dialog.text = "とんでもない爆発だったな、旦那――俺の船尾にキニッペルが直撃だ！まるでヴァルキリーの舷側砲撃みたいな音だったぜ。だが、 向こうの連中も気づいちまったみたいだな……";
			link.l1 = "気付いたなら、それはあいつらの問題だ。誰もここに呼んじゃいねえ。懲らしめてやる準備はできてるか、チャーリー？";
			link.l1.go = "Nemezida_Knippel_2";
		break;
		
		case "Nemezida_Knippel_2":
            dialog.text = "「いつでも準備万端だぜ、旦那！」";
			link.l1 = "素晴らしい。さあ、始めよう。";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Knippel_3":
            dialog.text = "申し訳ありませんが、もうすぐ仲間が増えそうです、船長。ご命令は？";
			link.l1 = "俺たちはもっと奥のジャングルに進んで隠れるぜ――全員を相手にするなんて無理だし、そもそもそんなために来たわけじゃねえからな。";
			link.l1.go = "Nemezida_Knippel_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_4":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "ああ、旦那。";
			link.l1 = "じゃあ、出発するぜ！";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Knippel_5":
            dialog.text = "奴らに見つかったぞ、船長！だが、ここで身を隠せるぜ――この道はどこかに続いてるみたいだが、誰かもう先にいる気がする。";
			link.l1 = "俺たちは避難なんかしねえ！どうやら他の奴らも宝の噂を嗅ぎつけたみたいだ。いいか、作戦だぜ： 俺が先に様子を見に行くから、あんたはここで仲間と一緒に奴らを食い止めてくれ！";
			link.l1.go = "Nemezida_Knippel_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_6":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "はい、旦那。";
			link.l1 = "素晴らしい。今すぐ下に向かうぜ！ここは任せたぞ。";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Knippel_7": // на берегу
            dialog.text = "けほっ、けほっ……大丈夫ですか、旦那？";
			link.l1 = "チャーリー！今さら俺のことを心配するなんて絶好のタイミングだな。無駄口は叩くな。お前、大丈夫か？ お前を船に残して、代わりにもっと人手を連れてくるべきだったぜ……";
			link.l1.go = "Nemezida_Knippel_8";
		break;
		
		case "Nemezida_Knippel_8":
            dialog.text = "ああ、かすり傷だよ、旦那。ちょっと疲れただけさ。あんな戦い方は若い頃でもしたことがねえ！だが、 あいつらにはしっかりお見舞いしてやったから、永遠にブドウ弾の音が耳から離れねえだろうよ！";
			link.l1 = "王立海軍、昔気質だな！チャーリー、お前はまるで獅子のように戦ったみたいだぜ。だが、立つのもやっとじゃねえか。 強がるな――傷はどれほどひどいんだ？";
			link.l1.go = "Nemezida_Knippel_9";
		break;
		
		case "Nemezida_Knippel_9":
            dialog.text = "大したことじゃありません、船長。ただの疲労です。あなたの後ろの入口はほとんどすぐに崩れてしまい、 俺たちは長い間あの連中を撃退し続けていました。結局、俺だけが傷を負って残されました。それで、 道を切り開いて応急処置を受けるためにここまで来たんです。";
			link.l1 = "なるほどな。まあ、今日はお前もよくやったぜ。だが俺は……失敗しちまった。俺たちはみんな騙されて、誰かの遊びのために争わされたんだ――宝なんて最初からなかったんだよ。俺だけが馬鹿だったわけじゃねえさ。";
			link.l1.go = "Nemezida_Knippel_10";
		break;
		
		case "Nemezida_Knippel_10":
            dialog.text = "失敗したのか？…でも生きてるじゃねえか、旦那。何があったんだ？逃げてきたのか？";
			link.l1 = "いや、でも少しは走る羽目になったぜ。悪いな、古い友よ、だが中で何があったかは誰にも話さねえ――たとえ一番の親友にもな。だが、必要な結論はちゃんと出したぜ。";
			link.l1.go = "Nemezida_Knippel_11";
		break;
		
		case "Nemezida_Knippel_11":
            dialog.text = "どんな結論だ、旦那？お前の考えはいつも理解できるわけじゃねえ。俺の哲学は単純だ――いいクルヴェリン砲と、マストに向けてのチェーンショットさ。";
			link.l1 = "教えてくれ、お前も最近の俺みたいにスペイン野郎を殺したことがあるだろう。昔、王立海軍にいた頃にな。 それから後も、フリートウッドと一緒にやったじゃねえか。";
			link.l1.go = "Nemezida_Knippel_12";
		break;
		
		case "Nemezida_Knippel_12":
            dialog.text = "やったさ。スペイン人もオランダ人も――他にもいろいろな奴らがいたぜ。ディックが昔言ってたが、俺たちの稼業は危険で骨が折れるもんだ。\nだが、なんでそんなことを聞くんだ？何が言いたいんだ？";
			link.l1 = "説明しよう。だがその前に、もう一つ質問だ。自分が何をしているのか、なぜそれをしているのか、疑ったことはあるか、 チャーリー？";
			link.l1.go = "Nemezida_Knippel_13";
		break;
		
		case "Nemezida_Knippel_13":
            dialog.text = "ふむ。自分では王冠のために動いていると思い込んでいた。命令のことを気に病んでも仕方ない仕事さ――どうせ従わなきゃならねえんだからな。";
			link.l1 = "王冠か……まあ、お前にはお前の理由があったんだろう。俺にはそれすらなかった――ミシェルにテラックスに近づけと言われただけさ。だが、あれだけ犠牲を払う価値があったのか？ 俺やあいつのためになったのか？ああ、ああ、ドンどもは好きじゃねえ……だが、俺たちも所詮人間だ。";
			link.l1.go = "Nemezida_Knippel_14";
		break;
		
		case "Nemezida_Knippel_14":
            dialog.text = "旦那、あんたの言いたいことがだんだん分かってきた気がするぜ。";
			link.l1 = "よし。教えてくれ、フリートウッドが去ったとき、もうオランダの商船に砲撃しなくて済むことを嬉しく思ったか？ あいつらの中には正直な連中もいたんだぞ。";
			link.l1.go = "Nemezida_Knippel_15";
		break;
		
		case "Nemezida_Knippel_15":
            dialog.text = "考えたこともありませんでしたよ、船長。でもこれだけは言わせてください――俺はずっとあんたと一緒に働くのが楽しかったんだ、旦那。もし嘘をついてたら、 首にカンニッペルを巻かれて地獄行きでかまいませんぜ！";
			link.l1 = "ははは、いいだろう。だが教えてくれ――お前は命令に従ってただけだが、どっちが辛かったと思う？それとも、誰にも強制されずに自分でやった俺の方か？";
			link.l1.go = "Nemezida_Knippel_16";
		break;
		
		case "Nemezida_Knippel_16":
            dialog.text = "わからねえよ、旦那……";
			link.l1 = "俺もだ。だが、そんなことはどうでもいい。大事なのは、もうテラックスとは一切関わりたくねえってことだ。 もうたくさんだ。チャーリー・プリンスは終わりだ。これからはシャルル・ド・モールだけだ。";
			link.l1.go = "Nemezida_Knippel_17";
		break;
		
		case "Nemezida_Knippel_17":
            dialog.text = "「でも、これは兄貴を救うお前の計画の一部じゃなかったのか？」";
			link.l1 = "そうだった。しかし結局、俺には何の助けにもならなかったんだ。だからもしまた同じようなことをやる羽目になっても――それは俺だけの決断だ。そして本当に自分の目的に近づける時だけだ。";
			link.l1.go = "Nemezida_Knippel_18";
		break;
		
		case "Nemezida_Knippel_18":
            dialog.text = "お前が何をしているのか分かっているといいがな、船長。テラックみたいになったり、 絞首台行きになったりしないことを祈るぜ。";
			link.l1 = "俺もそう願ってるぜ。だが、これからは俺の目的と利益が最優先だってことは確かだ。さて、お前の傷の手当てをしよう。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Лонгвэй
		case "Nemezida_Longway_1":
            dialog.text = "爆発で目立ったようです、船長閣下。敵の部隊がこちらに近づいてきているようです。";
			link.l1 = "くそっ！…あの木々をもっと上手く処理する方法があったと思うか？お前ならどうしたんだ？";
			link.l1.go = "Nemezida_Longway_2";
		break;
		
		case "Nemezida_Longway_2":
            dialog.text = "知らねえよ。だが、今やるべきことは分かってる――あいつらを片付けるんだ。";
			link.l1 = "まあ、いいだろう。たしかに、それをやるしかなさそうだな。";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Longway_3":
            dialog.text = "新しい者たちが到着しました、船長旦那。";
			link.l1 = "ああ、気づいている、ありがとう、ロングウェイ。だが、こいつらに構っている暇はない、ジャングルに退こう――もしかしたら撒けるかもしれない。";
			link.l1.go = "Nemezida_Longway_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_4":
            dialog.text = "ふむ、もちろん俺たちで片付けられるが、まあ、あんたの言う通りだな。";
			link.l1 = "この戦いは必要ねえ、だから行くぞ。";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Longway_5":
            dialog.text = "奴らは諦めずに追ってきますぜ、船長旦那！だから言ったじゃねえか、もっと早く殺しておくべきだったって。 あの洞窟で待ち伏せしますかい？……でも、もう誰かが中にいるみてえですぜ。";
			link.l1 = "ここで野郎どもと待ち伏せした方がいいな！俺が絶対に逃したくねえのは、あの宝だ。 どうやら他の奴もその隠し財宝の噂を嗅ぎつけたみてえだな…だから俺が自分で確かめに行くぜ。";
			link.l1.go = "Nemezida_Longway_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_6":
            dialog.text = "用心なさい、船長殿。たとえ偉大な竜であっても、かつて黄金の山の上で命を落としたことを忘れぬように。";
			link.l1 = "覚えておくぜ、Longway。今日は誰も死なないようにしようぜ。";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Longway_7": // на берегу
            dialog.text = "旦那船長、どうやらあそこから脱出できたようですね。";
			link.l1 = "驚いたか、ロングウェイ？まあ、俺も少しは驚いてるぜ。どうやら生き残ったのはお前だけみたいだな。だが、 どうやって切り抜けたんだ？";
			link.l1.go = "Nemezida_Longway_8";
		break;
		
		case "Nemezida_Longway_8":
            dialog.text = "小賢しい猫の群れでは虎に勝てねえ。蛇の巣窟でも竜は倒せねえ。白人どもの中で、 俺と渡り合える奴はほとんどいねえんだ。";
			link.l1 = "だが忘れるな、ロングウェイ、犬の群れでもライオンを引き裂くことができるんだぜ。";
			link.l1.go = "Nemezida_Longway_9";
		break;
		
		case "Nemezida_Longway_9":
            dialog.text = "今になってロード船長がロングウェイにご高説を垂れるのか？俺の忠告をもっと早く聞いておけばよかったのにな。";
			link.l1 = "黄金の山にいるドラゴンの話か？ああ、本当さ、俺はもう少しでドラゴンになりかけた――いや、実際死にかけたんだ。だが黄金の山じゃなかった――そんなものはどこにもなかった。俺が見つけたのは、別のものさ。それも同じくらい大事なものだった。";
			link.l1.go = "Nemezida_Longway_10";
		break;
		
		case "Nemezida_Longway_10":
            dialog.text = "次は「もう少しで」では済まないかもしれませんぞ。何を見つけましたか、船長殿？";
			link.l1 = "ああ、今はよく分かった。俺が見つけたのは……知恵、経験、理解、そして決断だ。なあ、ロングウェイ、俺たちは最近何をしてきたんだ？";
			link.l1.go = "Nemezida_Longway_11";
		break;
		
		case "Nemezida_Longway_11":
            dialog.text = "俺たちは海賊だ。お前の新しい主人、テラックス卿のために働いてる。密輸、町の略奪、殺し、救い、 そして奴の民を助けるんだぜ。";
			link.l1 = "あいつは俺の主人じゃねえよ。でもよ、くそっ、あんたは全部まるで見てきたみてえに言いやがる！ 俺は誇りも自尊心も忘れて、まるで犬みてえにあいつの後をついて回っちまったんだ。";
			link.l1.go = "Nemezida_Longway_12";
		break;
		
		case "Nemezida_Longway_12":
            dialog.text = "ロングウェイはあなたのことを理解しています、船長殿。俺もかつては、名誉も誇りも敬意も忘れ、 大切な目的のためにファン・メルデンやローデンブルクのために働いていました。";
			link.l1 = "教えてくれ、自分をそのことで責めているのか？自分自身が憎いのか？";
			link.l1.go = "Nemezida_Longway_13";
		break;
		
		case "Nemezida_Longway_13":
            dialog.text = "断罪するか？時にはな。憎むか？いや。俺は自分が誰かを知っているし、覚えている。俺の目的、導きの星も覚えている。 人生でそれ以上に大事なものはない。お前には目的があるのか？";
			link.l1 = "お前みたいな道しるべじゃねえが、それでも大事な目的はあった――兄貴を救い出すことだ。だが、その目的から外れてしまったんだ。それだけは二度と繰り返せねえ。";
			link.l1.go = "Nemezida_Longway_14";
		break;
		
		case "Nemezida_Longway_14":
            dialog.text = "天朝のもう一つの知恵をお前に伝えよう。完全に善い人間も悪い人間もいない。誰もが陰――闇と無知――と陽――光と知恵――の両方を持っている。その均衡は誰の中でも揺れ動くのだ。";
			link.l1 = "つまり、俺の陽はシャルル・ド・モールだ。\nそして俺の陰はチャーリー・プリンス。\nもっとも、シャルル・ド・モールでさえ、いつかは闇に満ちた苦しい決断を迫られるかもしれねえがな。";
			link.l1.go = "Nemezida_Longway_15";
		break;
		
		case "Nemezida_Longway_15":
            dialog.text = "それが人生というものです、船長旦那。誰しもが暗い選択も明るい選択もせざるを得ません。";
			link.l1 = "それでもプリンスの仮面は、まるで俺に溶けつきそうだった。\nだが、俺はそれを脱ぎ捨てる。シャルル・ド・モールは貴族であって、使い走りじゃない。\nこれからは、そうあるべきだ。俺の誇りと尊厳を取り戻す。\n今から俺は、自分自身の主人だ。";
			link.l1.go = "Nemezida_Longway_16";
		break;
		
		case "Nemezida_Longway_16":
            dialog.text = "「ロングウェイは"+GetAddress_Form(pchar)+"船長のご決断を支持しております。」";
			link.l1 = "ありがとう、Longway。ところで、お前は自由な船長にならなかったことを後悔したことはあるか？俺の言うところの「ご主人様」 に仕えていることを。";
			link.l1.go = "Nemezida_Longway_17";
		break;
		
		case "Nemezida_Longway_17":
            dialog.text = "ふむ。ロングウェイは自分の船を指揮するのが恋しいんだ。しかし、お前のことは覚えているぞ。 他の白人の野蛮人とは違って、俺に敬意と知恵を示してくれたからな。もしかしたら、違う人生も悪くないかもしれねえ。 でも、お前を助けたことは後悔してねえよ。";
			link.l1 = "それを聞いて嬉しいぜ、Longway。さて……この場所と陰の道を離れようじゃねえか。そしてもっと陽を俺たちの人生に取り込もう。合ってるか？";
			link.l1.go = "Nemezida_Longway_18";
		break;
		
		case "Nemezida_Longway_18":
            dialog.text = "はい、その通りです。これからはもっと良い道を歩んでくれることを願っています。";
			link.l1 = "「ダオ？」";
			link.l1.go = "Nemezida_Longway_19";
		break;
		
		case "Nemezida_Longway_19":
            dialog.text = "道だ、旦那船長。あるいは本質とも言うが、俺たちの場合は――道さ。";
			link.l1 = "たとえこれからどんな道を歩もうとも、本当に大切なものからもう二度と外れたりしない。さあ、ここを出よう、Longway。";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Тичингиту
		case "Nemezida_Tichingitu_1":
            dialog.text = "チャールズ船長、多くの人間がこっちに向かってきているぜ。あんたの狼煙がやつらを引き寄せたんだ。それに、 どう見ても俺たちの味方じゃねえな。";
			link.l1 = "ああ、お前が言ったような「狼煙」だけならよかったんだが……あの音はジャングル中に響き渡ったぜ。もう仕方ねえ、自分たちで身を守るしかねえな。 まさか丸ごと一隊に背後を突かれるなんてごめんだぜ。";
			link.l1.go = "Nemezida_Tichingitu_2";
		break;
		
		case "Nemezida_Tichingitu_2":
            dialog.text = "はい、チャールズ船長。先に攻撃だ！";
			link.l1 = "攻撃だ！弾薬を惜しむな！";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tichingitu_3":
            dialog.text = "もっと来るぞ！さらに人が増えてきた。";
			link.l1 = "「ジャングルに退くぞ、ティチンギトゥ！隠れてやり過ごそう。俺は宝を探しに来たんだ、戦うためじゃねえ！」";
			link.l1.go = "Nemezida_Tichingitu_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_4":
            dialog.text = "必要なら、ジャングルで待ち伏せを仕掛けることもできるぜ。";
			link.l1 = "その通りだ。さあ、急いで、だが静かに動こう。";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tichingitu_5":
            dialog.text = "「チャールズ船長、見てください！前方に通路があります。それに、あそこから足音と話し声が聞こえます。」";
			link.l1 = "誰か他の奴が宝のことを知っちまったのか？くそっ！おい、後ろの音も聞こえるか？どうやら追いつかれたみてえだ。 ティチンギトゥ！俺が前方を見てくる。お前は仲間と一緒に奴らを食い止めろ！";
			link.l1.go = "Nemezida_Tichingitu_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_6":
            dialog.text = "やってみるぜ！お前は行け！";
			link.l1 = "頼んだぜ！";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
			
		case "Nemezida_Tichingitu_7": // на берегу
            dialog.text = "チャールズ船長！生き延びたんだな！ティチンギトゥもこれを聞いたら喜ぶぞ。";
			link.l1 = "ありがとう、友よ。俺も嬉しいぜ。生き延びられてよかったし、お前も無事で何よりだ。 どうやら分隊の中で生き残ったのはお前だけみたいだな。奴らは多かったのか？よく持ちこたえたじゃねえか。";
			link.l1.go = "Nemezida_Tichingitu_8";
		break;
		
		case "Nemezida_Tichingitu_8":
            dialog.text = "多いさ。しかし、俺の仲間はマスコグ村でも屈指の戦士だぜ。\nそこで何があったんだ？探していた財宝は見つかったのか？";
			link.l1 = "いいや、ティチンギトゥ。俺たちは騙されたんだ――宝なんてなかった。さて、最近俺たちがやってきたことについて、お前はどう思う？";
			link.l1.go = "Nemezida_Tichingitu_9";
		break;
		
		case "Nemezida_Tichingitu_9":
            dialog.text = "俺たちは何をしてきたんだ、チャールズ船長？\n航海だ。\nお前の敵を倒してきたのさ。";
			link.l1 = "どうやら俺の言ってることが分かってねえようだな。じゃあ聞くが、部族から追放されたことを悲しんでいるのか？ 戻りたいのか、兄弟たちが恋しいのか？";
			link.l1.go = "Nemezida_Tichingitu_10";
		break;
		
		case "Nemezida_Tichingitu_10":
            dialog.text = "もちろん、友人や家族が恋しいさ。\nでも戻るのか？あいつ……彼女がいないなら、俺の故郷なんてもう存在しねえ。\nそれに、あの邪悪なコヨーテ、シャーマンもいるしな！";
			link.l1 = "すまない、そんな話を持ち出すつもりはなかったんだ。実はな、最近俺もいわば部族に加わったんだ。 俺みたいな船長たちの集まりさ。だが結局のところ、 あれはただ自分を海の狼だと勘違いしてるジャッカルどもの群れだったって気づいたんだ……";
			link.l1.go = "Nemezida_Tichingitu_11";
		break;
		
		case "Nemezida_Tichingitu_11":
            dialog.text = "「それでどうなったんだ？これからどうする？」";
			link.l1 = "いい質問だな。俺もあのジャッカルどもの中で、もう少しで自分がジャッカルになりかけたぜ。だから、もう十分だ。 俺の仲間と船員たち――それが俺の“部族”さ。";
			link.l1.go = "Nemezida_Tichingitu_12";
		break;
		
		case "Nemezida_Tichingitu_12":
            dialog.text = "ティチンギトゥは、チャールズ船長が自分の部族を見つけたことを喜んでいる。";
			link.l1 = "ありがとう、友よ。どうしても言いたかったんだ。俺たちはそれぞれ自分自身のリーダーであり、仲間でもある。さて、 本当に大事なことに戻る時だな。";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Айронс
		case "Nemezida_Irons_1":
            dialog.text = "誰か来るぞ！しかも、音からして感謝祭を祝うために来たんじゃなさそうだ。";
			link.l1 = "くそっ、根っこめ！よし、今この悪党どもを片付けるしかねえな――宝を船に運ぶ時より今の方がマシだぜ。";
			link.l1.go = "Nemezida_Irons_2";
		break;
		
		case "Nemezida_Irons_2":
            dialog.text = "その通りだ。準備はいいか？";
			link.l1 = "聞かなくても分かるだろう。俺たちに選択肢なんてねえんだからよ。";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Irons_3":
            dialog.text = "奴らはどこにでもいやがる、ロンドンのスラムのネズミみてえにな、旦那！\nどうします？ここで踏ん張って撃ち合うか、野郎どもと一緒に？";
			link.l1 = "今じゃねえ、退け！俺たちは宝を狙いに来たんだ、戦うためじゃねえぞ！";
			link.l1.go = "Nemezida_Irons_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_4":
            dialog.text = "へっ、こっちは文句ねえぜ。";
			link.l1 = "だったら急げ！";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Irons_5":
            dialog.text = "おい、船長、見てくれ――この道はどこかに続いてるみたいだぜ。あっちからは騒がしい音も聞こえてくるし、何か賑やかそうだな！";
			link.l1 = "まさか他の奴らが宝の噂を嗅ぎつけたのか？トミー、聞こえるか？追っ手が来やがった。\nよし、俺は前に出る。お前らはここでしっかり迎え撃てよ！";
			link.l1.go = "Nemezida_Irons_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_6":
            dialog.text = "今聞こえたぜ！誰だろうと、急いだほうがいいぞ、へっへっ。そうじゃねえと、 わざわざここまで来た意味がねえだろうが！？";
			link.l1 = "ああ、それは困るな。";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Irons_7": // на берегу
            dialog.text = "ああ、あんたか、船長！まあ、生き残ったんだな。正直に言うぜ――期待してなかった。でも嬉しいぜ、誤解すんなよ、へっへっ。";
			link.l1 = "俺も予想してなかったぜ、嘘はつかねえ。でも、お前が生き延びたことには全然驚いてねえよ。逃げたのか？";
			link.l1.go = "Nemezida_Irons_8";
		break;
		
		case "Nemezida_Irons_8":
            dialog.text = "俺に失礼だぜ！トミー・アイアンズは決して逃げたりしねえ！ただ援軍を呼びに戻るだけさ。だが今回は必要なかった――俺と仲間たちで片付けたんだ、まあ、またしても生き残ったのは俺だけだったけどな、へへ…";
			link.l1 = "もしかしたら今回は援軍を呼ぶべきだったかもしれねえ。\nでも俺は……俺は逃げちまったんだ。";
			link.l1.go = "Nemezida_Irons_9";
		break;
		
		case "Nemezida_Irons_9":
            dialog.text = "逃げたのか？へっ、また驚かされたぜ。だがな、実は用が済んだらすぐにお前のもとへ駆けつけたかったんだ！ 俺はどんな援軍より頼りになるんだぜ。だけどさ……";
			link.l1 = "どうしたんだ、トム？";
			link.l1.go = "Nemezida_Irons_10";
		break;
		
		case "Nemezida_Irons_10":
            dialog.text = "くそっ、俺がうろうろしてる間に、お前の後ろの入口が岩で塞がれちまったんだ。通り抜けられなかったぜ。 片付けるのに時間がかかって、お前の手助けもできなかったのは正直恥ずかしいぜ。 仲間を呼びに戻ろうとして道に迷っちまったしな……戻ってきた時には、もうお前は帰ってきてたってわけだ。";
			link.l1 = "ああ、もしかしたら今日自分に起きたことを話すのが恥ずかしくなるかもしれねえな。";
			link.l1.go = "Nemezida_Irons_11";
		break;
		
		case "Nemezida_Irons_11":
            dialog.text = "それで、どうなったんだ？怖がらずに話してみろよ。\nでも、もし面白い話なら、俺は笑うからな、覚悟しとけ。\n他にどうするってんだ？友達ってのは肩を貸して、笑いながら肘でつつくもんだぜ。";
			link.l1 = "おい、お前は慰め方をよく知ってるな。なあ、トミー、教えてくれ。お前は海賊稼業が好きだって言ってたよな。 俺と一緒にまた戻れて嬉しかったか？";
			link.l1.go = "Nemezida_Irons_12";
		break;
		
		case "Nemezida_Irons_12":
            dialog.text = "こう言わせてもらうぜ。俺が海賊だろうがなかろうが、昔っから大好きなのは冒険なんだよ！ 俺の答えじゃ納得できねえみたいだな。だがな、こういう大きな話は、正直言って俺の関心事じゃねえんだ。";
			link.l1 = "満足していないわけじゃねえんだ。でも、俺が話したかったのはそれじゃねえ。わかるか……ティラックスのことで、俺はすっかり自分の目標から外れちまったんだ。それに……チャーリー・プリンスは、勇敢な海賊船長なんかじゃなくて、ただの手下だったんだよ、トム。わかったか？もう十分だ。 ";
			link.l1.go = "Nemezida_Irons_13";
		break;
		
		case "Nemezida_Irons_13":
            dialog.text = "なるほどな。だからこそ、あんたがあんなふうにテラックスに操られてるのを見て驚いたんだ。 まるであんたらしくなかったぜ。";
			link.l1 = "もしかしたら、あの頃の俺は本当にチャーリー・プリンスだったのかもしれねえ。\nだが、また海賊に戻るかどうかは俺が決める！\nしかも、それが本当に俺の利益になり、目標に近づく時だけだ！";
			link.l1.go = "Nemezida_Irons_14";
		break;
		
		case "Nemezida_Irons_14":
            dialog.text = "そうこなくっちゃな！でも言わせてもらうぜ、チャーリー・プリンスだろうがシャルル・ド・モールだろうが、 結局お前はお前だ。だからお前といると、いつだってくそ面白かったぜ！";
			link.l1 = "それは良かった、Tommy。";
			link.l1.go = "Nemezida_Irons_15";
		break;
		
		case "Nemezida_Irons_15":
            dialog.text = "覚えておけ、自分以外はほとんど誰も助けてくれねえんだ。\n他人に決められるくらいなら、たとえ一人でも自分の好きなことをやった方がいいぜ！";
			link.l1 = "そうだ。その通りだ、テラックスの時もまさにそう感じたぜ。たとえまた誰かに従うことになったとしても、 今度はふさわしい条件のもとだけだ、使いっ走りなんかじゃねえ！";
			link.l1.go = "Nemezida_Irons_16";
		break;
		
		case "Nemezida_Irons_16":
            dialog.text = "その通りだ！さあ、ここを出ようぜ――もう足がガクガクだ。";
			link.l1 = "おい、今それを言おうとしたところだぜ、はは。でもお前の言う通りだ、行こう。これから大事な仕事が山ほどあるんだ、 トム。こんなことしてる場合じゃねえ。";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Алонсо
		case "Nemezida_Alonso_1":
            dialog.text = "船長、どうやらお客さんが来たみたいだぜ！ここには俺たちだけじゃねえぞ。";
			link.l1 = "まさに必要だったものだな……よし、今のうちに片付けよう。後になれば、もっと厄介なことになるだけだ。";
			link.l1.go = "Nemezida_Alonso_2";
		break;
		
		case "Nemezida_Alonso_2":
            dialog.text = "ああ、船長。";
			link.l1 = "準備しろ！";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Alonso_3":
            dialog.text = "奴らがどんどん増えてきやがる！";
			link.l1 = "なら、これ以上続ける意味はねえ！退却だ！奴らをまいて、一気に宝の場所へ向かうぞ！";
			link.l1.go = "Nemezida_Alonso_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_4":
            dialog.text = "ああ、船長！";
			link.l1 = "どけどけ、さっさと動け！";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Alonso_5":
            dialog.text = "船長、ここに入口があるみたいだぜ！しかも、もう誰か中にいるぞ。";
			link.l1 = "よく聞け――俺たちは尾けられてる。俺が中に入って様子を見てくるから、お前たちはここを守れ。援護しろ、野郎ども！";
			link.l1.go = "Nemezida_Alonso_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_6":
            dialog.text = "ああ、船長！";
			link.l1 = "踏みとどまれ。幸運を祈る――俺たち全員にな！";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("お前は "+GetSexPhrase("盗人か、なるほど！衛兵ども、そいつを捕まえろ","泥棒か、なるほど！衛兵ども、あの女を捕まえろ")+"!!!","信じられねえ！ちょっと目を離した隙に、お前が俺の持ち物を漁ってやがるとは！止まれ、泥棒！！！","衛兵！強盗だ！泥棒を止めろ！！！");
			link.l1 = "あああっ、悪魔め！！！";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
		
		// <-- legendary edition
	}
}
