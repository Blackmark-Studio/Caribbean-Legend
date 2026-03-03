// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "明らかなバグだ。開発者に知らせてくれ。";
			link.l1 = "ああ、そうするよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "girl":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "おや、こんにちは旦那！トルトゥーガへようこそ！あなたのような高貴な船長は、ここでは珍しいお客様ですよ…";
			link.l1 = "ごきげんよう、お嬢さん。温かい歓迎をありがとうございます。しかし、どうしてですか？こんなに重要な港は、 私なんかよりよほど高貴な運のいい紳士たちにとって、常に興味深い場所だと思っていましたが。";
			link.l1.go = "girl_1";
		break;
		
		case "girl_1":
			dialog.text = "ああ、旦那……あなたは明らかに新参者ですね、違いますか？いずれ自分で分かるでしょう。 総督の宮殿で踊るのにふさわしい男を見つけるのがどれほど大変か、あなたには想像もつかないでしょう。もしかして、 私に付き合ってくれませんか……？";
			link.l1 = "こんな美しい女性に、俺がどうお役に立てるかな？";
			link.l1.go = "girl_2";
		break;
		
		case "girl_2":
			dialog.text = "まあまあ、なんて勇ましいのかしら！（くすくす）今夜六時に私たちのところへいらしてくださらない？ うちの総督夫人はよく宮殿の使用人部屋で内輪の集まりを開いているの。こんな催しで面白い方とご一緒できるなんて、 滅多にないことですわ。いらしてくださる？ぜひお越しになって、私たちを喜ばせてくださいませ。";
			link.l1 = "光栄です、お嬢さん。今夜お伺いします。";
			link.l1.go = "girl_3";
			link.l2 = "申し訳ありません、お嬢さん、だが急ぎの用事があるんだ。\nまた今度でもいいかな？";
			link.l2.go = "girl_exit";
		break;
		
		case "girl_exit":
			dialog.text = "残念だな。俺とあたしの女友達の相手をしてくれる他の奴を探すしかねえな。じゃあな。";
			link.l1 = "さらば。";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			FMQT_ClearChest();
		break;
		
		case "girl_3":
			dialog.text = "ありがとうございます！約束しますよ、これは絶対に忘れられない夜になります、旦那！オルヴォワール！";
			link.l1 = "じゃあな……";
			link.l1.go = "girl_4";
		break;
		
		case "girl_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_serveroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "1");
		break;
		
		case "girl_5":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "よう、船乗り！今日はどんな幸運な風に乗ってここまで来たんだ？トルトゥーガじゃ、 こんな立派な男はめったに見かけねえぜ。";
			link.l1 = "あんたもこんにちは、お嬢さん。そんなに褒められると俺も照れちまうぜ。俺は自分の船を持つ船長で忙しい身だが、 この島なら俺みたいな放浪者でも十分楽しめるものがあるだろうさ。";
			link.l1.go = "girl_6";
		break;
		
		case "girl_6":
			dialog.text = "（くすくす）ああ、旦那、それならきっとお手伝いできるわ！トルトゥーガにはいつだって何かしらあるものよ。 あたしもね……いい海の話を聞いたら、ほとんど*何でも*しちゃうかもしれないわ。そういう話、大好きなの！ある船長が、無人島に置き去りにされそうになったとき、 ウミガメで筏を作って逃げたっていう大ぼら話をしてくれたことがあるの。なんて勇ましい人なのかしら！ あなたにもできる？";
			link.l1 = "「俺が何をできるって？」";
			link.l1.go = "girl_7";
		break;
		
		case "girl_7":
			dialog.text = "（くすくす）海ガメで筏を作れるかしら？";
			link.l1 = "もっとすごい話をしてやろう。俺はな、昔見習いから逃げ出したとき、 手斧一本でイギリス海軍で一番速い船を奪ったことがあるんだぜ。しかも、十分間息を止めることもできる。 見てみたいか？";
			link.l1.go = "girl_8";
		break;
		
		case "girl_8":
			dialog.text = "また今度な。俺はうちの総督の宮殿で召使いをしてるんだ。今夜六時までにそこへ来て、 あずまやで俺と友達を探してくれ。その時にお前の冒険話をたっぷり聞かせてくれよ…";
			link.l1 = "断れねえ見世物のお誘いってわけか。今夜六時に会おうぜ。";
			link.l1.go = "girl_9";
			link.l2 = "総督の宮殿に忍び込むだと？俺にはちょっと高級すぎる話だぜ。遠慮しとくよ、お嬢ちゃん。 本物の男と飲みたきゃ酒場で俺を探せよ。ヨーホーホー！";
			link.l2.go = "girl_exit_2";
		break;
		
		case "girl_exit_2":
			dialog.text = "ふんっ。どうでもいいさ、もっといい男で、もっとデカい奴を見つけてやるよ。あんたの股当て、 どう見ても小さすぎるしな。せいぜいせいせいしたぜ。";
			link.l1 = "お前のウィンドワード海峡を通れば、戦列艦でさえ小さく見えるぜ。";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_9":
			dialog.text = "楽しみにしてるぜ！";
			link.l1 = "...";
			link.l1.go = "girl_10";
		break;
		
		case "girl_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_bedroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "2");
		break;
		
		case "wife":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "ああ、いたか！船長 "+GetFullName(pchar)+"！お会いできて本当に嬉しいです、これほどの高貴なお方にお越しいただくのは久しぶりでございます！";
			link.l1 = "ここであなたとご一緒できることは、私にとって大変光栄であり喜びでございます、マダム。\nしかし、他のお客様方はいかがなさいましたか？私、早く来すぎてしまいましたでしょうか？";
			link.l1.go = "wife_1";
		break;
		
		case "wife_1":
			dialog.text = "ああ、あの人たちは都合が悪くて来られないのよ。でも気にしないで、ワインでも飲みながらお話しましょう……ああ、あなたがどれほどここで退屈で寂しい思いをしているか知っていたら！トルトゥーガなんて、ろくでなしや悪党、 そして海賊どもがうようよいる薄汚い巣窟よ！海賊ばかり！でもついに、私の家にふさわしい紳士が来てくれたのね！ うちの主人も、あなたのような階級と才能を持つ方々ともっと取引してくれればいいのに！でも現実は違う、 どこもかしこも海賊ばかり！\nねえ、パリの国王陛下の宮廷で流行り始めている新しいファッションのこと、聞いた？あなたはどう思う？";
			link.l1 = "すまないが、俺の意見って何についてだ？海賊のことか？それとも流行についてか？";
			link.l1.go = "wife_2";
		break;
		
		case "wife_2":
			dialog.text = "ああ旦那、あなたは本当に私のことをよくわかってくださるのね！信じられないくらいよ。うちの主人なんて、 あたしには小銭しかくれないくせに、自分は海賊どもで何百万も稼いでるのよ、想像できる？海賊よ！ あたしはこんな汚い穴蔵にドレスを届けさせなきゃならないのに、届く頃にはもう半年も遅れてるんだから！ こんなボロを身につけて、あたしみたいな身分の女がどうやってやっていけるの？ああ、パリの流行をこの目で見て、 身につけてみたいわ！あたし、あのドレスを着たら素敵に見えると思う？\n";
			link.l1 = "奥様、とてもお美しいですわ。パリの流行なんて必要ありません、 この美しい島の男たち全員がすでにそれを分かっておりますのよ。";
			link.l1.go = "wife_3";
		break;
		
		case "wife_3":
			dialog.text = "私にはもったいないお言葉です……船長、正直に申し上げますと、私は大変な困難に直面しております。でも、 あなたはこの哀れな女を助けてくださいますよね？";
			link.l1 = "かしこまりました、奥様。ご希望のことは何でもいたします。";
			link.l1.go = "wife_4";
		break;
		
		case "wife_4":
			dialog.text = "気をつけてね、船長旦那、じゃないと私、首が飛んじゃうかも！（艶っぽくクスクス）うちの旦那、 最近は一銭もくれやしないのよ。あの乱暴者、安い女どもを家に連れ込んで、 私のことなんて全然気にも留めないんだから！\nでもね、あいつが不正に手に入れた財宝の隠し場所、私知ってるの。執務室のチェストの中よ。これは妻として、 女として当然もらう権利があるお金なの。あいつから取り返すのを手伝ってくれたら、お礼はするわ……金貨も、それから……もっと素敵なものもね。";
			link.l1 = "それは興味深い提案ですね。よろしいですわ、奥様、お手伝いします。その箱はどこにありまして、 どうやって開ければよろしいのですか？";
			link.l1.go = "wife_5";
			link.l2 = "承知しました、奥方。あんたのためにその箱の中身を取ってきてやるよ。金を手に入れたら、その後でたっぷりと“お話”しようじゃねえか。こんな申し出を断る男がいるか？その箱はどこにあって、どうやって開けるんだ？";
			link.l2.go = "wife_6";
			link.l3 = "マダム、あなたは私を誘惑しようとしているのですね。申し訳ありませんが、 私の名誉があなたの申し出をお断りするよう求めております。お気持ちはお察ししますし、 あなたにはもっとふさわしい方がいるはずです。しかし、あなたの芝居には他の役者をお探しください。";
			link.l3.go = "wife_exit";
		break;
		
		case "wife_exit":
			dialog.text = "残念ですわね。ならば、もうお話しすることはありません、旦那。出ていってください。そして覚えておきなさい： このことを私の夫に一言でも漏らしたら、きっと後悔しますわよ！";
			link.l1 = "さらば。";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.FMQT.Common");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "4");
		break;
		
		case "wife_5":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "お前からこんなことをされるとは思わなかった……その宝箱は……後回しだ、まずは汚い海賊に盗まれた合鍵を見つけなければならん。今そいつは地元の酒場でどんちゃん騒ぎして、 豚みたいに酒を飲んでいる。急いで合鍵を取り戻してこい。私はここで待っているぞ。";
			link.l1 = "なら、ぐずぐずしてる暇はねえぞ！";
			link.l1.go = "wife_7";
		break;
		
		case "wife_6":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "後悔はさせませんぜ、船長。まずは、汚ねえ海賊に盗まれた合鍵を見つけなきゃならねえ。あいつは今、 地元の酒場でどんちゃん騒ぎして、豚みてえに飲んでやがる。急いで合鍵を俺のところに持ってきてくれ。待ってるぜ。";
			link.l1 = "じゃあ、ぐずぐずしてる暇はねえぞ！";
			link.l1.go = "wife_7";
		break;
		
		case "wife_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_PirateInTavern", 10.0);
			pchar.quest.FMQT_late2.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late2.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQT_late2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late2.function = "FMQT_TavernTime";
			AddQuestRecord("FMQ_Tortuga", "6");
		break;
		
		case "wife_8":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Captain "+GetFullName(pchar)+"！まあまあ！私の私室に男の人がいるなんて！驚いた？今夜ここにいるお客様はあなただけよ。（くすくす）";
			link.l1 = "驚きましたよ、奥様。しかし全く気にしません。これはお仕事の話ですか、それともお楽しみでしょうか？";
			link.l1.go = "wife_9";
		break;
		
		case "wife_9":
			dialog.text = "なんて直球なやり方だ！お前みたいな男は好きだぜ。船長、ひとつ商談があるんだ。うまくやってくれたら、 ちゃんと報酬を用意するぜ。";
			link.l1 = "続けろ。";
			link.l1.go = "wife_10";
		break;
		
		case "wife_10":
			dialog.text = "ああ……うちの旦那は金や宝石でいっぱいの箱を持ってるのよ。あいつなんて大嫌い、 私の苦労に見合うもっと大きな小遣いが欲しいわ。";
			link.l1 = "奥様、とてもお美しいですわ。これ以上パリの宝石や流行の服など必要ありませんのよ、 イスパニョーラの男たち全員にとって、すでに明らかですもの。";
			link.l1.go = "wife_11";
		break;
		
		case "wife_11":
			dialog.text = "私にはもったいないお言葉です……船長、正直に申しますと、私は大変な困難に陥っております。お困りの女を助けていただけませんか？";
			link.l1 = "もちろんでございます、奥様。名誉がそれを求めますわ。ご要望があれば何なりと。";
			link.l1.go = "wife_12";
		break;
		
		case "wife_12":
			dialog.text = "気をつけてくださいね、船長旦那、じゃないと私、首が飛んじゃいますわ！（艶っぽくクスクス）最近、 旦那ったら一銭もくれないんですの。あの乱暴者、安い女を家に連れ込んで、私のことなんてまるで無視ですわ！\nでも、あの人が悪事で手に入れた財宝の隠し場所、私知ってますのよ。執務室の箱に入れてありますわ。 これは妻であり女である私の当然の権利ですもの。取り返すのを手伝ってくだされば、お礼を差し上げますわ……金貨と……他にも素敵なものを。";
			link.l1 = "わかった。俺がやるぜ。その宝箱はどこにあるんだ？どうやって開けりゃいいんだ？";
			link.l1.go = "wife_13";
			link.l2 = "はっ！そんなことなら任せときな、あんたみたいな女のためならな。後悔はさせねえぜ、お嬢さん。金を手に入れて、 楽しい時間を過ごそうじゃねえか。で、その箱はどこにあって、どうやって開けりゃいいんだ？";
			link.l2.go = "wife_14";
			link.l3 = "俺じゃねえよ、お嬢さん。俺は一晩で男を寝取って盗むような紳士じゃねえ。少なくとも、こんなやり方はしねえ。 他にこの芝居の役者を探しな。";
			link.l3.go = "wife_exit_2";
		break;
		
		case "wife_13":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "ああ……ますますあなたが気に入ってきたわ……まずは、汚い海賊に盗まれた合鍵を取り戻さなければならないの。あいつは地元の酒場でどんちゃん騒ぎしながら、 豚みたいに酒を飲んでいるわ。急いでその合鍵を持ってきてちょうだい。私は待っているから。";
			link.l1 = "なら、ぐずぐずしてる暇はねえぞ！";
			link.l1.go = "wife_7";
		break;
		
		case "wife_14":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "落ち着いてください、旦那、そんなことは後でいくらでもできますわ。（くすくす）まずは、 汚い海賊に盗まれた合鍵を取り戻さなければなりません。その男は地元の酒場でどんちゃん騒ぎをして、 豚のように酒を飲んでいます。急いで合鍵を私のところに持ってきてくださいませ。お待ちしておりますわ。それ、 本当にできる自信はありますの？";
			link.l1 = "俺を疑うな、もう向かってるぜ。";
			link.l1.go = "wife_7";
		break;
		
		case "wife_exit_2":
			dialog.text = "堅物の野郎め！さっさとあたしの前から消えな！それと、これを旦那にチクるなんて考えもしないことね、後悔するわよ！ ";
			link.l1 = "じゃあな、お嬢ちゃん。";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_15":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_late3.over = "yes";
			dialog.text = "船長！鍵は手に入れたか？";
			link.l1 = "ああ、持ってるぜ。箱はどこだ？";
			link.l1.go = "wife_16";
		break;
		
		case "wife_16":
			dialog.text = "おお！あのろくでなしの旦那がついに報いを受けるってわけかい？あんたはすごい男だね、船長！ あんたには素晴らしい未来が待ってるよ、わかってるかい？宝箱のことは忘れておくれ。あたしが自分でやるよ。 明日また来てくれたら報酬を渡すからね。後悔はさせないよ、船長…";
			link.l1 = "わかったよ。好きにしな。明日会うのを楽しみにしてるぜ。";
			link.l1.go = "wife_17";
			link.l2 = "いや、俺は忙しい男だし、待って時間を無駄にしたくねえんだ。\nなんで待つ必要がある？やるべきことを教えてくれりゃ、俺がやるぜ。\nこんな美しい女の子に、鍵や錠前をいじらせて可愛い手を汚させるわけにはいかねえよ。";
			link.l2.go = "wife_18";
		break;
		
		case "wife_17":
			RemoveItems(pchar, "kaleuche_key", 1);
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			dialog.text = "六時までに私のところへ来てください、勇敢な旦那騎士様……";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_Deceive");
		break;
		
		case "wife_18":
			dialog.text = "本当に大丈夫か？お前には危険かもしれねえぞ。どうして命を危険にさらしたいんだ、船長？";
			link.l1 = "わかったよ。好きにしな。明日会うのを楽しみにしてるぜ。";
			link.l1.go = "wife_17";
			link.l2 = "俺はもう決めたぜ。具体的に何をすりゃいいんだ？";
			link.l2.go = "wife_19";
		break;
		
		case "wife_19":
			dialog.text = "百獣の王の心を持つ方ね！…旦那の執務室へ行って、その中にある箱を探してちょうだい。合鍵を使えばいいわ。この夜中、 上の階には誰もいないから、ゆっくりやって大丈夫よ。その箱の中には…ダイヤモンドが入っているの。しかも大量に。全部持ってきて、私のところへ戻ってきて。待ってるわ。 私の信頼を裏切らないで…お願い。";
			link.l1 = "すぐ戻るぜ。";
			link.l1.go = "wife_20";
		break;
		
		case "wife_20":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Tortuga", "11");
			sld = &Locations[FindLocation("Tortuga_townhallRoom")];
			sld.private2.key = "kaleuche_key"; // допуск к сундуку
			pchar.questTemp.FMQT = "chest";
		break;
		
		case "wife_21":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "ああ、船長！俺……お前……終わったのか？あ、それでこいつは誰だ！？あ、ああっ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_MercenAttackRoom");
		break;
		
		case "wife_22":
			dialog.text = "まあ！船長、助けてくれてありがとう！あなたは…あなたは私の英雄よ！あれは私の夫の手下だったの、あなたを殺そうとしてたのよ！やめてって必死に頼んだの！ 怪我はない？ダイヤモンドは持ってきてくれた？";
			link.l1 = "はっ。本当かよ？お前の旦那は嫉妬深い男だな……まあいい。くたばれってんだ、俺には度胸があるぜ。";
			link.l1.go = "wife_23";
		break;
		
		case "wife_21x":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "おお船長！俺は…お前は…終わったのか？";
			link.l1 = "ちょっとした問題はあったが、今はもう片付いた。\nどうしたんだ、奥さん？顔色が悪いぞ。大丈夫か？\n宝石は手に入れたから、元気が出るだろう、違うか？";
			link.l1.go = "wife_23";
		break;
		
		case "wife_23":
			dialog.text = "神に感謝を！これで仇は討てた！私の騎士よ！ダイヤは何個あったのだ？";
			if (GetCharacterItem(pchar, "jewelry2") >= 100)
			{
				link.l1 = "あなたの騎士は冒険から戦利品の袋を持って戻ってきたぞ。彼はその半分を奥方に残していくから、 パリの最高の流行を買えるだろう。私はあなたへの約束を守ったぞ。";
				if (CheckAttribute(pchar, "questTemp.FMQT.Honour")) link.l1.go = "wife_25";
				else link.l1.go = "wife_26";
			}
			else
			{
				link.l1 = "ああ、ダイヤはいくらでもあったが、お前には一つもやらねえ。俺を殺すために刺客を雇っただろう、この売女め！ こんなことの後で俺が分け前をやると本気で思ってるのか？このことを口にしたら、 お前の旦那にお前の強盗と寝取る計画を全部教えてやるからな。だから黙ってろ。";
				link.l1.go = "wife_24";
			}
		break;
		
		case "wife_24":
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_03.wav");
			dialog.text = "この野郎！くそったれ！こんなこと、許さねえぞ！";
			link.l1 = "ああ、それは前にも聞いたことがあるぜ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoJewelry");
		break;
		
		case "wife_25":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "お前は……他の連中とは違うな。欲しいものを手に入れる奴だ。これから先、明るい未来が待ってるぜ。忙しいのはわかってるが……少しだけ俺と一緒にいてくれないか？誰にも邪魔させねえ、約束する。";
			link.l1 = "あんたみたいな美人のためなら、いつでも時間はあるぜ。旦那のワインでも開けようか？";
			link.l1.go = "wife_sex";
		break;
		
		case "wife_sex":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
			DoQuestCheckDelay("PlaySex_1", 1.0);
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "Fuck"; 
		break;
		
		case "wife_26":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "あの人たちがいなくても生きていけると思うわ。ここにはお金を使う方法がいくらでもあるし、 トルトゥーガには素敵で立派な男たちもたくさんいるもの……。\nいろいろありがとう、船長。念のために言っておくけど、この件は絶対に内緒にしてちょうだい。もし夫に知られたら、 あなたは絞首台に吊るされるわ。あの人はろくな男じゃないの。さようなら。";
			link.l1 = "そんなあっさりと？勉強になったぜ。じゃあな、奥さん、このことも黙ってたほうがいいぜ。俺も善人じゃねえからな。 まあ、それはもう知ってるだろ？";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoSex");
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "NoFuck"; 
		break;
		
		case "wife_27":
			PlaySound("Voice\English\Girls_2.wav");
			dialog.text = "お前は誰だ、ここで何してやがる？";
			link.l1 = "何を企んでやがる？俺たちは取引したはずだろう…";
			link.l1.go = "wife_28";
		break;
		
		case "wife_28":
			dialog.text = "何の取引ですって、旦那？私は既婚の女よ、他の男と商売なんてしないわ！今すぐ私の部屋から出ていきなさい、 さもないと夫と護衛を呼びますわよ！";
			link.l1 = "そうかい、そんなに簡単に済ませるのか？よし、それなら旦那にしっかり教えてやるとしよう！";
			link.l1.go = "wife_29";
		break;
		
		case "wife_29":
			dialog.text = "今すぐ出て行け、この無礼者め！さもなくば俺の部下がフォール・ラ・ロシュの地下牢に放り込んでやるぞ！ お前の脅しなんか気にしない！出て行け！";
			link.l1 = "...";
			link.l1.go = "wife_30";
		break;
		
		case "wife_30":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "FMQT_FinalFail");
			pchar.questTemp.FMQT.Marceline = "Deception"; // Rebbebion, для "Путеводной звезды"
		break;
		
		case "pirate":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\tavern\Pyanici-03.wav");
			pchar.quest.FMQT_late2.over = "yes";
			FreeSitLocator("Tortuga_tavern", "sit_base2");
			dialog.text = "お前は誰だ？ああ、まあいい。女は信用するなよ、相棒。聖書にも書いてあるだろ……どんな間抜けな女でも、その手管で地獄の底まで引きずり込むんだぜ。座れよ、相棒、一杯やろうぜ！";
			link.l1 = "喜んで！";
			link.l1.go = "pirate_1x";
		break;
		
		case "pirate_1x":
			DialogExit();
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_base2");
			LAi_SetSitType(pchar);
			npchar.Dialog.currentnode = "pirate_1";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 2.0);
		break;
		
		case "pirate_1":
			PlaySound("Voice\English\tavern\Pyanici-05.wav");
			dialog.text = "何見てやがる？さっさと注げ！！";
			link.l1 = "お前に乾杯だぜ！…おい、友よ、ここで時間を無駄にする気はねえ。お前が持ってる合鍵が必要なんだ、わかってるだろ。 そいつを渡してくれりゃ、俺たちはおさらばだ。お前は飲み続けりゃいいし、俺は困ってるお嬢さんを助けに行くさ。";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "おいおい、相棒！俺の話、全然聞いてなかったのかよ！見た目は賢そうなのに、実際はそうでもねえな……あの売女の下で働いてるなんて。あいつの旦那が誰か知ってるか？つい最近、 ルヴァスール総督が忠実な黒人のカンパチョを地元の有名な商人のところに『話をしに』送ったんだ。 その黒人が可哀想な野郎を自分の店でぶち殺したんだぜ！ その商人は舞踏会かなんかで総督の妻にちょっと無礼を働いたらしい。それで、 あの同じ女が今度は俺を色気と旦那のドゥブロン金貨で誘惑しやがったんだ\n合鍵はもうある。フランスにいた頃はそこそこの金庫破りだったから、こんなの朝飯前さ。 リヨンの司令官の娘がいなけりゃ……俺が海賊になることもなかったろうよ。チッ！もうどうでもいいぜ！";
			link.l1 = "これは本当に残念だが、さて、取引の話をしよう。鍵はどこだ？";
			link.l1.go = "pirate_3";
		break;
		
		case "pirate_3":
			dialog.text = "聞いてるか？俺はもうこの世界から足を洗ったんだ、相棒！何が起きるかちゃんと分かってたからな！ 船の準備ができ次第、ここを永遠に離れるぜ。鍵が欲しいなら金を払え。ケチるなよ、 お前ももうすぐ金なんて必要なくなると思うぜ。";
			link.l1 = "そうだな、あんたの言う通りだ。女の玩具になるなんてごめんだぜ。忠告ありがとな、海では気をつけろよ！";
			link.l1.go = "pirate_4";
			link.l2 = "支払えだと？お前にか？お前は情けない泥棒で臆病者だ。あのクソみたいなリヨンにいればよかったんだよ。 もしかしたら、地元の司令官が哀れんで、堕落した泥棒を婿にしてくれたかもしれねえぞ。だが、 俺は絶対にお前に情けなんかかけねえ。鍵を素直に渡すか、痛い目に遭ってから渡すか、選ぶのはお前だ。";
			link.l2.go = "pirate_5";
			link.l3 = "（はぁ）いくらだ？";
			link.l3.go = "pirate_6";
		break;
		
		case "pirate_4":
			dialog.text = "賢い奴だな、それが正しい判断だぜ、相棒。幸運を祈るぜ。いつか本当に愛してくれる女を見つけられるといいな。 できれば赤毛か金髪がいいよな、そうだろ？";
			link.l1 = "じゃあな、相棒……";
			link.l1.go = "pirate_exit";
		break;
		
		case "pirate_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "9");
		break;
		
		case "pirate_5":
			dialog.text = "俺を侮辱しやがったな！剣を抜け、この野郎！";
			link.l1 = "腕がなけりゃ金庫をどうやって開けるか見ものだな！";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_duel":
			DialogExit();
			LAi_SetSitType(npchar);
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(npchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
			i = makeint(MOD_SKILL_ENEMY_RATE/4);
			pchar.questTemp.FMQT = "duel";
			PChar.questTemp.duel.enemy = NPChar.id;
			if (MOD_SKILL_ENEMY_RATE > 2) PChar.questTemp.duel.enemyQty = i;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
		break;
		
		case "pirate_6":
			dialog.text = "あんたは商売人だな、それは認めてやるぜ。案外やっていけるかもしれねえ。50ドゥブロンだ。テーブルの上に置いとくぜ。";
			link.l1 = "金貨五十枚だと？ただのブリキにか？くそったれ。鍵をテーブルに置け。今すぐだ。";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "ずいぶん高いな……まあいい。持っていけ。";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "なかなかの値段だな……いいだろう。すぐに持ってくるぜ。ここで待ってろ。";
				link.l2.go = "pirate_wait";
			}
		break;
		
		case "pirate_wait":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_SetSitType(npchar);
			npchar.Dialog.currentnode = "pirate_dublon";
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
		break;
		
		case "pirate_dublon":
			NextDiag.TempNode = "pirate_dublon"; // mitrokosta правка явного бага
			dialog.text = "50ドゥブロン持ってきたか？";
			link.l1 = "そうだな、あんたはあれがなくても生きていけると思うぜ。\n鍵だ。\nテーブルの上にある。";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "ああ。持っていけ。";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "まだ集めているところだ。";
				link.l2.go = "exit";
			}
		break;
		
		case "pirate_7":
			dialog.text = "踊ろうか？";
			link.l1 = "俺が先導するぜ。";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_8":
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			Log_Info("You have given 50 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "よし。頭を使えば、八枚金貨と首を持ってここを出られるかもしれねえぜ。鍵を持っていけ、そして俺の忠告を聞け。 タダで教えてやる。ルヴァスールの女は魚みてえに間抜けだが、自分は賢いつもりでいる。信用するな。股間にしまって、 財布に気をつけろ。大した相手じゃねえが、用心して旦那を巻き込むなよ。最後にもう一つ――あいつの部屋に宝石をしまう箱がある、簡単に開けられるぜ。あいつの取り分もそこに入れるだろう。ちゃんと聞いたな。 海では気をつけろよ、兄弟。いいか、女より仲間が先だぜ。";
			link.l1 = "幸運を祈るぜ、相棒……";
			link.l1.go = "pirate_9";
		break;
		
		case "pirate_9":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "key";
			pchar.questTemp.FMQT.Caution = "true";
			FMQT_KeyNextDay();
			pchar.quest.FMQT_late3.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.FMQT_late3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late3.function = "FMQT_KeyTime";
			AddQuestRecord("FMQ_Tortuga", "10");
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
		break;
		
		case "mercen":
			PlaySound("Voice\English\EvilPirates10.wav");
			dialog.text = "くそっ！まさか……あの女なんてくたばっちまえ！俺の親方はああいう女には関わるなって言ってたんだ。だが、仕事は仕事だ。 結局お前を捕まえてやるぜ。";
			link.l1 = "ほうほう、相棒……あの女、俺たち二人とも騙そうとしたみたいだな。まあ、驚きゃしねえよ。これ以上争う理由もねえだろ？ 仕事が欲しいか？ちょうどあるぜ。お前には腕がある、俺の船にはそういう奴が必要なんだ。飯、寝床、定期的な給金、 ラム酒、それに戦利品の分け前もきっちりやる。証文も書いてやるぜ。どうだ？";
			//if(CheckCharacterPerk(pchar, "IronWill") || CheckCharacterPerk(pchar, "HT2") || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) link.l1.go = "mercen_1";
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) link.l1.go = "mercen_1";
			else link.l1.go = "mercen_4";
		break;
		
		case "mercen_1":
			//if(CheckCharacterPerk(pchar, "IronWill")) notification("Iron Will", "IronWill");
			//if(CheckCharacterPerk(pchar, "HT2")) notification("Mimicry", "Mimicry");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) notification("Skill Check Passed", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) notification("Skill Check Passed", SKILL_FORTUNE);
			dialog.text = "お前は口がうまいし、評判も先に立ってるな、船長。それは認めるぜ。ああ、乗った！で、お前の船の名前は何だ？";
			link.l1 = "「」"+pchar.ship.name+"「。甲板長に話せば寝床を見つけてくれるぜ。乗船おめでとう！」";
			link.l1.go = "mercen_2";
		break;
		
		case "mercen_2":
			dialog.text = "はっ！俺も出世したもんだぜ。あの女に俺の分も蹴りを入れてやってくれ。";
			link.l1 = "...";
			link.l1.go = "mercen_3";
		break;
		
		case "mercen_3":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_MercenHire", 10.0);
			AddQuestRecord("FMQ_Tortuga", "17");
		break;
		
		case "mercen_4":
			//if(!CheckCharacterPerk(pchar, "IronWill")) notification("Perk check failed", "IronWill");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35) notification("Skill Check Failed (35)", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 21) notification("Skill Check Failed (21)", SKILL_FORTUNE);
			dialog.text = "口の利き方は悪くねえな。だが、本物のプロを仲間にしたいなら、まだまだ甘いぜ。覚えとけよ、もし次があるならな。";
			link.l1 = "やってみろ。急いでくれ、俺はこれからご婦人との約束があるんだ。";
			link.l1.go = "mercen_5";
			link.l2 = "今日は二度目のチャンスはないぜ。俺は忙しい男だ、だからカーペットを汚すなよ。 お前みたいな小物のプタンのために命を捨てるほどの報酬はもらってねえだろう。\nそもそも、ちゃんと金をもらってるのか？";
			link.l2.go = "mercen_6";
		break;
		
		case "mercen_5":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQT_MercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "mercen_6":
			dialog.text = "お前の言う通りだ。まだ誰からも報酬はもらってねえ……今すぐ片付けてやるさ。好きにしろよ……";
			link.l1 = "...";
			link.l1.go = "mercen_7";
		break;
		
		case "mercen_7":
			DialogExit();
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("FMQ_Tortuga", "18");
			pchar.questTemp.FMQT.Roomfight = "true";
			FMQT_WifeFinalTalk();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
