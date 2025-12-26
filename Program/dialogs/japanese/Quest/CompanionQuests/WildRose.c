void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
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
			dialog.text = "何の用だよ？";
			link.l1 = "「何でもない。」";
			link.l1.go = "exit";
		break;
		
		// =================================================================
		// ================== ЭТАП 1. «ЛОЩИНА ВЛЮБЛЁННЫХ» ==================
		// =================================================================
		case "Mary_1":
			dialog.text = ""+pchar.name+"ねえ、こっち見てよ！";
			link.l1 = "「静かに」 "+npchar.name+"、ここにはあたしたちだけじゃないかもしれないよ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_2":
			dialog.text = ""+pchar.name+"!";
			link.l1 = ""+npchar.name+"え？ここまでずっとあたしのこと追いかけてきたの？";
			link.l1.go = "Mary_3";
		break;
		
		case "Mary_3":
			dialog.text = "あたしの判断は正しかったみたいだよ、ね！ここで何があったの？";
			link.l1 = "「もし知ってたら、」 "+npchar.name+"…もし知っていればな…";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_4":
			dialog.text = "「なんてこった……」";
			link.l1 = "うん、かわいそうに、死ぬ前にずいぶん苦しんだみたいだね。誰だってそんな最期は迎えたくないよ……";
			link.l1.go = "Mary_5";
		break;
		
		case "Mary_5":
			dialog.text = "あれが彼女の旦那なの？一体あいつら、ジャングルで何してたんだ！？逃亡奴隷の話、聞いてなかったのか？";
			link.l1 = "もうその質問には答えられないんじゃないかな……";
			link.l1.go = "Mary_6";
		break;
		
		case "Mary_6":
			dialog.text = "これをやった奴は、まだどこか近くにいると思う？";
			link.l1 = "ありえるね。だから、静かにしたほうがいいよ――あたしたちが見つける前に、向こうに見つからないようにしないと。";
			link.l1.go = "Mary_7";
		break;
		
		case "Mary_7":
			dialog.text = "「もう遅い」 "+pchar.name+"……もう見つかっちゃったみたいだよ。あそこを見て。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "おいおい、野郎ども、これを見てみろよ。まるで恋人たちの隠れ家じゃねえか、へっへっ。 二羽の恋人がくたばったと思ったら、すぐに次のカップルが現れるってわけだな……";
			if (GetOfficersQuantity(pchar) >= 2)
			{
				link.l1 = "賢いね。でも、数を数えられないの？あの可哀想な連中と違って、あたしたちはここで一人じゃないんだよ。";
				link.l1.go = "Naemnik_2";
			}
			else
			{
				link.l1 = "あたしたちとやり合うのは、ちょっとややこしいことになるよ、信じていいから…";
				link.l1.go = "Naemnik_4";
			}
		break;
		
		case "Naemnik_2":
			dialog.text = "あんたがあいつらより賢いって言いたいけど――それは神をも恐れぬ嘘になるね。数が多くても、あの野郎どもには勝てなかったはずだよ。\nそれに、あんたの可愛い子も、今あんたの足元に転がってるあの子と同じ運命を辿ってたんじゃないかな…";
			link.l1 = "逃亡奴隷のことを言ってるの？こいつもその一人なの？じゃあ、あんたたちはビショップの仲間ってこと？";
			link.l1.go = "Naemnik_3";
		break;
		
		case "Naemnik_3":
			dialog.text = "ああ、全部の質問に「はい」だよ。二日以上も兵士たちと一緒に島中を奴らを追いかけ回したんだ。そしたら、 あの野郎どもが二手に分かれてさ。一部は洞窟の方へ逃げて、衛兵たちが後を追った。残りは湾の方へ走ったんだ。 ここから西に半マイルほどのところで待ち伏せされて、何人か仲間を失ったよ。 俺たちが立て直して状況を把握しようとしてたときに、奴らは……あの愚かな娘に好き勝手しやがったんだ……\n";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		
		case "Naemnik_4":
			dialog.text = "楊枝は自分で持っときな、伊達男――あたしやみんなをイライラさせないでよ。あんたが湾で倒したあの野郎どもに囲まれたら、 どれだけ役に立つか見てみたいもんだね。運が良かったのは一人だけ――でもそれも長くは続かないよ…あの野郎がビショップの手に渡ったらすぐにでも…";
			link.l1 = "つまり、あんたたちはあいつの傭兵なの？";
			link.l1.go = "Naemnik_5";
		break;
		
		case "Naemnik_5":
			dialog.text = "まあ、明らかに駐屯兵じゃないよ。あいつらの怠けぶりがなければ、昨日のうちにあの悪党どもを捕まえてたはずだし……あの馬鹿と奥さんもまだ生きてたのにね…";
			link.l1 = "じゃあ、これはあんたの仕業じゃないんだね…";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "俺たちを誰だと思ってるんだ、あん？まあ、俺たちは天使じゃねえけど、気が向いたら娼館に行くさ、でも…";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		case "Naemnik_6_add":
			StartInstantDialog("WildRose_Naemnik_Rab", "Naemnik_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_7":
			dialog.text = "「あいつは嘘をついてる、歯の根も合わないほどの大嘘つきだよ――あの汚いろくでなし！聞いちゃだめだよ、」 "+GetAddress_Form(NPChar)+"「！あたしたちはあの可哀想な人たちに指一本触れてないよ！」";
			link.l1 = "「へえ、そうなの？で、なんであんたの言うことを信じて、あいつのは信じないってわけ？」";
			link.l1.go = "Naemnik_8";
			link.l2 = "ね？それとも、結局嘘をついてるのはあんたの方なんじゃない？あたしには聖人には見えないけど。";
			link.l2.go = "Naemnik_9";
		break;
		
		case "Naemnik_8":
			dialog.text = "あのさ、ちょっと自分で考えてみてよ、お願いだから！あたしたち、あの化け物ビショップから逃げて、 二日間もジャングルをさまよって、足跡を消しながら――それが何のためだったの？今になって可哀想な女の人を襲って、あの吸血鬼どもに追いつかれるため！？ あたしの仲間たち、やっとの思いであの浜辺にたどり着いたんだよ、\n "+GetAddress_Form(NPChar)+"！あいつらに好き勝手させたのは、こっちにマスケットを撃つ力すら残ってなかったからだよ……全部あいつらの仕業だ、あたしたち、ちゃんと見てたんだよ！… ";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Naemnik_9":
			dialog.text = "あのさ、ちょっと自分で考えてみてよ、お願いだから！俺たちはあの悪魔みたいなビショップから逃げて、 二日間もジャングルをさまよって、足跡を消してきたんだ――何のために？今さら可哀想なご婦人を辱めて、あの吸血鬼どもに追いつかれるためか！？ 仲間たちはやっとの思いであの浜辺にたどり着いたんだよ、 "+GetAddress_Form(NPChar)+"！あいつらに好き勝手させたのは、あたしたちがマスケットを撃つ力も残ってなかったからだよ…全部あいつらの仕業さ、あたしたちはこの目で見たんだよ… ";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		case "Naemnik_9_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_10":
			dialog.text = "黙れ、カスパー、このみすぼらしい野良犬め！";
			link.l1 = "...";
			link.l1.go = "Naemnik_10_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab"));
		break;
		case "Naemnik_10_add":
			StartInstantDialog("Mary", "Naemnik_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_11":
			dialog.text = "何だって！？";
			link.l1 = "...";
			link.l1.go = "Naemnik_11_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_11_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_12":
			dialog.text = "あんた、耳が遠いのかい、お嬢さん？あたしはあいつに口を閉じろって言ったんだよ。 うちのジェリーは何時間でも大ぼらを吹けるんだ――ほんと、才能だよ！司教様は舌を引っこ抜いて食わせてやろうとしたけど、結局は哀れに思ったみたい。 あたしに言わせりゃ、もったいない話だけどね！";
			link.l1 = "...";
			link.l1.go = "Naemnik_12_add";
			CharacterTurnByChr(npchar, CharacterFromID("Mary"));
		break;
		case "Naemnik_12_add":
			StartInstantDialog("Mary", "Naemnik_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_13":
			dialog.text = "でも…あんた、カスパーって呼んでたよね、うん…";
			link.l1 = "...";
			link.l1.go = "Naemnik_13_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_13_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_14":
			dialog.text = "聞けよ、旦那、自分の彼女に説明してやれよ、人間ってのはな、こんなチビのクズでも名前が一つだけじゃねえんだ。 美人はコルクみたいに頭が悪いって話も聞いたことあるが、俺は納得できねえな…";
			link.l1 = "...";
			link.l1.go = "Naemnik_14_add";
			CharacterTurnByChr(npchar, pchar);
		break;
		case "Naemnik_14_add":
			StartInstantDialog("Mary", "Naemnik_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_15":
			dialog.text = "その言葉の代償はちゃんと払ってもらうからね、いい？";
			link.l1 = "メアリー、待って！あたしが自分でやるから。武器をしまって。今すぐに。";
			link.l1.go = "Naemnik_15_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "normal to fight", "1", 2.5);
			DoQuestFunctionDelay("WildRose_Etap1_EscapeSlaves_6_1", 3.0);
		break;
		case "Naemnik_15_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_16":
			dialog.text = "あら、ここには本物の紳士がいるのね。まあ、あんたの礼儀はあの小さな虫けらの悲鳴よりずっとマシだよ。あいつ、 自分のかわいそうな奥さんよりも大声で叫んでたんだから――あの丘の向こうからでも聞こえるくらいさ。正直、ちょっとは助かったよ――あいつのおかげであの野郎どもを見つけられたんだから…";
			link.l1 = "ここカリブでは、貴族なんて珍しいものさ。さあ、みんな深呼吸しよう――今ここで死ぬことに高貴さなんてないからね。\n";
			link.l1.go = "Naemnik_17";
			link.l2 = "ここにいる悪党はお前たちだけだ。今すぐメアリーに謝れ、そうすれば流血は避けられるかもしれないぞ。";
			link.l2.go = "Naemnik_22";
		break;
		
		case "Naemnik_17":
			dialog.text = "それは反論しづらいね。でも、まずは落ち着いて……";
			link.l1 = "彼女の名前はメアリー・カスパーだよ。これでだいたい分かるでしょ。";
			link.l1.go = "Naemnik_18";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Naemnik_18":
			dialog.text = "「カスパー？あいつの娘か何かか、はは？」";
			link.l1 = "あたしはそれ、全然信じられないよ。だけど、今ならわかってくれたと思うし、 自分の言ったことを取り消してくれるといいんだけどね。";
			link.l1.go = "Naemnik_19";
		break;
		
		case "Naemnik_19":
			dialog.text = "戻ったの？それとも何？あたしに決闘でも挑むつもり？どうぞ……大事な人をジャングルの真ん中に一人きりで置いていくのが怖くなければね、ふふっ。あたしと仲間たちは、 そうなったら大喜びだよ。\n";
			link.l1 = "ほらね、やっぱり本性が出たじゃない。仮面なんてすぐに剥がれちゃったね。";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_22":
			dialog.text = "あんたって、旦那、ほんとに矛盾してるよね――穏やかそうなのに、めちゃくちゃ無作法だし。で、 どうしてあたしがこの赤毛のイカレ女に許しを請わなきゃいけないわけ？";
			link.l1 = "彼女の名前はメアリー・キャスパーで、そして…";
			link.l1.go = "Naemnik_23";
		break;
		
		case "Naemnik_23":
			dialog.text = "カスパー？いやあ、こりゃ驚いた！ジェリー、もしかしてそっちの娘さんかい、ああ？はははは！信じられねえよ！ 誰が想像したってんだよ！";
			link.l1 = "笑っていられるうちに笑ってなよ。あんたみたいな男は、口ばっかりで品もなくて、女をゴミみたいに扱って、 それを遊びだと思ってるんだよね。納屋で生まれてジャッカルに育てられたって感じ？その礼儀知らずも納得だよ。でも、 頭の中が藁でいっぱいなら、まともな常識が入る余地なんてないよね。";
			link.l1.go = "Naemnik_24";
		break;
		
		case "Naemnik_24":
			dialog.text = "ほうほう……ずいぶん生意気な小虫じゃねえか。なあ、相棒、お前の女はハンモックの上でどんなもんなんだ？\nま、俺はちょっと疑ってるけどよ……自分で確かめてみてもいいぜ。";
			link.l1 = "ほら、やっぱり本性が出たね。仮面なんてすぐに剥がれちゃったじゃない。";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_7");
		break;
		
		case "Djerry_1":
			dialog.text = "あんた、本当にあいつらをやっつけたね、 "+GetAddress_Form(NPChar)+"「――あいつらめ。地獄で焼かれちまえ！あたしが間に合わなくて悔しいよ。ここに来る途中で見つけたマスケットは、 遠すぎて手が届かなかったんだ。どうやら、あたしたちが命からがら逃げるときに、誰かが落としたみたい。 あたしが自分であのクソ野郎プリメールを撃てたらよかったのに。」";
			link.l1 = "あんたが戻ってきたってことは、プライマーに相当苦しめられたみたいだね。";
			link.l1.go = "Djerry_2";
		break;
		
		case "Djerry_2":
			dialog.text = "控えめに言ってもそれどころじゃないよ。あいつのせいで、あたしの背中は傷だらけなんだ。\n一番ひどかったのは、水を好きなときに取り上げられたことさ。";
			link.l1 = "あいつらの野郎ども、一人も生き残らなかったのは残念だな。もうすぐ兵隊が来るだろうし、奴を引き渡せたのにな。";
			link.l1.go = "Djerry_3_1";
		break;
		
		case "Djerry_3_1":
			dialog.text = "あたし、なんでだか、えっと、よくわかんないんだよ、\n "+GetAddress_Form(NPChar)+"...";
			link.l1 = "あのね……司令官が彼から自白を無理やり引き出して、あんたの潔白と、亡くなった仲間たちの名誉も晴らしてくれたはずなんだよ。 ";
			link.l1.go = "Djerry_4";
		break;
		
		case "Djerry_4":
			dialog.text = "うんうん、そうだね、はは。で、そのあとウィリアム・ビショップがあたしの皮まで剥ぐってわけだ。 プランテーションの黒人から全部聞いたよ……ビショップは黒か白かなんて気にしない――逃亡者には容赦なく手を下すんだってさ。 ";
			link.l1 = "どうしても何らかの形でプランテーションに戻ってもらうしかないんだよ……";
			link.l1.go = "Djerry_5";
			link.l2 = "じゃあ、プランテーションには戻らないの？";
			link.l2.go = "Djerry_6";
		break;
		
		case "Djerry_5":
			dialog.text = "あんたって本当に冗談好きだよね、誰かに言われたことある？ "+GetAddress_Form(NPChar)+"?";
			link.l1 = "冗談じゃないよ、 "+npchar.name+"。俺がここに偶然来たと思ってるのか？お前らの小さな一味を追いかけてジャングルに入ったんだ、 全員をプランテーションに引きずって帰って、ちょっとばかり金を稼ごうと思ってな。でも生き残ってるのはお前だけだ。 一人じゃ大した値打ちもねえし、もしかしたら逃がしてやるかもな。だが教えてくれ、お前は何を考えてたんだ？ お前は一人だ。他の奴らはみんな死んだ。何をしようとしてるんだ、くそっ？丘や茂みに隠れ続けて、 そのうち銃弾に当たるか、熱病で倒れるか、ジャガーに食われるまで待つつもりか？";
			link.l1.go = "Djerry_8";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Djerry_6":
			dialog.text = "あんたって本当に冗談好きだね、誰かに言われたことある？ "+GetAddress_Form(NPChar)+"?";
			link.l1 = "冗談じゃないよ、 "+npchar.name+"。俺がここに偶然たどり着いたと思ってるのか？お前らの小さな一味を追ってジャングルに入ったんだ、 みんなをプランテーションに引きずって戻して、ちょっとばかり金を稼ごうと思ってな。でも生き残ったのはお前だけだ。 一人じゃ大した値打ちもねえし、もしかしたら逃がしてやるかもな。だが教えてくれよ、何を考えてたんだ？ お前は一人だ。他の連中はみんな死んだ。いったい何をしようってんだ、この野郎？丘や茂みに隠れ続けて、 そのうち弾に当たるか、熱病でくたばるか、ジャガーに食われるのを待つつもりか？";
			link.l1.go = "Djerry_8";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Djerry_8":
			dialog.text = "「この方がいいさ、神様だけが知ってるんだよ」 "+GetAddress_Form(NPChar)+" あたしに言わせれば、ビショップがあたしに用意してたどんな拷問で死ぬより、そっちのほうがずっとマシだよ。\nでも、正直そんなに悪くないんだ――ラグド・ポイントの近くに帆付きのボートを隠してあるからね。";
			link.l1 = "バルバドスに一番近い陸地は、先住民のいるドミニカと、スペイン人のいるトバゴだよ。\nどっちが"+GetSexPhrase("お前","あんた")+"にとってマシか、あたしにも分からないね……";
			link.l1.go = "Djerry_9";
		break;
		
		case "Djerry_9":
			dialog.text = "あたしはドンたちと賭けてみるよ――密輸業者や海賊はトバゴによく錨を下ろすからね。ああ、その不満そうな顔、ちゃんと見えてるよ、 "+GetAddress_Form(NPChar)+"。でも、あたしは国に忠実に仕えてきたんだよ。なのに、国があたしを採石場に放り込んだ時、どうすればよかったの？";
			link.l1 = "あたしは別に責めてるわけじゃないよ、 "+npchar.name+"。誰にも自分の道があるんだ。さあ、火薬と弾をもっと持って行け。兵隊が来る前に行くんだ。";
			link.l1.go = "Djerry_10";
		break;
		
		case "Djerry_10":
			dialog.text = "「ありがとう」 "+GetAddress_Form(NPChar)+"。それから、君だよ、お嬢さん、えっと、メアリー。（お辞儀する）もちろん、血縁じゃないけど、こんな、えっと、 状況で同じ姓の人に会うなんて……本当に予想外で……";
			link.l1 = "...";
			link.l1.go = "Djerry_10_add";
		break;
		case "Djerry_10_add":
			StartInstantDialog("Mary", "Djerry_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Djerry_11":
			dialog.text = "そうだと思うよ、うん。じゃあ、さよなら、ジェリー。";
			link.l1 = "...";
			link.l1.go = "Djerry_12";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab_mushketer"));
		break;
		
		case "Djerry_12":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_9");
		break;
		
		case "Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+"「ねえ、何か悩んでるの？自分と同じ名前の人に、ずいぶんあっさり別れを告げたじゃない。」";
			link.l1.go = "Mary_12";
		break;
		
		case "Mary_12":
			dialog.text = "あたし、ただあの男のそばから一刻も早く離れたかっただけだよ……あいつの話、穴だらけなんだよね。";
			link.l1 = "何言ってるの、あなた？";
			link.l1.go = "Mary_13";
		break;
		
		case "Mary_13":
			dialog.text = "司教の手下から聞いた話の後じゃ、あの哀れな人たちが司教の手で殺されたのは間違いないと思うよ。\nでもその前に……カスパー、あいつが何を言ってたか、ちゃんと聞いてた？";
			link.l1 = "「それで、何が気に入らなかったの、ねえ？」";
			link.l1.go = "Mary_14";
		break;
		
		case "Mary_14":
			dialog.text = "「浜辺に隠されたボートがあるって彼は言ってるんだ。でも、プランテーションから逃げ出したのは二十人以上だよ。 だから、そのボートはかなり大きいはずでしょ？ジェリーは海軍の脱走兵で、 一人で大きな船を操るのが簡単じゃないって、よく分かってるんだよ、ね…」\n";
			link.l1 = "帆を上げて進路を保てば、あとは風がすべてやってくれるんだよ。\nもちろん、本当に危険な賭けだけど、もしかしたら、 海で死ぬ方がプランターの処刑人に殺されるよりマシかもしれないね。";
			link.l1.go = "Mary_15";
		break;
		
		case "Mary_15":
			dialog.text = "たぶんね。でも、今になって他にもおかしいことがあるって気づいたんだよ…彼の話だと、彼とその仲間たちは傭兵たちがあの可哀想な女の子を虐げるのを遠くから見ていたって…";
			link.l1 = "地獄に落ちる勢いで自分たちの船に逃げるんじゃなくて…うん、あんたが言いたいこと、わかるよ。 "+npchar.name+"…ね。カスパーさんにもう少し質問したほうがいいかも…";
			link.l1.go = "Mary_15_add";
		break;
		case "Mary_15_add":
			StartInstantDialog("WildRose_Naemnik_Rab_mushketer", "Mary_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Mary_16":
			dialog.text = "...";
			link.l1 = " 「ねえ、」 "+npchar.name+"、古い友よ！ちょっと待って……";
			link.l1.go = "Mary_17";
		break;
		
		case "Mary_17":
			dialog.text = "...";
			link.l1 = " くそっ！！！メアリー、気をつけろ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_11");
		break;
		
		case "Mary_21":
			dialog.text = "卑劣な悪党め！あたしたちがあいつの命を救ったのに、あいつは！それって、どういうことなの、 "+pchar.name+"？じゃあ、そういうことになるんだね…";
			link.l1 = "「ああ、」 "+npchar.name+"……ここで何が起きたのか、本当のことを知っている生き残りはもう誰もいないんだよ……";
			link.l1.go = "Mary_22";
		break;
		
		case "Mary_22":
			dialog.text = "ここを出たほうがいいよ、 "+pchar.name+"。もし兵士たちにここで見つかったら、面倒なことになるよ。";
			link.l1 = "そうだね、メアリー。行こう……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_15");
		break;
		
		case "Mary_23":
			dialog.text = "ねえ、 "+pchar.name+"…こんなことの後だし、あたし、いい酒が欲しいんだよ、ね。";
			link.l1 = "異論はないよ、ダーリン。あたしも一杯やりたい気分だよ。『アイリッシュ・カッコールド』に寄っていこう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_2");
		break;
		
		case "Barmen_1":
			dialog.text = "起こしてごめんね、船長…";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "まあ、少なくともノックはしたんだね、そこは評価するよ。で、何の用なの、あたしに？";
				link.l1.go = "Barmen_2";
			}
			else
			{
				link.l1 = "ノックしてくれて助かったよ、旦那。もし勝手に入ってきてたら、今ごろ階段から転げ落ちてたところだぜ。\n何じっと見てんのさ？さっさと言いなよ――なんでここまで来たの？";
				link.l1.go = "Barmen_2";
			}
		break;
		
		case "Barmen_2":
			dialog.text = "町の住人の一人があんたに会いたいって――ルイス・ガーノンだよ。あんたと大事な話があるって言ってたよ。";
			link.l1 = "その名前は聞いたことがないな。大事な用が本当にあるんだろうな、こんな……仕事からあたしを呼び出すなんて。中に入れてあげて……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_5");
		break;
		
		case "Lewis_1":
			dialog.text = "こんにちは、旦那 "+pchar.lastname+"…カスパー嬢。";
			link.l1 = ""+TimeGreeting()+"、旦那 "+npchar.lastname+"……あたしたち、前に会った覚えはないよ。じゃあ、どうしてあたしたちのこと知ってるの？";
			link.l1.go = "Lewis_2";
		break;
		
		case "Lewis_2":
			dialog.text = "思い出せない？ああ、そうか……あたしの顔、血と埃でぐちゃぐちゃだったんだよ。数時間前に鏡で自分の姿を見て、あたし自身もゾッとしたんだから…";
			link.l1 = "...";
			link.l1.go = "Lewis_2_add";
		break;
		case "Lewis_2_add":
			StartInstantDialog("Mary", "Lewis_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_3":
			dialog.text = "あんた…あんたがその男だよ、うん、あたしたちが見つけたんだ、そして…";
			link.l1 = "...";
			link.l1.go = "Lewis_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_3_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_4":
			dialog.text = "そして、あたしのスーザン。かわいそうなスージー…";
			link.l1 = "...";
			link.l1.go = "Lewis_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_4_add":
			StartInstantDialog("Mary", "Lewis_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_5":
			dialog.text = "あんたは死んだと思ってたよ。それで…あの人はあんたの奥さんだったんだよね？";
			link.l1 = "...";
			link.l1.go = "Lewis_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_5_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_6":
			dialog.text = "はい、お嬢さん。あの人はあたしの妻だったんだよ、でもあたしは恐怖で体が動かなくて……何もできなかったんだ。神様、神様……";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_8");
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		
		case "Lewis_7":
			dialog.text = "（すすり泣き）あいつら、あたしを殴って、見せつけたんだよ……";
			link.l1 = "「立って」 "+GetAddress_Form(NPChar)+"……あんたのせいじゃないよ。あんな大勢の人斬り相手に、一人で立ち向かえる人なんていないんだから。\n";
			link.l1.go = "Lewis_8";
		break;
		
		case "Lewis_8":
			dialog.text = "あんなにたくさんいた、すごくたくさん……でも、それでも、あたし……";
			link.l1 = "それでも、あんたは生き延びて、奥さんを殺した奴らは地獄で焼かれてる。わずかな慰めかもしれないが、 それでも何かにはなる、旦那\n "+npchar.lastname+"。でも、ちょっと聞きたいことがあってさ…";
			link.l1.go = "Lewis_9";
			LAi_ActorAnimation(npchar, "ground_standup", "WildRose_Etap1_City_8_1", 7);
		break;
		
		case "Lewis_9":
			dialog.text = "ねえ、旦那 "+pchar.lastname+"?";
			link.l1 = "あいつらは誰だったんだい？司教の用心棒か、それとも逃げ出した奴隷かい？";
			link.l1.go = "Lewis_10";
		break;
		
		case "Lewis_10":
			dialog.text = "それはジェレミー・カスパーと他の逃亡者たちだったんだよ。ブルース・プライマーとその仲間については、 あんたが間違ってたんだよ。";
			link.l1 = "司教の傭兵たち？";
			link.l1.go = "Lewis_11";
		break;
		
		case "Lewis_11":
			dialog.text = "うん。ブルースは確かにろくでなしで、ビショップのために汚い仕事もたくさんやってたけど、 あいつは強姦魔じゃなかったよ。";
			link.l1 = "あたしにはその時そうは見えなかったよ。でも、あなたと口論するつもりはないよ、\n "+npchar.name+"。でも、あんたは意識があって全部見てたんだから、立ち上がって……\n";
			link.l1.go = "Lewis_12";
		break;
		
		case "Lewis_12":
			dialog.text = "「許して、」 "+GetAddress_Form(NPChar)+"……あたしのことを情けない臆病者って呼んでもいいよ――でも、本当に体が動かなかったんだ、怖すぎてさ。あの悪党どもがスージーとあたしの行く手を塞いだとき、 最初はただ思いっきり叫んだんだ、誰か助けに来てくれるんじゃないかって思ってさ。\n";
			link.l1 = "それで、あんたは殴られたんだよ。";
			link.l1.go = "Lewis_13";
		break;
		
		case "Lewis_13":
			dialog.text = "ジェリーが銃床であたしを殴りつけて、スーザンの目の前でバラバラにしてやるって言ったんだ。あの…恥ずかしいけど、恐怖でほんの数秒、気を失っちゃったと思う。で、その間に…\n";
			link.l1 = "あんたのこと、わかるよ "+npchar.lastname+"。お前の行動に恥じることなんて何もないよ。お前が耐えたことを、誰もが耐えられるわけじゃないんだ。 手を出せなかったのは残念だけど――もう済んだことさ。それでも、せめてお前の奥さんを殺した奴の一人だけでもあの世に送ることができてよかったよ――あいつ、もう少しで俺たちを騙しきるところだったけどな。";
			link.l1.go = "Lewis_14";
			link.l2 = "「つまり、あんたが怖がってたせいで、あたしたちビショップの傭兵どもと戦って殺されかけたってわけ？ なんて素敵な言い訳だね、」 "+npchar.name+"……最後にはなんとか解決できてよかったよ、ちょっと遅くなっちゃったけどね……";
			link.l2.go = "Lewis_15";
		break;
		
		case "Lewis_14":
			dialog.text = "「うん、」 "+GetAddress_Form(NPChar)+"……そのことでお礼を言いに来たんだよ。最初はあいつのことを信じてたとしても……";
			link.l1 = "ブルース・プライマーは、それを実現するためにできる限りのことをしたんだ、まったくあいつめ。 あいつがもう少し口を慎んでいればな…";
			link.l1.go = "Lewis_16";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Lewis_15":
			dialog.text = "「うん、」 "+GetAddress_Form(NPChar)+"……そのことでお礼を言いに来たんだよ。最初はあいつのことを信じてたとしても……";
			link.l1 = "ブルース・プライマーは、そのためにできることは何でもやったんだ、くそったれ。 あいつがもう少し口を慎んでいればな…";
			link.l1.go = "Lewis_16";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Lewis_16":
			dialog.text = "あの日は、みんなが過ちを犯したんだよ……スーザンと私はラグド・ポイントを散歩しに行くべきじゃなかったし、ブルースは余計なことを言うべきじゃなかった……そして君もジェレミーを信じるべきじゃなかった。でも、キャスパー嬢のおかげで、正義は取り戻されたんだ。";
			link.l1 = "...";
			link.l1.go = "Lewis_16_add";
		break;
		case "Lewis_16_add":
			StartInstantDialog("Mary", "Lewis_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_17":
			sld = CharacterFromID("WildRose_Lewis");
			dialog.text = "あんたがあたしに何を聞きたいのか、だいたい分かるよ、旦那\n "+sld.lastname+"。でもあたしはあの男とは何の関係もないんだよ。";
			link.l1 = "...";
			link.l1.go = "Lewis_17_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_17_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_18":
			dialog.text = "わかっています、お嬢さん。あたしはこの部屋に入った瞬間に気づいたよ。あなたとあの人の間には、 少しの面影もないんだ。\nそれでも、スーザンは……この世で起こることに偶然なんてないって、確信してたんだよ。";
			link.l1 = "...";
			link.l1.go = "Lewis_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_18_add":
			StartInstantDialog("Mary", "Lewis_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_19":
			dialog.text = "あんたの奥さんの言う通りだったよ。あたしも何度もこの目で見たんだ、ね。で、それは "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Lewis_19_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_19_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_20":
			dialog.text = "...";
			link.l1 = "まったくその通りだよ。でもさ、今は哲学的な話をしてる場合じゃないと思うんだ。役に立つとも思えないしね。 "+npchar.name+"…そういうことは、時間だけが解決してくれるんだよ。";
			link.l1.go = "Lewis_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), pchar);
			CharacterTurnByChr(CharacterFromID("Mary"), pchar);
		break;
		
		case "Lewis_21":
			dialog.text = "もしかしたら、旦那、あんたの言う通りかもね\n "+pchar.lastname+"。さて、改めてお礼を申し上げます。それではお別れです。あなたとカスパー嬢のためにお祈りいたします。";
			link.l1 = "気をつけてね "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_10");
		break;
		
		case "Mary_31":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "わかってるよ、ねえ、あたし、あの野郎をもう少しで逃がすところだったんだよ…";
			link.l1.go = "Mary_32";
		break;
		
		case "Mary_32":
			dialog.text = "ジェリー・キャスパーっていうろくでなしだよ。";
			link.l1 = "そうだよ…ちょっと待って…まさか、あんた、彼が…って思ってるの…";
			link.l1.go = "Mary_33";
		break;
		
		case "Mary_33":
			dialog.text = "すごく馬鹿みたいに聞こえるのは分かってるんだけど…";
			link.l1 = "もちろん！それに、もしあんたの名字がスミスとかジョーンズだったらどうする？そういう名前の人なんて、 道を歩けば山ほどいるし…その中には絶対悪いことする奴もいるよ…それにあのジェリー、地獄の業火に焼かれちまえって感じだけど――もしかしたら、あいつはカスパーですらないかもしれないよ…";
			link.l1.go = "Mary_34";
			link.l2 = "そうだよ、ダーリン。あたしたちが知ってる限り、彼は本当にジェリーだったかどうかも怪しいし、 偽名を使ってた可能性だってあるんだよ。";
			link.l2.go = "Mary_35";
		break;
		
		case "Mary_34":
			dialog.text = "それでも…あんたにはあたしの気持ちなんて分からないだろうけど、もし彼があんたの名字を名乗ってたら、 どう思うか想像してみてよ\n "+pchar.lastname+".";
			link.l1 = "同じことじゃないよ、メアリー。 "+pchar.lastname+" – は由緒ある家名で、そして…";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Mary_35":
			dialog.text = "それでも……あんたにはあたしの気持ちなんて分からないだろうけど、もし彼があんたの姓を名乗ってたら、 どんな気持ちになるか想像してみてよ\n "+pchar.lastname+".";
			link.l1 = "同じことじゃないんだよ、メアリー。 "+pchar.lastname+" - 名門の家名で、それに…";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Mary_36":
			dialog.text = "カスパー家なんて、あたしたちには名前もなければ、家族もいない、そうでしょ？あたしなんかに気づいてくれたこと、 毎日神様に感謝しなきゃいけないんだろうね、偉そうな連中じゃなくてさ…";
			link.l1 = ""+npchar.name+"…それは全然あたしの言いたいことじゃないよ、わかってるでしょ。\n貴族の家系の者は血で結ばれてるんだ――ただ名字を共有してるだけとは全然違うんだよ。\n前にも言ったけど、名字なんて誰かが勝手に名乗ることだってできるんだから…";
			link.l1.go = "Mary_37";
		break;
		
		case "Mary_37":
			dialog.text = "それだけの話じゃないんだよ、 "+pchar.name+"...";
			link.l1 = "ねえ、あたしたち、今日は本当に長くて大変な一日だったよね。\nジャングルを何マイルも歩き回って、死にかけたし……それに、ほとんど眠れなかったじゃない。\nだから、変なことを考えちゃうのも無理ないよ。\nあたしたち、二人とも、ちゃんと休まなきゃね。";
			link.l1.go = "Mary_38";
		break;
		
		case "Mary_38":
			dialog.text = "あたしは全然変だと思わないけど、うん……明日話そう。";
			link.l1 = "頭をすっきりさせれば、全部もっと早く片付くよ。\n横になって、ねえ。今日はもう忘れちゃおう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_1");
		break;
		
		case "Waitress_1":
			dialog.text = "「大丈夫、」 "+GetAddress_Form(NPChar)+"あれ？なんか変だよ、まるで幽霊でも見たみたい。ラムでも飲む？それともワイン？うちにはいいお酒が揃ってるんだ、 ちょっとリラックスしたらどう？";
			link.l1 = "酒なんかどうでもいいよ。あたしは女の子を探してるんだ…";
			link.l1.go = "Waitress_2";
		break;
		
		case "Waitress_2":
			dialog.text = "それなら、ここは間違いだよ、船長。ここは酒場で、売春宿じゃないんだ。外に出てみな、 通りの向こうにちゃんと見えるから…";
			link.l1 = "聞けよ、冗談を言ってる気分じゃないんだ。赤いダブレットを着た赤毛の娘を探してるんだ、武装してる。 名前はメアリー・キャスパーだ。";
			link.l1.go = "Waitress_3";
		break;
		
		case "Waitress_3":
			dialog.text = "まあ、冗談抜きなら、あたしから話すことは何もないよ。あたしの当番は一時間前に始まったけど、 ここで赤いコートを着た赤毛の子なんて見てないよ。\n";
			link.l1 = "だから夜のうちに彼女は出て行ったんだね…でも、どこに行ったっていうの？！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_4");
		break;
		
		case "Mary_41":
			dialog.text = "おはよう、あたしの大事な人！けっこう長く寝てたね…";
			link.l2 = "「あんた、本当にあたしを心配させたんだから」 "+npchar.name+"…もう、あんなふうに黙っていなくならないでよ…";
			link.l2.go = "Mary_43";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_43":
			dialog.text = "あたし、起こしたくなかったんだよ。それにさ、あんたも時々、何も言わずにふっといなくなるじゃない…";
			link.l1 = "それで、あたしに同じやり方で仕返ししようってわけ？";
			link.l1.go = "Mary_44";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;
		
		case "Mary_44":
			dialog.text = "正直に言うと、ちょっと一人で考えたい時間が欲しかったんだよ、ね。心配かけたくなかったの。";
			link.l1 = "何か気になることでもあるの？";
			link.l1.go = "Mary_46";
		break;
		
		case "Mary_46":
			dialog.text = "昨日の会話のことだよ。名字とか、血のつながりの話……";
			link.l1 = "だから、やっぱりあたしのこと怒ってるんだね……";
			link.l1.go = "Mary_47";
		break;
		
		case "Mary_47":
			dialog.text = "全然違うよ、ダーリン、あたしが言いたかったのはそういうことじゃないんだ。ただ、 急に自分の家族について何も知らないって気づいちゃってさ。例えばあんたは貴族の家の息子でしょ。船の連中だって、 時々自分の家族の話をしてくれる。でも、あたしは何も語れることがないんだ。両親のことも知らないし、正直、 自分がどこで生まれたのかさえ分からないんだよ…";
			link.l1 = "正義の島じゃなかったっけ？";
			link.l1.go = "Mary_48";
		break;
		
		case "Mary_48":
			dialog.text = "エリック、あたしを育ててくれた人が、いつもそう言ってたんだよ。\nでも、それが本当なら、なんで正義の島の誰もあたしの両親のことを話したことがないの？\n一言も、かすりもしないんだ。\n一度ドナルド・グリーンスパンに聞いたことがあるけど、はっきりした答えはもらえなかったんだよ。";
			link.l1 = "あるいは、そうしたくなかったのかもね。";
			link.l1.go = "Mary_49";
		break;
		
		case "Mary_49":
			dialog.text = "そうそう！あたしも同じこと思ったんだよ、ね。あのさ、あたし、これまであんまり深く考えずに生きてきたんだ。 でも昨日、あのクソ野郎ジェリーに会ったとき……自分に問いかけたんだ――あたしの父親って誰？母親は？なんで誰も二人のこと教えてくれなかったの？まるで最初から存在しなかったみたいにさ。 もし父親が、あのジェリーみたいなろくでなしだったらどうしようって。\n";
			link.l1 = "「全然関係ないよ、」 "+npchar.name+"。あんたは他の人たちに育てられたんだ――しかも、すごく立派にね。";
			link.l1.go = "Mary_50";
			link.l1 = "それは違うと思うよ。だって、あんた、今までそんなこと気にしたことなかったじゃない。";
			link.l1.go = "Mary_51";
		break;
		
		case "Mary_50":
			dialog.text = "「でも、あたしには大事なんだよ」 "+pchar.name+"、うん。あたしだって知りたいよ、自分の親が誰だったのか知る権利があるでしょ？そう思わない？";
			link.l1 = "もちろん、あたしは賛成だよ、間違いなくね。\nでも、もしあんたの父さんと母さんについて何か知りたいなら、正義の島で探すしかないよ。\nだって、あんたは二人の名前すら知らないんでしょ？";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "Mary_51":
			dialog.text = "「でも、あたしには大事なんだよ、」 "+pchar.name+"うん、あたしね。自分の親が誰だったのか知りたいんだよ。知る権利があるでしょ？そう思わない？";
			link.l1 = "もちろん、あたしも賛成だよ、間違いなくね。\nでも、もし君の父さんと母さんについて何か知りたいなら、正義の島で探すしかないよ。だって、 君は二人の名前すら知らないんでしょ？";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Mary_52":
			dialog.text = "あたしは知らないよ、あなた。名前を聞いた覚えはないんだ、ね。";
			link.l1 = "それなら、植民地の記録庫に行くのはまだ早いよ。まずは、あの船の墓場に戻って、 あんたの家系の手がかりを探してみなきゃ。";
			link.l1.go = "Mary_53";
		break;
		
		case "Mary_53":
			dialog.text = "「あたしのこと、わかってくれて嬉しいよ、」 "+pchar.name+"。ありがとうございます。";
			link.l1 = ""+npchar.name+"あんたには本当に驚かされるよ、ね。これくらい、あたしの愛する人にできる最低限のことだよ。";
			link.l1.go = "Mary_54";
		break;
		
		case "Mary_54":
			dialog.text = "あたし、どういうわけか、両親のことを何も知らないまま、二十年近くも生きてきたんだよ…";
			// dialog.text = "だって、二十年以上も気にしてなかったんだよね…";
			link.l1 = "...";
			link.l1.go = "Mary_55";
		break;
		
		case "Mary_55":
			dialog.text = "だから、もう少し待てるよ。";
			link.l1 = "「あんたにとってこれは大事なことなんだね、」 "+npchar.name+"…だから、待たせないようにするね、ダーリン。さあ行こう、船に戻らなきゃ。あんたがそこにいてくれるだけで、 あたしも少しは安心できるからさ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_6");
		break;
		
		// ============================================================
		// ================== ЭТАП 2. «ДИТЯ ОСТРОВА» ==================
		// ============================================================
		case "Mary_61":
			dialog.text = "「故郷の岸辺……あのさ、」 "+pchar.name+"、あたしさ、もし十年後にここへ戻ってきても、今とまったく同じ景色なんじゃないかなって思うんだよ、ね。";
			link.l1 = "「たぶん、」 "+npchar.name+"…かもね。内側の輪の船は浮かび続けるけど、ここに住む人たちは変わっちゃうんだよ。";
			link.l1.go = "Mary_62";
			link.l2 = "あたしはそれ、すごく疑ってるよ。ここはもう、全部がギリギリで持ちこたえてるだけなんだ。全部、 ある機械工の天才のおかげでね。";
			link.l2.go = "Mary_63";
		break;
		
		case "Mary_62":
			dialog.text = "そして、十年か十五年前にこの難破船で暮らしていた人たちのことなんて、ほとんど覚えてないんだよ。 あたしの一番近くにいた人たちだけ――アラン、エリック…";
			link.l1 = "まあ、そういうものなんだろうね。全部もみんなも覚えていられるわけじゃないし。あたしだって、 名前や顔なんてパリ時代のことも、ガスコーニュのことなんてなおさら、どんどん記憶から薄れていくんだよ。 年寄りだけの話かと思ってたけど、違うんだね。";
			link.l1.go = "Mary_64";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Mary_63":
			dialog.text = "そして、十年か十五年前にこの難破船で暮らしていた人たちのことなんて、ほとんど覚えてないんだよ。\nあたしにとって一番大事だった人たちだけ――アラン、エリック……";
			link.l1 = "まあ、そういうものなんだよね。全部のことやみんなのことなんて覚えていられないよ。あたしだって、 パリにいた頃の名前や顔なんて忘れちゃうことあるし――ガスコーニュのことなんてなおさらさ。年寄りだけの話かと思ってたけど、そうでもないんだね。";
			link.l1.go = "Mary_64";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Mary_64":
			dialog.text = "でもここって……まるで別世界みたいだよね？想像できる？最近ここに来たばかりの人たちの中には、 正義の島では本土よりも時間が三倍くらい早く流れるって言う人もいるんだよ……\n";
			link.l1 = "あはは、それじゃあ、あんたはいくつになるの？";
			link.l1.go = "Mary_65";
		break;
		
		case "Mary_65":
			dialog.text = "あたし、本気だったんだよ、 "+pchar.name+"、ね！";
			link.l1 = "そうだね、真面目な話をするなら、そろそろ本題に入ろうか。ナーワルズの中でグリーンスペンより年上の人っている？";
			link.l1.go = "Mary_66";
		break;
		
		case "Mary_66":
			dialog.text = "うーん、違うよ、そうは思わない。でも、あたしもう言ったでしょ、あたしがそのことを聞いたとき、 彼は何も言わなかったんだよ。";
			link.l1 = "それでも、二十年前に何が起きたのかを解き明かす手助けをしてくれる人について、他に思い当たる人はいないんだよ。 少なくとも、今のところはね。\nだから、「エスメラルダ号」へ向けて進路を取るよ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_2");
		break;
		
		case "Schmidt_1":
			dialog.text = "「あっ、」 "+pchar.name+" それにメアリー、なんてこった！二人とも…無事で元気そうでよかったよ、へっへ。ここ最近だけで外輪に二、三隻も難破してるんだ――海がやけに荒れててさ。\nそれと、頼むから鍵のかかった扉に無理やり入ろうとするなよ――錠前が壊れちまって、結局直すのは俺なんだからな。ドナルドに会いに来たんだろ？";
			link.l1 = "「やあ、いい日だね、友よ。あたしたちは彼に直接会いに来たんだよ。\nでも、扉が閉まってるってことは、別の船に移ったか、昔の友達には会いたくないってことかもね。」";
			link.l1.go = "Schmidt_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Schmidt_2":
			dialog.text = "どちらでもないよ、あはは。グリーンスペンは今、外輪で訓練中なんだ。";
			link.l1 = "訓練？本気で？リバドスとの新しい戦争に備えてるの？";
			link.l1.go = "Schmidt_3";
		break;
		
		case "Schmidt_3":
			dialog.text = "「戦争は本当の意味で終わったことがないんだ」 "+pchar.name+"。最近は昔ほど喧嘩が多くないんだよね、うん。でも、サンチョの酒場じゃ、今でもたまに誰かが顔を殴られたり……時にはナイフが抜かれることもあるんだ。";
			link.l1 = "うーん、前は一族の連中が酒場に顔を出すことなんてなかったんだよね。";
			link.l1.go = "Schmidt_4";
		break;
		
		case "Schmidt_4":
			dialog.text = "あのさ、あんたが正義の島を離れてから、ちょっと色々変わったんだよ。\nドナルドとエディが、今のところみんなをなんとかまとめてるんだ。\nでも、明日どうなるかなんて誰にも分からないでしょ？\nだから、ドニーおじさんが全部始めたんだよ…";
			link.l1 = "あたしがあんなに苦労して正義の島で虐殺を止めたのは、あんたがここでまた兵隊ごっこをするためだったの？\nそれで、あいつはどれくらい外輪にうろついてるの？";
			link.l1.go = "Schmidt_5";
			link.l2 = "訓練はまあいいけどさ、でもそれでただでさえ危うい休戦が危険にさらされるんじゃない？それに、 グリーンスペンはもうどれくらい前からみんなを訓練してるの？";
			link.l2.go = "Schmidt_6";
		break;
		
		case "Schmidt_5":
			dialog.text = "もう三日経ったよ。彼は明日の正午までには戻るはずなんだ。\nあそこであいつらがマスケット銃をあんなにゴシゴシ磨いてたら、朝には撃つものなんて残ってないんじゃない？ははっ！ ";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Schmidt_6":
			dialog.text = "もう三日経ったよ。明日のお昼までには戻ってくるはずだよ。 あっちであいつらがマスケットをあんなにゴシゴシ磨いてたら、明日には撃つもんなんて残ってないんじゃない？ははっ！ \n";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Schmidt_5_add":
			StartInstantDialog("Mary", "Schmidt_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_7":
			dialog.text = "「『セレス・スミシー』号のあたしの船室、まだ空いてる？それとも、もう誰か入っちゃった？」";
			link.l1 = "...";
			link.l1.go = "Schmidt_7_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_7_add":
			StartInstantDialog("Schmidt_Clone", "Schmidt_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_8":
			dialog.text = "前にあんたがそこにいた時と、何も変わっちゃいないよ。\nドアだってまだ開けてないし、正直言うと、鍵もずっと掃除も油差しもしてないんだ。\nだから、壊す必要があるなら、あたしに言ってくれればいいよ。";
			link.l1 = "...";
			link.l1.go = "Schmidt_8_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_8_add":
			StartInstantDialog("Mary", "Schmidt_9", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_9":
			dialog.text = "もちろん。ありがとう、ユルゲン。";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_3");
			
			//доп
		break;
		
		case "Mary_71":
			dialog.text = "本当に、すべてが昔のままだよ。あたしの物は全部、置いたままの場所にある――まるで一度もここを離れたことがないみたい……ここが、あたしとあんたが初めて出会った場所なんだよ、ね？\n "+pchar.name+"。覚えてるでしょ？";
			link.l1 = "もちろん！あの二人をうまくやっつけてくれて、あたしも斬られるんじゃないかって心配だったよ。\n";
			link.l1.go = "Mary_72";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_72":
			dialog.text = "全然そんなことなかったんだよ、ね！あんた、あたしをまさに死の淵から引っ張り上げてくれたんだから！";
			link.l1 = "運命に導かれて、あんたのところに来たみたいだよ。";
			link.l1.go = "Mary_73";
		break;
		
		case "Mary_73":
			dialog.text = "「本当にそう思うの、あなた？」";
			link.l1 = "もちろんだよ、あたしの愛しい人。それから毎日、あたしを『ケレス鍛冶屋』に導いてくれた運命に感謝してるんだ。";
			link.l1.go = "Mary_74";
		break;
		
		case "Mary_74":
			dialog.text = ""+pchar.name+"…ねえ、あたしのこと、初めて見たときどう思った？";
			link.l1 = "うーん…あたしが覚えてるのは、それが起きた時、胸が張り裂けそうなくらいドキドキしたってことだけ。あんたは本当に…";
			link.l1.go = "Mary_75";
		break;
		
		case "Mary_75":
			dialog.text = "何？";
			link.l1 = "あたしが今まで出会った誰とも違うんだよ。あんたの気品、声……それにあの赤いダブレット。あたし、最初からあんたには敵わなかったんだ。ねえ、前から気になってたんだけど、 どうして赤いダブレットなの？ドレスとかコルセットじゃなくてさ？";
			link.l1.go = "Mary_76";
		break;
		
		case "Mary_76":
			dialog.text = "あたしがそれを見つけたのは九歳のとき、外輪でだったんだよ。あの頃はあそこをうろうろするのが大好きで――新しいものを探したり、島じゃ手に入らないものを見つけたり、特に本なんかね。 すぐにでも着てみたくてたまらなかったけど、そのときのあたしには大きすぎて、飲み込まれちゃいそうだったんだ。 だから、他の宝物と一緒に隠しておいたの――水面から突き出してる見張り台のひとつにね。";
			link.l1 = "それで、自分にふさわしくなったと思ったら、取り戻しに行ったの？";
			link.l1.go = "Mary_77";
		break;
		
		case "Mary_77":
			dialog.text = "数年前、赤い上着を着た勇敢な船長について書かれた本を見つけたんだよ。彼は何も怖がらず、 愛する人のために何百人もの敵に立ち向かったんだって。\nそれで、あたしも初めてダブレットを着てみたの。そうすると、勇気が湧いてくるんだよ。";
			link.l1 = "その抗いがたい魅力、ねえ、ダーリン！でもさ、今はね、あたしが欲しいのはたったひとつだけ……それを、あんたから脱がせたいんだよ……\n";
			link.l1.go = "Mary_78";
		break;
		
		case "Mary_78":
			dialog.text = "「じゃあ、何を待ってるの、あたしの勇敢な船長？」";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_5");
		break;
		
		case "Mary_81":
			dialog.text = "おはよう、ダーリン。ナーワル号の連中が今ちょうど「エスメラルダ」と「サン・ガブリエル」に戻ったんだよ、 ドナルドも一緒さ。あたし、ボートのひとつで彼を見かけたんだ、うん。";
			link.l1 = "おはよう、おはよう…正直言うと、あんな夜の後なら昼まで寝てたいけど、あんたはもう起きて、ちょこまか動き回ってるんだね。\n";
			link.l1.go = "Mary_82";
		break;
		
		case "Mary_82":
			dialog.text = "昨日はダブレットと見張り台の話をしたよね、あたしがそこに隠してたってやつ…そしたら急に、あの頃が恋しくなっちゃってさ、みんなから隠れて、世界中の本を静かに読むためにあそこに登ってた日々 …気がついたら、あたし、そこへ向けて帆を上げてたんだ。昔は何時間もあそこで過ごしてたけど、今日は…ただ日の出を眺めてた。そして気づいたの、世界中の何よりも、あたしはあなたのそばにいたいって。";
			link.l1 = "「そしてあたしも、あなたのそばにいたいんだよ」 "+npchar.name+"…さて、ドナルドのところへ行こうか？話したいことが山ほどあるよ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_7");
		break;
		
		case "Grinspy_1":
			dialog.text = ""+pchar.name+"「おお、メアリー、会えて嬉しいぞ！昨日お前が来たことはもう聞いておる。わしも『ケレス鍛冶屋』 に寄ろうと思っておったが、先を越されてしまったな。この年寄りもお前くらい若ければなあ…」";
			link.l1 = "あんたも自分のエネルギーは十分あるじゃない、あたしたちも見てきたしね。訓練のほうはどうだった？";
			link.l1.go = "Grinspy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_2":
			dialog.text = "思ったよりずっと良かったよ。敵船への乗り込みや船室の突入の練習もしたし……全体的にうまくやれたんだ。うん、あたし、みんなを結構しごいたけど、それが彼らのためになったんだよ。みんな、 ずっと体を動かしてなかったからさ、ああ、ほんと久しぶりだった、はは。";
			link.l1 = "で、何があんたをそんな大それたことに駆り立てたの？正義の島が、あんたには静かすぎたってわけ？";
			link.l1.go = "Grinspy_3";
		break;
		
		case "Grinspy_3":
			dialog.text = "うーん、あんたの声にちょっと不満そうな響きがあるね、\n "+pchar.name+"…あんたには、そうなる権利があるんだろうね…";
			link.l1 = "「本当に、」 "+npchar.name+"?";
			link.l1.go = "Grinspy_4";
		break;
		
		case "Grinspy_4":
			dialog.text = "あたしたちが互いに喉を掻き切らずに済むように、この腐った難破船の間をずいぶん走り回らなきゃならなかったよね、 あたしはそれを忘れてないよ。誰も忘れてないさ。";
			link.l1 = "「それであたしの努力に報いるつもり？やっぱり言われてる通りだね――本物の戦士は平和に苦しむものなんだよ。」";
			link.l1.go = "Grinspy_5";
			link.l2 = "それに、あたし正直言うとね、あんたの分別に期待してたんだよ、海賊連中やリバドスの奴らよりも、ずっとさ。";
			link.l2.go = "Grinspy_6";
		break;
		
		case "Grinspy_5":
			dialog.text = "最後まで言わせてくれ。ああ、俺たちはなんとか平和を保ったが、俺たちの違いが消えたわけじゃない。 少なくとも黒い肌の異教徒たちとはな。先週も、ナーワルの一人が酒場の喧嘩で殺されたんだ。だが、 俺たちもきっちり仕返しはしたさ…";
			link.l1 = "うん、うん――いつもそうやって始まるんだよね。";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_6":
			dialog.text = " 最後まで言わせてくれ。ああ、俺たちはなんとか平和を保ったけど、俺たちの違いが消えたわけじゃない。 少なくとも黒い肌の異教徒たちとはな。先週も、ナーワルの一人が酒場の喧嘩で殺されたんだ。でも、 俺たちもきっちり仕返ししてやったさ…";
			link.l1 = "あたしさ、これっていつもそうやって始まるんだよね。";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_7":
			dialog.text = "「あんた、二つ勘違いしてるよ、」 "+pchar.name+"まず最初に、始まるんじゃなくて、続いてるんだよ。もしこれで終わるって素直に思ってたなら、それは間違いだよ。 あとね、あたしは聖人じゃないから、やられっぱなしで済ますつもりもない。 黒人たちがまた手に負えなくなってきてるし、あたしはそれが気に入らない。ちなみにデクスターも同じだけど、 あいつは自分を偉い政治家だと思い込んでて、争いごとには関わりたくないらしい。だから、いろいろ考えた結果、一番…痛みの少ない形でこのかりそめの平和を保つ方法を選んだんだ。\n";
			link.l1 = " あんた、リバドスたちをその小さな訓練で脅かそうってわけ？";
			link.l1.go = "Grinspy_8";
		break;
		
		case "Grinspy_8":
			dialog.text = "数週間前に、軍用の積み荷を積んだイギリスのガレオン船が外輪に打ち上げられたんだよ、 信じられないかもしれないけど…でも一番すごかったのは、真新しいマスケット銃が五十丁と上等な火薬さ。それにボートもね…塗料がまだ乾いてなかったんだよ！古いボートはもうボロボロで、 嵐の後は無事なボートなんてほとんど残ってないんだから、ほんとに…\n";
			link.l1 = "それで全部がイッカク団のものになったのか？";
			link.l1.go = "Grinspy_9";
		break;
		
		case "Grinspy_9":
			dialog.text = "あたし、もしかしたら提督にも話してたかもしれないけど、あの人、自分が一番賢いって思ってるからさ、 あたしまでバカに見られたくないんだよね。\nでも、まあ、あたしの作戦はうまくいったんだから、いいでしょ？";
			link.l1 = "ブラック・エディが「もうお前の仲間を殺さない」って手紙を送ってきたのかい？";
			link.l1.go = "Grinspy_10";
		break;
		
		case "Grinspy_10":
			dialog.text = "ブラック・エディは自分の黒人たちに静かにしてろと命じたんだ。あたしがいない間に、あいつらがもっと図々 しくなるんじゃないかって心配してたけど――実際はまったく逆だったよ。リバドスの連中は大人しくしてて、うちの仲間にも、時々 ちょっかい出してた町の連中にも近づこうとしない。黒人は黒人――力しか通じないんだって、アランがよく言ってたよ。もしそれが間違いだったら、 この船が今すぐ海の底に沈んでもいいさ！";
			link.l1 = "で、しばらくしたらまた奴らが騒ぎ出したら、 あんたは新しいマスケットでフューリー号とプロテクター号に鉛玉をぶち込んで、脅して大人しくさせるつもりなの？\n";
			link.l1.go = "Grinspy_11";
		break;
		
		case "Grinspy_11":
			dialog.text = "考え自体は大胆で無謀だけど、そこまでにはならないと思うよ。たぶん、 私たちがあいつらの船を襲うふりでもしてみせればいいんじゃない？そうしたらレイトンも、 やっと腹をくくって動くでしょ。あいつ、最近ちょっと調子に乗ってるけど、さすがに馬鹿じゃないしね。 私たちの一族か黒人たち、どっちかを潰すなんて、あいつにとっても得じゃない。勢力が三つくらい均衡してるからこそ、 なんとかバランスが保たれてるんだよ。一つでも崩れたら、全部めちゃくちゃになる。 あいつもそれくらい分かってるはず――なのに、なぜか私があいつの仕事までやらなきゃいけないんだよね。";
			link.l1 = "ここにいる間に、あの人に会いに寄ってみてもいいかな――もちろん、あの人がまた訓練を始める気にならなければ、だけどね、ははっ。";
			link.l1.go = "Grinspy_12";
			link.l2 = "機会があったら、あたしが寄って彼と話してみるよ。\nもしかしたら、聞いてくれるかもしれないしね。";
			link.l2.go = "Grinspy_13";
		break;
		
		case "Grinspy_12":
			dialog.text = "あいつに黒人たちを抑えさせることができるのは、あんただけだよ、 "+pchar.name+"。でも、あんたたちの顔を見る限り、政治の話をしに来たわけじゃないでしょ。で、どうしたいの？";
			link.l1 = "...";
			link.l1.go = "Grinspy_12_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Grinspy_12_add":
			StartInstantDialog("Mary", "Grinspy_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_13":
			dialog.text = "あたしの両親よ、ドナルド。";
			link.l1 = "...";
			link.l1.go = "Grinspy_13_add";
		break;
		case "Grinspy_13_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_14":
			dialog.text = "あたしに何を求めてるのか、よくわからないよ、メアリー。";
			link.l1 = "...";
			link.l1.go = "Grinspy_14_add";
		break;
		case "Grinspy_14_add":
			StartInstantDialog("Mary", "Grinspy_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_15":
			dialog.text = "彼らのことを教えてよ、お願い。あんたは知ってたんでしょ！前にも一度聞いたのに、答えてくれなかったじゃない…";
			link.l1 = "...";
			link.l1.go = "Grinspy_15_add";
		break;
		case "Grinspy_15_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_16":
			dialog.text = "だからチャールズをここに引っ張ってきたってわけか、ははは！お前は本当に面白い女だな、 もし嘘なら雷に打たれてもいいぜ！お前の父ちゃんと母ちゃんのことを話したことがないのは、 単に俺が知らなかったから、それだけだ！";
			link.l1 = "...";
			link.l1.go = "Grinspy_16_add";
		break;
		case "Grinspy_16_add":
			StartInstantDialog("Mary", "Grinspy_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_17":
			dialog.text = "でも、あんたはうちの一族で一番年上なんだよ、ね！あたしが物心ついた時からずっとここにいるんだから…";
			link.l1 = "...";
			link.l1.go = "Grinspy_17_add";
		break;
		case "Grinspy_17_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_18":
			dialog.text = "あたしが正義の島に来たのは、ちょうど二十年ほど前、あんたが生まれた後のことだったよ。あの頃のあんたは、 まだちっちゃくて、テーブルやスツールの下を走り回ったり這い回ったりして、 かわいそうなエリック・ユデットを全然休ませてやらなかったね……もちろん、あたしは彼に、こんな落ち着きのない子がどこから来たのか聞いたんだ――そしたら、数年前に島で生まれたって教えてくれた。でも、父親や母親のことは一言も言わなかったよ。 もし何か言ってたとしても――あたしが聞き流したか、すっかり忘れちゃったか、どっちかだね……\n";
			link.l1 = "...";
			link.l1.go = "Grinspy_18_add";
		break;
		case "Grinspy_18_add":
			StartInstantDialog("Mary", "Grinspy_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_19":
			dialog.text = " もう何年も経ったんだね……わかるよ、ドナルド、あたし、わかってるよ。";
			link.l1 = "...";
			link.l1.go = "Grinspy_19_add";
		break;
		case "Grinspy_19_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_20":
			dialog.text = " エリックがもうここにいないのは残念だよ――あの人、あたしよりずっと前からこの場所にいたんだ。\nそうそう、あの人があんたの最近の冒険を話すとき、よくオレリー・ベルティーヌのことを口にしてたよ。あの婆さん、 あんたのこと大好きだったもんね、それだけははっきり覚えてる……\n今思えば、あの人、あんたが生まれた頃にはもう正義の島に住んでたんじゃないかな。もしかしたら、 力になってくれるかも？";
			link.l1 = "...";
			link.l1.go = "Grinspy_20_add";
		break;
		case "Grinspy_20_add":
			StartInstantDialog("Mary", "Grinspy_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_21":
			dialog.text = " たぶんね。彼女に会いに行く理由にはなるよ。しばらく会ってなかったし。あたしってば、本当に気が利かないよね、 うん！";
			link.l1 = "...";
			link.l1.go = "Grinspy_21_add";
		break;
		case "Grinspy_21_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_22":
			dialog.text = "あの子はあなたに怒ってるわけじゃないと思うよ。\nでも、あまり無理させないでね――体調が悪いって聞いたし。\nこれ以上悪くなったら困るでしょ……";
			link.l1 = "...";
			link.l1.go = "Grinspy_22_add";
		break;
		case "Grinspy_22_add":
			StartInstantDialog("Mary", "Grinspy_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_23":
			dialog.text = "静かにして、ドナルド、面倒を呼び込む気？オレリーはあたしたち全員より長生きするんだよ、ね。";
			link.l1 = "...";
			link.l1.go = "Grinspy_24";
		break;
		
		case "Grinspy_24":
			dialog.text = "行こう、 "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "Grinspy_24_add";
		break;
		case "Grinspy_24_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_25":
			dialog.text = "...";
			link.l1 = "「さよなら。」 "+npchar.name+"。じゃあ、またね。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_9");
		break;
		
		//
		case "Jillian_1":
			dialog.text = "慈悲深き主よ、心臓が飛び出るかと思ったよ。そんなふうに人を驚かせちゃだめだよ。";
			link.l1 = "...";
			link.l1.go = "Jillian_1_add";
			DelLandQuestMark(npchar);
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_1_add":
			StartInstantDialog("Mary", "Jillian_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_2":
			dialog.text = "ジリアン！ここで会うなんて思わなかったよ、ね。何してるの？それと、オレリーはどこ？";
			link.l1 = "...";
			link.l1.go = "Jillian_2_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_2_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_3":
			dialog.text = "「やあ、メアリー。君にも挨拶を。」 "+pchar.name+"…オレリーは病気なんだよ、知らなかったの？あたし、ジュリアン兄弟に頼まれて彼女の世話してるんだ。 彼が薬を送ってくれて、あたしがそれを飲ませてるんだけど…あんまり効いてるようには見えないんだよね。今は船尾のキャビンで寝てるよ。ここを片付けるために、 あたしが彼女をそこに連れていったんだ。";
			link.l1 = "...";
			link.l1.go = "Jillian_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_3_add":
			StartInstantDialog("Mary", "Jillian_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_4":
			dialog.text = "今日になってやっと知ったんだよ、ね。ドナルドが教えてくれたんだ。彼女はどう？";
			link.l1 = "...";
			link.l1.go = "Jillian_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_4_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_5":
			dialog.text = "よくないな。彼女は体がだるいと訴えていて、ほとんどベッドから出てこないんだ。\n時々、何か意味不明なことをぶつぶつ言ってるし、くだらないことばかり……\n昔のことについての話をあまりにもたくさん聞かされて、もう数えきれないよ。";
			link.l1 = "...";
			link.l1.go = "Jillian_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_5_add":
			StartInstantDialog("Mary", "Jillian_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_6":
			dialog.text = "ふむ、それこそ俺たちが聞きに来た話だな。あの娘、話してくれるといいんだが……";
			link.l1 = "...";
			link.l1.go = "Jillian_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_6_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_7":
			dialog.text = "「本当に必要なのかい、メアリー？あたしは、彼女がこんな様子の時に邪魔しない方がいいと思うんだよ。」";
			link.l1 = "...";
			link.l1.go = "Jillian_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_7_add":
			StartInstantDialog("Mary", "Jillian_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_8":
			dialog.text = "これはあたしの両親のことなんだ。オレリーは二人のことを知ってたかもしれない。あたしにとって本当に大事なんだよ、 ジリアン、ね。\n";
			link.l1 = "...";
			link.l1.go = "Jillian_9";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "Jillian_9":
			dialog.text = "この島には彼女の容体を良くする薬はないの？";
			link.l1 = "...";
			link.l1.go = "Jillian_9_add";
		break;
		case "Jillian_9_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_10":
			dialog.text = "ジュリアン兄さんが彼女のために薬酒を作ってくれるんだ。でも、それも少しの間しか効かないんだよね。しかも、 彼女はそれを飲もうとしないから、あたしが無理やり口に流し込まなきゃいけないんだ。時々、 本当に喉に詰まらせるんじゃないかって心配になるよ――全部飲み込ませるのも、あたしの役目なんだよね…";
			link.l1 = "...";
			link.l1.go = "Jillian_10_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_10_add":
			StartInstantDialog("Mary", "Jillian_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_11":
			dialog.text = "かわいそうなオレリー！正義の島には、彼女を助けてくれる人は本当に誰もいないの？\n";
			link.l1 = "...";
			link.l1.go = "Jillian_11_add";
		break;
		case "Jillian_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_12":
			dialog.text = " あんたもあたしと同じくらいよく知ってるでしょ、ここにはちゃんとした医者なんていないんだよ。\nそれに、どうしようもないじゃない？年には誰だって勝てないんだから… ";
			link.l1 = "...";
			link.l1.go = "Jillian_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_12_add":
			StartInstantDialog("Mary", "Jillian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_13":
			dialog.text = ""+pchar.name+"、あたしたちの船から誰か連れてくるってのはどう？";
			link.l1 = "怖いんだよ、 "+npchar.name+"ここで必要なのは船医じゃなくて、腕のいい医者だよ。";
			link.l1.go = "Jillian_14";
		break;
		
		case "Jillian_14":
			dialog.text = "今なら魔法だって信じちゃいそうだよ、うん。\n";
			link.l1 = "うーん……魔法？あたし、チミセットに相談したほうがいいかな……";
			link.l1.go = "Jillian_14_add";
		break;
		case "Jillian_14_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_15":
			dialog.text = "チミセット？あの黒い魔術師？ "+pchar.name+"、本気なの？";
			link.l1 = "今まで以上にそうだよ。彼が黒人だろうと白人だろうと、今のあたしにはどうでもいいことなんだ。 オレリーを助けられる他の人なんて、あたしには思いつかないし、あんたもきっと同じでしょ。だから、どいて。 あたしの邪魔は絶対にしないでよ。\n";
			link.l1.go = "Jillian_16";
			link.l2 = "ああ、そうだよ。薬も彼女には効かなかったし、ジュリアン兄弟の祈りも無駄だった。 チミセットだけが最後の望みなんだ。";
			link.l2.go = "Jillian_17";
		break;
		
		case "Jillian_16":
			dialog.text = "あたしの耳を疑うよ！でも、彼は…神をも恐れぬ男なんだ！";
			link.l1 = "そして、彼女は死にかけている女――自分の名前さえ忘れそうなほどだよ。うん、あいつは魔術師だけど、 魔術師っていろんなことができるって聞いたことあるんだ。信じられないようなこともね。 もし彼が彼女の心を取り戻せるなら、どんな神を信仰していようと関係ある？";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_17":
			dialog.text = "あたしの耳を疑っちゃうよ！でも、あいつは……神をも恐れぬ男なんだよ！";
			link.l1 = " そして、彼女はもう死にかけている――自分の名前すら忘れそうなほどだよ。ああ、彼は魔術師だけど、あいつらはいろんなことができるって聞いたんだ。 信じられないようなこともね。もし彼が彼女の心を取り戻せるなら、どんな神を信仰していようと関係ないんじゃない？";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Jillian_18":
			dialog.text = ""+pchar.name+"ねえ、あたしだってオレリーのことを心配してるんだよ…神様に誓って、あたしは彼女の苦しみを和らげるためにできることは全部やってる！でもさ、 本当にあの黒い異端者にこの船室で儀式をやらせるつもり？もしあいつが船に火をつけたり、 誰かを生け贄にしようとしたらどうするの？\n";
			link.l1 = "そんなことはさせないよ、 "+npchar.name+"、あたしが保証するよ。";
			link.l1.go = "Jillian_19";
		break;
		
		case "Jillian_19":
			dialog.text = "それに、二人に言っておくけど、もし誰かにこのことがバレたら……ここで何が起きるかわかってる？他の島民たちは絶対に気に入らないし、とくにナーワルズなんて大騒ぎになるよ！\n";
			link.l1 = "それはそうだよね。チミセットをここに連れてくるべきじゃない、オレリーを彼のところに連れて行くべきだよ。";
			link.l1.go = "Jillian_20";
		break;
		
		case "Jillian_20":
			dialog.text = "あんたはあの婆さんを見てないんだろう――もう足元もおぼつかないんだよ。海に落ちずに済んだら奇跡だね！";
			link.l1 = "まあ、時には奇跡を願うしかないこともあるよ。で、ジリアン…";
			link.l1.go = "Jillian_21";
		break;
		
		case "Jillian_21":
			dialog.text = "他には？";
			link.l1 = "これ、誰にも言わないでほしいんだよ。あんたは頭のいい女だし、全部ちゃんと見抜いてる…正義の島の騒ぎは、すぐに流血沙汰になっちゃうかもしれないし、そんなの誰も望んでないでしょ？";
			link.l1.go = "Jillian_22";
			link.l2 = "誰にも一言も言わないで。わかった？私たちはあんたを信じたんだ、後悔させないでよ。 あたしもあんたも分かってるでしょ、もしこのことが広まったら、 正義の島は今まで見たこともないような大虐殺になるんだから。\n";
			link.l2.go = "Jillian_23";
		break;
		
		case "Jillian_22":
			dialog.text = "あたしとしてはいいよ。でも、誰にもあの子を『プロテクター』号に引きずり込むところを見られないようにしてね…\nじゃないと、あたしが妙な質問に答えなきゃいけなくなるからさ。";
			link.l1 = "気まずい返事をする手間は取らせないよ。今夜やるからね。";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Jillian_23":
			dialog.text = "あのさ。でも、誰にも見られずに彼女を『プロテクター』号へ連れていくんだよ……じゃないと、あたしが変な質問に答えなきゃいけなくなるからね。\n";
			link.l1 = "そんなことはさせないよ。夜にやるんだ。";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_24":
			dialog.text = "真夜中を過ぎてから来て。彼女はここにいるよ。お願いだから、気をつけてね。";
			link.l1 = "「心配しなくていいんだよ、」 "+npchar.name+"、あたし、絶対そうするって約束するよ。";
			link.l1.go = "Jillian_25";
		break;
		
		case "Jillian_25":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10");
		break;
		
		case "Jillian_26":
			if (GetHour() >= 3 && GetHour() <= 24)
			{
				dialog.text = "真夜中を過ぎてから来て。彼女はここにいるから…";
				link.l1 = "うん。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Jillian_26";
			}
			else
			{
				dialog.text = "オレリーは準備できてるよ。連れて行っていいよ。";
				link.l1 = "うん。じゃあ、行こう。";
				link.l1.go = "exit";
				DelLandQuestMark(npchar);
				AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10_2");
			}
		break;
		
		case "Oreli_1":
			dialog.text = "若い者たち、ど、どこへ行くんだ！？これはリヴァドスの船だよ！エリックはどこ！？";
			link.l1 = "エリックはエディ・ブラックと友達になったんだよ、知ってた？";
			link.l1.go = "Oreli_2";
		break;
		
		case "Oreli_2":
			dialog.text = "何を言ってるんだ、坊や！エリックは黒人が大嫌いなんだぞ！";
			link.l1 = "へえ、そうなんだ！じゃあ、あいつにここで一体何してるのか聞きに行こうよ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_11");
		break;
		
		case "Eddy_1":
			dialog.text = "「おや、誰が会いに来てくれたのかな！」 "+GetFullName(pchar)+" 本物じゃん！白い兄弟に会えて嬉しいよ、はは！それで、今日は何の用で来たの？";
			link.l1 = "「そして、あんたにもこんにちは、」 "+npchar.name+" …あたし、本当はラム酒を一杯飲みに立ち寄れたらいいんだけど、残念ながら急ぎの用事があるんだよ、あんたに――いや、正確にはチミセットにね。";
			link.l1.go = "Eddy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Eddy_2":
			dialog.text = "俺たちはお前に一生借りができたよ、友よ。できる限りのことは何でも手伝うぜ。";
			link.l1 = "それはよかったよ。だって、あたしにはもう頼れる人が誰もいないんだもん。";
			link.l1.go = "Eddy_3";
		break;
		
		case "Eddy_3":
			dialog.text = "「この中のどの女性を手伝ってほしいの、」 "+pchar.name+"?";
			link.l1 = "あんたが本気なのか、ただふざけてるだけなのか、あたしには分からないよ、 "+npchar.name+"、でも今は冗談を言う気分じゃないよ。助けが必要なのはもちろんオレリーだよ。";
			link.l1.go = "Eddy_3_add";
		break;
		case "Eddy_3_add":
			StartInstantDialog("LSC_Oreli", "Eddy_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_4":
			dialog.text = "エリック！エリック！どこにいるの、あんたこの怠け者！これは一体どういうこと！？ さっさとその貧相なケツをこっちに持ってきなさいよ！\n";
			link.l1 = "...";
			link.l1.go = "Eddy_4_add";
		break;
		case "Eddy_4_add":
			StartInstantDialog("Eddy", "Eddy_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_5":
			dialog.text = "じゃあ、本当なんだね……あたしの仲間が、この難破船はちょっとおかしいって言ってたけど、嘘じゃなかったんだ。\nでも、あんたがリバドスから何を望んでるのか、あたしにはまだよくわかんないよ……";
			link.l1 = "チミセットと話させてよ、そしたら全部わかるから…";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_12");
		break;
		
		case "Chimset_1":
			dialog.text = "話して、親愛なる友よ。あたし、ちゃんと聞く準備できてるよ。";
			link.l1 = "手短に言うよ、チミセット。オレリーは、あたしとメアリーに必要な情報を持ってる。でも、彼女の状態――あたしの理解が正しければ、単に年齢の問題なんだけど――のせいで、あたしたちはその知識を得ることができないし、正確かどうかも確信できないんだ。 インディアンやアフリカのシャーマンができる奇跡については聞いたことがある――だからこそ、チミセット、君の助けを求めに来たんだ。";
			link.l1.go = "Chimset_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Chimset_2":
			dialog.text = "聞こえてるよ、相棒。シャーマンは神秘的で不思議な力を持っていて、よそ者はもちろん、 身内ですら理解できないことが多いんだ。白人なんてなおさらさ。ある者はそれを魔術と呼び、またある者は奇跡と呼ぶ。 俺たちは確かに色んなことができる――でも、川の流れを逆にすることは誰にもできない……それに、その流れを止めることもな。";
			link.l1 = "「どういう意味、チミセット？」";
			link.l1.go = "Chimset_3";
		break;
		
		case "Chimset_3":
			dialog.text = "俺が言ってるのは時の流れだよ、旦那。あるいは人生の川――どっちでも好きな方でいいさ。分かるかい、あんたの言う通りだ――この可哀想な娘の病の根っこは、年月にあるんだよ、それ以外にはないんだ。";
			link.l1 = "それについては少し聞いたことがあるよ。あたしが知ってるのは、それがそんなに珍しい問題じゃないってことだけ。";
			link.l1.go = "Chimset_4";
		break;
		
		case "Chimset_4":
			dialog.text = "あんたの言う通りだよ。あの年頃の人たちは、よく夢の谷へと連れていかれるんだ、時には悪夢の谷にもね。 戻ってきても、またすぐにどこかへ行ってしまう――自分の意志というより、不思議な力に引き寄せられてさ。時が経つにつれて、その病はどんどん強くなっていく――やがて自分のことも、友達のことも思い出せなくなるまでね。";
			link.l1 = "じゃあ、どうしようもないの？";
			link.l1.go = "Chimset_5";
		break;
		
		case "Chimset_5":
			dialog.text = "病を追い払うなんて、できないよ。あたしには無理だよ、うん。でも、他にできることがあるんだ……";
			link.l1 = "具体的に何が？";
			link.l1.go = "Chimset_6";
		break;
		
		case "Chimset_6":
			dialog.text = "この女が目を覚ました瞬間、あたしはすぐに儀式を行うよ、そのための準備は事前にしておくからね。";
			link.l1 = "「少なくとも病気の進行を遅らせることはできるの？完全に止められなくてもさ？」";
			link.l1.go = "Chimset_7";
		break;
		
		case "Chimset_7":
			dialog.text = "正確には違うよ。彼女は正気を保つために、持てる限りの力を振り絞らなきゃならなくなるんだ。";
			link.l1 = "「できるだけ長く」って、具体的にはどれくらいなの？";
			link.l1.go = "Chimset_8";
		break;
		
		case "Chimset_8":
			dialog.text = "それは儀式じゃなくて、人によるんだよ。ある人は一週間もつし、別の人は一ヶ月ももつ……一年近く、いやそれ以上も正気と記憶を保った男の話も聞いたことがあるんだ。\nでも、みんながもう治ったと思ったその時に、病が戻ってきて――その夜のうちに彼を連れていったんだよ。";
			link.l1 = "一時間あれば必要なことは分かるだろう。\nいつ儀式を行える、チミセット？";
			link.l1.go = "Chimset_9";
		break;
		
		case "Chimset_9":
			dialog.text = "今すぐ女を連れていくぞ、船倉まで連れてこい――そこにはこういう時のための隠れ場所が用意してあるんだ。\nあとは、あの女が正気に戻るのがいつか次第だが……まあ、朝までには終わると思うぜ。";
			link.l1 = "じゃあ、あたしは邪魔しないよ。あんたの…神様、チミセットが助けてくれますように。";
			link.l1.go = "Chimset_10";
		break;
		
		case "Chimset_10":
			dialog.text = "ジコモ！白人の女を船倉まで運ぶのを手伝ってくれ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_13");
		break;
		
		case "Chimset_11":
			dialog.text = "うまくいったよ、白い兄さん。あたしたち、なんとか……";
			link.l1 = "...";
			link.l1.go = "Chimset_11_add";
			DelLandQuestMark(npchar);
		break;
		case "Chimset_11_add":
			StartInstantDialog("LSC_Oreli", "Chimset_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_12":
			dialog.text = "「あっ、」 "+GetFullName(pchar)+"！あんたとメアリーがまた正義の島に戻ってきてたなんて、全然知らなかったよ！なんて素敵なサプライズなんだ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_14_1");
		break;
		
		case "Chimset_13":
			dialog.text = "...";
			link.l1 = "チミセット、ありがとう！あたし、どうやってお礼を言えばいいかわからないよ…";
			link.l1.go = "Chimset_14";
			link.l2 = "へえ、見てよ、チミセットがやってのけたじゃない！あたし、一瞬たりとも疑ってなかったよ…";
			link.l2.go = "Chimset_15";
		break;
		
		case "Chimset_14":
			dialog.text = "リバドス一同、あなたには永遠に借りができたよ、友よ！『プロテクター』の扉はいつでもあんたに開かれてるからね。";
			link.l1 = "これ以上ご迷惑をおかけしないといいんだけど……メアリー、オレリー、『プルートー』に戻らないと。";
			link.l1.go = "Chimset_15_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Chimset_15":
			dialog.text = "リバドスの皆は永遠にあなたに借りができたよ、友よ！『プロテクター』の扉はいつでもあなたに開かれているからね。";
			link.l1 = "これ以上ご迷惑をおかけしないといいんだけど……メアリー、オレリー、あたしたち『プルート』に戻らなきゃ。";
			link.l1.go = "Chimset_15_add";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		case "Chimset_15_add":
			StartInstantDialog("LSC_Oreli", "Chimset_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_16":
			dialog.text = "自分の船室をどうやって出たのかすら覚えてない……ああ、歳は取りたくないもんだな、記憶なんてもうボロボロだよ。 ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_15");
		break;
		
		case "Oreli_11":
			dialog.text = "おやおや、お嬢さん、どうして俺の船室に来たんだい？";
			link.l1 = "...";
			link.l1.go = "Oreli_11_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_12":
			dialog.text = "「オレリー、あたし……」";
			link.l1 = "...";
			link.l1.go = "Oreli_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_12_add":
			StartInstantDialog("Mary", "Oreli_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_13":
			dialog.text = "オレリー、あんたがいない間にここを片付けるよう彼女に頼んだんだよ。膝も悪いし、 無理して腰を痛めることないからね…";
			link.l1 = "...";
			link.l1.go = "Oreli_13_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
			
		break;
		case "Oreli_13_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_14":
			dialog.text = "片付けだって！？あんた…";
			link.l1 = "ジリアン、お疲れさま。\n（小声で）やったね。チミセットがやり遂げたよ。";
			link.l1.go = "Oreli_15";
		break;
		
		case "Oreli_15":
			dialog.text = "そんなはずない…";
			link.l1 = "ご覧の通りだよ。さて、お願いだから、話をさせて。";
			link.l1.go = "Oreli_15_add";
		break;
		case "Oreli_15_add":
			StartInstantDialog("LSC_Oreli", "Oreli_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_16":
			dialog.text = "さて、若い方々、年寄りの私を送ってくれてありがとうね。もうすぐ外に出ることもできなくなりそうでね。 かわいそうなこの足、足がねぇ…";
			link.l1 = "もしよければ、 "+npchar.name+"、ちょっとだけ一緒にいさせてもらうよ。あたしとメアリーは、あんたにとっても大事な用事があるんだ。";
			link.l1.go = "Oreli_17";
		break;
		
		case "Oreli_17":
			dialog.text = "もう二度と別の船に乗り込まなくていいなら、あたしにできることは何でも手伝うよ。うん、聞いてるよ。";
			link.l1 = "...";
			link.l1.go = "Oreli_17_add";
		break;
		case "Oreli_17_add":
			StartInstantDialog("Mary", "Oreli_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_18":
			dialog.text = "オレリー、あたしの両親のことを教えてほしいんだ。それと、あたしが生まれた日のことも。ここ、 この島で起きたんでしょ？ドナルドはそう言ってるけど、あの人はその頃ここにいなかったから、 本当のことは知らないはずだよ。でも、オレリーはドナルドよりずっと長くここに住んでるよね、うん！二十年以上も、 そうでしょ？\n";
			link.l1 = "...";
			link.l1.go = "Oreli_18_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_18_add":
			StartInstantDialog("LSC_Oreli", "Oreli_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_19":
			dialog.text = "落ち着け、落ち着け、娘さん、そんなに早口でしゃべらないでくれ、頼むよ！あたし、ついていけないよ…";
			link.l1 = "...";
			link.l1.go = "Oreli_19_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_19_add":
			StartInstantDialog("Mary", "Oreli_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_20":
			dialog.text = "うん、わかったよ。じゃあ、もう一回だけ確認しようか…";
			link.l1 = "...";
			link.l1.go = "Oreli_20_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_20_add":
			StartInstantDialog("LSC_Oreli", "Oreli_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_21":
			dialog.text = "心配するな、メアリー、俺はまだそんなに年寄りじゃないさ、はは……あんたの言ったことはちゃんと聞こえてたよ。\nでもな、実際に俺は誰よりも長く正義の島に住んでるんだ。だから、 俺の年齢には少しは敬意と理解を示してくれると嬉しいんだが……";
			link.l1 = "...";
			link.l1.go = "Oreli_21_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_21_add":
			StartInstantDialog("Mary", "Oreli_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_22":
			dialog.text = "もちろんだよ、オレリー！どうしてそんなふうに思うの？";
			link.l1 = "...";
			link.l1.go = "Oreli_22_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_22_add":
			StartInstantDialog("LSC_Oreli", "Oreli_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_23":
			dialog.text = "ああ、最近の若い者たちを見ているとさ……いやいや、俺たちは年長者にそんな態度は取らなかったんだ。でも、もちろんあんたは違うよ。俺が言いたかったのは、 質問は一度に全部じゃなくて、一つずつ答えた方が俺たちには楽だってことさ……";
			link.l1 = "...";
			link.l1.go = "Oreli_23_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_23_add":
			StartInstantDialog("Mary", "Oreli_24", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_24":
			dialog.text = "わかったよ、オレリー。あんたが楽なようにすればいいんだ、ね。で、あたしが生まれた時、あんたは正義の島にいたの？ つまり、もし本当にここで生まれたんなら……";
			link.l1 = "...";
			link.l1.go = "Oreli_24_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_24_add":
			StartInstantDialog("LSC_Oreli", "Oreli_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_25":
			dialog.text = "1633年に正義の島へ来たんだよ、あの日のことは今でも時々悪夢に出てくるんだ。\n嵐だったし、あたしたちの“リプライザル”――旦那と一緒にフロリダへ向かってたフリュート船――は波に翻弄されて、今にも転覆しそうでさ、知ってる祈りを全部唱えて、新しい祈りまで作ってたんだよ…\nそして、バキッて音がして…";
			link.l1 = "...";
			link.l1.go = "Oreli_25_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_25_add":
			StartInstantDialog("Mary", "Oreli_26", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_26":
			dialog.text = "あんたはあたしが生まれる五年前にここに来たってわけだね、うん。";
			link.l1 = "...";
			link.l1.go = "Oreli_26_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_26_add":
			StartInstantDialog("LSC_Oreli", "Oreli_27", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_27":
			dialog.text = "まあ、そんなところかな。あの頃は今とは全然違ったよ。サン・ヘロニモ号はまだ浮かんでたし、 外側の船の輪も今の半分、いや、それ以下だったかも…しかも、今残ってない船は数に入れてないからね！ひとつ言っておくよ、若いのたち――晴れた日に水面を覗き込んでごらん、下に見える難破船の数には本当にゾッとするから…\n";
			link.l1 = "...";
			link.l1.go = "Oreli_27_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_27_add":
			StartInstantDialog("Mary", "Oreli_28", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_28":
			dialog.text = "あたしの両親がここに来たとき乗ってた船に興味があるんだよ。あたしも一緒だったのか…それとも、いなかったのか？";
			link.l1 = "...";
			link.l1.go = "Oreli_28_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_28_add":
			StartInstantDialog("LSC_Oreli", "Oreli_29", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_29":
			dialog.text = "「あんたと一緒にだよ、あんたと一緒に。」";
			link.l1 = "...";
			link.l1.go = "Oreli_29_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_29_add":
			StartInstantDialog("Mary", "Oreli_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_30":
			dialog.text = "じゃあ、あたし、やっぱり本土で生まれたんだね？";
			link.l1 = "...";
			link.l1.go = "Oreli_30_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_30_add":
			StartInstantDialog("LSC_Oreli", "Oreli_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_31":
			dialog.text = "違うよ、あたしが言いたかった「一緒に」は、ちょっと違う意味なんだ。あんたはお母さんのお腹の中にいて、 それから一週間後に生まれたんだよ。";
			link.l1 = "「これが面白いと思うの、オレリー？」";
			link.l1.go = "Oreli_32";
			link.l2 = "「それに、あんたは年月を重ねてもユーモアのセンスを失ってないね、オレリー。」";
			link.l2.go = "Oreli_33";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_32":
			dialog.text = "あたしさ、自分のことは他の人よりずっとよく笑っちゃうんだよ。ごめん、メアリー、傷つけるつもりはなかったんだ。";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_33":
			dialog.text = "あたしさ、自分のことの方が他人よりずっとよく笑っちゃうんだよね。\nごめん、メアリー、傷つけるつもりじゃなかったんだ。";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		case "Oreli_33_add":
			StartInstantDialog("Mary", "Oreli_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_34":
			dialog.text = "大丈夫だよ、オレリー。お願い、続けて。あたしが生まれた後、両親に何があったの？";
			link.l1 = "...";
			link.l1.go = "Oreli_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_34_add":
			StartInstantDialog("LSC_Oreli", "Oreli_35", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_35":
			dialog.text = "その後？あら、あなた、二人ともその時まで生き延びていたこと自体が奇跡みたいなものよ！あの六月の夜は、 ひどい嵐だったんだから！\n朝になって、ボートがあなたのお母さんを内側の環まで運んできたとき、最初は誰も信じられなかったのよ――出産間近の女性が、あんな恐ろしい難破を生き延びたなんて。可哀想なテレサ……昨日のことみたいに覚えてるわ……";
			link.l1 = "...";
			link.l1.go = "Oreli_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_35_add":
			StartInstantDialog("Mary", "Oreli_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_36":
			dialog.text = "「テレサ？それが彼女の名前だったの？」";
			link.l1 = "...";
			link.l1.go = "Oreli_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_36_add":
			StartInstantDialog("LSC_Oreli", "Oreli_37", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_37":
			dialog.text = "ああ、そうやって彼女は自己紹介したんだ――それが彼女のほとんど唯一の言葉だったよ。\nその日の終わりには、彼女は熱にうなされるようになり、そのまま出産までずっと続いた。\n誰も彼女が生き延びるとは思わなかったし、それ以上に、あれだけのことを乗り越えてきた子供が無事に生まれるなんて、 誰も信じていなかった。\nでもテレサはやり遂げた。彼女はやり遂げて――そしてその後、息を引き取った。\n神よ、彼女の魂に安らぎを……";
			link.l1 = "...";
			link.l1.go = "Oreli_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_37_add":
			StartInstantDialog("Mary", "Oreli_38", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_38":
			dialog.text = "母さんは死んで、あたしは父さんと残されたの？でも、 だったらなんでみんなエリック・ユデットに育てられたって言うの？それに……";
			link.l1 = "...";
			link.l1.go = "Oreli_38_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_38_add":
			StartInstantDialog("LSC_Oreli", "Oreli_39", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_39":
			dialog.text = "メアリー、愛しい人よ、頼むから……そんなにたくさん質問攻めにしないでくれ……";
			link.l1 = "...";
			link.l1.go = "Oreli_39_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_39_add":
			StartInstantDialog("Mary", "Oreli_40", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_40":
			dialog.text = "ごめんね、オレリー、ちょっと調子に乗っちゃった、ね。あたしの父さんも、難破から生き延びたんだよね？";
			link.l1 = "...";
			link.l1.go = "Oreli_40_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_40_add":
			StartInstantDialog("LSC_Oreli", "Oreli_41", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_41":
			dialog.text = "あんたのお父さん…あのね、あんたのお父さんについては、正直あんまり言うことないんだよね——あんな親父、誰にも勧めたくないってくらいさ。あんたが生まれてほんの数日で、あの人は消えちゃって、 あんたを一人にしたんだよ。エリックが優しくて、心がビスケットをラム酒でふやかしたみたいに柔らかい人で、 本当に運が良かったよ…";
			link.l1 = "...";
			link.l1.go = "Oreli_41_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_41_add":
			StartInstantDialog("Mary", "Oreli_42", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_42":
			dialog.text = "せめて彼の名前だけでも教えてよ！";
			link.l1 = "...";
			link.l1.go = "Oreli_42_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_42_add":
			StartInstantDialog("LSC_Oreli", "Oreli_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_43":
			dialog.text = "ああ…ジェフリーだったかジョンだったか、思い出せたらいいのに…";
			link.l1 = "だから、あんたは本当は覚えてないんだよね、 "+npchar.name+"?";
			link.l1.go = "Oreli_44";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_44":
			dialog.text = "あたしの言葉を疑ってるの、若造！？";
			link.l1 = "「静かに」 "+npchar.name+"「まあまあ、落ち着いてよ。傷つけるつもりはなかったんだ。ただ、 あの頃のことをよく覚えてるみたいだなって思っただけだよ、それだけ。」";
			link.l1.go = "Oreli_45";
			link.l2 = "「あたしは疑ってないよ、」 "+npchar.name+"…あたし、ただ全部の細かいことをちゃんと思い出そうとしてるだけだよ、それだけ。だけど、 このごちゃごちゃでちょっとややこしくなっちゃうんだよね。";
			link.l2.go = "Oreli_46";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_45":
			dialog.text = "「記憶って、気まぐれな女だよ、」 "+pchar.name+"、かなり選り好みしてるんだよ。特にこんなに長い年月が経った後じゃね。テレーザのことは忘れられないよ――あたし、一週間ずっと彼女が苦しむのを見てたんだ！ああ、彼女が可哀想でたまらなかったよ！";
			link.l1 = "「それで、旦那は？一緒にいなかったのか？」";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Oreli_46":
			dialog.text = "「記憶って、気まぐれな女だよ、」 "+pchar.name+"、かなり選り好みしてるよ。特にこんなに年月が経った今はね。テレサのことは忘れられないよ――あたし、彼女が一週間ずっと苦しんでるのを見てたんだ！ああ、どれだけ彼女が気の毒だったか！";
			link.l1 = "「それで旦那は？彼女と一緒じゃなかったの？」";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_47":
			dialog.text = "とても珍しかったよ。あの頃は正義の島には薬や治療薬がほとんどなくて……父さんはほとんど一週間中いなかった、薬を探しに出かけてたんだよ……\n";
			link.l1 = "つまり、彼はきっといい旦那だったんだろうね――奥さんを助けようとしたならさ。";
			link.l1.go = "Oreli_48";
		break;
		
		case "Oreli_48":
			dialog.text = "いい旦那だったかもしれないよ。あたし、そうじゃないなんて一言も言ってないからね。混乱させようとしないでよ、 坊や！";
			link.l1 = "あたし、そんなこと考えたこともなかったんだよ、誓うよ。 "+npchar.name+"……あんたが彼のことをあまり良く思ってないのは、見ててすぐ分かるよ。それに、名前すら覚えてないなんて……";
			link.l1.go = "Oreli_49";
		break;
		
		case "Oreli_49":
			dialog.text = "あたし、その男をちらっと見たことがあるんだよ、ほとんど影みたいにね、今はユルゲンさんが住んでる『セレス鍛冶屋』 の船室の暗闇でさ。\n彼は夜しか来なかったし、顔もほとんど覚えてないんだ。\n名前だって、誰も下の名前で呼ばなかったよ。いつも「カスパーがどうした」「カスパーがこうした」って……";
			link.l1 = "あんたのこと、わかるよ "+npchar.name+"。それでメアリーが生まれて、数日後に彼は跡形もなく消えたんだ。殺されたの？";
			link.l1.go = "Oreli_50";
		break;
		
		case "Oreli_50":
			dialog.text = "それは難しい質問だね、若者よ。ここでは何かを隠すのは本当に大変なんだ――みんながいつも見張ってるからさ。ちょっとした喧嘩があれば――たとえ船の中で起きても――翌日には正義の島中に知れ渡っちまうんだよ。\n";
			link.l1 = "そりゃそうだよ。";
			link.l1.go = "Oreli_51";
		break;
		
		case "Oreli_51":
			dialog.text = "殺された者たちの遺体が必ずしも見つかるとは限らない――腕や足をチェーンショットで縛ったり、大砲の弾や石のような重りを付けて、手慣れた悪党どもが死体を沈めるんだ。\nでも、海底のカニたちが最後の仕上げをしてくれる。\nだけど、死者の持ち物は結局いつか浮かび上がってくるんだよ。";
			link.l1 = "「底からだって！？」";
			link.l1.go = "Oreli_52";
		break;
		
		case "Oreli_52":
			dialog.text = "もちろん違うよ！あたしが言いたかったのは、ただ目につくものってこと――指輪とか、彫刻入りのピストルとか、儀礼用のサーベルとかさ……そういうのは、みんなあんまり気にしないんだよ。もうその人は戻ってこないし、 誰もこれ以上面倒ごとはごめんだもんね。\n";
			link.l1 = "ジェフリーかジョン・カスパーに、何か特徴的な持ち物はあった？";
			link.l1.go = "Oreli_53";
		break;
		
		case "Oreli_53":
			dialog.text = ""+pchar.name+" あんたの魂に祝福を――あたし、あいつの名前すら思い出せないのに、そんなこと聞くなんて！もし何かあったとしても、 その品が誰かの手に渡ったなんて話、正義の島じゃ聞いたことないよ。あの頃は酒場の女中やってて、 噂話はほとんど聞き逃さなかったんだ、うん。でも、だからって全部知ってたわけじゃないよ。";
			link.l1 = "人が「跡形もなく消えた」と言う時は、たいてい殺されたって意味だよ。でもカスパーさんの場合、 あんたはどうもそう思ってないみたいだね…";
			link.l1.go = "Oreli_54";
		break;
		
		case "Oreli_54":
			dialog.text = "「『行方不明』って言っても、必ずしも『死んだ』って意味じゃないんだよ。特にあの頃は、 密輸業者や盗品売りがいっぱい乗ったタルタナ船が、正義の島とキューバの間をしょっちゅう行き来してたし……ね？あたし、彼の顔は思い出せないけど、あの目だけは……どこにいても絶対に迷わない男の目だったよ。少なくとも、本人はそう信じてたんだろうね。」";
			link.l1 = "タルタン船、タルタン船…それ自体は別に不可能じゃないよ。もし彼の名前が分かれば、その時代の植民地の記録を調べられるんだけどね。\nでも、彼が乗っていた船の種類と名前が分かれば、もっと簡単なんだけどな。";
			link.l1.go = "Oreli_55";
		break;
		
		case "Oreli_55":
			dialog.text = "なんであたしを見るの、若造？あたしがそれを覚えてると思ってるの？";
			link.l1 = "そうだといいんだけど、 "+npchar.name+" - あんたがもうこれだけ話してくれたことを考えれば、ね。";
			link.l1.go = "Oreli_56";
			link.l2 = "うーん…それは本当に怪しいと思うよ。";
			link.l2.go = "Oreli_57";
		break;
		
		case "Oreli_56":
			dialog.text = "もしかして、あの船に大砲が何門あって、口径がどれくらいだったか聞きたいの？ねえ、あんた、 ここで何年もの間にどれだけの船が沈んだか分かってる？全部覚えてると思う？それに、 その船から生き残った人なんてほんのわずかしかいなかったんだよ――あの船、水面に浮かんでたのはほんの一日もなかったんだから、分かるでしょ…";
			link.l1 = "そうか……まあ、納得だよ、二十年も経ってるもんね。少なくとも言われたことを覚えててくれて、ありがとう。";
			link.l1.go = "Oreli_58";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Oreli_57":
			dialog.text = "もしかして、あの船に大砲が何門あって、口径がどれくらいだったか聞きたいの？あのね、 ここで何年もの間にどれだけの船が沈んだか、あんた分かってる？全部覚えてると思う？それに、 その船から生き残ったのはほんの一握りだけだったんだよ――一日も浮かんでいられなかったくらいさ…";
			link.l1 = "そうか……まあ、二十年も経ってるんだもんね、仕方ないよね。少なくとも、 あたしたちが聞かされたことを覚えててくれてありがとう。";
			link.l1.go = "Oreli_58";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_58":
			dialog.text = "冗談を言ってるんじゃなくて、記憶が穴だらけの年寄りをからかおうとしてるわけじゃないといいんだけど。";
			link.l1 = "「全然そんなことないよ、」 "+npchar.name+"。あんた、本当に助けてくれたよ。早く元気になってね。じゃあ、あたしたちは行くよ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_16");
		break;
		
		case "Mary_91":
			dialog.text = "そうか、テレサ……それが彼女の名前だったんだ。あたしのお母さん、かわいそうに、ね……";
			link.l1 = "まあ、これであんたのその強さと頑固さがどこから来たのか、やっと分かったよ。\n沈みかけた船の上で妊婦だったなんて……考えただけでゾッとしちゃうよ。";
			link.l1.go = "Mary_92";
		break;
		
		case "Mary_92":
			dialog.text = "「でも、彼女はどうしてそんな状態でこの船にいたんだ」 "+pchar.name+"！？そんなこと考えるなんて、正気じゃないよ！";
			link.l1 = "その質問に答えられるのはあんたの父さんだけだよ――ジョン、ジャック、ジェイコブ、ジャスパー、ジョーダン……";
			link.l1.go = "Mary_94";
		break;
		
		case "Mary_94":
			dialog.text = "「“J”で始まる英語の名前を全部思い出そうとしてるの？オレリーが言ってたのはジェフリーとジョンだけだよ、ね。」";
			link.l1 = "もしかしたら、あの人も他のことは覚えてなかったのかも、あたしみたいにさ？年齢とか、そういうのもあるでしょ…";
			link.l1.go = "Mary_95";
		break;
		
		case "Mary_95":
			dialog.text = ""+pchar.name+"……って、思うんだよ……";
			link.l1 = "今の彼女の記憶は完全には信用できないだろうな。\nそれでも、植民地の記録だけじゃなくて、1638年の海軍の記録も探し出さなきゃならない。そっちはもっと厄介だよ、特に士官に関するものは機密扱いだし。\nそれに、普通の水兵が自分の妻をこっそり船に乗せるなんて、まず許されないと思うぜ。";
			link.l1.go = "Mary_96";
		break;
		
		case "Mary_96":
			dialog.text = "一方で、士官についての情報を見つけるのは、普通の水夫よりずっと簡単なんだよ。";
			link.l1 = "もし船の名前を知っているなら。あるいは正式な名前でもいい。単なる「ジェフリーとかジョンとか、 最悪の場合はジャック…」じゃなくてさ。\nそれも、運が良ければその船が軍艦だった場合だけだよ。商船なんて、乗組員名簿なんてもっとひどいもんさ。";
			link.l1.go = "Mary_97";
		break;
		
		case "Mary_97":
			dialog.text = "「でも、その後どうすればいいの、」 "+pchar.name+"？またオレリーに話すのか？もう彼女から聞けることは全部聞き出したんじゃない？";
			link.l1 = "オレリーじゃなくて、ドナルドとだよ。";
			link.l1.go = "Mary_98";
		break;
		
		case "Mary_98":
			dialog.text = "「それで、彼がどうやって私たちを助けてくれるっていうの？彼自身が、1638年には正義の島には全然いなかったって言ってたんだよ、ね。」";
			link.l1 = "でも、ここには他にもナーワルたちがいたんじゃない？";
			link.l1.go = "Mary_99";
		break;
		
		case "Mary_99":
			dialog.text = "あたし、正直言って、あなたが何を言いたいのかよくわからないよ。";
			link.l1 = "見てて、ね、見てて。まだ引っ張れる糸が一本残ってるんだよ。行こう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_17");
		break;
		
		case "Grinspy_31":
			dialog.text = "あっ、またあんたか！で、捜索の方はどうなってるの？";
			link.l1 = "「こんにちは。」 "+npchar.name+"。状況はもっと良くなってもいいんだけどね。今はまるで謎と不思議に満ちた洞窟をさまよってるみたい。でも、 出口は近いって感じてるよ。";
			link.l1.go = "Grinspy_32";
			link.l2 = "「そして、あんたにもこんにちは、」 "+npchar.name+"最初に思ってたより、ずっといいよ。状況も……思ったほど絶望的じゃないみたいだね。";
			link.l2.go = "Grinspy_33";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_32":
			dialog.text = "それは嬉しいよ。ほんとにさ。だけど、また二人ともあたしに何か用があるんでしょ？何か分かったことでもあるの？";
			link.l1 = "メアリーはここ、正義の島で1638年6月に生まれた。\n母親のテレサは出産直後に亡くなった。\n父親――カスパーという名の男――は、メアリーが生まれて数日後、跡形もなく姿を消した。\n彼についてわかっているのは、名前が「J」で始まることだけだ。\n地元の浅瀬でカニの餌になったわけじゃなく、密輸業者のタルタン船で島を出たんだって言う人もいる……";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_33":
			dialog.text = "それは良かったよ、ほんとに。だけど、またあたしに用があるんでしょ、ね？それで、何か分かったの？";
			link.l1 = "メアリーはここ、正義の島で1638年6月に生まれた。母親のテレサは出産直後に亡くなった。父親はカスパーという名の男で、 メアリーが生まれて数日後に跡形もなく姿を消した。彼についてわかっているのは、名前が「J」で始まるということだけだ。一部の者は、彼がこの島の浅瀬でカニの餌になったのではなく、 密輸業者のタルタン船の一隻で島を去ったのだと言っている……\n";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_34":
			dialog.text = "「それで娘を置き去りにしたの？それって、変なことだよね。」";
			link.l1 = "そうだよ。でも、それを説明できるのは、このJさん本人だけなんだよね。";
			link.l1.go = "Grinspy_35";
		break;
		
		case "Grinspy_35":
			dialog.text = "「それで、あんたは彼がまだ生きてると思ってるの？だから探してるんだよね？」";
			link.l1 = "それだけじゃないんだよ。あたしたちは、彼がどんな人だったのか、どう生きてきたのかを知りたいんだ。 あたしにとって、とても大事なことなんだよ。";
			link.l1.go = "Grinspy_36";
		break;
		
		case "Grinspy_36":
			dialog.text = "ふーん、そうなんだ。あたし、何も力になれなくてごめんね…";
			link.l1 = "実は、できるんだよ。ねえ、ナーワルズは正義の島で失われた船の記録を何かしら残してるでしょ？";
			link.l1.go = "Grinspy_37";
		break;
		
		case "Grinspy_37":
			dialog.text = "「ちょっと、何を言いたいのかよくわからないんだよ、」 "+pchar.name+".";
			link.l1 = "グリーンスペン、グリーンスペン……あたしのおかげでまだその椅子を温めていられるって、忘れないでよ。だから、お願い、あたしの我慢を試さないでね。";
			link.l1.go = "Grinspy_38";
			link.l2 = "ドナルド、わかってくれるよね。あたしたちの友情のためにも、質問から逃げたりしないでよ。";
			link.l2.go = "Grinspy_39";
		break;
		
		case "Grinspy_38":
			dialog.text = "うーん…";
			link.l1 = "時々、船が外輪に打ち上げられるんだよ。すぐに沈む船もあれば、しばらく浮かんでる船もある――そういうのは調べられて、価値のあるものは全部持っていかれちゃうんだ。\nリバドスのことはよく知らないけど、ナーワルたちが船で見つけたガラクタ一つ一つで争うとは思えないな。たぶん、 全部まとめて一つの山にして、それから戦利品の合計を数えて、やっと分け前を決めるんだよ。";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Grinspy_39":
			dialog.text = "うーん…";
			link.l1 = "外輪には時々船が流れ着くんだよ。すぐに沈む船もあれば、しばらく浮かんでるのもある——そういう船は調べられて、価値のあるものは全部持っていかれちゃうんだ。リバドスのことはよく知らないけど、 ナーワルたちが船の中で見つけたガラクタ一つ一つで争うとは思えないな。たぶん、 全部まとめて一つの共有財産にしてから、ちゃんと目録を作って、それから分け前を決めるんだよ。";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "Grinspy_40":
			dialog.text = "あんたは馬鹿じゃないよ、+pchar.name+。ここらの連中とは違ってさ。うん、だいたいそんな感じで合ってるよ。あたし個人としては、 ああいう書類仕事はうんざりなんだけど、アラン・ミルローの時代や、 その前のナーワル一族の長たちの頃からずっとそうなんだ。そういう記録はちゃんと残してるし、それだけじゃなくてさ、 リヴァドスや海賊が最初にたどり着いた船まで記録してるんだよ。そういう場合はもちろん、誰が乗ってたとか、 何があったかなんて分からないけどね……";
			link.l1 = "メアリーの両親が難破の後にセレス鍛冶屋へ連れて来られたという事実から判断すると、 彼らの船を見つけたのはナーワルズだったんだ。\nつまり、その記録が残っているはずだよ。";
			link.l1.go = "Grinspy_41";
		break;
		
		case "Grinspy_41":
			dialog.text = "そうかもしれないね。あたしにははっきりとは言えないよ。これからも言えないだろうね。";
			link.l1 = "「今はあんたの言ってること、あたしにはわかんないよ」 "+npchar.name+".";
			link.l1.go = "Grinspy_42";
		break;
		
		case "Grinspy_42":
			dialog.text = "難破船の記録だよ。ドッドソンが去った後、レイトン・デクスターが提督になった時に、 あたしたちからその書類を持っていっちゃったんだ。";
			link.l1 = "そんなふうに――彼が持って行ったの？あんた、反対しなかったの？";
			link.l1.go = "Grinspy_43";
		break;
		
		case "Grinspy_43":
			dialog.text = "まず第一に、彼は十分に礼儀正しかったよ。\n第二に、すぐに返すって約束したんだ。\nそして三つ目……あたしがそんな書類のことなんて、なんで気にしなきゃいけないの？";
			link.l1 = "まあ、全く役に立たない記録ってわけじゃないんだよ。";
			link.l1.go = "Grinspy_44";
		break;
		
		case "Grinspy_44":
			dialog.text = "あたしが言った通り、これはただの伝統だよ、主にうちの一族が船の戦利品で喧嘩しないようにするためのね。 船が流れ着いたら、できる限り全部剥ぎ取って、リストを作って、一部を分け合って、残りは倉庫に隠す――それだけのことさ。引き出しをゴチャゴチャにする必要なんてないでしょ？今はちょっとスペースもできたし――アドミラルに感謝しなきゃいけないくらいだよ、うん。";
			link.l1 = "わかったよ。じゃあ、「サン・アウグスティン」に進路を取るね。でも、 またあんたに会いに立ち寄るかもしれないからね。\n "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_18");
		break;
		
		case "WildRose_Dexter_1":
            dialog.text = "「あっ、」 "+pchar.name+"どうぞ、どうぞ。用事で来たのかい、友達？それともただ挨拶しに寄っただけ？";
            link.l1 = "今回は仕事だよ。まあ、個人的な用事ってことにしとこうか。";
            link.l1.go = "WildRose_Dexter_2";
			DelLandQuestMark(npchar);
        break;

        case "WildRose_Dexter_2":
            dialog.text = "「そして、あんたのその興奮ぶりを見る限り、あたしにとっても、あんたにとっても大事なことなんだろうね。」";
            link.l1 = "本当？あたしから言わせれば、むしろ疲れてるって感じだよ。ここ数日、 あんたの縄張りをずいぶん歩き回らされたんだからさ。関節が文句言い始めてるし――まったく、こんなのはあんたみたいな年寄りだけの悩みだと思ってたあたしがバカだったね。";
            link.l1.go = "WildRose_Dexter_3_1";
            link.l2 = "ちょっと息が切れただけだよ、あたし。だって、あたしは一日中椅子に座ってるわけじゃないからさ。 あんたとは違ってね――どうやらあんたの足はもう完全に役立たずみたいじゃない、ははは！";
            link.l2.go = "WildRose_Dexter_3_2";
        break;

        case "WildRose_Dexter_3_1":
            dialog.text = "ねえ、なんであたしがこの椅子にくっついてるか、考えたことある？へへっ\nわかる？自分の健康は、正義の島のどんな大金を積んだって買えないって気づいたら、 人生の見方がガラッと変わるもんだよ。";
            link.l1 = "面白いね――それこそ、あたしがここに話しに来たことなんだよ。";
            link.l1.go = "WildRose_Dexter_4";
			AddCharacterExpToSkill(pchar, "Defence", 100);
        break;
		
		case "WildRose_Dexter_3_2":
            dialog.text = "ねえ、あたしがこの椅子にくっついてる理由、考えたことある？へへっ。\nわかる？自分の健康は、この正義の島のどんな大金を積んでも買えないって気づいたら、 人生観なんてガラッと変わっちゃうもんだよ。";
            link.l1 = "おかしいね、ちょうどその話をしに来たんだよ。";
            link.l1.go = "WildRose_Dexter_4";
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;

        case "WildRose_Dexter_4":
            dialog.text = "「あたしの健康のこと？」";
            link.l1 = "いや、正義の島の財宝のことだよ。いや、もっと正確に言えば、その財宝の目録についてさ。さらに言うと、 その目録が記された帳簿のことなんだ。";
            link.l1.go = "WildRose_Dexter_5";
        break;

        case "WildRose_Dexter_5":
            dialog.text = "えっと…もう少し分かりやすく言ってくれない？ "+pchar.name+"?";
            link.l1 = "少し前に、正義の島で座礁した船の航海日誌をナーワル号の連中から手に入れたんだよね…";
            link.l1.go = "WildRose_Dexter_6";
        break;

        case "WildRose_Dexter_6":
            dialog.text = "それで、あの間抜けグリーンスペンが本当にあんたを奴らの後を追わせたの？よくもまあ、そんなことできるよね。";
            link.l1 = "「全然そんなことないよ」 "+npchar.name+"「…ドナルドは関係ないよ。あたしがこの件で彼に相談したら、あなたのところに行けって言われたんだ。だけど、 あなたの反応には正直、笑っちゃったよ。ねえ、どうしてナーワル号の記録が必要だったのか、教えてくれない？」";
            link.l1.go = "WildRose_Dexter_7";
        break;

        case "WildRose_Dexter_7":
            dialog.text = "なぜダメなの？まあ、わかるでしょ、あたしは船そのものには全然興味ないんだよ。積み込まれてる財宝？それも同じ。 ここにはみんなに行き渡るくらいあるし、みんなが欲張らなきゃね。少なくとも、あたしはそう思ってる。 あたしが本当に気にしてるのは武器さ。マスケット、サーベル……大砲だって。はい、あの賢ぶった連中は時々それも引き上げるんだよ。頭の悪い黒い野郎どもには無理だけど、 ナーワルたちは……\n";
            link.l1 = "それで、グリーンスペンの人たちが新たな争いにどれだけ備えているか、確かめに来たんだね？";
            link.l1.go = "WildRose_Dexter_8";
        break;

        case "WildRose_Dexter_8":
            dialog.text = "それと、あたしと仲間たちがしっかり目を光らせてるって伝えておいてよ。\nまあ、かなり分かりやすい合図だけど、ドナルドがあの訓練でやったちょっとした茶番を考えたら、 あたしが彼のお金を狙ってるって思われても不思議じゃないよね。";
            link.l1 = "うん、あんたの思い通りにはいってないみたいだね。\nそれで、リバドスの連中はどう？ブラック・エディがまた何かやらかしてるの？";
            link.l1.go = "WildRose_Dexter_9";
        break;

        case "WildRose_Dexter_9":
            dialog.text = "リバドス、エディ……あいつら黒んぼは本当に汚ねえな。シャークがあいつらをあれほど憎んでたのも無理はねえよ。";
            link.l1 = "つまり、あいつが本当に問題を起こしてるんだね。";
            link.l1.go = "WildRose_Dexter_10";
        break;

        case "WildRose_Dexter_10":
            dialog.text = "そうなんだよ、いや、嘘ついたら呪われてもいいさ！あの黒い野郎どもは静かになっちまって、 自分たちの船に引きこもってるんだ……";
            link.l1 = "じゃあ、一体何がそんなに気に食わないんだよ？\n "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_11";
        break;

        case "WildRose_Dexter_11":
            dialog.text = "「あたし、これをどう説明したらいいのか……」 "+pchar.name+"…ね、まるで大海原の風みたいなものなんだよ。時には優しくて、時には強くて、時には本物の嵐になることもある。でも、 どんな風でも船を前に進めてくれるし、いい船長ならその風をうまく使いこなせるんだよね。\n";
            link.l1 = "穏やかなそよ風は、荒れ狂う嵐よりもいつだっていいんだよ。";
            link.l1.go = "WildRose_Dexter_12";
        break;

        case "WildRose_Dexter_12":
            dialog.text = "そうだよ。でもさ、時々は全く風が吹かないこともあるんだ。凪――どんな船長だってどうしようもない。船尾甲板に座って、水面をじっと見つめて、 次に何が起こるのかって考えるしかないんだよ。エディとその相棒チミセットも同じさ――あいつら、何か企んでるって、あたしの勘が言ってるし、絶対にろくなことじゃないって、雷に誓って言うよ！";
            link.l1 = "もしかしたら、自分の尻を上げてエドワードとちゃんと面と向かって話すべきじゃない？それか、いっそ三人で集まって、 ドナルドも連れてきて、腹を割って話し合うとかさ。それがまた正義の島を血で染め直すより、 ずっといい考えだと思うよ。まあ、いいや…あたしがここに来た理由に話を戻そうか。\n";
            link.l1.go = "WildRose_Dexter_13";
        break;

        case "WildRose_Dexter_13":
            dialog.text = "あんた、イッカクの財宝に興味あるんだよね？そこで何を見つけたいの？";
            link.l1 = "ここで失われた船の一覧に興味があるんだ。特に、1638年の分だよ。\n実は、メアリーの両親についての情報を探しているんだ。母親についてはある程度わかっているけど、 父親のことは全然わからないんだよ。\n彼についての詳細はかなり曖昧で、名前すら知らない。唯一の手がかりは、1638年6月に外輪で難破した船の名前だけなんだ……";
            link.l1.go = "WildRose_Dexter_14";
        break;

        case "WildRose_Dexter_14":
            dialog.text = "貴族か。あたしも昔は自分の父親が誰なのかで悩んだことがあるんだ、うん。\nでも、残念だけどあたしには力になれないよ。";
            link.l1 = "「それはどうしてなの、もしよかったら教えてくれない？」";
            link.l1.go = "WildRose_Dexter_15";
        break;

        case "WildRose_Dexter_15":
            dialog.text = "「あんたには隠しごとなんてないよ、」 "+npchar.name+"。あたしじゃなくて、ドナルドのことだよ。彼が渡してくれた書類は1651年からのものだけだったんだ。あたしはもっと古い記録、せめてその前の十年分くらいはないかって聞いたけど、 彼はそれがアラン・ミルローから受け継いだ全てだって言ってた。そう言われたんだよ。";
            link.l1 = "彼が嘘をつく理由なんてなかったと思うよ。";
            link.l1.go = "WildRose_Dexter_16";
        break;

        case "WildRose_Dexter_16":
            dialog.text = "あたしも分からないよ、友達。だって、彼は何の質問もせずに新しい記録を渡してくれたんだもん。むしろ、 あのガラクタを手放せてちょっと嬉しそうに見えたくらいだし…\nもしかしたら、ミルローは何十年も前の書類をただ処分しただけかも…燃やしたとか、あるいは…";
            link.l1 = "いや、そんなはずないよ。";
            link.l1.go = "WildRose_Dexter_16_Add";
        break;

        case "WildRose_Dexter_16_Add":
            StartInstantDialog("Mary", "WildRose_Dexter_17", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_17":
            dialog.text = "違うよ、そんなはずない。アランがそんなことするわけないじゃない。";
            link.l1 = "「なんでそんなに自信があるの、」 "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_17_1";
            link.l2 = "あいつは書類仕事よりナイフや手斧の方が似合うと思ってたよ。字が読めるなんて、意外だね。";
            link.l2.go = "WildRose_Dexter_17_2";
        break;

        case "WildRose_Dexter_17_1":
            dialog.text = "彼は正義の島に関するあらゆる記録をとても丁寧に扱っていたんだよ。\nそれらを島の物語の一部として見ていたの。\nそして、歴史――この場所だけじゃなくて――それこそがアランの本当の情熱だったんだ、ね？\n手に入る歴史書や文献は全部読み漁っていたよ……\n時々、あたしは彼のこと、戦士より学者の方がずっと向いてるんじゃないかって思ってた。\nそれを一度本人にも言ったことがあるんだ。";
            link.l1 = "...";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_17_2":
            dialog.text = "彼は正義の島に関するあらゆる記録をとても大切に扱ってたよ。\nそれらをこの島の歴史の一部として見てたんだ。\nそして歴史――この場所だけじゃなくて――それこそがアランの本当の情熱だったんだよ、うん。\n手に入る限りの歴史的な文書や本を全部読み漁ってた……\n時々、あたしは彼、戦うより学者になったほうがずっと向いてるんじゃないかって思ったこともあるんだ。\n一度、本人にもそう言ったことがあるよ。";
            link.l1 = "もしかしたら、彼は本当に剣やピストルよりも眼鏡と紙と羽ペンを選ぶべきだったのかもね――そうしていれば、今でもこの腐った船の甲板をうろうろしていたかもしれないよ。\nでも、ミルローがそんなに記録好きだったなら、その記録はどこにしまったんだろう？\nうっかりインクを一枚にこぼしたってことはあるかもしれないけど――何十枚、いや何百枚もあったはずでしょ？";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_18":
            dialog.text = "あたしが知ってるのは、あの人がその書類を自分の命より大事に守ってたってことだけだよ。 誰かに盗まれたのかもしれないし、もしかしたら自分で誰かに渡したのかもね……";
            link.l1 = "盗まれたって？何のために、何十年も前に船楼から竜骨まで丸裸にされた船の情報なんて必要とする奴がいるの？ あたしが渡した――その方がよっぽどありそうだけど、でも誰に？何のために？";
            link.l1.go = "WildRose_Dexter_19_Add";
        break;

        case "WildRose_Dexter_19_Add":
            StartInstantDialogNoType("Dexter", "WildRose_Dexter_20", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_20":
            dialog.text = "他の歴史マニアにでも、ははは！チャールズの言う通りだよ、 あたしもあんな古い落書きを欲しがる人なんて他に思いつかないよ。";
            link.l1 = "誰かが必要としてたんだよね。でも、ちょっと考えてみるよ。うん、 "+npchar.name+"、もうこれ以上引き止めないよ。また会おうね。";
            link.l1.go = "Exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19");
        break;
		
		case "WildRose_Betancur_1":
			dialog.text = ""+pchar.name+"、また会えて嬉しいよ。メアリーはどうしてる？";
			link.l1 = "「そして、あたしたちも会えて嬉しいよ、」 "+npchar.name+"。でも、あたしたちがどうなるかは――それはあなた次第だよ。";
			link.l1.go = "WildRose_Betancur_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Betancur_2":
			dialog.text = "会話を始めるには興味深いやり方だね、正直に言うと。\nそれに、君たちの顔つきを見る限り、ちょっと不安になるよ。";
			link.l1 = "「慌てなくていいんだよ、」 "+npchar.name+"、あんたのせいじゃないよ。あたしたち、ただこのギシギシいう難破船の上を休みなしに走り回って、 ちょっと息が切れてるだけさ。今日の空気も重いし、そう思わない？";
			link.l1.go = "WildRose_Betancur_3_1";
			link.l2 = "あんたを探して正義の島中を走り回ってたんだよ、だから手を貸してほしいんだ。ふう、この暑さは本当にたまらないね…";
			link.l2.go = "WildRose_Betancur_3_2";
		break;

		case "WildRose_Betancur_3_1":
			dialog.text = "ええっと、そうだね、今はそよ風でも吹いてくれたら本当にありがたいよ。\nでも、あんたを疲れさせてるのは天気だけじゃないんでしょ？\nそれで、あたしに何かできることある？";
			link.l1 = "あのね、あたしとメアリーで二十年前に何があったのか、真相を明らかにしようと調査を始めたんだよ。";
			link.l1.go = "WildRose_Betancur_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Betancur_3_2":
			dialog.text = "ええっと、そうだね、今はそよ風でも吹いてくれたら嬉しいよ。でも、 あんたを疲れさせてるのは天気だけじゃないんでしょ？それで、あたしに何かできることある？";
			link.l1 = "あのね、あたしとメアリーで二十年前に何があったのか、真相を明らかにしようと調査を始めたんだよ。";
			link.l1.go = "WildRose_Betancur_4";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Betancur_4":
			dialog.text = "面白そうだね。で、具体的にはどんな話なの？";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_4_add";
		break;
		
		case "WildRose_Betancur_4_add":
			StartInstantDialog("Mary", "WildRose_Betancur_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_5":
			dialog.text = "あたしの両親のことだよ、アントニオ。チャールズと一緒に、二人がどんな人だったのか、 何があったのかを調べてるんだ。母さんはあたしを産んだときに亡くなったって、もう分かってる。でも、 父さんのことは、そんなに単純じゃないんだよね…";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_5_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_6":
			dialog.text = "何年に生まれたんだっけ、教えてよ…";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_6_add":
			StartInstantDialog("Mary", "WildRose_Betancur_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_7":
			dialog.text = "1638年に。6月に。";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_7_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_8":
			dialog.text = "あの頃、あたしはまだ十二歳だったんだよ、メアリー。あの時代のことは、正直あまりよく覚えていないんだ。もちろん、 今になって思い出がふと頭をよぎることはあるけど、正直、それらを全部つなぎ合わせるのはちょっと難しいんだ。 ごめんね、でも、あたしが力になれるかどうかは自信がないよ…";
			link.l1 = "あんたにそこまでは求めてないよ、アントニオ。でも、メアリーが生まれた日のことを何か思い出せたら、 すごくありがたいんだ。";
			link.l1.go = "WildRose_Betancur_9";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_9":
			dialog.text = "「それじゃ、どうやってあたしが手伝えばいいの、」 "+pchar.name+"?";
			link.l1 = "あんた、歴史に興味があるって言ってたよね。世界の歴史だけじゃなくて、特に正義の島の歴史にも、だよ。";
			link.l1.go = "WildRose_Betancur_10";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;

		case "WildRose_Betancur_10":
			dialog.text = "本当だよ。あたし、見つけられる本は全部読んだし、手に入る写本も全部勉強したんだ…";
			link.l1 = "話しているのはあの写本のことだよ。あんた以外に、正義の島で歴史にあんたと同じくらい情熱を持ってた人は、 もう一人しかいなかったんだ……";
			link.l1.go = "WildRose_Betancur_12";
		break;

		case "WildRose_Betancur_12":
			dialog.text = "アラン・ミルロー。ね、あの人とはリバドスを一掃する計画を立ててなかった頃に話したんだよ。 それから後には海賊たちまで標的にしてたけどね。頭の切れる人で、すごい才能も持ってたんだ。";
			link.l1 = "間違いない――あの坊やはただ者じゃなかったよ。あいつは、あたしたちの役に立つ何かを持ってたんだ。しかも、 それは正義の島じゃ誰の役にも立たないものさ、あんたたち二人以外にはね。島の近くで難破した船の航海日誌――積み荷や回収された財宝の記録、もしかしたら乗客の名前まで……\n";
			link.l1.go = "WildRose_Betancur_13";
		break;

		case "WildRose_Betancur_13":
			dialog.text = "そうだよ。";
			link.l1 = "それで、あいつらを見たの？";
			link.l1.go = "WildRose_Betancur_14";
		break;

		case "WildRose_Betancur_14":
			dialog.text = "あたし、見ただけじゃなくて、その中身も自分のノートに写したんだよ。ある時の会話で、 彼がその日誌の存在をちらっと話してくれてさ、あたし、それを勉強したくて頼んだんだ――あたし、「正義の島年代記」みたいなものをまとめようとしてて、あの記録はすごく役立ったんだよ。\nアランもあたしのアイデア――この場所の歴史を書くってやつ――に大喜びだったよ。まあ、彼は全部はくれなくて、1650年代の記録は自分で持ってたけど、その時は他の分だけで十分だったんだ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_14_add";
		break;
		
		case "WildRose_Betancur_14_add":
			StartInstantDialog("Mary", "WildRose_Betancur_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_15":
			dialog.text = " その記録……1638年も含まれてるよね？お願い、そうだって言ってよ！";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_15_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_15_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_16":
			dialog.text = "あたし、その航海日誌なら山ほど持ってるよ――1620年までさかのぼるやつもね。アランの話だと、その頃から記録をつけ始めたらしいんだ。で、そう、1638年のもちゃんとあるよ、メアリー。";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_16_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_16_add":
			StartInstantDialog("Mary", "WildRose_Betancur_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_17":
			dialog.text = "あたしたちにそれを見せてくれる？";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_17_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_17_add":
			if (PChar.location == "PlutoStoreSmall") StartInstantDialog("LSC_Betancur", "WildRose_Betancur_18", "Quest\CompanionQuests\WildRose.c");
			else StartInstantDialog("LSC_Betancur", "WildRose_Betancur_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_18":
			dialog.text = "選択肢なんてなさそうだね、あはは！ちょっと待って。全部ここ、このキャビネットの一番下の引き出しにあるよ。\n";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19_1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_19":
			dialog.text = " どうぞ、くつろいで、心ゆくまで調査していって……";
			link.l1 = "それをやるんだよ、あたしたち。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_20");
			AddQuestRecordInfo("WildRose_Records", "1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;
		
		case "WildRose_Mary_101":
			dialog.text = "「ほら、」 "+pchar.name+"、見てよ！ジョシュアとテレサ・カスパーだよ！信じられない、やったんだ、ほんとにやったんだよ、ね！ しかも船の名前は『ラングラー』！これでお父さんのこと、全部わかるかもしれない――どんな人だったのか、どうしてここに来たのか…";
			link.l1 = "あたし、怖いよ、 "+npchar.name+"…急ぎすぎだよ…そんなに簡単じゃないかもしれないよ。陛下の船…王立海軍の記録から情報を手に入れるには、誰に頼めばいいか考えないとね…";
			link.l1.go = "WildRose_Mary_102";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Mary_102":
			dialog.text = "考えよう！考えればきっとわかるよ、 "+pchar.name+"！一番大変だったところはもう乗り越えたんだよ、ね！";
			link.l1 = "もしかしたら、ヤング旦那やフリディック旦那とも話してみる意味があるかもしれないね。\nでも、あたし、正義の島にそんな名前の人がいた覚えはないよ。";
			link.l1.go = "WildRose_Betancur_20_add";
		break;
		
		case "WildRose_Betancur_20_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "「ここにいないからだよ」 "+pchar.name+"。その二人はカスパー一家と一緒に救出された翌晩、すぐに亡くなったんだよ。";
			link.l1 = "興味深いね。妊婦はさらに一週間生き延びたのに、王立海軍の水夫二人は急に死んじまったんだ……";
			link.l1.go = "WildRose_Betancur_22";
		break;

		case "WildRose_Betancur_22":
			dialog.text = " 最初からあまり元気じゃなかったよね、あたしの記憶だと。今になって思い出してきた、うん。 "+pchar.name+" ――セレス鍛冶屋の近くにいた時に、彼らが船に連れてこられたんだよ……うん、あたしはオレリー・ベルティーヌと一緒にエスメラルダ号に乗ってたと思う。それから、 黒人異教徒のシャーマンのチミセットも、なぜか店に来てたんだ。最初は、 その二人の水夫はもう死んでるのかと思ったけど、実際に息を引き取ったのはその翌日だった……";
			link.l1 = "まあ、仕方ないよね。でも、もうかなり色々分かったじゃない。手伝ってくれてありがとう、アントニオ。";
			link.l1.go = "WildRose_Betancur_23";
		break;

		case "WildRose_Betancur_23":
			dialog.text = " 「お礼なんていらないよ、」 "+pchar.name+"。全部アランのおかげだよ――あの胸甲騎兵たちのほとんどは、あの記録の本当の価値なんて分かりっこなかった。でも、 こういう文書を通してこそ歴史は蘇るんだよ！";
			link.l1 = "いつかメアリーと俺があんたの年代記を読む日が来るといいな、相棒。\nほら、あんたの日誌だ――なくすなよ。\nさて、俺たちはもう行く時間だ。\nまた会えるかもしれないな、友よ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_21");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "「ここにいないからだよ、」 "+pchar.name+"。その二人は、カスパー一家と一緒に救出された翌晩に亡くなったんだ。";
			link.l1 = "興味深いね。妊婦はもう一週間生き延びたのに、王立海軍の水夫二人は突然死んじゃったんだよ……";
			link.l1.go = "WildRose_Betancur_22";
		break;
		
		case "WildRose_Chimiset_21":
			dialog.text = "また会えて嬉しいよ、友達。どうしてここに来たの？\n";
			link.l1 = " お願いがあるんだ、+npchar.name+……いや、むしろ質問かな。";
			link.l1.go = "WildRose_Chimiset_22";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_22":
			dialog.text = "質問があればどうぞ。あるいは、お願いでもいいよ。あたしにできることなら、なんでも力になるからね。";
			link.l1 = "あのさ、どれくらいの間、正義の島に住んでるの？";
			link.l1.go = "WildRose_Chimiset_23";
		break;

		case "WildRose_Chimiset_23":
			dialog.text = "何十年も、何十年もだよ、旦那。あたしは子供の頃にここに流れ着いたんだ、でもその時から頭の回転は早かったよ――奴隷船の上でね。あたしの話は、ここで聞いた他のみんなと大して変わらないんだ。嵐、難破……あたしが閉じ込められてたイギリスのガレオン船は、外輪にすら辿り着けなかった。波に押し流されて岩礁にぶつかり、 真っ二つに割れちまったんだよ。\n";
			link.l1 = "どうやって生き延びたの？正義の島の外縁からここまで暗礁はかなり離れてるし、 嵐の波をくぐり抜けてここまで来るなんて、正直、簡単なことじゃないよ…";
			link.l1.go = "WildRose_Chimiset_24";
		break;

		case "WildRose_Chimiset_24":
			dialog.text = "あの夜は神々があたしの味方だったんだよ。あたしはなんとか枷を外して、元は船だった木片をつかんだんだ。 部族の仲間、アサナも一緒だった――二人で波と戦って、力尽きて気を失うまで頑張ったんだよ。\n";
			link.l1 = "どこかの船に流れ着いたの？";
			link.l1.go = "WildRose_Chimiset_25";
		break;

		case "WildRose_Chimiset_25":
			dialog.text = "うん、あたしたち、船倉の穴に這い込んだんだよ…そこでまた気を失っちゃって、すごく弱ってたからさ。アサナが叫び出したときに目が覚めたんだ――あいつ、あたしたちが流れ着いた同じ船に登ってきた巨大なカニに引き裂かれてたの。で、 あたしはただ立ち尽くして見てるだけ…次は自分だって分かってるのに、恐怖で体が固まって、一歩も動けなかったんだよ。";
			link.l1 = "友達を助けようとすることもできたはずだよ。だけど、そうしたら今こうして話してることはなかったんじゃない？\nそれで、どうやって逃げてきたの？";
			link.l1.go = "WildRose_Chimiset_26_1";
			link.l2 = "「あんたから始めなかっただけ運がよかったね」 "+npchar.name+"「それで、どうやって逃げたの？また海に飛び込んで泳いでいったの？」";
			link.l2.go = "WildRose_Chimiset_26_2";
		break;

		case "WildRose_Chimiset_26_1":
			dialog.text = "アサナの悲鳴は、最近のハリケーンの後に船の船倉をあさりに出てきた数人のリバドスたちに聞こえたんだ。 彼らはその獣を取り囲んで殺した。アサナのためにできることは何もなかったけど、あたしはずっと運が良かったんだよ。 そうして、あたしはここにいるってわけ。\nでも、今度はあんたの番だよ、友達――どうしてこんなことを知りたがったの？";
			link.l1 = "「実は、」 "+npchar.name+"、どうしてここに来たのかじゃなくて、いつここに来たのかを聞こうと思ってたんだよ。";
			link.l1.go = "WildRose_Chimiset_27";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_26_2":
			dialog.text = "アサナの悲鳴は、最新のハリケーンの後に船の積み荷を探しに出ていた何人かのリバドスたちに聞こえたんだ。 彼らはその獣を取り囲んで殺した。アサナにはもうどうしようもなかったけど、あたしはずっと運が良かったってわけ。 そうしてここに来ることになったんだよ。\nでも、今度はあんたの番だ、友達――なんでこんなことを知りたかったの？";
			link.l1 = "「実は、」 "+npchar.name+"、あたしが聞こうと思ってたのは、どうしてここに来たかじゃなくて、いつそうなったのかってことだよ。";
			link.l1.go = "WildRose_Chimiset_27";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Chimiset_27":
			dialog.text = "うーん、あんたたちの暦だと1623年、晩夏だったよ……それ以上は正確には言えないんだよね…";
			link.l1 = "それは必要ないよ。じゃあ、1638年には、もう十五年も正義の島にいたんだね。";
			link.l1.go = "WildRose_Chimiset_28";
		break;

		case "WildRose_Chimiset_28":
			dialog.text = "そうみたいだね、友達。";
			link.l1 = "その年の六月、ハリケーンが国王チャールズ一世陛下の艦隊所属のブリッグ船『ラングラー』を外輪部へと押し流した。\n乗組員のうち生き残ったのはわずか四人――その中にメアリーの両親、ジョシュアとテレサ・カスパーがいた。";
			link.l1.go = "WildRose_Chimiset_29";
		break;

		case "WildRose_Chimiset_29":
			dialog.text = "うん、それは覚えてるよ、友だち。ぼんやりと、まるで霧の中みたいだけど、でもちゃんと覚えてるんだ……";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_29_add";
		break;
		
		case "WildRose_Chimiset_29_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_30":
			dialog.text = "本当に覚えてるの？じゃあ、教えてよ！";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_30_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_30_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_31":
			dialog.text = "あまり多くは語れないよ。四人いたんだ――士官、その妻、そして二人の水夫。女の人は妊娠していて、助けた人たちは朝までもたないだろうと思ってたけど、 彼女はまるで雌ライオンみたいに強かったんだよ、でも二人の水夫は一日も経たずにこの世を去った……あたしは彼らを見たよ。弱ってたけど、まだ命の灯は残ってたんだ……";
			link.l1 = "「殺されたって言いたいの？」";
			link.l1.go = "WildRose_Chimiset_32";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_32":
			dialog.text = "それなら、誰も目撃者はいなかったし、遺体にも傷はなかったんだよ、旦那…";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_32_add";
		break;
		
		case "WildRose_Chimiset_32_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_33", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_33":
			dialog.text = "「士官」って言ったよね、うん……本当にあたしの父さんは士官だったの？";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_33_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_33_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_34":
			dialog.text = "将校の制服を着てた――あたしが彼の顔を思い出そうとすると、たぶんそれだけしか覚えてないんだよね。";
			link.l1 = "もし彼が士官だったなら、他の服は着ていなかったはずだよ――きっと服のバリエーションなんてなかったんじゃないかな…他に何か覚えてること、ある？ "+npchar.name+"？何か特徴は……そうだね、顔に傷があるとか、他に怪我の跡とか……";
			link.l1.go = "WildRose_Chimiset_35";
		break;
		
		case "WildRose_Chimiset_35":
			dialog.text = "あまり覚えていないんだ、友よ。彼の顔はほとんど記憶から消えかけている――もう二十年も経つからな……。だが、あの視線だけは、今でもはっきり覚えている。この男と話したのは一度きりだったが、彼の灰色の目――メアリーとそっくりな――その眼差しは決して忘れない。そこには絶望があり、追い詰められたカモシカのような恐怖があり、同時に――ライオンにふさわしい激しさと覚悟があった……。";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_35_add";
		break;
		
		case "WildRose_Chimiset_35_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_36":
			dialog.text = "あの人と話したんだよね？何について？";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_36_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_36_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_37":
			dialog.text = "それは、あなたが生まれる数時間前のことだった。彼はここ、「プロテクター」にやって来て、 私に会わせろと要求したんだ。リバドスの長モゲディは、その大胆さに唖然としていた――でも、私は突然その男に興味を持った。彼が私の前に立ったとき、膝をついて、妻を救ってくれと懇願した……誰かが、彼らがここにいた短い間に、私のことを彼に伝えたのだろう。私は承諾した、 モゲディが反対したにもかかわらず……";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_37_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_37_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_38":
			dialog.text = " じゃあ、あたしはあなたに命を救われたってことになるの？";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_38_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_38_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_39", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_39":
			dialog.text = "嘘をついても仕方ない――君のお母さんにたどり着くことはできたけど、遅すぎたんだ。ナーワルズたちは俺を『セレス・スミシー』 号に乗せるのを拒んだ。君のお父さんが……なんとか説得してくれたけど、俺が可哀想なテレーザを見たのは、彼女が最期の息を引き取る時だった。 彼女は君を産んだよ。もし俺がもっと早く着いていれば、助けられたかもしれない、でも……";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_39_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_39_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_40", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_40":
			dialog.text = "母さんは死んだ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_40_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_40_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_41", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_41":
			dialog.text = "ああ……。彼女はあなたを見て、最後の息を引き取ったんだ。でもその前に、まるで力を振り絞るように、「ルパート」 という名の誰かを呼んだんだよ。助けを求めるかのように、思い切りその名前を叫んで――そして、息を引き取ったんだ。";
			link.l1 = "「ルパート？ジョシュアじゃなくて？」";
			link.l1.go = "WildRose_Chimiset_42";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_42":
			dialog.text = "あたしがこの話をしてる間、友達、まるであの瞬間をもう一度体験してるみたいだったよ。あれは絶対に忘れられない――彼女の絶叫も、苦しみに歪んだ顔も。そして、そう、彼女の唇から最後にこぼれたのは「ルパート」だったんだ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_42_add";
		break;
		
		case "WildRose_Chimiset_42_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_43":
			dialog.text = "あたしの母さんは綺麗だった？どんな人だったか、チミセット、教えてくれる？";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_43_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_43_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_44", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_44":
			dialog.text = " そんなことする必要はないよ、メアリー。鏡を見てごらん――君はまるで彼女の生き写しだ。ただ、その鋭い眼差しだけは父親譲りだね。";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_44_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_44_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_45", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_45":
			dialog.text = "それで、彼はどうなったの？あたしたちが調べたところ、あたしが生まれてほんの数日後に、 彼は跡形もなく消えちゃったんだよ、ね！でも、殺されたわけじゃないよね？";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_45_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_45_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_46", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_46":
			dialog.text = "テレサが死にかけていると知らされた途端、ジョシュアは本当に激怒したんだよ――誓って言うけど、サバンナのライオンだって獲物にあそこまでの猛り狂った勢いで襲いかかったことはないよ。 君のお父さんが、あたしをフルートに乗せてくれなかったあのイッカクたちに向かっていったときのことさ…彼を押さえつけるのに六人がかりだったんだ――しかも、その前に氏族の戦士二人を鎧ごと海に投げ込んだ後でね。";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_46_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_46_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_47", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_47":
			dialog.text = "「それで、彼に何をしたのか――教えてよ、ねえ！」";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_47_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_47_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_48", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_48":
			dialog.text = "奴は「タルタロス」の牢の一つに放り込まれたんだ。誰も裁こうとはしなかった――まずは騒ぎが収まるのを待ちたかったんだよ……ほとんどの者が彼に同情してたけど、あんな男と一緒に暮らしたいと思う者は少なかった。数日後、 ジョシュアは姿を消した――ちょうどその頃、何隻かの密輸業者の小舟が正義の島を出ていった。でも、誰もその舟で彼を見た者はいなかった。 それが彼の死の噂の始まりさ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_48_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_48_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_49", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_49":
			dialog.text = "つまり、あんたは彼が生きてるって思ってるんだね、うん？";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_49_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_49_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_50", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_50":
			dialog.text = "あたしが言うことは、他のみんなもきっと言うだろうけど――誰も彼の遺体を見つけてないんだよ。もしかしたら、どこかのボートの底に隠れてたのかもしれないし、 あるいはあの牢屋で喉を切られてカニの餌にされたのかもね…";
			link.l1 = "あいつがあの商人たちと同じ時期に姿を消したってことは、最初の可能性の方が濃厚だよね、うん、 そんな偶然はないもん。\nそれに、もしかしたら誰かに自分の計画をうっかり漏らしちゃったのかも？\nもし逃げたんだとしたら、ここに生まれたばかりの娘を置いて行ったってことになるけど、それもまあ、 ある意味では納得できるよ――赤ん坊があんなちゃちな船でキューバまでの航海を生き延びられたとは思えないし…\nでも、きっと彼は娘を迎えに戻るつもりだったんだよ。";
			link.l1.go = "WildRose_Chimiset_51";
		break;
		
		case "WildRose_Chimiset_51":
			dialog.text = "あたしには分からないよ、友よ。ジョシュア・カスパーがあの頃誰かと話したとしたら、 それは看守たちだけだったはずさ――でも、その連中もみんなとっくにこの罪深い世界を去っちまったよ。あ、そうだ、 ある日ドミンゴ神父が彼に会いに来たことがあったっけ――ジュリアン修道士の前に白人たちのための神父だった人さ…";
			link.l1 = "告白でもするつもりだったの？逃げる途中で死ぬのが怖かったんだろうね。";
			link.l1.go = "WildRose_Chimiset_52";
		break;

		case "WildRose_Chimiset_52":
			dialog.text = "あたしにわからないことは説明できないよ、友達。ドミンゴも何も教えてくれないさ――彼はもう十五年くらい前に死んじゃったんだ、ね。誰かに頭を殴られたのかもしれないし、 ただ酒を飲みすぎて死んだのかもしれない――あの人、お酒が大好きだったからね…";
			link.l1 = "でも、もしかしたらドミンゴが日記をつけてたかも…あるいは、そのジョシュアとの会話を兄のフリアンに話したんじゃない？\n";
			link.l1.go = "WildRose_Chimiset_52_add";
		break;
		
		case "WildRose_Chimiset_52_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_53", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_53":
			dialog.text = "「彼と話さなきゃ」 "+pchar.name+"、うん。早ければ早いほどいいよ。これを片付けるまでは、船に戻ることなんて考えたくもないんだ。";
			link.l1 = "もしまだ何か分かっていないことがあるなら、ジュリアンだって知らないかもしれないけど――あたしたちで必ず真相を突き止めるよ。ありがとう、チミセット。";
			link.l1.go = "WildRose_Chimiset_53_add";
		break;
		
		case "WildRose_Chimiset_53_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_54", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_54":
			dialog.text = "あたしはいつでもあなたの力になるよ、友達。だけど、二人に一つアドバイスしてもいいかな。";
			link.l1 = " 「それは何なの？」";
			link.l1.go = "WildRose_Chimiset_55";
		break;
		
		case "WildRose_Chimiset_55":
			dialog.text = "狩りに出るときは、藪の奥深くまで入り込むなよ――二度と抜け出せなくなるかもしれないからな。";
			link.l1 = "それは覚えておくよ、シャーマン。さて――さらばだ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_22");
		break;
		
		case "WildRose_Julian_1":
			dialog.text = "神の家の庇護の下へようこそ、我が子たちよ。\n告解に来たのか、それともただ祈りたいだけなのか？";
			link.l1 = "ごきげんよう、ジュリアン兄弟。俺たちの罪を全部挙げてたら、とても時間が足りねえんだ、残念ながらな。\nだが安心してくれ、俺たちは善良なカトリックとして、寄港するたびにちゃんと教会に通ってるぜ。";
			link.l1.go = "WildRose_Julian_2_1";
			link.l2 = "ごきげんよう、ジュリアン兄弟。あたしたち敬虔なカトリック教徒は、 一日の始まりも終わりも主への祈りから始めるんだよ。";
			link.l2.go = "WildRose_Julian_2_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Julian_2_1":
			dialog.text = " 結婚もせずに一つ屋根の下で暮らす善良なカトリック信者たち……それは冒涜に近いぞ、息子よ。それに、思い出してほしいが、それは大罪だ！";
			link.l1 = "「そして、聖書には“愛はすべての罪を覆う”って書いてあるんじゃない？」";
			link.l1.go = "WildRose_Julian_3";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Julian_2_2":
			dialog.text = " 結婚もせずに同じ屋根の下で暮らす善良なカトリック信者たち……それは冒涜に近いぞ、息子よ。それに、思い出してほしいが、それは大罪だ！";
			link.l1 = "「そして、聖書には“愛はすべての罪を覆う”って書いてあるんじゃない？」";
			link.l1.go = "WildRose_Julian_3";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_3":
			dialog.text = "愛とは主の戒律に従って生きることだ――息子よ、あの戒律をもう一度思い出させてやろうか？";
			link.l1 = "また今度だよ。あたしたちは別の用事で来てるんだ。";
			link.l1.go = "WildRose_Julian_4";
		break;

		case "WildRose_Julian_4":
			dialog.text = "迷える魂が正しい道へ戻るのに、遅すぎることは決してない……。\nだが、私はお前たちの話を聞いているよ、私の子供たちよ。";
			link.l1 = "私たち、本当に少し迷ってしまったみたい、ジュリアン兄さん。過去の茂みに迷い込んじゃったんだよ。\nだから、あたしたちがまた光のもとに戻れるよう、手を貸してほしいんだ。";
			link.l1.go = "WildRose_Julian_5";
		break;

		case "WildRose_Julian_5":
			dialog.text = "とても機知に富んでいるな、息子よ。人が光へ導くのではなく、主が導くのだということを忘れてはならんぞ――そして主に従う時、その御業は神秘に満ちていることを忘れるでないぞ。";
			link.l1 = "手短に話すよ、ジュリアン兄弟。俺たちはメアリーの両親について、できる限りのことを調べているんだ。 母親のテレサについては、だいたい分かってる――夫と一緒に正義の島に来て、その一週間後に出産で亡くなった。でも父親の方は……メアリーが生まれて数日後に姿を消して、「タルタロス」号から逃げ出したらしい。噂では、 ここで最後に彼と話したのはドミンゴ神父――あんたの前任者だそうだ。";
			link.l1.go = "WildRose_Julian_6";
		break;

		case "WildRose_Julian_6":
			dialog.text = "じゃあ、あんたたちは十五年以上も遅かったんだよ、あたしの子たち。";
			link.l1 = "ああ、神父様がかなり前に亡くなったことは知ってるよ。\nそれにその頃は、ジュリアン兄弟、あなたはまだ若すぎて、正当な地位で正義の島に来てなかったんじゃない？";
			link.l1.go = "WildRose_Julian_7";
		break;

		case "WildRose_Julian_7":
			dialog.text = "彼が亡くなって数年後に、あたしはここにたどり着いたんだよ。\nこの船で全部を整えるのは大変だったけど、神様の助けもあって、どうにかやり遂げたんだ、息子よ。";
			link.l1 = "ここでいろいろ片付けている間に、ドミンゴ神父の記録を見かけたりしなかった？";
			link.l1.go = "WildRose_Julian_8";
		break;

		case "WildRose_Julian_8":
			dialog.text = "「何か具体的なことを言っているのかい、息子よ？」";
			link.l1 = "航海日誌や何かの記録帳を探しているんだ……奇跡はあまり期待できないけど、神父があの会話の内容をどこかのメモに書き残しているかもしれない。\nメアリーの父親は密輸業者の船で正義の島を離れたと俺たちは考えている――もしかしたら、神父にどこへ向かうのか、いつ娘を迎えに戻るつもりなのか、それとなく伝えていたかもしれないだろう？ ";
			link.l1.go = "WildRose_Julian_9";
		break;

		case "WildRose_Julian_9":
			dialog.text = "あたし、日記とかそういうのは見つけたことないよ、間違いなく。でも記録はいろいろあったんだ……教会のことになると、彼はすごく几帳面だったよ。主に仕える者がみんなそんな細かさを持ってるわけじゃないからね、 うん。でも、彼の書類には乾いた数字と名前しか書かれてなかった――それ以上のものはなかったよ。";
			link.l1 = "わかった範囲では、ジョシュア・カスパー――それが彼の名前――は、妻の死に激怒して、リバドスの魔術師チミセタがメアリーの母親に会うのを拒んだナーワル一族の二人を殺したんだ…";
			link.l1.go = "WildRose_Julian_10";
		break;

		case "WildRose_Julian_10":
			dialog.text = "やつらはまさに教会の子供たちのように振る舞った！異端審問の地下牢がこの悪魔のしもべを待ち構えているぞ！";
			link.l1 = "神様ってさ、もし自分の名のもとにどれだけ多くの人が拷問されたか知ったら、きっとぞっとすると思うよ。 カスパーはまだ運が良かった――ただ『タルタロス』の牢屋に放り込まれただけ。でも、結局裁判までたどり着けなかったんだ。";
			link.l1.go = "WildRose_Julian_11_1";
			link.l2 = "うん、うん、間違いないよ。カスパーは「タルタロス」の独房の一つに放り込まれたけど、判決は下されなかった――妻を失った夫の行動を、みんながみんな非難したわけじゃないからね。\n";
			link.l2.go = "WildRose_Julian_11_2";
		break;

		case "WildRose_Julian_11_1":
			dialog.text = "その後どうなったの――あの異端者は逃げたのか？";
			link.l1 = "1週間も経たないうちに、ジョシュアが姿を消したんだよ。\nその前の晩、ドミンゴ神父が彼のもとを訪ねてきたんだ。\nだから問題は――なぜかってことさ。カスパーが間違いなくプロテスタントだったなら、 カトリックの神父に告解するなんて考えにくいと思わない？";
			link.l1.go = "WildRose_Julian_12";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_11_2":
			dialog.text = "その後どうなったの――あの異端者は逃げたのか？";
			link.l1 = "一週間も経たないうちに、ジョシュアが姿を消したんだよ。\nその前の晩、ドミンゴ神父が彼に会いに来てたんだ。\nだから問題は――なぜかってことだよ。カスパーが間違いなくプロテスタントだったなら、 カトリックの神父に告解するなんてありえないでしょ、どう思う？";
			link.l1.go = "WildRose_Julian_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Julian_12":
			dialog.text = "真の信仰に立ち返るのに遅すぎるということはない、息子よ。しかし、お前の考えは筋が通っている。 もし彼が告解を必要としなかったのなら、もしかすると神父と妻の葬儀について話していたのかもしれない――もちろん、彼女がカトリックであればの話だ。あるいは娘の洗礼、いやむしろその拒否についてかもしれない。 プロテスタントは幼児洗礼を行わず、人は自分自身の意思と自覚で洗礼を受けるべきだと考えているからな。";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_12_add";
		break;
		
		case "WildRose_Julian_12_add":
			StartInstantDialog("Mary", "WildRose_Julian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_13":
			dialog.text = "でも、あたしは洗礼を受けたんだよ、ジュリアン兄弟。エリック・ユデットがそのことを教えてくれたんだ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_13_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_13_add":
			StartInstantDialog("Julian", "WildRose_Julian_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_14":
			dialog.text = "それはあくまで私の推測に過ぎません、我が子よ。真実は私にも分かりません。 主は本当に大切で必要なことだけを私たちに示してくださるのです。";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_14_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_14_add":
			StartInstantDialog("Mary", "WildRose_Julian_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_15":
			dialog.text = "あたしもまさにそんな感じだよ、ね。パドレ・ドミンゴの記録のページに、兄弟ジュリアン、 あんたが気づかなかった何かがまだ残ってるかもしれないじゃない？だって、 あんたはただパラパラめくってただけでしょ？";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_15_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_15_add":
			StartInstantDialog("Julian", "WildRose_Julian_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_16":
			dialog.text = "あそこに行く理由はなかったのだよ、我が子よ。\n長い間、しかもとても丁寧にこのことに取り組んできたのがよく分かる――主がこの茨の道を導いておられるのだ。\nもしお前が探しているものを見つける運命なら、それは主の御心であり、私がそれを妨げることはできない。\nお前が生まれた年のドミンゴの記録を渡そう。何か役立つものが見つかるかもしれん。";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_16_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_16_add":
			StartInstantDialog("Mary", "WildRose_Julian_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_17":
			dialog.text = "それはとても寛大ですね、ジュリアン修道士。1638年の記録はまだお持ちですか？";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_17_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;
		
		case "WildRose_Julian_17_add":
			StartInstantDialog("Julian", "WildRose_Julian_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_18":
			dialog.text = "ふうん、ふうん……（埃を吹き飛ばす）。どうやらこれだね。西暦1638年の台帳だよ。";
			link.l1 = "「任せて、ジュリアン兄弟……」";
			link.l1.go = "exit";
			AddQuestRecordInfo("WildRose_Records_2", "1");
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_23");
		break;
		
		case "WildRose_Mary_111":
			dialog.text = "「ねえ、」 "+pchar.name+"：8月3日。それがファビアンとあたしが洗礼を受けた日だよ。あたしは6月22日に生まれた。でも、お父さんのことは一言も書いてないんだ、ね。";
			link.l1 = "ちょうどジュリアン修道士が言った通り――乾いた数字と名前ばかりだよ。\n面白いのは、ドミンゴ神父があまりにも熱心だったせいで、プロテスタントにも臨終の儀式をしていたことさ。 エッカスやヤング、それにフリディックスがカトリックだったとは思えないけどね。";
			link.l1.go = "WildRose_Mary_111_add";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Mary_111_add":
			StartInstantDialog("Julian", "WildRose_Mary_112", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_112":
			dialog.text = "彼らはまさに天国の門に足を踏み入れるその直前に、真の信仰に立ち返ったのかもしれません、息子よ。";
			link.l1 = "もちろんだよ、ジュリアン兄さん――他に何をするっていうの？特にソーレンやロハスみたいに死んだなら、あたし思うんだけど、 それこそチミセットの行く手をふさいだナーワルたちなんじゃないかな。";
			link.l1.go = "WildRose_Mary_112_add";
		break;
		
		case "WildRose_Mary_112_add":
			StartInstantDialog("Mary", "WildRose_Mary_113", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_113":
			dialog.text = "パドレ・ドミンゴがミドルネームをちゃんと全部書いてくれた方がよかったんだよ、ね。 あたしと母さんの名前の後ろについてる「V.」とか「J.」って、一体何の意味なの？";
			link.l1 = "「それで、そのファビアンって誰？あんたと同じ日に洗礼を受けたっていう人？」";
			link.l1.go = "WildRose_Mary_114";
		break;
		
		case "WildRose_Mary_114":
			dialog.text = "セシル・アラールの息子。あっ、今思い出した！あたしを育ててくれたけど、特に優しかったわけじゃないんだ。たぶん、 あたしだけが生き残って、ファビアンはそうじゃなかったからだよ。彼は生まれて数ヶ月で死んじゃったんだ、ね。\n";
			link.l1 = "この小さな本からはほとんど役に立つことは分からなかったし――まあ、あなたの誕生日と洗礼の日付を知ったのを「役に立つ」と言うなら別だけど――だから、彼女に話を聞いてみた方がいいんじゃないかな。";
			link.l1.go = "WildRose_Mary_115";
		break;

		case "WildRose_Mary_115":
			dialog.text = "「彼女はオレリーよりそんなに年下じゃないんだよ、」 "+pchar.name+"。せめて彼女がしっかりしてくれていればいいんだけどね。\nでも、あんたは彼女に何を聞くつもりなの？";
			link.l1 = "そうだね、彼女はあんたの乳母だったから、 ドミンゴ神父がジョシュアと話した内容について何か知ってたかもしれないよ。もし彼女じゃなかったら、 誰に話すっていうのさ？オレリーやエリックもいるけどさ。でも、 最初の人からはもう聞き出せることは全部聞いたと思うし、二人目はもう誰にも何も話せないよね。\n";
			link.l1.go = "WildRose_Mary_115_add";
		break;
		
		case "WildRose_Mary_115_add":
			StartInstantDialog("Julian", "WildRose_Mary_116", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_116":
			dialog.text = "この善良な女性は、この神の家の熱心な信者です。ミサを一度も欠かさず、定期的に告解にも来ています。 きっとあなたたちを本当に助けてくれると私は信じています、子供たちよ。";
			link.l1 = "ありがとうございます、神父様。さようなら。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_24");
		break;
		
		case "WildRose_Sesil_1":
			dialog.text = ""+GetFullName(pchar)+" そしてメアリー・キャスパー。なんて嬉しい驚きなんだ！";
			link.l1 = "「あたしも、だよ」 "+npchar.name+"……あのね、実はあんたに会いに来たんだよ。ちょっと話したいことがあるんだ。";
			link.l1.go = "WildRose_Sesil_2";
			DelLandQuestMark(npchar);
			LAi_SetStayType(npchar);
		break;
		
		case "WildRose_Sesil_2":
			dialog.text = "あら、そうなの？うん、今はあたし、全部あんたに集中してるよ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_2_add";
		break;
		
		case "WildRose_Sesil_2_add":
			StartInstantDialog("Mary", "WildRose_Sesil_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Sesil_3":
			dialog.text = "これはあたしの両親のことなんだ、セシル。あたしたちはもう母さんについて知れることは全部調べたよ……あたしが生まれてすぐに亡くなったんだ。でも父さんは……ほんの数日後に跡形もなく消えちゃった。あたしたちは、父さんは死んでないって思いがちなんだよ、ね。\n";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_3_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_4":
			dialog.text = " 確かに、ああいう男をあの世に送るには、相当な手間がかかっただろうね…";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_4_add":
			StartInstantDialog("Mary", "WildRose_Sesil_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_5":
			dialog.text = "あいつを見た！？話したの！？";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_5_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_6":
			dialog.text = "あたしの娘、あいつが素手でナーワル二人を倒すのを見たんだよ、ほとんど…";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_6_add":
			StartInstantDialog("Mary", "WildRose_Sesil_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_7":
			dialog.text = "ソレノとロハス？";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_7_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_8":
			dialog.text = "あの頃は手一杯でさ、あいつらの名前なんて覚えてる暇なかったんだよね――今じゃ全然思い出せないよ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_8_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_8_add":
			StartInstantDialog("Mary", "WildRose_Sesil_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_9":
			dialog.text = "うん、いいよ。気にしないで、続けて、セシル。";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_9_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_9_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_10", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_10":
			dialog.text = "続けるって、何を？あいつはあの二人を海に放り投げて、石みたいに沈んだんだよ。それから、あいつ自身は縛られて『 タルタロス』に引きずられていったのさ。まあ、それで正解だったんじゃない？あんな人殺し、 他に誰を溺れさせようとしたかわかったもんじゃないし…";
			link.l1 = "人殺し？それはちょっと言い過ぎじゃない、ハラード夫人？今話してるのは、奥さんを亡くしたばかりの男の人、 士官のことだよ…";
			link.l1.go = "WildRose_Sesil_11_1";
			link.l2 = "あんまり彼のことを良く思ってないみたいだね――そんなふうに噂される士官なんて、そうはいないよ。";
			link.l2.go = "WildRose_Sesil_11_2";
		break;

		case "WildRose_Sesil_11_1":
			dialog.text = "「士官さん、いやあ、まあまあ。あの制服はなかなかのもんだったよ、はっきり覚えてる。ほとんど新品みたいだったね。 だけど、あたしも今までにたくさんの士官を見てきたんだよ、坊や。で、どの士官もあの…紳士さんよりずっとまともな振る舞いをしてたよ。」";
			link.l1 = "他に何かしたの？その二人を殺した以外にさ？";
			link.l1.go = "WildRose_Sesil_12";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;

		case "WildRose_Sesil_11_2":
			dialog.text = "「士官さん、いやあ、まあまあ。あいつの制服はなかなかのもんだったよ、今でもはっきり覚えてる。ほとんど新品で、 仕立て屋から出てきたばかりって感じだったね。でもね、あたしもこれまでにたくさんの士官を見てきたんだよ、坊や。 だけど、みんなこの…旦那よりはよっぽどまともな振る舞いをしてたさ。」";
			link.l1 = "他に何かしたの？あの二人を殺した以外にさ？";
			link.l1.go = "WildRose_Sesil_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Sesil_12":
			dialog.text = "彼は自分の独房で神父に会わせろと要求した――デ・ラ・クルス神父に…";
			link.l1 = "へえ、見てよ！それこそ、あたしたちがちょうど話したかったことなんだよ。あの会話の詳しい内容、知ってる？";
			link.l1.go = "WildRose_Sesil_13";
		break;

		case "WildRose_Sesil_13":
			dialog.text = "もちろんだよ、若者！あのプロテスタントのろくでなしが、神父に自分の娘を洗礼させるなって言いやがったんだ――母親はアイルランド人で、つまりカトリックなのによ。";
			link.l1 = "「そんなふうにプロテスタントについて話すイギリス女なんて、ほとんど初めて聞いたよ……えっと、邪魔してごめんね、奥さん。」 "+npchar.lastname+".";
			link.l1.go = "WildRose_Sesil_14";
		break;

		case "WildRose_Sesil_14":
			dialog.text = "あたしも昔はプロテスタントだったんだよ、隠すこともないさ。\nでもジュリアン兄弟があたしを正しい道に導いてくれたんだ。";
			link.l1 = "そういうことか……本当に主に仕える忠実な僕だね。でも、話が逸れちゃった。つまり、 カスパーは自分の娘をプロテスタントの信仰で育ててほしかったんだ。";
			link.l1.go = "WildRose_Sesil_15";
		break;

		case "WildRose_Sesil_15":
			dialog.text = "それがまさに彼がうちのデラクルス神父に言ったことなんだよ。\nそれに、女の子にはジュリアって名付けろって命令したんだ…";
			link.l1 = "「そういうことか、“J.”はその意味だったんだね。メアリー・ジュリア・キャスパー……でも、じゃあ、なんで彼女のことをメアリーって呼んでたの？」";
			link.l1.go = "WildRose_Sesil_16";
		break;

		case "WildRose_Sesil_16":
			dialog.text = "それは彼女の母親が望んだからだよ、だからさ。娘が母親の胎から取り上げられたとき、彼女は名前をささやいた――メアリーってね。俺はその場にいなかったけど、オレリー・ベルティーヌが出産に立ち会っていたんだ。聞きたければ、 彼女に聞いてみな…";
			link.l1 = "じゃあ、あんたはお母さんの願いに従ったんだね。";
			link.l1.go = "WildRose_Sesil_17";
		break;

		case "WildRose_Sesil_17":
			dialog.text = " それも当然だよね、だってダメ親父はまるで煙のように消えちゃったんだからさ？";
			link.l1 = "……デ・ラ・クルス神父の腕前を考えると、たとえ父親がタルタロス号に残っていたとしても、 意見なんて意味なかっただろうね。\nドミンゴは何も言わなかったの？カスパーが脱出して、もしかしたらあの娘を迎えに戻るつもりだったってこと、 知らなかったの？";
			link.l1.go = "WildRose_Sesil_18_1";
			link.l2 = "もしかしたら、あんたの言う通りかもね。\nでも、ドミンゴ神父とカスパーさんの会話に戻るけど――神父は、ジョシュアが脱出について話したとか、娘を迎えに戻る時期について何か言ってた？";
			link.l2.go = "WildRose_Sesil_18_2";
		break;

		case "WildRose_Sesil_18_1":
			dialog.text = " そんなこと、一言も言ってなかったよ。ねえ、考えてみてよ、\n "+npchar.name+"もしあんたが牢屋から逃げ出すつもりだったら、通りすがりの誰彼かまわず言いふらすかい？ あいつは絶対にそんなことしないよ、あたしが保証するよ。";
			link.l1 = "だから、この手がかりも結局は無駄だったね。うん、時間を割いてくれてありがとう、奥さん。 "+npchar.lastname+"。またね。";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", -1);
			AddCharacterExpToSkill(pchar, "charisma", 100);
		break;

		case "WildRose_Sesil_18_2":
			dialog.text = " そんなこと、一言も言ってなかったよ。ねえ、考えてみてよ、\n "+npchar.name+"「もしあんたが牢屋から逃げるつもりだったら、通りすがりの人みんなに言いふらすかい？ あいつは絶対そんなことしないよ、あたしが保証するから。」";
			link.l1 = "つまり、この手がかりは結局行き止まりだったんだね。うん、時間を割いてくれてありがとう、奥さん。 "+npchar.lastname+"。またね。";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;
		
		case "WildRose_Sesil_19":
			StartInstantDialog("Mary", "WildRose_Mary_121", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_121":
			dialog.text = "あたしたち、けっこう面白いことをいくつか見つけたよ、 "+pchar.name+"。でも、あんまり進んでないんだよ、ね。\n";
			link.l1 = "それに、ちょっとした揉め事にもなったんだよ。ねえ、誰なんだろう、 あんたのお母さんが亡くなる前に呼んでたルパートって？\n";
			link.l1.go = "WildRose_Mary_122";
		break;

		case "WildRose_Mary_122":
			dialog.text = "兄弟かも、あるいは…親しい友達とか？";
			link.l1 = "友達、だってさ、うーん……ジョシュアはあいつのこと知ってたのかな……";
			link.l1.go = "WildRose_Mary_123";
		break;

		case "WildRose_Mary_123":
			dialog.text = "「何が言いたいの、 "+pchar.name+"?";
			link.l1 = "ちゃんと考え直さなきゃいけないってことだよ。\nでもね、探し物を手伝ってくれる人を探してる間に、じっくり考える時間はたっぷりあるから、安心して。\nここまで色々やってきたけど、まだ終わりじゃないんだよね。\nあたしたちだけじゃ王立海軍の事務所には入れないし、それにロンドンは海の向こうだし…\nねえ、誰か助けてくれそうな人、心当たりない？";
			link.l1.go = "WildRose_Mary_127";
		break;
		
		case "WildRose_Mary_127":
			dialog.text = "セルジュ・ブノワのことはどうするの、チャールズ？";
			link.l1 = "アボット？まあ、顔は広いけど、正義の島の王立海軍の記録庫に入り込めるとは思えないよ。";
			link.l1.go = "WildRose_Mary_128";
		break;
		
		case "WildRose_Mary_128":
			dialog.text = "もし自分でできないなら、できる誰かを紹介してくれるかも、ね。";
			link.l1 = "そうだね。じゃあ、サン・ピエールに向かうんだね。";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_25");
		break;
		
		// =================================================================
		// =================== ЭТАП 3. «БУМАЖНАЯ РАБОТА» ===================
		// =================================================================
		
		case "WildRose_Mary_131":
			dialog.text = "さて、今はもう待つしかないよ、ね。";
			link.l1 = "きっと彼が全部突き止めてくれるよ、 "+npchar.name+"。時が経つのなんて、あっという間だよ、気づかないくらいさ。\n今は――やることがあるんだから。";
			link.l1.go = "WildRose_Mary_132";
		break;

		case "WildRose_Mary_132":
			dialog.text = "「ねえ、何か特別なことを言いたいの、ダーリン？」";
			link.l1 = "やることは山ほどあるけど、さ、船に戻って、扉をしっかり閉めて、二人きりで過ごさない？どうかな？";
			link.l1.go = "WildRose_Mary_133";
		break;

		case "WildRose_Mary_133":
			dialog.text = "あたし、そう言うと思ってたよ、ね！あたしの意見はこうだよ：時間を無駄にしないで行こう！";
			link.l1 = "おいでよ、あたしのダーリン。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_3");
		break;
		
		case "WildRose_Mary_134":
			dialog.text = "「あっ、」 "+pchar.name+"、あんたには分からないよ、ほんとに分からないくらい、今あたしの心からどれだけ重荷が下りたか、ね！";
			link.l1 = "想像できるよ、ダーリン――あんた、まるで輝いてるみたいだね、はは！見ての通り、全部やった甲斐があったでしょ。";
			link.l1.go = "WildRose_Mary_135";
		break;

		case "WildRose_Mary_135":
			dialog.text = "あたしの父さんは有名な将校だったんだよ、想像できる？でも、会うことができなかったのは本当に残念だよね。しかも、 彼が本土にたどり着けたかどうかも結局わからなかったんだ、ね…";
			link.l1 = "もしそんなことが起きてたら、彼はきっとまた現役に戻ってたはずだし、誰かがどこかで彼の噂を聞いてたはずだよ、ね。 \nああいう男がじっとしていられるわけないじゃない――じゃなきゃ、あんたはどこでその話を聞いたのさ？";
			link.l1.go = "WildRose_Mary_136";
		break;

		case "WildRose_Mary_136":
			dialog.text = "本当に彼が死んだと思うの？キューバでスペイン人の手に落ちたとか、正義の島で殺されたとか、そう思ってるの？";
			link.l1 = "「あたし、現実的に物事を見るようにしてるんだよ、」 "+npchar.name+"あの頃は、まだ正義の島との行き来が少しはあったんだよ。密輸業者たちがよくタルタナ船で通ってたしね。 もし彼が島を出ることに成功してたら、きっとあんたのために必ず戻ってきてくれたはずだよ。\n";
			link.l1.go = "WildRose_Mary_137";
		break;

		case "WildRose_Mary_137":
			dialog.text = "あたしをあそこから連れ出してくれるってこと。でも、そうしたらあたしたち出会えなかったよね、うん。";
			link.l1 = "それが人生だよ、ダーリン。どこで何かを見つけるか、どこで失うかなんて、誰にもわからないんだ。 あたしと一緒にここにいること、後悔してないよね、ね？";
			link.l1.go = "WildRose_Mary_138";
		break;

		case "WildRose_Mary_138":
			dialog.text = "あたしの人生でこんな馬鹿げた話、聞いたことないよ、ね！\n "+pchar.name+"、あんたって最高だよ、素敵だね！あたしのためにこんなに頑張ってくれて、本当にありがとう。すっごく嬉しいんだ、 ね！でも、書類を見てみようよ――もしかしたら、あの人が教えてくれなかった何かが見つかるかも…";
			link.l1 = "いい考えだね。さあ、今すぐ始めよう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_7");
		break;
		
		case "WildRose_Mary_139":
			dialog.text = "「えっと、」 "+pchar.name+"、何か面白いことに気づいた？";
			link.l1 = "「ね、」 "+npchar.name+"…何かがあるんだ…";
			link.l1.go = "WildRose_Mary_140";
		break;

		case "WildRose_Mary_140":
			dialog.text = "幽霊でも見たみたいな顔してるね、うん。";
			link.l1 = "ルパート・ノースウッドという人物について言及している。";
			link.l1.go = "WildRose_Mary_141";
		break;

		case "WildRose_Mary_141":
			dialog.text = "「ルパート・ノースウッド！？本当にあいつなの？」";
			link.l1 = "「静かに」 "+npchar.name+" - そんなに大声出さないでよ。うーん…そうだね、うん――チミセットが話してたのはその人だと思うよ。間違いないって、こんな偶然はありえないもん。";
			link.l1.go = "WildRose_Mary_142";
		break;

		case "WildRose_Mary_142":
			dialog.text = "「で、あんたはこの全部についてどう思うの、」 "+pchar.name+"?";
			link.l1 = "この話、どんどんややこしくなってきたよ。だから……「コーンウォール号」はプリマスから出航して、「コーンウォール号」はアンティグアにも到着した。でも、 正義の島の暗礁で難破したのは「ラングラー号」――しかも、どちらも舵を取っていたのは同じジョシュア・カスパー。 彼はどういうわけか海軍本部に隠れて女と密かに結婚して、その女は死の苦しみの中で「ルパート」 という名の誰かを呼んでいたんだ。";
			link.l1.go = "WildRose_Mary_143";
		break;

		case "WildRose_Mary_143":
			dialog.text = "あたしには何もわからないよ。誰に聞けば何かわかるのかさえ見当もつかないし。 父さんのことを調べようとすればするほど、秘密と謎の沼にどんどん沈んでいくんだ、ね。\n";
			link.l1 = "これについて何か知っている人がいるとしたら、ジョシュア・カスパーかルパート・ノースウッドのどちらかだよ。";
			link.l1.go = "WildRose_Mary_144";
		break;

		case "WildRose_Mary_144":
			dialog.text = "ノースウッド？でも、あいつはもう死んでるんだよ、ね。\n「コーンウォール」がセント・ジョンズに到着したときに提出された報告書が偽造だったなんて、本気で思ってるの？";
			link.l1 = "「あんたのその純真さ、」 "+npchar.name+"…あたし、だんだんこの話全部が嘘まみれなんじゃないかって思い始めてるよ。考えてみてよ、 ジョシュア・カスパーは模範的な士官で、勲章もたくさんもらってて、一度も叱責されたことがないんだって。だけど、 それって正義の島であたしたちが知った彼の姿とは全然合わないじゃない？あそこで彼は、 二人の男を何のためらいもなく墓に送ったんだよ、そう思わない？";
			link.l1.go = "WildRose_Mary_145";
		break;

		case "WildRose_Mary_145":
			dialog.text = "「彼は自分の妻であり、あたしの母の命のために戦ったんだ」 "+pchar.name+"!";
			link.l1 = "もちろんだけど、じゃあ彼女はいったいどこから来たの？それに、もっと大事なのは、なぜ彼は結婚を提督府に隠したの？ 筋金入りの職業軍人で、規則や任務に忠実じゃなきゃ、あんなに経歴がきれいなはずないのに、 急にこんなことをしでかすなんて。";
			link.l1.go = "WildRose_Mary_146";
		break;

		case "WildRose_Mary_146":
			dialog.text = "もしかしたら、その裏には美しくてロマンチックな物語が隠れてるかもしれないでしょ？たまには、 そういうこともあるんだよ、うん。\n";
			link.l1 = "誤解しないでくれ、メアリー。でも、これは全然恋愛物語には聞こえないよ。どちらかと言えば、何かの芝居みたいだし、 俺はいまだに何のためだったのか分からないんだ。なぜプロビデンスへ向かう途中で船の名前を変えたんだ？ あれは軍艦だぞ、そんな真似をしたら軍法会議にかけられるかもしれないんだぞ。\n";
			link.l1.go = "WildRose_Mary_147";
		break;

		case "WildRose_Mary_147":
			dialog.text = "うん、いい質問だね。";
			link.l1 = "それに、このルパート・ノースウッド、どう考えても怪しいんだよ。あの戦いで乗組員の半分近くが死んだのに、 なぜか士官で生き残ったのは彼だけだったんだ。\nそれに、テレサが死ぬ間際に呼んだのはルパートで、夫のジョシュアじゃなかったのはどうして？";
			link.l1.go = "WildRose_Mary_148";
		break;

		case "WildRose_Mary_148":
			dialog.text = "じゃあ、本当に副長はスペイン人と戦って死んだわけじゃないってことなんだね？\nそれに、あたしはジョシュア・カスパーの娘じゃなくて、ルパート・ノースウッドの娘だったってこと、 そう言いたいんでしょ？";
			link.l1 = "前にも言ったけど――真実を知っているのはたった一人だけ。理由はわからないけどテレサを妻と呼んだジョシュア・カスパーか、 それとも同じく不可解な理由で自分の船長の名を名乗ったルパート・ノースウッドか、どちらかだよ。";
			link.l1.go = "WildRose_Mary_149";
		break;

		case "WildRose_Mary_149":
			dialog.text = "なんてひどい有様だよ、ね！それで、これからどうするの？ "+pchar.name+"？あたし、ますます真実を知りたくなっちゃったけど、でももうみんなから聞き出せることは全部聞き出しちゃったよね。 ";
			link.l1 = "もし答えがどこかにあるとしたら、それは正義の島だよ――この海のこちら側で、君の両親を少しでも知っていた人は、もう他に誰も残ってないからね。\nもう一度オレリー・ベルティーヌに話を聞いてみるべきだと思うんだ。あたしたちが見落としていた何かを、 彼女が思い出してくれるかもしれないよ。";
			link.l1.go = "WildRose_Mary_150";
		break;

		case "WildRose_Mary_150":
			dialog.text = "でも、あたしに何を聞きたいの？もう彼女が知ってることは全部話してくれたみたいだよ。";
			link.l1 = "彼女はあたしたちが聞いたことを話してくれたけど、大事なことを見落としてたかもしれないよ。あんたの父さん、 顔に傷があったとか、指が一本なかったとか……そういうのもあるかも。船の名前を変えたり、自分の名前まで変えたり、あんな手の込んだことを考えつく人が、 どこかの島やカスティリアの牢獄でみじめに死ぬなんて、あたしは思えないな。";
			link.l1.go = "WildRose_Mary_151";
		break;

		case "WildRose_Mary_151":
			dialog.text = "もしかしたら、あんたの言う通りかもね……";
			link.l1 = "もし私たちが探し続けると決めたなら――提督府の埃をかぶった棚じゃなくて、この諸島でだよ――必要なのは名前だけじゃないし、それも偽名なんかじゃ足りないんだよ。";
			link.l1.go = "WildRose_Mary_152";
		break;

		case "WildRose_Mary_152":
			dialog.text = "ねえ、こういうの、あたし鳥肌立っちゃうんだよ、うん。全部が…すごくドキドキするからかもしれないし、もしかしたら、 あたしの父さんもビショップのプランテーションのあのクソ野郎とそんなに変わらなかったんじゃないかって思うからかも しれない。";
			link.l1 = "どっちにしても、あたしたちができる限りのことをして、絶対に真相を突き止めるって約束するよ。\nだから、時間を無駄にしないで行こう！\nさあ、行くよ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_9");
		break;
		
		// =================================================================
		// ==================== ЭТАП 4. «ПУТЬ К СВЕТУ» =====================
		// =================================================================
		case "WildRose_Mary_161":
			dialog.text = "行こう、 "+pchar.name+"もうこれ以上時間を無駄にしないでおこう、ね。";
			link.l1 = "オレリーが自分の船室にいてくれるといいんだけど、あたしたちが正義の島中を探し回る羽目にならなきゃいいけどね…";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_2");
		break;
		
		case "WildRose_Mary_162":
			dialog.text = "また運がないみたいだね、うん。今度は彼女、どこに行っちゃったんだろう？";
			link.l1 = "またあの病が彼女の心を蝕んでいなければいいんだけど…";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_4");
		break;
		
		case "WildRose_Jillian_31":
			dialog.text = "あら、また来たのね。うん、こんにちは……どうしたの、またオレリーが必要なの？";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_31_add";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_31_add":
			StartInstantDialog("Mary", "WildRose_Jillian_32", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_32":
			dialog.text = "頭の回転が速いのは否定できないね、ジリアン。で、彼女がどこにいるか知ってたりしない？";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_32_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_32_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_33", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_33":
			dialog.text = "教会で、彼女はちょうど告白しようとしていたんだ。\n急げば、まだそこにいるはずだよ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_33_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_33_add":
			StartInstantDialog("Mary", "WildRose_Jillian_34", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_34":
			dialog.text = "まあ、もし彼女が自白してるんなら、正気で記憶もはっきりしてるってことだよ、ね。";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_34_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_35", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_35":
			dialog.text = "何とも言えないな……ここ三日間、彼女はまるで別人で、落ち着きがないんだよ。\nあのさ、どういうわけか、外輪の向こうにお前の船のマストを見た時、ひどく動揺してたんだ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_35_add":
			StartInstantDialog("Mary", "WildRose_Jillian_36", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_36":
			dialog.text = "どうしてそんなことになったんだろうね？";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_36_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_37":
			dialog.text = "そうだね、あんたにまた問い詰められることを考えると、彼女も落ち着かないんだろうさ。\nでも、あんたが他人の悩みなんて気にしたこと、今まであったかい？";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_37_add":
			StartInstantDialog("Mary", "WildRose_Jillian_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_38":
			dialog.text = "あたしにそんな口きかないでよ、ジリアン。今回は許してあげるけど、もう一度そんなこと言ってみなさい…";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_5");
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "WildRose_Jillian_41":
			dialog.text = "気分屋な女だよね、ちょっとでも気に入らないことがあるとすぐピリピリしちゃうんだから、そうじゃない？";
			link.l1 = "理由もなく彼女を怒らせないほうがいいよ。 "+npchar.name+"。あの子があの剣を飾りで身につけてるわけじゃないって、わかってるでしょ。";
			link.l1.go = "WildRose_Jillian_42";
		break;
		
		case "WildRose_Jillian_42":
			dialog.text = "「そして、あんたはそれを許したんだ、」 "+pchar.name+"?";
			link.l1 = "あんたはまだ戦いの中のメアリーを見たことがないだけだよ、 "+npchar.name+"。じゃなきゃ、あの子を止められるものなんて、この世に何もないって思い知るはずだよ。じゃあ、またね。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_7");
		break;
		
		case "WildRose_Mary_163":
			dialog.text = "「何かあたしに聞きたいことがあるんでしょ、」 "+pchar.name+"……うん、ね……";
			link.l1 = "正直言って、あたしはあなたたち二人の間に何があったかなんて、あんまり気にしてないよ。まあ、 誰か特定の人が原因だったんじゃないかって、だいたい想像はつくけどね。で、本当にその話をしたいの？";
			link.l1.go = "WildRose_Mary_164_1";
			link.l2 = "あんたとジリアン、何かで喧嘩でもしたの？それとも、誰かのことで揉めたって言うべきかな？";
			link.l2.go = "WildRose_Mary_164_2";
		break;

		case "WildRose_Mary_164_1":
			dialog.text = "うーん、そうでもないよ、うん。";
			link.l1 = "あんたがそう言うなら、いいよ。さて、オレリーを探しに行こう。";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Mary_164_2":
			dialog.text = "あの小さなヒル女は、アランがあたしを選んだことを絶対に許さないだろうね。まあ、彼はもういないんだから、 許してもよさそうなもんだけど……正直言って、\n "+pchar.name+"…その話はしたくないんだよ、ね。";
			link.l1 = "あんたの言う通りだよ、ダーリン。じゃあ、オレリーを探しに行こう。";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Mary_165":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_9");
		break;
		
		case "WildRose_Oreli_61":
			dialog.text = ""+pchar.name+"「メアリー！戻ってきたんだね、正義の島に。なんて嬉しいんだ！」";
			link.l1 = "「元気そうでよかったよ、」 "+npchar.name+"……あのね、実はまたあんたと話したくて正義の島に来たんだよ。\nでも心配しないで、すぐ終わるからさ。";
			link.l1.go = "WildRose_Oreli_62";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Oreli_62":
			dialog.text = "おやおや、若い者たちよ、本当に年寄りに容赦がないね。でも、あんたたちが来る気がしてたよ。今回もまた、 あんたの両親のことだろう、メアリー？\n";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_62_add";
		break;

		case "WildRose_Oreli_62_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_63", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_63":
			dialog.text = "お願い、オレリー。長い時間が経って思い出すのは辛いってわかってるけど、 もう一度だけあたしのために思い出してみてよ、ね。";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_63_add";
		break;

		case "WildRose_Oreli_63_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_64", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_64":
			dialog.text = "あたしが覚えてることは、もう全部話したよ。これ以上あたしから何を絞り出したいのか、全然わかんないんだけど。";
			link.l1 = "「ちょっと聞きたいことがあるんだよ、」 "+npchar.name+"……お願い、何か思い出してみて――どんな細かいことでも、何でもいいの。無理に聞き出したりはしないから……";
			link.l1.go = "WildRose_Oreli_65";
		break;

		case "WildRose_Oreli_65":
			dialog.text = "それって、まさに今あんたがやってることじゃない？";
			link.l1 = "「もうあたしたちのために、たくさんしてくれたじゃない」 "+npchar.name+"…あたしらは、あんたの記憶の迷宮のどこかに、まだ何か――あたしたちの大きな助けになるものが残ってるんじゃないかって、そう願ってるんだよ。";
			link.l1.go = "WildRose_Oreli_66_1";
			link.l2 = "「ここまで長い道のりを歩んできたね、」 "+npchar.name+"。あんたには想像もつかないくらい、あたしたちがどれだけ努力して、どれだけ時間をかけたか……でも、あたしたちは道に迷っちゃったんだよ。今は、あんたとあんたの記憶だけが、 あたしたちを真実の道へ導いてくれるんだ。";
			link.l2.go = "WildRose_Oreli_66_2";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;

		case "WildRose_Oreli_66_1":
			dialog.text = "思い出……本当に残っているのは何だろうね。朝によっては自分の名前さえ思い出せないこともあるんだよ、 なのに二十年前の出来事の詳細を聞きたいってわけか。まあ、いいよ、聞きたいならどうぞ。";
			link.l1 = "俺たちはメアリーの父親、キャスパー氏について知りたいんだ。\n彼の外見で何か特徴的なことを覚えてないか？顔に傷があったとか、足を引きずって歩いていたとか……";
			link.l1.go = "WildRose_Oreli_67";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "WildRose_Oreli_66_2":
			dialog.text = "思い出か……残ってるのは、ほんのわずかだよ。朝なんか、便所の場所すら思い出せないこともあるのに、 あんたは二十年前にこの沈没船で何があったか、詳しく聞きたいってわけだね。まあ、いいさ、 聞きたいことがあるならどうぞ。";
			link.l1 = "あたしたちはメアリーの父親、キャスパー氏について知りたいんだよ。\n彼の見た目で何か特徴を覚えてない？顔に傷があったとか、足を引きずって歩いてたとかさ…";
			link.l1.go = "WildRose_Oreli_67";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Oreli_67":
			dialog.text = "ああ…もう言ったと思うけど、あたしが彼を見たのは真っ暗な『セレス・スミッティ』号の船倉、 可哀想なテレサのために寝床を作ってた場所だけなんだよ。彼は絶対に足を引きずってなかった――むしろ、かなり身軽な男だったよ。";
			link.l1 = "「それで、彼の年齢は？若かったのか、それとももう年を取っていたのか？」";
			link.l1.go = "WildRose_Oreli_68";
		break;

		case "WildRose_Oreli_68":
			dialog.text = "あたし、彼のことを「おじさん」なんて呼ばないよ、うん…でも、正直あんまり気にしてなかったんだ――テレサのことの方が心配だったからさ。彼はかなりやつれてて、まるで幽霊みたいだったよ。でもね、 覚えておいてほしいんだけど、奥さんが出産間近で、彼は一週間ほとんど寝てなかったんだ…正義の島中を走り回って、全然休まなかったんだよ。";
			link.l1 = "そうか、彼は奥さんのことをとても愛していたんだね。あんたは彼女とよく一緒に過ごしてたんでしょ？ 彼女が旦那さんのことを話したことはある？";
			link.l1.go = "WildRose_Oreli_69";
		break;

		case "WildRose_Oreli_69":
			dialog.text = "テレーザは彼のことを何度も聞いてたんだ。たくさん眠って、時にはうわごとを言ってたけど、 正気に戻るたびに最初にするのは彼がどこにいるかを尋ねることだった。かわいそうに、彼のことを本当に、 本当に待ってたんだよ。でも一番大事な時に――彼は結局来なかったんだ。";
			link.l1 = "なるほど。二人の愛は明らかに両想いだったんだね……うん、ありがとう、オレリー。あなたには本当に助けられたよ。";
			link.l1.go = "WildRose_Oreli_70";
		break;

		case "WildRose_Oreli_70":
			dialog.text = "「それで終わり？あたし、少なくとも一時間か二時間くらいは話すと思ってたよ。」";
			link.l1 = "長くお邪魔しないと約束したよね。自分のこと、大事にしてね、 "+npchar.name+"。じゃあ、元気でね。";
			link.l1.go = "WildRose_Oreli_71";
		break;

		case "WildRose_Oreli_71":
			dialog.text = "待ちなさい、若者たち！まだ渡したいものがあるんだ……いや、正確には、メアリー、君にだよ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_a";
			NPCsLookEachOther("LSC_Oreli", "Mary");
		break;
		
		case "WildRose_Oreli_72_a": //
			dialog.text = "はい、ほら、お嬢ちゃん、これを受け取って……あんたの船の帆が見えた瞬間、この帽子を持ってきたんだ、忘れないようにね。でも、桟橋まで歩いていくのは……どうしてもできなかったんだよ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_add";
		break;

		case "WildRose_Oreli_72_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_73", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_73":
			dialog.text = "どうしたの、オレリー？帽子……？";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_73_add";
		break;

		case "WildRose_Oreli_73_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_74", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_74":
			dialog.text = "お母さんの帽子、テレーザのだよ。難破船の生存者たちが『セレス鍛冶屋』に連れてこられたとき、彼女が持ってたんだ。 テレーザが亡くなったとき、あたしがベッドのそばの床からその帽子を拾ったんだよ、うん、 それでそのまま忘れちゃってさ……今日、あんたと話しててやっと思い出したんだ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_74_add";
		break;

		case "WildRose_Oreli_74_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_75", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_75":
			dialog.text = "オレリー…ずっと大事にしてくれてたんだね！それに…それに捨てたり、売ったりもしなかった…ありがとう、ほんとにありがとう！あたしにとってどれだけ大切か、わかんないでしょ、ね！";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_75_add";
		break;

		case "WildRose_Oreli_75_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_76", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_76":
			dialog.text = "ごめんな、メアリー――ずっと前に渡しておくべきだったのに……でも最近のあたしの記憶なんて、古いザルみたいなもんでさ――だから……";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_76_add";
		break;

		case "WildRose_Oreli_76_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_77", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_77":
			dialog.text = "これ以上のタイミングはないよ、オレリー！今すぐ試してみるね、うん！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_hat_1");
		break;
		
		case "WildRose_Mary_166":
			dialog.text = "ねえ、あなた、あたしのこと、どう思う？..";
			link.l1 = "あんた、きれいだよ。あと、その帽子も…まだ流行遅れじゃないし、すごく似合ってるよ。";
			link.l1.go = "WildRose_Mary_167";
		break;
		
		case "WildRose_Mary_167":
			dialog.text = "本当に？気に入ってくれて、あたしすごく嬉しいよ！";
			link.l1 = "他の方法なんてあるわけないでしょ？";
			link.l1.go = "WildRose_Mary_167_add";
		break;
		
		case "WildRose_Mary_167_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Mary_168", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;
		
		case "WildRose_Mary_168":
			dialog.text = "...";
			link.l1 = "もう一度ありがとう、オレリー。今日はちょっとだけ明るくなったよ！じゃあ、元気でね。ゆっくり休んで。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_10");
		break;
		
		case "WildRose_Mary_171":
			dialog.text = "やっぱりルパートだったんだ。ルパート・ノースウッド、ね。";
			link.l1 = "もちろん、そうだよ、ダーリン。彼は奥さん…それか恋人を救うためにできる限りのことをしたんだ、うん、あたしにはどっちか分からないけどさ。正直、 そこはあんまり重要じゃないよ。大事なのは、今あたしたちが誰を探してるのか分かったってことだよね。\n";
			link.l1.go = "WildRose_Mary_172";
		break;

		case "WildRose_Mary_172":
			dialog.text = "「でも、本物のジョシュア・カスパー、『コーンウォール』号の船長はどうなったの？」";
			link.l1 = "いい質問だけど、今はそれが一番大事じゃないよ。さて、どうしてルパートはあんなにテレサのことを愛してたのに、 迎えに戻ってこなかったのか――そっちの方がずっと気になるよね。まず最初に彼にそれを聞くんだ。もしまだ生きてて、見つけられたらだけど。 ひとつだけ確かなのは――彼は艦隊には戻らなかったってこと。そんな危険を冒す理由がなかったんだよ。";
			link.l1.go = "WildRose_Mary_174";
		break;

		case "WildRose_Mary_174":
			dialog.text = "彼がなぜジョシュア・カスパーという名前を名乗ったのか、何があったんだろう。\n「コーンウォール」号が「ラングラー」号になった時、船の上で何が起きたの？\nあたしの父さん、本当に犯罪者だったのかな、 "+pchar.name+"?";
			link.l1 = "「その可能性も否定できないんだよね、」 "+npchar.name+"……何が起きても、絶対に備えておかないとね。";
			link.l1.go = "WildRose_Mary_175";
		break;

		case "WildRose_Mary_175":
			dialog.text = "そんなこと、考えたくもないよ……";
			link.l1 = "今は別のことを考えないと――どこで彼を探すべきかだよ。海賊や密輸団に加わったかもしれないし、どこかの町に落ち着いて、身を潜めてるのかも。 何だってあり得るよ。\n";
			link.l1.go = "WildRose_Mary_176";
		break;
		
		case "WildRose_Mary_176":
			dialog.text = "それで、どうしろって言うの？どうやって彼を見つければいいの？\n全部の植民地に行って、彼の名前を言って、誰かがルパート・ノースウッドを知ってることを願えばいいの？";
			link.l1 = "あるいはジョシュア・カスパー。彼は元の船長の身分を使って生き続けていた可能性も十分ある——その船長はおそらく死んでいるだろうけどね。\nだが、それにはいくつかのリスクがあった。なぜなら、行方不明のブリッグを探し始める者が現れるかもしれないからだ。 \n特に、プロビデンス駐屯地向けの銀の積まれた箱が船に積まれていたことを考えれば、なおさらだよ。";
			link.l1.go = "WildRose_Mary_177";
		break;

		case "WildRose_Mary_177":
			dialog.text = "あんたの言う通りだよ、うん。";
			link.l1 = "それでも、アゾレス付近で消息を絶ったとされるルパート・ノースウッドなんて、誰にも興味を持たれないはずだよ。\nでもさ、ここには確かに考える価値のある何かがあるんだよね。";
			link.l1.go = "WildRose_Mary_178";
		break;

		case "WildRose_Mary_178":
			dialog.text = "「これにあとどれだけ時間をかけなきゃいけないんだ、」 "+pchar.name+"！？どこにでもいるかもしれない、どの植民地にもね！";
			link.l1 = "もし生き延びていれば、だけどね。あたしはそうは思わないよ。スペイン語が流暢だったとは考えにくいから、 キューバやイスパニョーラは除外だね。フランス語が少しできたなら、 トルトゥーガか小アンティル諸島のどこかに行ったかもしれないし、 あるいは西インドの本土でイギリス人仲間の庇護下にいた可能性もある。何ヶ月も彼を探し回っても、 結局手がかりがつかめないかもしれないよ。";
			link.l1.go = "WildRose_Mary_179";
		break;

		case "WildRose_Mary_179":
			dialog.text = "「でも、あたしは諦めたくないんだよ、」 "+pchar.name+"……でも、今じゃないよ、もうこんなに色々分かったんだから、ね！";
			link.l1 = "あきらめようって言ってるわけじゃないよ、 "+npchar.name+"。でも、あたしたちが自分で探す必要はないよ、ね？ちゃんとしたコネを持ってる人に頼めばいいんだよ。 一度うまくいったんだから、もう一回やってみてもいいでしょ？\n";
			link.l1.go = "WildRose_Mary_180";
		break;

		case "WildRose_Mary_180":
			dialog.text = "また院長に助けを求めろって言うの？この件については、もうこれ以上頼るなってはっきり言われたと思ったんだけど、 ね。";
			link.l1 = "それはちょっと親父に対して図々しすぎるよ、あんたの言うとおりだね。";
			link.l1.go = "WildRose_Mary_181";
		break;

		case "WildRose_Mary_181":
			dialog.text = "「でも、じゃあ、誰に頼ればいいの？こういうことに必要なお金とコネを持ってるのは誰なの？」";
			link.l1 = "うーん、これは間違いなく自分たちで捜索の資金を出さなきゃいけないね。\nコネについては……そうだな、ファディ・モスコヴィットなら力になってくれるかも。 あの人なら植民地を回れる腕の立つ人を知ってるはずだし、あるいは誰か紹介してくれるかもしれないよ。";
			link.l1.go = "WildRose_Mary_182";
		break;

		case "WildRose_Mary_182":
			dialog.text = "それで、バステールに向かうんだよね？";
			link.l1 = "うん、友達に会いに行こうよ。あたしが思うに、彼にはそんなに難しい仕事じゃないでしょ。";
			link.l1.go = "WildRose_Mary_183";
		break;

		case "WildRose_Mary_183":
			dialog.text = "明日出航しようよ、どう思う？今日は残りの時間と夜を、あたしたち二人きりで『セレス・スミッティ』 で過ごしたいんだ。";
			link.l1 = "そんな申し出、誰も断らないよ、ダーリン。あたしたち、間違いなくちょっと休む権利あるよね。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_12");
		break;
		
		case "WildRose_Jillian_51":
			dialog.text = "えっ、もう正義の島を出るの？葬式にも残らないのかい？\n";
			link.l1 = "葬式？…";
			link.l1.go = "WildRose_Jillian_52";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_52":
			dialog.text = "あら、まだ聞いてなかったのね。そうか……オレリー・ベルティーヌが昨夜亡くなったのよ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_52_add";
		break;

		case "WildRose_Jillian_52_add":
			StartInstantDialog("Mary", "WildRose_Jillian_53", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_53":
			dialog.text = "「えっ！？そんなはずないよ、昨日あたしたち、彼女とちゃんと話したばかりだったし、全然元気だったじゃない。 まさか誰かが……」";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_53_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_53_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_54", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_54":
			dialog.text = "いいえ、メアリー。オレリーは眠っている間に亡くなったんだ。今日、 彼女の関節用にジュリアン修道士が作った軟膏を持って行ったんだけど――その時に彼女を見つけたんだよ。ベッドに横たわって、不思議な微笑みを浮かべていた。でも、 すでに顔色は青白くて冷たかった。\nこの一週間、あの老婆はいつもと違っていた。黒い魔術師が追い払った病が戻ってきたのかと思ったくらいだ。 でも意識ははっきりしていたし、うわごとを言っている様子もなかったよ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_54_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_54_add":
			StartInstantDialog("Mary", "WildRose_Jillian_55", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_55":
			dialog.text = "少なくとも、あの子は苦しまなかったんだよ、ね。";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_55_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_55_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_56", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_56":
			dialog.text = "それで、葬式に残るつもり？明日、いちばん遠い礁でやるんだよ――あそこは十分に深いし、カニもあんまり来ないからね。\n";
			link.l1 = "私たちは残るよ、ジリアン。オレリーはメアリーのためにたくさんしてくれたんだ、他に選択肢はないよ。 誰も異論がなければ、式は私たちの船で行おう。彼女を海に葬って、きちんとした敬意を払うんだ。";
			link.l1.go = "WildRose_Jillian_57";
		break;
		
		case "WildRose_Jillian_57":
			dialog.text = "誰も文句は言わないよ。だって、その方が便利だし、結局のところ、残骸を乗り越えるより安全だからね。\n";
			link.l1 = "それじゃあ、葬儀の手配を頼むよ――メアリーが手伝ってくれるから。あたしはちょっと話したい相手がいるんだ……\n";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_14");
		break;
		
		case "WildRose_Chimiset_61":
			dialog.text = "そしてまた来てくれたんだね、あたしの大切な友達！今回は何をしてあげようか？";
			link.l1 = "「こんにちは。」 "+npchar.name+"……ねえ、昨夜何があったか聞いた？";
			link.l1.go = "WildRose_Chimiset_62";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_62":
			dialog.text = "オレリーの死のことを話してるの？うん、そうみたいだね。もちろん聞いたよ。彼女は『プルート』に住んでたし、 そこはほとんどリヴァドスの縄張りだもん。ほかの船の人たちも、その話しかしてないよ。\n";
			link.l1 = "俺たちはつい昨日も彼女を見かけたんだ、元気そうだったよ――まあ、もちろん、この一週間ずっと何かに不安そうだったけどな。\nそれに、俺たちの船を見つけたときは、さらに動揺してたぜ。";
			link.l1.go = "WildRose_Chimiset_63";
		break;

		case "WildRose_Chimiset_63":
			dialog.text = "人は、自分の人生という川が枯れかけているとき、それを感じるものだよ。\nそれを周りに見せる人もいれば、心の奥に隠す人もいる。でも、誰もが何らかの形でそれを感じ取るんだ――特に、自分の心の声に耳を傾けることができる人はね。";
			link.l1 = "あたしには、彼女は元気そうに見えたよ、まるで若い雌鹿みたいにね、\n "+npchar.name+"……それに、ここにはどうも腑に落ちないことがあるんだよね……";
			link.l1.go = "WildRose_Chimiset_64_1";
			link.l2 = "それでも、彼女は明らかにまだ限界ではなかったんだよ、 "+npchar.name+".";
			link.l2.go = "WildRose_Chimiset_64_2";
		break;

		case "WildRose_Chimiset_64_1":
			dialog.text = "友よ、心と体はまったく異なる次元のものだよ。\n心は体を支配するが、時には体が心を支配しようとすることもある。\n両者は密接に結びついているが、決して同じものではないんだ。\n人は外見上はまったく健康そうに見えても、その魂はすでに死への道を歩んでいることもあるんだよ。";
			link.l1 = "あんた、頭が切れるね、友よ、ほんとに賢いよ。真実が近くにあると感じたら、 あんたはライオンがシマウマを追いかけるみたいに、それを追いかけるんだろうね――そして捕まえるまで絶対に止まらない。あたし、それ、会った瞬間にすぐわかったよ。";
			link.l1.go = "WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Chimiset_64_2":
			dialog.text = "旦那、心と体はまったく別の次元のものだよ。心が体を支配することもあれば、 時には体が心を支配しようとすることもある。二つは密接に繋がっているけど、本当の意味で一つじゃないんだ。 外見はどこも悪くなさそうに見えても、魂はすでに死の道を歩んでいることだってあるんだよ。\n";
			link.l1 = "ねえ、思ったんだけど、オレリーはまるで私たちが来るのを待っていたみたいだったよ。あたしたちが来るって、 分かってたみたいにさ。あの老婆は一日早くても遅くても死ねたはずなのに、 メアリーのお父さんについて大事なことを話してくれた直後に、ほとんどすぐ亡くなったんだよね。\n"link.l1.go ="WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Chimiset_65":
			dialog.text = "あんた、頭いいね、友達。ほんとに賢いよ。もし真実が近くにあるって感じたら、 あんたはライオンがシマウマを追いかけるみたいに、それを追いかけるんだろうね――そして捕まえるまで絶対に止まらない。あたし、あんたを初めて見た瞬間にそれがわかったんだよ。";
			link.l1 = "あたしは……いや、ちょっと待って。「プロテクター」の船倉でやったあの儀式……あれ、オレリーの病気を遅らせる効果なんてなかったんでしょ？じゃあ、あんたは一体何をしたの？\n";
			link.l1.go = "WildRose_Chimiset_66";
		break;

		case "WildRose_Chimiset_66":
			dialog.text = "石をいくら積んでも、川の流れは止まらない。あんたがオレリーから大事なものを必要としているって、 あたしには分かってた――でも、それをすぐに手に入れられるわけじゃないこともね。だけど、あんたの旅がどれだけ長くなるかは分からなかった。 だから、あたしは堰を作ったんだ、彼女の命の力をすべて使って、病を押しとどめておいた。 彼女が役目を果たしたその瞬間、障壁は崩れ落ちたんだよ……\n";
			link.l1 = " じゃあ、オレリー……彼女が死ぬ瞬間、あの人は全然自分じゃなかったんだね、 あたしたちが思ってたみたいに何もわかってなかったわけじゃないんだ？\n ";
			link.l1.go = "WildRose_Chimiset_67";
		break;

		case "WildRose_Chimiset_67":
			dialog.text = "彼女は心を澄ませ、記憶を保つためだけに全ての力を使い果たしたんだ。\nそして、もはやその必要がなくなったとき、病は大波のように彼女を襲い、死の谷へと連れて行った。\n彼女の最期が穏やかだったのか、それとも過去の亡霊や恐ろしい悪夢に苦しみながらお前の神のもとへ旅立ったのか――それは分からない、あたしには知る由もないよ。";
			link.l1 = "あんた、これがどうなるかちゃんと分かってたんでしょ、ね？どうして結果について教えてくれなかったのよ！？さあ、 答えてよ！";
			link.l1.go = "WildRose_Chimiset_68_1";
			link.l2 = "あんた、自分が何をしていたか、ちゃんと分かってたんだよね。 "+npchar.name+"……どうして、これがどうなるか、あたしに教えてくれなかったの？";
			link.l2.go = "WildRose_Chimiset_68_2";
		break;

		case "WildRose_Chimiset_68_1":
			dialog.text = "あんたを助けることに決めたのは、友よ、あんたが知るべきことを知ってもらうため、 そして彼女が自分の運命を全うできるようにするためだったんだ。もし彼女に何が待っているかをあんたに話していたら、 あんたは最後までやり遂げなかったかもしれない――そうなれば、オレリーは自分の秘密を墓場まで持っていっただろう。それで何の意味がある？ 彼女は何のためにもならずに死んでしまったはずだ。まるでライオンに倒されたのに食べられず、 ハゲタカに放置されるカモシカのようにな。\n";
			link.l1 = "目的とか、有用性とか……あんた、運命を操る達人だね、 "+npchar.name+"。人の姿をした神様。";
			link.l1.go = "WildRose_Chimiset_69";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_68_2":
			dialog.text = "あたしが助けるって決めたのはね、友達のあんたのために必要なことを知ってもらうため、 そして彼女が自分の運命を全うできるようにするためだったんだよ。もし彼女に何が待ってるかをあんたに話してたら、 きっとあんたはやり遂げなかっただろうし――オレリーは自分の秘密を墓まで持っていったはずさ。それじゃ何の意味もないでしょ？彼女は無駄死にするだけだった。 まるでライオンに倒されたのに食べられもせず、ハゲタカに見捨てられたカモシカみたいにさ。";
			link.l1 = "目的とか、有用性とか……あんた、運命を操る達人なんだね、あたしから見れば。 "+npchar.name+"。人の姿をした神様。";
			link.l1.go = "WildRose_Chimiset_69";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Chimiset_69":
			dialog.text = "あんたの声に不満の色が感じられるよ、友よ。\nでもね、あたしは自分を神様だなんて全然思ってないよ――それに信じてほしい、神様だって万能じゃないんだ。\nあんたが信じてる神様も、あたしたちが崇めてる神様たちもね。\n神様は、生まれつき与えられた以上の力を人に授けることはできないんだよ。\nシャーマンであるあたしたちにできるのは、その力をどっちかの方向に導いてやること――それだけさ。";
			link.l1 = "「そしてあんたは、彼女を死へと導く航路に乗せたんだね……」";
			link.l1.go = "WildRose_Chimiset_70";
		break;

		case "WildRose_Chimiset_70":
			dialog.text = "俺はただオレリーに道を示しただけで、その道を進んだことで彼女はメアリーを助けたんだ——メアリーが生まれた日からずっと深く繋がっていた相手をな。結局のところ、 お前の仲間はオレリーの目の前でこの世に生を受けたんだから。どうか、俺が正気を失ったみたいな目で見ないでくれ。 まさか、俺のことを手ひとつで時の流れを逆戻しできる親切な魔法使いに見えた、なんて言わないだろう？\n";
			link.l1 = "「あんたに何て言えばいいのか、わかんないよ、」 "+npchar.name+"……もしかしたら、本当に全部が無駄じゃなかったのかも。でも、こんな形で終わるべきじゃなかった。 あんたがあたしに話すべきだったし、あたしが自分で選ぶべきだったんだよ。それでも、もう終わったことだしね。 じゃあ、さよなら、友よ。";
			link.l1.go = "WildRose_Chimiset_71";
		break;

		case "WildRose_Chimiset_71":
			dialog.text = "ああ、こんなふうに最後の別れになるなんて、あたしは思ってなかったよ、友達…";
			link.l1 = "なんで彼女が最後の一人だと思うの？";
			link.l1.go = "WildRose_Chimiset_72";
		break;

		case "WildRose_Chimiset_72":
			dialog.text = "ある川は他の川に流れ込み、その一部となり、また別の川は干上がってしまう。そして、私たちの川のように――壮大な滝でその終わりを迎えるものもあるんだ…";
			link.l1 = "また謎かい、チミセット？今日はもう十分だよ。きっとまた会うでしょ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_15");
		break;
		
		case "WildRose_Mary_191":
			dialog.text = "ここにいると思ったよ、ね。チミセットに何の用だったの？ "+pchar.name+"？彼はあんたに何を話したの？";
			link.l1 = "あたしが期待してた…いや、聞きたかったこととはちょっと違うけどさ。けど、なんとなくそんな気がしてたんだよね。";
			link.l1.go = "WildRose_Mary_192";
		break;

		case "WildRose_Mary_192":
			dialog.text = "あたしに話してくれるよね？";
			link.l1 = "いや、 "+npchar.name+"……今回は違うよ。護衛官の船室で話したことは全部、あたしとチミセットの間だけの秘密だよ。";
			link.l1.go = "WildRose_Mary_193";
		break;

		case "WildRose_Mary_193":
			dialog.text = "「そんな決意のこもった声を聞くのは久しぶりだよ、」 "+pchar.name+"。でもね、他にも心配しなきゃいけないことがあるんだよ。葬式は明日、日没の七時に行われるからね。";
			link.l1 = "さあ、あたしが手伝って全部準備しようよ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_17");
		break;
		
		case "WildRose_Mary_201":
			dialog.text = "来たがってた人はみんな揃ったみたいだね、うん。";
			link.l1 = "もっと人がいると思ってたよ。せめて、もう少し穏やかな人たちがいるかと思ったんだ。";
			link.l1.go = "WildRose_Mary_202";
			CharacterTurnToLoc(npchar, "quest", "quest1");
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;

		case "WildRose_Mary_202":
			dialog.text = "ええと、クラナもリヴァドスも誰も呼んでないよ。アボットっていう偉そうで気持ち悪い七面鳥は、 「カトリックの女を埋葬するより大事な用がある」って言って来なかったし、 ローダーデールとマスケットも似たようなことをぶつぶつ言ってた。カッセルなんて、あの乱暴者は「行かねえ」 って一言だけ。\nでも、それ以外のみんなは来てるよ。";
			link.l1 = "あたしには、どうしても分からないことがあるんだよ、うん。まあ、それは神様に任せるしかないよね。\nそれに……ジュリアン修道士が来たよ……さあ、ここからが本番だね。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_2");
		break;
		
		case "WildRose_funeral_1":
			dialog.text = "悲しみに心が沈んでいるけれど、主が亡きオレリーに与えてくださったすべての恵みに感謝しよう。そして宣言しよう――神よ、私たちの父よ、感謝します\n"+"オレリーが私たちと共に過ごしたすべての年月と日々のために\n"+"オレリーがあなたの娘となるための聖なる洗礼という大いなる賜物のゆえに\n"+"彼女に授けてくださった贈り物と知恵のために\n"+"彼女が家族や他の人々のために尽くした功績に対して\n"+"私たちの失敗に対する彼女の忍耐に感謝して\n"+"神に祈りましょう。主が亡き姉妹オレリーをその栄光の中に迎えてくださるように。そして共に叫びましょう――主よ、私たちの願いをお聞きください\n"+"オレリーの善行が豊かな実を結びますように\n"+"彼女が始めたことを受け継いでいこう\n"+"彼女が犯した罪をお許しください\n"+"彼女の思い出を私たちの心に生き続けさせよう\n"+"苦しむ者たちの信仰と希望を強めてくださるよう、神に祈りましょう。そして、こう願いましょう――主よ、私たちの信仰を深めてください\n"+"御子が人となられたことによって\n"+"あなたの御子イエス・キリストを通して、私たちを限りなく愛してくださった方よ\n"+"あなたの御子を通して、私たちの罪のために死を受け入れ、私たちの救いのために復活された方\n"+"あなたの御子を通して、私たちのために天への道を開いてくださった方よ\n"+"私たちより先に天の住まいへ旅立ったすべての信仰深き者たちと共に、救い主が教えてくださったように祈りましょう。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_7");
			
			WildRose_Etap4_PathToLight_18_funeral_6_1();
		break;
		
		case "WildRose_funeral_2":
			dialog.text = "全能の神よ、私たちの祈りをお聞きください。あなたの復活された御子への信仰をもって捧げます。 あなたのもとに召された僕と共に、私たちにも復活の希望が与えられるよう、私たちの望みを強めてください。\n私たちの主イエス・キリスト、あなたの御子によって、この方は聖霊の一致のうちに、あなたとともに世々に生き、 支配しておられます。アーメン。";
			link.l1 = "全能の父なる神よ、十字架の神秘は私たちの力であり、御子の復活は私たちの希望の礎です。どうか、 あなたの僕であるこの世を去った女を死の束縛から解き放ち、救われし者たちの仲間に加えてください。\n私たちの主キリストによって。アーメン。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_8");
			WildRose_Etap4_PathToLight_18_funeral_7_1();
		break;
		
		case "WildRose_funeral_3":
			dialog.text = ""+pchar.name+"「じゃあ、早く船室に行こう、ね。もう泣きそうなんだよ……こんな姿、誰にも見られたくないよ。」";
			link.l1 = "「もちろん、」 "+npchar.name+"。行こう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_13");
		break;
		
		case "WildRose_Mary_211":
			dialog.text = "「人は誰かがいなくなって初めてその人の大切さに気づくって――そんな話、聞いたことある？」 "+pchar.name+"?";
			link.l1 = "ああ、何度もあるよ。。";
			link.l1.go = "WildRose_Mary_212";
		break;

		case "WildRose_Mary_212":
			dialog.text = "エリックはよくそう言ってたよ。たぶん家族のことを言ってたんだと思う。あたし、 彼に家族のことを聞いたことはなかったんだ——いつか聞ける時間があるって思ってたから。だけど、彼は死んじゃったんだよ、ね。\nそれからオレリーもいなくなっちゃって——今になってやっと、あたしがどれだけ彼女に時間も気持ちも向けてなかったか気づいたよ。彼女が受けるべきものより、 ずっと少なかったんだ。";
			link.l1 = "あんたは何も悪くないよ。主がいつ大切な人たちを御許に呼ばれるかなんて、誰にも分からないんだ。\nそして、一緒にいられる時間は、どれだけあっても足りないものさ。絶対に、ね。";
			link.l1.go = "WildRose_Mary_213";
		break;

		case "WildRose_Mary_213":
			dialog.text = "そうかもね、うん。エリックはよく言ってたし、オレリーも同意してたんだ――どんな場所も、まず第一に「そこにいる人たち」だって。家でも木でも道でもなくて、人なんだよ。 地図のどこかを思い浮かべるとき、最初に思い出すのは、そこに住んでる人たち、 あるいはかつて住んでた人たちなんだよね。";
			link.l1 = "あたし、そんなこと考えたことなかったよ。だけど、エリックの言う通りかもしれないね、うん。だって、家に帰っても、 もう二度とお父さんやお兄ちゃんに会えないなら、その家にどんな価値があるんだろう？";
			link.l1.go = "WildRose_Mary_214_1";
			link.l2 = " あたしはそうは思わないよ。例えば、パリのことを考えると、思い浮かぶのは通りの景色や匂い…記憶に残ってる人なんてほんのわずかで、他のみんなはほとんど消えかけてるんだ、たった数年しか経ってないのにさ。\n ";
			link.l2.go = "WildRose_Mary_214_2";
		break;

		case "WildRose_Mary_214_1":
			dialog.text = "エリックとオレリーは正義の島のことを話してたと思う、ね。昔々、ここに住んでた人たちのことも――あたしはまだ子どもで、何も分かってなかったけど、今は全部はっきり見えるよ。だって、アントニオやセシル……それにチミセットみたいなリヴァドの何人かは、あたしよりずっと前からここにいる――でも、あたしは誰とも親しくなれなかった。残りのみんな――エリック、オレリー、アラン、それに他にもたくさん――みんな死んじゃったんだ。";
			link.l1 = "そうなんだ。世界が……ちょっとだけ小さくなったよね？";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "WildRose_Mary_214_2":
			dialog.text = "エリックとオレリーが正義の島のことを話してたんだよ、ね。昔々、ここに住んでた人たちのこともね。 あたしはまだ子どもで、何もわかってなかったけど、今は全部はっきり見えるんだ。だって、アントニオやセシル……それにリヴァドスの何人か、たとえばチミセットなんかは、あたしよりずっと前からここにいたんだよ。でも、 あたしは誰とも特別に親しかったわけじゃない。残りのみんな――エリック、オレリー、アラン、それに他のみんな――もうみんな、いなくなっちゃった。";
			link.l1 = "そうなんだ。世界が……ちょっとだけ狭くなったね、うん？";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Mary_215":
			dialog.text = "むしろ、空っぽになったって感じだよ。この世界――外輪の内側はさ。今はもう、何も残ってないんだ、ね。で、もうすぐ――全部消えちゃうかもしれないよ。\n";
			link.l1 = "何を言ってるんだい、メアリー？";
			link.l1.go = "WildRose_Mary_216";
		break;

		case "WildRose_Mary_216":
			dialog.text = "感じなかったの、 "+pchar.name+"？さっき、オレリーの墓のそばに立っていたときだよ。";
			link.l1 = "具体的に何のこと？";
			link.l1.go = "WildRose_Mary_217";
		break;

		case "WildRose_Mary_217":
			dialog.text = "どう説明したらいいかわからないよ。嵐の前の空気の匂い、わかるでしょ？思い出して――あんたがここに初めて来たとき、そこら中にピリピリした空気があった…みんな今にも喉笛を噛み切りそうな勢いで、火薬や血の匂いがすると言う人もいた。でも、あんたがチャドを殺してから、 全部が変わった――息がしやすくなった気がしたんだ…でも今――あの感じがまた戻ってきてるよ。\n";
			link.l1 = "あたしも、そんな感じがしたかも。だけど、ただの雰囲気のせいかもしれないよ？だって、 なんだかんだ言ってお葬式だもんね…";
			link.l1.go = "WildRose_Mary_218_1";
			link.l2 = "「あんた、疲れてるよ」 "+npchar.name+"。少し休んだらいいよ――そうすれば、少しは楽になるから。ねえ、正直、葬式で違う気持ちになれる人なんているのかな？";
			link.l2.go = "WildRose_Mary_218_2";
		break;

		case "WildRose_Mary_218_1":
			dialog.text = "エリックや正義の島の仲間たちを海に送り出した時は、こんなんじゃなかったんだよ。あの時は…一体感があった。でも今日は――みんな同じ祈りを捧げてるのに、狼みたいな目で互いを見てる奴もいたんだ。";
			link.l1 = "「レイトンとドナルドのこと？」";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;

		case "WildRose_Mary_218_2":
			dialog.text = "エリックや正義の島の仲間たちを海に送り出したときは、こんなんじゃなかったんだよ、あたしが言うんだから。 あのときは…一体感があった。でも今日は――みんな同じ祈りを唱えてるのに、何人かは狼みたいな目で互いを見てたんだ。\n";
			link.l1 = "「レイトンとドナルドのこと？」";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Mary_219":
			dialog.text = "あたしも気づいたんだね、うん。";
			link.l1 = "グリーンスペンが訓練にちょっかいを出そうとするたびに、デクスターは緊張しちゃうんだよね――まあ、無理もないでしょ？";
			link.l1.go = "WildRose_Mary_220";
		break;

		case "WildRose_Mary_220":
			dialog.text = "うまくいかないよ、ね。";
			link.l1 = "もしそうなら、今日はオレリー・ベルティーヌの葬式だけじゃなくて、この……見捨てられた船の街の葬式でもあったんだよ。\n";
			link.l1.go = "WildRose_Mary_221";
		break;

		case "WildRose_Mary_221":
			dialog.text = "「見捨てられた船の街？」";
			link.l1 = "ごめん、メアリー。でも、どうしてもこの場所を正義の島なんて呼ぶ気にはなれないんだ。";
			link.l1.go = "WildRose_Mary_222";
		break;

		case "WildRose_Mary_222":
			dialog.text = "あたし、世界を見てその広さに気づいた今じゃ、ここがまるで……牢獄みたいに感じるんだよ、ね。ここで育ったなんて、信じられないよ。";
			link.l1 = "この壊れた船だらけの中で、あんたみたいにこんなに野生で美しいバラが咲くなんて、あたし、ほんと信じられないよ。";
			link.l1.go = "WildRose_Mary_223";
		break;

		case "WildRose_Mary_223":
			dialog.text = "「あたし、この場所にさよならを言いたいんだ」 "+pchar.name+"…もうここには二度と戻ってこないんだろうね、うん。あたしは戻りたくないよ。ここで何が起きるか、 この目で見たくないんだ。";
			link.l1 = "エディとドナルドに話してみるよ。ちょっとは落ち着かせられるかもね。";
			link.l1.go = "WildRose_Mary_224";
		break;

		case "WildRose_Mary_224":
			dialog.text = "わかってないよ……これはただ避けられない運命を少し遅らせるだけで、あんたが頑張る意味なんてないんだよ。そのうち、 あたしたちが戻ってくる日が来る――そしてここで\nそのほうが、きっといいんだよ。 "+pchar.name+"……うん、もうあたしをここに引き止めるものは何もないよ。";
			link.l1 = "あんたの言う通りだよ、ダーリン。やるべきことを片付けたら――それから、ここをきっぱり離れるんだ。\n";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_20");
		break;
		
		// =================================================================
		// ==================== ЭТАП 5. «ЧУЖИМИ РУКАМИ» ====================
		// =================================================================
		case "WildRose_Mary_231":
			dialog.text = "ルパート・カスパー？ジョシュア・ノースウッド？";
			link.l1 = "ずっとそのことを考えてたんだよ、 "+npchar.name+"。それでね、あたし思ったんだよ、君のお父さんは、すでに使った名前や姓で隠れたりはしなかったんじゃないかなって。 同時に、本当の名前や姓を捨てる勇気もなかったかもしれない。だって、 もし大事なときに偽名で呼ばれても反応できなかったらどうする？\n";
			link.l1.go = "WildRose_Mary_232";
		break;

		case "WildRose_Mary_232":
			dialog.text = "何だって名乗れたんだよ、ね。";
			link.l1 = "もちろん、できたはずだよ。もしかしたら、本当にそうしたのかもしれない。 密輸船のタルタンでキューバにたどり着いて、生き延びていればね。もしそこまで行けて、 正義の島のカニの餌にならなかったなら。今はもう待つしかない――前回ほど長くはならないはずだし。ひと月くらいなら、あたしたちだって余裕でやっていけると思うよ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Mary_235":
			dialog.text = "「私の父は生きてるんだ、」 "+pchar.name+"……あたし、ずっと分かってたんだよ、ね！";
			link.l1 = "あたしと同じだよ、ダーリン。さて、そろそろジェロームに会いに行こうか――早いほうがいいよね。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_7");
		break;
		
		// =================================================================
		// ================= ЭТАП 6. «ЖИЗНЬ ПОСЛЕ СМЕРТИ» ==================
		// =================================================================
		case "WildRose_Mary_241":
			dialog.text = "やっと着いたよ、ね。で、これからどうするの？ "+pchar.name+"?";
			link.l1 = "ジェロームを探さなきゃ。あいつ、酒場の部屋でだらだらしてるか、家を借りてるかのどっちかだよ――まあ、金は十分持ってるはずだからね。";
			link.l1.go = "WildRose_Mary_242";
		break;

		case "WildRose_Mary_242":
			dialog.text = "ファディがあいつにどれだけ払ったかを考えると…あたし、絶対に二つ目の選択肢を選んだと思うよ。";
			link.l1 = "了解だよ。『ガラスの眼』の店主に彼のことを聞くか、町の人たちに聞き込みしてみよう。行こう、時間は貴重だからね。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_2");
		break;
		
		case "WildRose_BanditBeliz_1":
			dialog.text = "ほうほうほう……ここにいるのがうちのアツアツカップルか。よし、みんな、さっさと片付けてあいつに報告しようぜ。";
			link.l1 = "「ジェローム・スヴェルニエ？一体ここで何が起きてるんだよ！？」";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_5");
		break;
		
		case "WildRose_BanditBeliz_2":
			if (!CharacterIsAlive("WildRose_Bandit_1") && !CharacterIsAlive("WildRose_Bandit_2"))
			{
				dialog.text = "ああ、この野郎ども、けほっけほっ。まあ、いいんだけどね…";
				link.l1 = "自分の身が大事なら、口の利き方に気をつけな… ";
				link.l1.go = "WildRose_BanditBeliz_2_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "WildRose_BanditBeliz_2_1":
			dialog.text = "...";
			link.l1 = "それもだよ。さあ、白状しなよ。あんたが私たちを襲った理由は何？しかもスーヴェニールと一緒に、ってさ…";
			link.l1.go = "WildRose_BanditBeliz_3";
		break;

		case "WildRose_BanditBeliz_3":
			dialog.text = "お前のスーヴェルニエは欲深くて臆病な野郎だよ。カスパーがちょっと痛い目に遭わせて、さらに小銭をちらつかせたら、 すぐにいい子ぶってあの手紙を書きなぐったんだ、えへん…\n";
			link.l1 = "「じゃあ、本当に見つけたんだ。」";
			link.l1.go = "WildRose_BanditBeliz_4";
		break;

		case "WildRose_BanditBeliz_4":
			dialog.text = "見つけたぞ、見つけたぞ。もうすぐお前は死ぬんだ。お前の小さな彼女も同じ運命さ。 カスパーが二人ともズタズタにしてやる、へっへっ。俺はもう死んだも同然だが、お前の最期には付き合ってやるよ。 カスパーに捕まった時、お前が命乞いする声を聞けないのが残念だな……\n";
			link.l1 = "あたし、もうすぐこの世からいなくなるんだよ、うん。本当のことさ。だから、あたしが最後の息を引き取る前に、 早く話してよ。\n";
			link.l1.go = "WildRose_BanditBeliz_6";
		break;

		case "WildRose_BanditBeliz_6":
			dialog.text = "あいつに会いたいなら、チェトゥマル湾へ行きなよ、あそこがあいつの住処だよ。\n探す必要なんてないよ、向こうからあんたを見つけてくるからね。";
			link.l1 = " 素晴らしいね。ゆっくり死んでくれていいよ。あたしたちの話はこれで終わりだよ。";
			link.l1.go = "WildRose_BanditBeliz_Just_Deth";
			link.l2 = "そうだといいけどね。じゃあ、地獄に落ちな。";
			link.l2.go = "WildRose_BanditBeliz_Hit_Deth";
		break;
		
		case "WildRose_BanditBeliz_Just_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_8");
		break;
		
		case "WildRose_BanditBeliz_Hit_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_7");
		break;
		
		case "WildRose_Mary_251":
			dialog.text = "「ああ、神様、」 "+pchar.name+"…信じられない、あたし、ほんとに信じられないよ、ね！あたしの父さんがこんなことを！？";
			link.l1 = "そうみたいだね、うん。 "+npchar.name+"……彼を突き動かしたものが何なのか、そもそも何者なのか、あたしには全然わからないよ、うん……。でも、別のルパート・カスパーだなんて、そんな偶然はありえないでしょ。";
			link.l1.go = "WildRose_Mary_252";
		break;

		case "WildRose_Mary_252":
			dialog.text = "「それで、あたしたちはこれからどうすればいいの？あたし、彼の目を見て何を言えばいいんだろう？」";
			link.l1 = "まずは、彼に会いに行かないとね。たぶん、探してるってだけであんなに神経質な反応をしたんだから、 今は無法者になってるんじゃないかな。\nでも、どんな事情があっても、彼はあんたのお父さんだよ。\nそれに、あたしたち、彼を見つけるために、ものすごい努力と時間とお金をかけてきたんだから。";
			link.l1.go = "WildRose_Mary_253";
		break;

		case "WildRose_Mary_253":
			dialog.text = "でも、もし彼が私たちと話そうともしなかったらどうするの？どうして私たちを殺せって命じたの？";
			link.l1 = "少なくとも、彼は自分を狙っている相手が誰なのか正確には知らなかったかもしれないよ。 ファディーがあんたの名前だけを伝えて、詳しいことは省いた可能性もあるし。そうじゃなきゃ、 今こうして刃を血で汚す羽目にはなってなかったと思うんだ、うん。";
			link.l1.go = "WildRose_Mary_254";
		break;

		case "WildRose_Mary_254":
			dialog.text = "それで、これからどうするの？チェトゥマル湾に向かうの？でも、もしここで罠を仕掛けられてたら……向こうで何が待ってるか、誰にもわからないよね？";
			link.l1 = "奴がここで何が起きたか知るまで、俺たちには時間の余裕があるんだ。この利を活かそう。\n湾まで航海して、士官の一人を率いる分隊を陸路で送り、俺たちを支援させるぞ。";
			link.l1.go = "WildRose_Mary_255";
		break;

		case "WildRose_Mary_255":
			dialog.text = "納得できる話だよ、うん。でも、それを率いるのは誰なの？";
			if (CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				link.l1 = "ティチンギトゥ。陸戦のベテランだよ。あいつほど上手くやれる奴はいないんだ。";
				link.l1.go = "WildRose_Etap6_Tichingitu";
			}
			if (CheckPassengerInCharacter(pchar, "Duran"))
			{
				link.l2 = "クロード。もちろん喜ばないだろうけど、いずれは受け入れるよ。";
				link.l2.go = "WildRose_Etap6_Duran";
			}
			if (CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l3 = "エルキュール。こういうことのやり方は、彼がよく知ってるんだよ。";
				link.l3.go = "WildRose_Etap6_Tonzag";
			}
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l4 = "トミー。たとえ何かうまくいかなくても、あいつならきっと切り抜けるよ、信じて。";
				link.l4.go = "WildRose_Etap6_Irons";
			}
			if (CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l5 = "ロングウェイだよ。敵をジャングルで追うのは、あいつにとって初めてじゃないんだ。";
				link.l5.go = "WildRose_Etap6_Longway";
			}
			if (!CheckPassengerInCharacter(pchar, "Tichingitu") && !CheckPassengerInCharacter(pchar, "Duran") && !CheckPassengerInCharacter(pchar, "Tonzag") && !CheckPassengerInCharacter(pchar, "Irons") && !CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l99 = "アロンソ。剣の腕は速いし、馬鹿じゃないよ。";
				link.l99.go = "WildRose_Etap6_Alonso";
			}
		break;
		
		case "WildRose_Etap6_Tichingitu":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tichingitu");
		break;
		
		case "WildRose_Etap6_Duran":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Duran");
		break;
		
		case "WildRose_Etap6_Tonzag":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tonzag");
		break;
		
		case "WildRose_Etap6_Irons":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Irons");
		break;
		
		case "WildRose_Etap6_Longway":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Longway");
		break;
		
		case "WildRose_Etap6_Alonso":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Alonso");
		break;
		
		//
		case "WildRose_Tichingitu_1":
			dialog.text = "ティチンギトゥはじっと耳を傾けているよ、船長 "+pchar.name+".";
			link.l1 = "友よ、君には重要な任務が待っている。\nチェトゥマル湾に人斬りどもの一味が潜んでいるんだ。\n奴らを見つけ出して殲滅しなければならない。\n俺たちは船で海から近づくぞ。";
			link.l1.go = "WildRose_Tichingitu_2";
		break;

		case "WildRose_Tichingitu_2":
			dialog.text = "";
			link.l1 = "お前は俺たちの部下を率いてジャングルを抜け、あの野郎どもの背後に回るんだ。何か質問はあるか？";
			link.l1.go = "WildRose_Tichingitu_3";
		break;

		case "WildRose_Tichingitu_3":
			dialog.text = "インディアンは質問はない。明日の正午に一行は所定の場所に潜み、待ち伏せする。";
			link.l1 = "わかったよ、Tichingitu。幸運を祈ってるね。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Duran_1":
			dialog.text = " 呼んだ、船長？ ";
			link.l1 = "クロード、あんたに頼みたい仕事があるんだよ。";
			link.l1.go = "WildRose_Duran_2";
		break;

		case "WildRose_Duran_2":
			dialog.text = "";
			link.l1 = "戦闘員の部隊を集めて、ジャングルを抜けてチェトゥマル湾まで導く必要があるんだ。\nそこにはルパート・カスパーって奴が率いる一味が待ち伏せしてる。\nやつら、俺たちにひどい罠を仕掛けてるみたいだ。\nでも、驚くのはあいつらの方――いや、正確にはあんたの方だよ。\n俺の合図で攻撃してくれ。\n質問はある？ ";
			link.l1.go = "WildRose_Duran_3";
		break;

		case "WildRose_Duran_3":
			dialog.text = "ジャングルを歩くのは嫌だよ。でも、ほら、命令は命令って言うでしょ。\nじゃ、またそこで会おう――たぶん明日の正午ごろだと思うよ。 ";
			link.l1 = "「幸運を祈るよ、Claude。」";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Tonzag_1":
			dialog.text = " 聞いてるよ、船長。 ";
			link.l1 = "エルキュール、あんたに仕事があるよ。";
			link.l1.go = "WildRose_Tonzag_2";
		break;

		case "WildRose_Tonzag_2":
			dialog.text = "頭の固いバカに弾を何発かぶち込む奴が必要？あたしだよ、いつでも準備万端、わかってるでしょ。";
			link.l1 = "その通りだよ。あたしたちの船から戦闘員の小隊を率いて、ジャングルを抜けてチェトゥマル湾まで行ってもらうんだ。\nそこで、きっとあたしたちを待ち伏せしているはずの連中に、逆に待ち伏せを仕掛けるのさ。";
			link.l1.go = "WildRose_Tonzag_3";
		break;

		case "WildRose_Tonzag_3":
			dialog.text = "あたし、もっと手ごわいことを考えてるのかと思ったよ、船長。でもこれなら、ただの酒場巡りじゃない。 明日のお昼までには、ちゃんと着くから任せてよ。\n";
			link.l1 = "そこで会おうね。幸運を祈ってるよ、エルキュール。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Irons_1":
			dialog.text = " はは、船長、なんでそんなに深刻な顔してるの？\n葬式にでも行くつもり？ ";
			link.l1 = "いつも面白い奴だな、トミー？あたしからも一つあるよ――今月は給料なし。来月もね。どうしてそんなにピリピリしてるの？";
			link.l1.go = "WildRose_Irons_2";
		break;

		case "WildRose_Irons_2":
			dialog.text = "冗談も言えないんだよ…";
			link.l1 = "何事にも時があるんだよ、トミー。あんたはまだまだ学ぶことがたくさんあるんだ。いい？よく聞いて、 仲間を集めてジャングルを抜けてチェトゥマル湾まで進むんだ。\n到着したら、あたしの合図を待ってて。";
			link.l1.go = "WildRose_Irons_3";
		break;

		case "WildRose_Irons_3":
			dialog.text = "ジャングルを歩いて行くの？早くても明日の正午までには着かないよ。";
			link.l1 = "じゃあ、明日正午にそこで会おう。\n命令があるまで手を出すな、持ち場も離れるな。\nわかったな？\nうん、わかってるみたいだな。じゃあ、さっさと行動しろ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Longway_1":
			dialog.text = "「長話になっちゃったね、船長。」";
			link.l1 = "ねえ、あんたに頼みたい仕事があるんだよ。";
			link.l1.go = "WildRose_Longway_2";
		break;

		case "WildRose_Longway_2":
			dialog.text = "...";
			link.l1 = "お前が我々の部下を率いてジャングルを抜け、チェトゥマル湾まで行くんだ。\nそこで敵と遭遇するかもしれないから、しっかり準備させておけよ。";
			link.l1.go = "WildRose_Longway_3";
		break;

		case "WildRose_Longway_3":
			dialog.text = "ロングウェイは全部わかってるから、心配いらないよ、船長。明日の正午ごろには目的地に着くよ。";
			link.l1 = "行ってきなよ、気をつけてね。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Alonso_1":
			dialog.text = "「呼んだ、船長？」";
			link.l1 = "いい？よく聞いて、アロンソ。";
			link.l1.go = "WildRose_Alonso_2";
		break;
		
		case "WildRose_Alonso_2":
			dialog.text = "";
			link.l1 = "お前は戦闘員の分隊を率いてジャングルを抜け、チェトゥマル湾へ向かうんだ。\nそこには悪党どもが待ち伏せしている可能性が高い。\n俺が合図を出したら、持ち場につき、背後からやつらを襲撃しろ。";
			link.l1.go = "WildRose_Alonso_3";
		break;

		case "WildRose_Alonso_3":
			dialog.text = "楽勝だよ、船長。でもね、明日の正午前に湾に上陸しないでよ――あたしと仲間たちはそれまでに着けないからさ。";
			link.l1 = "準備して、アロンソ。神のご加護がありますように。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Mary_256":
			dialog.text = "チャールズ、今の見た？";
			link.l1 = "もう俺たちを待ち構えてるみたいだね。きっとあの曲がり角のすぐ先で待ち伏せしてるんだよ。";
			link.l1.go = "WildRose_Mary_257";
		break;

		case "WildRose_Mary_257":
			dialog.text = "それでもあたしたちはまだ立ってるよ。奴ら、撃とうともしないんだよね。 ";
			link.l1 = "もしかしたら、まだあたしたちと話してくれるかもしれないよ。\n刺激しないようにしよう――あたしたちが自分で行くんだ、仲間たちが後ろについてくれるし。\nさあ、これに決着をつけよう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_18_1");
		break;
		
		case "WildRose_Rupert_1":
			dialog.text = "そこまでだ！もう一歩も動くな！野郎ども、あのキザ野郎が少しでも動いたら蜂の巣にしろ。女には手を出すな。";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_1_add";
			// link.l1.go = "WildRose_Rupert_87";
		break;

		case "WildRose_Rupert_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_2", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_2":
			dialog.text = "お父さん？…";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_3":
			sld = CharacterFromID("Mary");
			if (CheckCharacterItem(sld, "hat11")) // У Мэри есть своя шляпа
			{
				dialog.text = " うーん……あたしの長くて厳しい人生で、いろんなものを見てきたよ。もう何にも驚かないって思った時に限って、 人生はあたしの思い違いを教えてくれるんだよね。\nそれで、あんた本当に生き延びたんだ……しかもテレサの帽子まで持ってるなんて。もう二度と見ることはないと思ってたよ。 ";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_1_add";
			}
			else
			{
				dialog.text = " うーん……あたしの長くて厳しい人生で、いろんなものを見てきたよ。もう何も驚かないって思った時に限って、 人生は裏切ってくるんだよね。だから、ほんとに生き延びたんだね、ジュリア…… ";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_add";
			}
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_3_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_2":
			dialog.text = "オレリーがあたしにくれたんだよ、彼女が…亡くなる前にさ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_3":
			dialog.text = "なんて感動的なんだ……泣きそうだよ。てっきりテレサも一緒に埋められたと思ってたのに。あれを渡してから、 彼女は一秒たりとも手放さなかったんだ。お前の母さんは、ただの給仕娘だったけど、冒険心があふれ出てて、 耳からこぼれそうなくらいだったよ。フルール・ド・リス号を拿捕したときにそれを見つけて、 すぐにテレサが夢中になるって分かったんだ。あの帽子をかぶった彼女はちょっとおかしかったけど、 本人は全然気にしなかった。寝るときだけしか外さなかったんだ。でもな、ジュリア、お前には本当に似合ってるよ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_add":
			StartInstantDialog("Mary", "WildRose_Rupert_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_4":
			dialog.text = "「ジュリア？違うよ、あたしの名前はメアリーだよ…」";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_4_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_5":
			dialog.text = "ふーん、そうか。つまり、あいつらはあたしの言葉を無視して勝手に動いたってわけだね。まあ、 あのカトリックの野郎どもに他に期待なんてできないよね。\n";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_5_add":
			StartInstantDialog("Mary", "WildRose_Rupert_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_6":
			dialog.text = "あんた…あんた…本当にあたしの父親なの？";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_6_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_6_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_7":
			dialog.text = "「まあ、そうじゃなかったら、あんたとその相棒はもう鉛玉で地面に転がってたよ。あたし、 神様も悪魔ももう長いこと信じちゃいないけど、もしかしたら本当にいるのかもね。少なくとも神様はいるでしょ――だって、あんたにテレサそっくりの顔をくれたんだから。それが今、あんたの命を救ったんだよ。なんて言うんだっけ……神様のやることは不思議だらけ、だよね？あははは！」";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_7_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_7_add":
			StartInstantDialog("Mary", "WildRose_Rupert_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_8":
			dialog.text = "お父さん…あたし…わかんないよ、ね…";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_8_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_8_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_9":
			dialog.text = " もちろん、わからないよね。どうしてわかるっていうの…";
			link.l1 = "あんまり嬉しそうには見えないね、カスパー旦那。自分の娘だって認めたばかりなのにさ。";
			link.l1.go = "WildRose_Rupert_10";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_10":
			dialog.text = "あんた、なかなか頭が切れるじゃない、ダンディ…。えっと、名前は何だっけ？";
			link.l1 = ""+GetFullName(pchar)+"……あんたを探している間、ずっとどんなふうに暮らしていたのか、ちゃんと生き延びていたのかって考えてたんだよ。\nでも、ここでずいぶんうまくやってるみたいだね、ノースウッド旦那。";
			link.l1.go = "WildRose_Rupert_11";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_11":
			dialog.text = "あら、そこまで調べたんだ。まあ、感心するよ、カエル食いの旦那。あたしが全部きっちり後始末したつもりだったのに、 他に言うことないね。";
			link.l1 = "まだあるんだよ。『コーンウォール』とその積み荷のことも知ってるし、 あんたがしばらく借りてたジョシュア・カスパーの名前も、そしてその姓――どうやらそっちはずっと使い続けてるみたいだね。";
			link.l1.go = "WildRose_Rupert_12";
		break;

		case "WildRose_Rupert_12":
			dialog.text = "ブラボー（拍手）。感心したよ。全部自分で考えたの？それとも、あたしの大事な子も手伝ってくれたのかな？";
			link.l1 = "メアリーがいなければ、俺にはできなかったよ。彼女は自分の両親についてすべてを知ろうと決意していたんだ。 テレサに何が起きたかはすぐに分かったけど、君を探し出すのにはかなり時間がかかったんだよ…";
			link.l1.go = "WildRose_Rupert_13";
		break;
		
		case "WildRose_Rupert_13":
			dialog.text = "これは本当に感動的で、思わず涙が出そうだよ。\nさて、娘よ、これで満足か？幸せかい？パパにハグでもしたいか？";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_13_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_13_add":
			StartInstantDialog("Mary", "WildRose_Rupert_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_14":
			dialog.text = "わからないよ、お父さん……どうしてあたしを苦しめるの？何のために！？（叫ぶ）あたしをあそこ――あの難破船の上に置き去りにしたのはお父さんじゃない！それに、その後一度だって戻ろうともしなかったじゃない、ね！ どうして？そもそもお父さんって誰なの、そしてその後ろに立ってる人たちは誰なの？";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_14_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_14_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_15":
			dialog.text = "「教えて、」 "+pchar.lastname+"、あの子はいつもあんなふうに癇癪を起こすのか？母親譲りなんだよ。テレサは素晴らしい娘だった、 俺が今まで会った中で一番さ。でもな、怒ったときは嵐みたいに叫ぶんだよな……まあ、仕方ないさ……アイリッシュだからな。";
			link.l1 = "彼女を侮辱するなんて絶対に許さないよ！メアリーはあんたの不幸のせいじゃないし、 こんな扱いを受ける理由なんて全然ないんだ。";
			link.l1.go = "WildRose_Rupert_16";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;
		
		case "WildRose_Rupert_16":
			dialog.text = "あたしの口を塞ごうっての、子犬ちゃん！？";
			link.l1 = "逆だよ。あんたの話を聞かせてほしいんだ。メアリーにとって、それを知ることはとても大事なんだよ。\nでも、あたしはメアリーを侮辱させたりしないからね。だから、自分の言動には気をつけてよ。";
			link.l1.go = "WildRose_Rupert_17";
		break;
		
		case "WildRose_Rupert_17":
			dialog.text = "あたしがあんたに心の内をぶちまけたくてたまらないって思ってるの？あたしの人生はこうなっちまったし、ええっと、 あんたたちカトリックがよく言うみたいに――神が証人だよ――何も後悔してないさ。あの時テレサを失ったこと以外はね――あの女のせいで。あたしがあんたを憎んでるって？昔はそうだったかもしれないけど、今はもう、 あんたのことなんてどうでもいいんだよ。";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_17_add";
		break;

		case "WildRose_Rupert_17_add":
			StartInstantDialog("Mary", "WildRose_Rupert_18", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_18":
			dialog.text = "あたしがママの死を責められてるってこと！？どうしてそんな理屈になるの？あたしがしたことって――生まれたこと？それがあたしの罪なの？いいよ、お父さん。+pchar.name+の言う通り、全部話してよ。そのあと、あたしたちは出ていくから。もう二度とあたしの顔を見ることはないよ……それが望みなら……（泣き始める）";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_18_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_19", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_19":
			dialog.text = "あああ、まるでテレサみたいだね。まるで二十年前に戻った気分だよ、あはは！まあ、いいさ、好きにしなよ。 あたしはあの思い出をまた味わうのは、正直気が進まないけど……\nだからさ、この話が終わる頃に、もしあたしがあんたの頭に鉛玉ぶち込みたくなったら――ねえ、そしたら自業自得だと思いなよ、ダーリン。";
			link.l1 = "じゃあ、ルパート、あんたも弾に当たることになるよ。あんたの計画にはそれは入ってないんじゃない？ 自分の命を大事にしてそうな顔してるしね。";
			link.l1.go = "WildRose_Rupert_20";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_20": //
			dialog.text = "あたしは自分の人生の価値くらい、わかってるよ、坊や。でも、それと自分を大事に思うのは別の話だよね。ま、 あんたにはわからないでしょ？いいよ、話そうじゃない。全部知りたいんでしょ？じゃあ、教えてあげる。あたしは1611年、イーストボーンの近くの農場で生まれたんだ。チャンネル海岸沿いの小さな町さ。年は前後するかも、 誰にもわかんないよ――母さんは日付なんて全然覚えてなかったしね。あれだけ酒ばっか飲んでたら、そりゃ無理もないよね。";
			link.l1 = "辛い子供時代だったの？そうなんだね。";
			link.l1.go = "WildRose_Rupert_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_21":
			dialog.text = "頼んだのはあんたなんだから、聞きな、口を挟まずに、賢ぶるなよ。あたしには父親なんていなかったし、 その理由すら知らなかった――でもな、お嬢ちゃん、あんたと違って、あたしはそんなこと気にしなかったんだ。父親からもらった姓で十分だったよ。 あたしが十三のとき、ある晩ダンケルクの私掠船が海岸に上陸したんだ。ねえ、今じゃみんなその話をしたがらないけど、 被害を受けたのはオランダ人だけじゃなくて、あたしたちもだった――イギリス婆さんの東の岸辺に住んでたあたしたちもね。";
			link.l1 = "それ、聞いたことあるよ。あいつらは誰一人容赦しなかったって。どうやって生き延びたの？";
			link.l1.go = "WildRose_Rupert_22_1";
			link.l2 = "奴らがどんな恐ろしいものを残していったか、あたしは知ってるよ。年寄りだろうが子供だろうが、 誰も容赦しなかったんだ。\nそんな中であんたが生き残ったなんて、本当にすごいことだよ。";
			link.l2.go = "WildRose_Rupert_22_2";
		break;

		case "WildRose_Rupert_22_1":
			dialog.text = "あの夜、あのカトリックの豚どもがいくつもの農場を焼き払ったんだ、うちの農場も含めてさ。 あたしはなんとか逃げ出せたけど、 母さんはシードルを飲みすぎてベッドから自分のデカい尻を持ち上げることもできなくて、 そのまま焼け死んじまったんだよ。もちろん自業自得だけど……それでも、母さんだったんだ。";
			link.l1 = "それで、あんたはその時からカトリック野郎どもを全部憎むようになったの？";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_22_2":
			dialog.text = "あの夜、あのカトリックの豚どもがいくつかの農場を焼き払ったんだ、うちも含めてさ。 あたしはなんとか逃げ出せたけど、母さんはシードルを飲みすぎてベッドから自分の重い尻を引きずり出せなくて、 そのまま焼け死んじまったんだよ。自業自得だけど――それでも母親だったんだ。";
			link.l1 = "それで、あんたはカトリックの連中を全部憎むようになったの？";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_23":
			dialog.text = "あたしが飢えを憎むようになったのは、その時だよ、賢ぶりやがって。あんたは本当の飢えなんて知らないだろうけど、 あたしは身をもって味わったんだ。北へ行って、都に着いて、海軍に志願したんだ——そこじゃ、食い物より鞭打ちの方が多かったけど、二十回も打たれりゃ目が覚めるってもんさ。その後は慣れたもんで——そして海の暮らしが好きになったんだ。特に、退屈なんて一度もなかったからね…";
			link.l1 = "それは信じられるよ。王立海軍の評判は、それだけで十分だもんね。";
			link.l1.go = "WildRose_Rupert_24";
		break;

		case "WildRose_Rupert_24":
			dialog.text = "1633年、私は士官試験に合格して、コーンウォール号のブリッグに配属された。";
			link.l1 = "ジョシュア・カスパーの指揮下で。";
			link.l1.go = "WildRose_Rupert_26";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_26":
			dialog.text = "ああ、そうだね……ジョシュア・カスパー……あんなクソ野郎、艦隊中探してもいないよ。もう何年も経つのに、あの豚野郎はいまだにあたしの夢に出てくるんだよ。";
			link.l1 = "それで、彼は何をしたの？あんたが張り切りすぎて見張りを増やされたとか？それとも、実はカトリックだったとか？";
			link.l1.go = "WildRose_Rupert_27";
		break;

		case "WildRose_Rupert_27":
			dialog.text = "あの冷酷な野郎は乗組員をこれでもかってほどしごいて、疲労困憊で海に落ちる奴までいたんだよ。 あんたがあいつの名前を知ってて、『コーンウォール』の指揮官だったってことも知ってるってことは、 きっとあいつの書類も見たんだろ？猫の舐めた尻みたいにピカピカだったよ。\n俺たちの英雄ジョシュアは勲章を箱いっぱい持ってた。あんたみたいな世間知らずの若造が、 あいつの下で働きたいって思うのも無理はないさ。何だかんだ言っても、 あいつは雨上がりの濡れた草を鎌で刈るみたいに、カエル食いどもをバッサバッサとなぎ倒したんだ、ね？でもな、『 コーンウォール』に乗った途端、みんなすぐに自分の間違いに気づくんだよ。\nもう我慢するのはうんざりだったんだ。 "+pchar.lastname+"。転属の嘆願書を書いた者もいたけど、それらは海軍本部の棚で消えたり、炉で焼かれたりしたんだよ。\nそれでも、人生はあたしたちにチャンスをくれた――あたしたちが『コーンウォール』から外されることはなかったけど、代わりに別の誰かが乗り込んできたの。 ジョン・ローソン――クロムウェルのお気に入り、聞いたことあるでしょ？";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_28";
		break;

		case "WildRose_Rupert_28":
			dialog.text = "あいつはあの頃からもうゴマすりが得意だったんだよね――もしかしたらカスパーと気が合ったかもしれないけど、あたしがそれを許さなかったんだ。\nあたしがジョニーをハメて、事情を知らないジョシュアが怒りに任せて杖でジョニーを殴ったのさ。";
			link.l1 = "士官にとって本当に屈辱的だよ。で、ローソンは全部お父さんに話したの？";
			link.l1.go = "WildRose_Rupert_32";
		break;

		case "WildRose_Rupert_32":
			dialog.text = "もちろんそうだよ――それがあたしの計画だったんだ。でもね、システムって自分自身を食い尽くすことはできないの。全部もみ消されたんだ――ローソンには早期昇進の話が持ちかけられて、ジョシュアと“コーンウォール”は影に追いやられた――あたしたちはロンドンからイングランド南部のプリマスに転属させられたの。 あんたたちカエル食いをもっと脅かし続けることもできたけど、“コーンウォール”は補給船にされて、アイルランドの小さな町ダンダルクまで軍需品を運ぶことになったんだよ。";
			link.l1 = "「そこでテレサに会ったの？」";
			link.l1.go = "WildRose_Rupert_33";
		break;

		case "WildRose_Rupert_33":
			dialog.text = "初めてあそこに寄港したんだよ。テレサ・オファット――あの町の酒場の女給だったんだ。お互いに運命の相手だって気づくまで三日もかかったんだよ。あんたも、 あたしの言いたいこと、わかるでしょ？\n "+pchar.lastname+"、そうでしょ？";
			link.l1 = "そうだと思うよ。";
			link.l1.go = "WildRose_Rupert_34_1";
			link.l2 = "今のあんたを見てると、「愛」って言葉の意味なんて知らないんじゃないかって思っちゃうよ。";
			link.l2.go = "WildRose_Rupert_34_2";
		break;

		case "WildRose_Rupert_34_1":
			dialog.text = "あたしは、あんなに素敵な人に会ったことがないんだよ――それは昔も、あれから二十年経った今も同じ。\n人生で初めて、本当に幸せだって感じたんだ。彼女もそうだった――少なくとも、そう言ってたよ。";
			link.l1 = "「それで、あんたは彼女に一緒に出て行こうって頼んだの？」";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Rupert_34_2":
			dialog.text = "あたしは、あの人ほど素敵な人に出会ったことがないんだよ――それは昔も、そしてこの二十年の間も、ずっとね。人生で初めて、本当に幸せだって感じたんだ。あの人も同じだった――少なくとも、そう言ってたよ。";
			link.l1 = "「それで、あんたは彼女に一緒に行こうって頼んだの？」";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_35":
			dialog.text = "もちろん違うよ――そんなの無理だったんだ、だって「コーンウォール」はまだ軍艦で、しかも船長はろくでなしだったからね。 永遠にも感じる一週間の後、うちのブリッグはプリマスへ向けて出航したんだ。二か月後にダンダルクへ戻った――そしたらテレサが驚きの知らせをくれたんだよ。彼女、妊娠してたんだって。";
			link.l1 = "そうだよ、女の子と寝たらそうなるもんだよ。";
			link.l1.go = "WildRose_Rupert_36";
		break;

		case "WildRose_Rupert_36":
			dialog.text = "賢ぶるんじゃねえぞ、このガキ。テレサは俺の肩で泣きじゃくってて、俺はどうしたらいいか考えてたんだ。 本当は彼女のそばにいたかった、心からそう思ってた――でもその時ですら、あの子供からは何もいいことが生まれない気がしてたんだよ。\nまだ間に合ううちにテレサに堕ろすよう説得しようとした――でもその代わりに、もっと激しいヒステリーを起こされた。俺たちはどうすればいいか分からなくなって――だから『コーンウォール』号が次にダンダークに戻るまで、 つまりその時点ではまだ海軍本部がカスパーに怒りを向けたままだったから、あと二ヶ月待つことにしたんだ。\n戻ってからすぐには彼女を見つけられなかった――テレサの妊娠はもう隠せないほどになっていて、彼女が働いていた酒場の主人によれば、 あのクソ親父が彼女を殴って家に閉じ込めたらしい。当然、俺はそのジジイをこっぴどく懲らしめてやったよ、 腸を吐き出す寸前までな。もちろん、もう彼女があの家に住み続けるなんてあり得なかったさ。";
			link.l1 = "「それで『コーンウォール』号に彼女を乗せたの？」";
			link.l1.go = "WildRose_Rupert_37";
		break;

		case "WildRose_Rupert_37":
			dialog.text = "私は素早く決断しなければならなかった。カスパーが女を船に乗せるのを絶対に許さないと分かっていたから、 出航した翌晩にボートを盗んで、進路の右舷側にあるダブリンまで自力で行くつもりだったんだよ。\n";
			link.l1 = "それでどうなったの？捕まっちゃったの？";
			link.l1.go = "WildRose_Rupert_38";
		break;

		case "WildRose_Rupert_38":
			dialog.text = "そうそう。カスパーはもう自分にたっぷりウイスキーを注いでて、誰がどんなに頼んでも耳を貸さなかったんだ。 ただ女の子を海に放り投げろって命令しただけ。あたしがどれだけ懇願しても、 あいつは息が切れるほど笑ってばかりでさ……くそ、今こうして話してても、あいつの笑い声が頭から離れないんだよ…";
			link.l1 = "「それで、反乱を起こすことにしたの？」";
			link.l1.go = "WildRose_Rupert_39";
		break;

		case "WildRose_Rupert_39":
			dialog.text = "他に選択肢はなかったんだよ。近くの見張りの腰からピストルを奪って、あの野郎の額に穴を開けてやったんだ。\nすぐに船内は大虐殺になった――誰も船長のことは好きじゃなかったけど、裁判所への恐怖の方が強かったんだよ。\nそのせいで乗組員の三分の一近くが命を落とした――ようやく正気に戻った時には、『コーンウォール』の甲板は血にまみれ、仲間たちの死体で埋め尽くされていたんだ。";
			link.l1 = " その後は、イングランドに戻るなんて無理だったんだろうね。あんたたち全員、あそこで絞首刑にされちゃうもん。";
			link.l1.go = "WildRose_Rupert_40";
		break;
		
		case "WildRose_Rupert_40":
			dialog.text = "俺は「コーンウェル号」を海を越えて操縦できると確信していた。ここでは俺たちの顔を知る者は誰もいなかったし、 それが新しい人生を始めるチャンスを与えてくれたんだ。ほかの士官たちを説得するのはほとんど手間がかからなかった――それは俺の権威というよりも、普通の水夫たちが知らないいくつかの箱の中身のおかげだった。乗組員たちは決めた――ジョシュア・カスパーは生かしておく、と。俺たち高地出身の士官たちは、時間を稼ぐために箱の一つを犠牲にし、 アンティグアに寄港して、そこで俺が彼の名を名乗ることにした。その後、プロビデンスへ向かうつもりだった。\n実際、その通りになった。誰も入れ替わりに気づかなかったが、プロビデンスまであと数日というところで、 誰かが二つ目の箱のことを口外しやがって――それが乗組員の間に亀裂を生んだんだ。";
			link.l1 = "それで今度はあんたに反乱を起こしたの？\n";
			link.l1.go = "WildRose_Rupert_45";
		break;

		case "WildRose_Rupert_45":
			dialog.text = "いや、でもさ、うちの栄光ある王様に仕え続けたいって奴はどんどん減っていったんだよね。\nそれに、海賊になりたがる奴もそんなに多くなかったし。\nだから、あたしたちは間を取ったの。フランスの港に停泊して、船を売って、売った金と宝箱の中身を分け合って、 それぞれ別々の道を行くことにしたんだよ。";
			link.l1 = "それに、あんたがあれほど嫌ってるカトリックの連中の中で暮らすことになるって、気にもしなかったの？";
			link.l1.go = "WildRose_Rupert_46";
		break;

		case "WildRose_Rupert_46":
			dialog.text = "あの時、どこに上陸しようが気にしなかったんだよ。\nテレサはね、強がってたけど、三ヶ月も揺れっぱなしじゃ、妊婦なら誰だって同じさ。\nそれに、三ヶ月前と同じで、カトリックに囲まれていようが、彼女と一緒ならどうでもよかったんだ。";
			link.l1 = "「しかし、カリブ海の北西部にはフランスの植民地は存在しないし、かつて存在したこともないんだ。」";
			link.l1.go = "WildRose_Rupert_47";
		break;

		case "WildRose_Rupert_47":
			dialog.text = "「コーンウォール号」で事態が沸点に達した頃には、すでに順風に乗って航路の半分を進んでいて、 その時点ではもうセントクリストファーへ針路を変えることもできなかったんだよ…";
			link.l1 = "「それで目的地にトルトゥーガを選んだの？」";
			link.l1.go = "WildRose_Rupert_48";
		break;

		case "WildRose_Rupert_48":
			dialog.text = "あの頃は、ただの小さな村だったんだよ。\n役人たちの追跡を遅らせるために、船尾の名前板を取り替えたんだ――それで「コーンウォール」は「ラングラー」になったのさ。";
			link.l1 = "でも、どういうわけか、あなたはタートル島にはたどり着かなかったんだよね。\nトルトゥーガじゃなくてキューバの西まで航路を外れるなんて、そんなに迷うはずないでしょ？";
			link.l1.go = "WildRose_Rupert_49";
		break;

		case "WildRose_Rupert_49":
			dialog.text = "念のため言っとくけど、あたしは経験豊富な航海士だよ――大抵の奴より腕はいいんだ。間違いなんてなかった、あたしたちは真北へしっかり進路を取ってたんだ。\nでもウィンドワード海峡に入った途端、ひどい突風に襲われたんだよ。今でも不思議なんだけど、 どうしてキューバの岸に叩きつけられなかったのか……そのまま岸沿いに引きずられていったんだよね……";
			link.l1 = "まさに奇跡、他に言いようがないよ。";
			link.l1.go = "WildRose_Rupert_50";
		break;

		case "WildRose_Rupert_50":
			dialog.text = "泣きじゃくるテレサを抱きしめながら、私は心の底から主に祈り、どうか私たちに救いをお与えくださいと懇願したんだ。 \nそして本当に、主は私たちを助けてくださったんだよ。";
			link.l1 = "あんたは正義の島に打ち上げられたんだよ。";
			link.l1.go = "WildRose_Rupert_51";
		break;

		case "WildRose_Rupert_51":
			dialog.text = "正義――ああ、そうだよ！「ラングラー号」が暗礁にぶつかったとき、船体は真っ二つになったけど、どうにか沈まずに済んで――他の難破船が積み重なってる場所まで流されていったんだ。嵐はさらにほぼ二日間も荒れ続けて、ようやく静まったとき――あの哀れな小さな島の人たちが、あたしたちを助けてくれたんだよ。";
			link.l1 = "あんたとテレサ、それにあと二人の船乗り。\nその後何が起きたかは大体わかってるよ。\nあたしたちに、どうやって牢屋から抜け出して正義の島を離れたのか、教えてくれない？";
			link.l1.go = "WildRose_Rupert_63";
		break;

		case "WildRose_Rupert_63":
			dialog.text = "あの時、撃たれていればよかったのに……。あたしを待っていたものが分かっていたら、檻に鎖で繋いで、一歩も動かなかったよ。";
			link.l1 = "タルターヌのほうがブリッグより本当に居心地悪かったの、ね？ "+npchar.name+"?";
			link.l1.go = "WildRose_Rupert_64_1";
			link.l2 = "あんたもタルターヌ船で嵐に巻き込まれたなんて、まさか言わないでよ。";
			link.l2.go = "WildRose_Rupert_64_2";
		break;

		case "WildRose_Rupert_64_1":
			dialog.text = "タルターヌ？ははは…うん、それがあたしの計画だったんだよ。運が向いてきたって思ったの。牢屋の看守長は元イギリス海軍の士官で、 あたしに同情してくれたんだ。キューバの密輸業者たちのタルターヌのことや、 あたしが処刑される計画があるって全部教えてくれたの。まあ、名誉ある男って呼んでもいいかもね――あたしに逃げるチャンスをくれたのは彼だったし、運命を賭けてみろって言ってくれたんだよ。";
			link.l1 = "わかんないよ……タルタン船じゃないなら、どうやって正義の島を出たの？";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_64_2":
			dialog.text = "タルタン？ははは…うん、それがあたしの計画だったんだよ。運が良かったと思ったんだ。牢屋の看守長は元イギリス海軍の士官でさ、 あたしの不運に同情してくれたんだよ。キューバの密輸業者たちのタルタンのことも、 あたしを処刑するつもりだってことも、彼が教えてくれたの。彼は名誉ある男って呼べるかもしれないね――自分の手であたしを逃がしてくれるって申し出てくれたんだ。運命を運に任せてみろってさ。";
			link.l1 = "わかんないよ……タルタン船じゃなかったら、どうやって正義の島を出たの？";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Rupert_68":
			dialog.text = "黙ってちゃんと聞いてれば、わかるんだよ。あたしはタルターナ船に向かって泳いでたんだ、ずっと長い間泳いでて――そしたら雨の壁の向こうに光が見えたの。信じられないくらいのものだったんだ、くそっ。 半分沈んだガレオン船の甲板で太陽みたいに輝いてて、あたしはまっすぐそこに向かったんだ。 まさかそれが人生最大の過ちになるなんて、まだ知らなかったけどね。乗り込み用のはしごを使って水から這い上がった――そしたらその光と真正面で向き合うことになったの。その光は金色の像の上でキラキラしてて、そして…\n";
			link.l1 = "ククルカンの偶像だよ。そう、あの頃は「サン・ヘロニモ」はまだ沈んでなかったんだよね…";
			link.l1.go = "WildRose_Rupert_69";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_69":
			dialog.text = "「じゃあ、あんたも彼を見たんだね、」 "+pchar.lastname+"?";
			link.l1 = "見ただけじゃないよ。あたし、それの力で空間を旅したんだ、しかも一度や二度じゃないんだよ、ね。";
			link.l1.go = "WildRose_Rupert_70";
		break;

		case "WildRose_Rupert_70":
			dialog.text = "嘘でしょ！何度もって、言ったの？！じゃあ、どうしてこんなに元気そうにここに立ってるの！？";
			link.l1 = "移された後、インディアンの薬を飲んだんだよ、それがあたしを生き延びさせて、元気を取り戻す助けになったんだ。";
			link.l1.go = "WildRose_Rupert_71";
		break;

		case "WildRose_Rupert_71":
			dialog.text = "ああ、そういうことなんだね。あたしが元気を取り戻すのにどれだけ時間がかかったか、わかってる？わかってるの！？";
			link.l1 = "まあ、だいたい想像はつくよ。あんたがあの偶像に触ったら、ドミニカのインディアンの村に飛ばされて、 そこで像に生け贄にされて――それから本土に流れ着いたんでしょ？";
			link.l1.go = "WildRose_Rupert_72";
		break;

		case "WildRose_Rupert_72":
			dialog.text = "そう、まさにその通りだよ。あの時、あの像のそばに横たわっていた時ほどの痛みは、今まで感じたことがなかったんだ。 何に例えたらいいかも分からないよ。石造りの家が自分の上に崩れ落ちたとしても、 あんな苦しみにはならないんじゃないかな。気がついた瞬間、また現地人の群れがこっちに向かってくるのが見えたんだ。 もしあたしがあの人たちの言葉を話せたら――神に誓って、その場で殺してくれって頼んでたよ。\n";
			link.l1 = "あれは近くの村のミスキート族だったの？";
			link.l1.go = "WildRose_Rupert_76";
		break;

		case "WildRose_Rupert_76":
			dialog.text = "あいつらだよ。あたしを小屋のひとつに引きずり込んでさ、なんか変な現地人――他の連中とは違う感じのやつ――が、何かをあたしの口に無理やり流し込んだんだ。痛みはちょっと和らいだけど、完全には消えなかった。夕方になると、 火のそばに引っ張り出されて、あの化粧した野郎がなんか儀式みたいなことを始めやがった。情けないやつだよ。";
			link.l1 = "スネークアイ……あんたは自分の命を救ってくれた彼に感謝すべきだったんじゃない？";
			link.l1.go = "WildRose_Rupert_77";
		break;

		case "WildRose_Rupert_77":
			dialog.text = "「助けに？…三年だよ、」 "+pchar.lastname+"三年間、あたしはほとんど身動きもできずに寝たきりで、垂れ流しにして、自分の吐瀉物の中で目覚めてたんだよ、 だって、あいつらが無理やり飲ませてくるあの臭い煎じ薬やチンキがどうしても我慢できなかったからさ！\nそれからまたほぼ一年かけて、歩くことを一から覚え直したんだよ。";
			link.l1 = "胸が痛くなる話だね。でも、正直言って、あんたのことちょっと可哀想に思っちゃうよ。";
			link.l1.go = "WildRose_Rupert_78";
		break;

		case "WildRose_Rupert_78":
			dialog.text = "同情なんてクソくらえだよ、ローマ教皇のデブったカトリック尻にでも突っ込んでな。あたしに同情なんていらないよ。 続けようか？それとも泣く時間が欲しいのかい、小さな孔雀ちゃん？\n";
			link.l1 = "この旅でお前の礼儀が良くなったとは思えないね。でも、まあ、メアリーのために我慢してやるよ。 もう肝心なことは分かったと思うけど……最後までちゃんと聞いてやろうじゃないか。";
			link.l1.go = "WildRose_Rupert_79";
		break;

		case "WildRose_Rupert_79":
			dialog.text = "どうにか立ち直って、あの呪われた村を離れ、海岸へ――アマティケ湾へ向かったんだ。そこで、近くに停泊していた密輸船の連中に出会って仲間に加わった。 自分の名はルパート・カスパーだと名乗ったよ。\n本当は自分の名前を捨てたくなかったけど、人生をめちゃくちゃにした奴らの姓はそのまま使った。\nここに辿り着いた理由を、絶対に忘れないためにな。";
			link.l1 = " お前にとっちゃ、ノースウッド、誰もかれもが悪いんだろう…自分以外はさ。まあ、わかるけどね――長年の屈辱と苦労の末に、今じゃこんな森の中に閉じ込められてるんだもん。正気を失わない方がおかしいよね？ ";
			link.l1.go = "WildRose_Rupert_80_1";
			link.l2 = "ノースウッド、あんたは本当に色々あったんだよね、間違いないよ。で、今はどう？ 文明の端っこの森の中にいるじゃない…ここで正気を失ったりしないよ…\n";
			link.l2.go = "WildRose_Rupert_80_2";
		break;

		case "WildRose_Rupert_80_1":
			dialog.text = "「あたしがこの森の主だよ、」 "+pchar.lastname+"。十五年以上かけて、あたしは密輸船の惨めな水夫から、そこのリーダーにまでなったんだよ。 ちっぽけな船の船長なんかじゃなくて、アマティケ湾から死の湾まで、海岸全体を仕切る主になったんだ。";
			link.l1 = "うん、それはなかなか見事な切り返しだね、認めるよ。";
			link.l1.go = "WildRose_Rupert_81";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_80_2":
			dialog.text = "「あたしがこの森の主だよ、」 "+pchar.lastname+"十五年以上かけて、あたしは密輸船の惨めな水夫から、みんなのリーダーになったんだよ。\nちっぽけな船の船長なんかじゃなくて、アマティケ湾から死の湾まで、この海岸全体を仕切る主になったんだ。";
			link.l1 = "うーん、まあ、それはなかなか見事な切り返しだよ、認めるわ。";
			link.l1.go = "WildRose_Rupert_81";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "WildRose_Rupert_81":
			dialog.text = "「ここは森の悪魔の領域だって言う奴もいるけど……なんて図々しい嘘だよ、ここはあたしの縄張りだよ。スヴェンソンもそれを知ってるんだ、ははは。あいつ、 何度も手下を送り込んできて、あたしが誰なのか探ろうとしたけど――誰一人として生きて戻った者はいないんだよ、へへ。あたしが密輸を始めた時の名前を知ってる奴や、 この森のどこに住んでるか知ってる奴なんて、片手で数えられるくらいだよ。」\n";
			link.l1 = "つまり、今は別の名前を名乗ってるんだね。だから「ルパート・カスパー」を探してるって聞いたとき、 あんなに慌てたんだ。";
			link.l1.go = "WildRose_Rupert_82";
		break;
		
		case "WildRose_Rupert_82":
			dialog.text = "慌ててる？本気か、坊や？ここで慌ててるのはお前だけだ――あたしの縄張りで、あたしの仲間に囲まれて、完全にあたしの手の内なんだから！お前に何をしようがあたしの勝手さ。 そしてあの女にもな――あたしがあんな苦しみを味わう羽目になったのは、全部あいつのせいだからな！";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_82_add";
		break;

		case "WildRose_Rupert_82_add":
			StartInstantDialog("Mary", "WildRose_Rupert_83", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_83":
			dialog.text = "あんた、ほんとに頭おかしいよ、うん。ルパート・ノースウッド、あんたを治せる薬も医者も知らないよ！ 地獄みたいな目にあったのはわかるけど…なんで全部あたしのせいにするの？！";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_83_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_83_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_84", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_84":
			dialog.text = "もう言ったでしょ――あんたがいなければ、こんなこと全部起きなかったんだよ。認めちゃいなよ、ね？";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_84_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_84_add":
			StartInstantDialog("Mary", "WildRose_Rupert_85", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_85":
			dialog.text = "...";
			link.l1 = "「彼を放っておいて」 "+npchar.name+"……もう十分聞いたよ。世の中には最後まで進んじゃいけない道もあるんだよね。 あたしたちがこの件に首を突っ込むって決めた時から、嫌な予感がしてたんだ。でも、その声を無視しちゃった。 残念だよ。";
			link.l1.go = "WildRose_Rupert_85_add";
		break;
		
		case "WildRose_Rupert_85_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_86", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_86":
			dialog.text = "ああ、そうすればお前たち二人ともここに閉じ込められて、何もできずに無力になることはなかったんだ。\nさあ、自分で感じてみろ、娘よ、俺が味わった苦しみを！";
			link.l1 = "「誰が俺たちに何もできないなんて言ったんだ？部隊、武器を取れ！」";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_20");
		break;
		
		case "WildRose_Rupert_87":
			dialog.text = "どうした、新入り？誰か失くしたのか？ははは…ははは。ハーハーハーハーハーハー！！！今のお前の顔、見せてやりたいぜ、この間抜け！おい、メイソン、 客人たちへの俺の贈り物を持ってこい。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_22");
		break;
		
		case "WildRose_Rupert_88":
			dialog.text = "...";
			link.l1 = "この野郎！あたしの仲間はどこだよ！？";
			link.l1.go = "WildRose_Rupert_89";
		break;
		
		case "WildRose_Rupert_89":
			dialog.text = "あたしを待ち伏せできると思い込んでた、あの愚か者たちのこと？酒場の旦那があんたが町に来るって、 ちゃんと教えてくれたからさ、あたしは奴らにふさわしいお出迎えをしてやったよ…何人かはうまく逃げたけどね。\nでも心配しないで――一人は生け捕りにしたから。今日あんたにどんな運命が待ってるか、自分の目で確かめてごらん。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_25");
			
			// WildRose_Etap6_LifeAfterDeath_24_1();
		break;
		
		case "WildRose_Rupert_90":
			dialog.text = "このろくでなし！絶対に許さないからね！（泣く）誓うよ、あたし、うん！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_29");
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Alonso_11":
			dialog.text = "...";
			link.l1 = "「アロンソ！会えて本当に嬉しいよ！」";
			link.l1.go = "WildRose_Alonso_12";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_12":
			dialog.text = "あたしも会えて嬉しいよ、船長！あんたがあいつを追ってるって、誰かがあの悪党に密告したみたいでさ――途中でぶどう弾の嵐を浴びせられたんだ。なんとか少人数で引き返して、 港まで一目散に走ってあんたに警告しに来たのさ。運よく、当番の見張りが、 あたしが町で急いで買った小舟に乗ってるのを見て、すぐに状況を察してくれた。彼はすぐに男たちを集めて――こうして助けに駆けつけたってわけ。";
			link.l1 = "ありがとう、友よ。君がいなければ俺たちは確実に死んでいたんだ。";
			link.l1.go = "WildRose_Alonso_13";
		break;

		case "WildRose_Alonso_13":
			dialog.text = "そんなの大したことないよ。次はどうする、船長？";
			link.l1 = "乗組員を集めて船へ向かってくれ。\nメアリーとあたし、ちょっと二人きりになりたいんだよ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		case "WildRose_Mary_261":
			dialog.text = "「なんてこと、」 "+pchar.name+"…まだ信じられない、どうしても信じられないよ。あたしの父さんが…あんな化け物だったなんて…どうしてこんなこと、あたしにするの？本当に正気を失っちゃったの…？";
			link.l1 = "彼はひどい苦しみに耐えなければならなかったんだよ。『コーンウォール』号での反乱、大西洋を越えての脱出、嵐、 そして君のお母さんの死……。コマンチ族の薬なしであの偶像の門をくぐり抜けてどうやって生き延びたのか、あたしには想像もつかないけど――それが彼の心を壊したんだよ。\n";
			link.l1.go = "WildRose_Mary_262";
			locCameraFromToPos(-3.80, 1.10, 52.00, false, 0.61, 0.27, 49.69);
			LAi_ActorAnimation(pchar, "sharle_mary_sit", "", 50.0);
			LAi_ActorAnimation(npchar, "sharle_mary_sit", "", 50.0);
			CharacterTurnAy(pchar, 6.00);
			CharacterTurnAy(npchar, 6.00);
		break;

		case "WildRose_Mary_262":
			dialog.text = "もし彼が最初からそういう人だったら？それとも、やっぱりろくでなしだったけど、少しは優しくて、 本当に母さんのことを愛してたのかも？もしかして、全部はもともと彼の中にあったものが、ただ表に出ただけなのかな？ そして、もしそうなら……あたしの中にも彼の何かがあるってこと？そういうことも、あるよね、\n "+pchar.name+"、ね？";
			link.l1 = "「あんた、確かにあの人から何か受け継いでるよ、」 "+npchar.name+"。今日の戦いで気づいたんだ――あんたは、あの人と同じ決意、同じ目の炎、同じ激しさで戦ってた。でも、あの人の狂気は持ってない。 あんたは全然違う存在だよ。生き生きしてて、素直で、心を隠さない。だからこそ、あたしはあんたに惚れたんだよ。 それに、ノースウッドの言った通りみたいだね。あんたはお母さんの魂をしっかり受け継いでるよ。";
			link.l1.go = "WildRose_Mary_263";
		break;

		case "WildRose_Mary_263":
			dialog.text = "「本当にそう思うの、あなた？」";
			link.l1 = "もちろんだよ、あたしの大事な人。もしあたしが彼にただ会っただけで、誰なのか知らなかったら、 あんたと親子だなんて絶対に思わなかったよ。";
			link.l1.go = "WildRose_Mary_264";
		break;

		case "WildRose_Mary_264":
			dialog.text = "ねえ、正義の島にはあんまり娯楽がないんだよ。あたし、子供の頃から剣術が大好きでさ――最初は男の子たちと木の棒で戦ってたけど、そのうち大人の男たちと、本物の剣で戦うようになったんだ、うん。でもね、 ずっと彼らと同じになりたかったのに……どうしても自分の方が弱い気がしてたんだ、勝った時ですら。\nだから家に帰って、また練習したよ。何時間も稽古して、手が震えるまでやったんだ、うん。それが、あんたの言う「炎」 なの？その「怒り」ってやつ？";
			link.l1 = "ある意味――そうだよ。あたしは、その炎があんた自身が思ってるよりずっと大きな力をくれてるって思うんだ。好きでも嫌いでも、 それはお父さんからの贈り物なんだよ。たとえ、あの人が何もあげるつもりがなかったとしてもね。";
			link.l1.go = "WildRose_Mary_265";
			locCameraSleep(false);
			locCameraFromToPos(-1.95, 1.81, 48.29, true, -2.11, -0.04, 52.55);
		break;

		case "WildRose_Mary_265":
			dialog.text = "あたしたち、過去を掘り返して正しいことをしたと思う？";
			link.l1 = "これで全部わかったけど……もうそんなにいい考えじゃない気がするよ。\nでも、もし本当のことを知りたいなら、気に入らないかもしれないって覚悟しなきゃね。";
			link.l1.go = "WildRose_Mary_266";
		break;

		case "WildRose_Mary_266":
			dialog.text = "「そうだよ、」 "+pchar.name+"……うん、もう少しここにいようよ。まだ船に戻る気分じゃないんだ。ただ……こうして静かな場所で座っていたいの。";
			link.l1 = "もちろんだよ、あたしの愛しい人。ちょうど同じことを言おうとしてたんだ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_38");
		break;
		
		// Тичингиту
		case "WildRose_Tichingitu_Final_1":  
			dialog.text = npchar.name + "「ちょうどいい時に来てくれたよ、船長」 " + pchar.name + ".";
			link.l1 = "あんたなら頼りになるって思ってたよ、友だち。ありがとう――誰にもあんた以上にはできなかったよ。";
			link.l1.go = "WildRose_Tichingitu_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tichingitu_Final_2":
			dialog.text = "ジャングルは " + npchar.name + "の家。 " + npchar.name + " ジャングルで戦えて嬉しいよ。ジャングルは力をくれるんだ。 " + npchar.name + ".";
			link.l1 = "だからこそ、あたしはあんたを隊のリーダーにしたんだよ。ほら、見ての通り、大歓迎で迎えてくれたじゃない。\n";
			link.l1.go = "WildRose_Tichingitu_Final_3";
		break;

		case "WildRose_Tichingitu_Final_3":
			dialog.text = "「どの船長」 " + pchar.name + " 次は何をするつもり？";
			link.l1 = "メアリーと俺に少し二人きりの時間が必要だ。負傷者を集めて船に運んでくれ。死者もだ――海で弔う。あと、\n " + npchar.name + "…アロンソに、メアリーの父親はここに、きちんとしたプロテスタントのやり方で埋葬すべきだと伝えてくれ。\nこのことはお前とアロンソだけが知っていればいい。他の誰にも――メアリーにさえ――絶対に知られてはならない。\n彼女には、これ以上苦しんでほしくないんだ。";
			link.l1.go = "WildRose_Tichingitu_Final_4";
		break;

		case "WildRose_Tichingitu_Final_4":
			dialog.text = npchar.name + " わかったよ、船長 " + pchar.name + "……ティチンギトゥが全部やるよ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Дюран
		case "WildRose_Duran_Final_1":   
			dialog.text = "手強い野郎どもだったな…でも、あたしたちが一枚上手だったよ、あはは！ここで腐って、もう一度あたしたちに手を出す前によく考えるんだね。\n";
			link.l1 = "「ありがとう」 " + npchar.name + "、よくやってくれたね。もし君を後ろの守りにつかせていなかったら、メアリーや……あたし自身に何が起きていたか考えるだけでぞっとするよ……";
			link.l1.go = "WildRose_Duran_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Duran_Final_2":
			dialog.text = "はは、船長なら何とかしちゃうって、あたし知ってるよ。あのリーダーが持ってたでっかい剣、見た？あたし、 目が離せなかったんだ。もし気に入らないなら、あたしにくれても全然気にしないよ。\n";
			link.l1 = "ふむ……どうなるか見てみようぜ、相棒、どうなるか。今は生存者を集めて船へ向かえ。倒れた者たちも船に運び込め――海に還してやる。\nそれと……あの指導者――あいつはメアリーの父親だった。アロンソを連れて、ここでプロテスタントの作法に則ってきちんと埋葬してやれ。\n墓の場所は誰にも知らせるな。特にメアリーには絶対にだ。あいつにそんな苦しみは必要ない。";
			link.l1.go = "WildRose_Duran_Final_3";
		break;

		case "WildRose_Duran_Final_3":
			dialog.text = "了解だよ、船長。\nあっ……やっぱり……なんでもない。あたしが行くよ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Тонзаг
		case "WildRose_Tonzag_Final_1": 
			dialog.text = "ここはめちゃくちゃ暑いね、船長。あいつら、自業自得だよ。あたしたちが現れたとき、あのチビの顔が歪んだの見た？";
			link.l1 = "あいつはまさかの展開に気づいてなかったな。\nあたしもメアリーも、あんな最低野郎だとは思わなかったけど。\nでも、背後を守るって決めたときの直感は間違ってなかったよ。";
			link.l1.go = "WildRose_Tonzag_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tonzag_Final_2":
			dialog.text = "カリブの海は初めてじゃないだろ、船長。ここにうようよしてるクズどもにももう慣れてるはずだし、 トラブルの匂いも遠くから嗅ぎ分けられるようになったんじゃない？さて、どうする？船に戻るのかい？\n";
			link.l1 = "負傷者を集めて、死者を収容し、全員を船に乗せろ。失った者たちは――本物の海の子らしく、海に還してやるんだ。\nメアリーと俺はしばらくここに残る――二人きりの時間が必要なんだ。\nもう一つ頼む。メアリーの父親はプロテスタント式で埋葬してくれ。必要ならアロンソを連れて行け。\nただし、誰にも墓の場所を知られないようにしろ。特にメアリーには絶対にだ。 彼女に過去の記憶で苦しんでほしくないんだ。";
			link.l1.go = "WildRose_Tonzag_Final_3";
		break;

		case "WildRose_Tonzag_Final_3":
			dialog.text = "あんたの言う通りだよ。彼女がここに戻ってきて涙を流す意味なんてないさ。心配しないで――ちゃんとやるし、生きてる誰にも絶対に知られやしないからね。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Айронс
		case "WildRose_Irons_Final_1":
			dialog.text = "船長、旦那、ご報告します：待ち伏せは成功、クズどもは始末し、船長は確保しました。";
			link.l1 = "今は皮肉を言う時じゃないよ、それにもし冗談を言おうとしてるなら――やめといた方がいいよ。みんなの前で甲板を磨く羽目になりたいわけじゃないでしょ？ああ、みんな大喜びするだろうね……今日は、あたしの我慢を試さない方が身のためだよ。";
			link.l1.go = "WildRose_Irons_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Irons_Final_2":
			dialog.text = "えっと…あたし、一応士官だよ、うん…";
			link.l1 = "今はね。今日は士官――明日は甲板員、その次の日には乞食さ。\n";
			link.l1.go = "WildRose_Irons_Final_3";
		break;

		case "WildRose_Irons_Final_3":
			dialog.text = "了解： " + GetFullName(pchar) + " こっちは真面目な船長だよ。もう冗談はなし。命令は、旦那？";
			link.l1 = "負傷者を集めて船に乗せろ。アロンソに乗組員を連れて我々の仲間の遺体を回収するよう伝えろ――海に還してやるんだ。あと、メアリーの父親はプロテスタントの習わしに従って埋葬させろ。 その埋葬場所はアロンソと手伝う者だけが知っていればいい。メアリーには知らせるな。 彼女にこれ以上つらい思いをさせたくないんだ。";
			link.l1.go = "WildRose_Irons_Final_4";
		break;

		case "WildRose_Irons_Final_4":
			dialog.text = "はいはい……任せといてよ。心配しないで——あたし、口は堅いんだから。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Лонгвэй
		case "WildRose_Longway_Final_1":
			dialog.text = "船長、旦那、やりましたよ。犬っころ一匹も逃しませんでした。";
			link.l1 = "「よくやったね、」 " + npchar.name + "、ありがとう。あんたなら頼りになるって思ってたよ。生き残ったみんなを集めて船に戻ってくれ。 あたしとメアリーはもう少し陸に残るから。";
			link.l1.go = "WildRose_Longway_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Longway_Final_2":
			dialog.text = "死体をどうすればいいんだ？";
			link.l1 = "奴らは海に還すんだ。アロンソに準備を任せるよう伝えてくれ。\nそれからもう一つ、メアリーの父親はプロテスタントの習わしに従って、 このジャングルのどこか人目につかない場所に埋葬するように言ってくれ。\n墓の場所は誰にも知られてはならない――特にメアリーにはな。あの子の性格なら、きっとまたここに戻って来たがるだろうが、それはあの子のためにならない。";
			link.l1.go = "WildRose_Longway_Final_3";
		break;

		case "WildRose_Longway_Final_3":
			dialog.text = "了解だよ。他に何かある、旦那？";
			link.l1 = "以上だよ、友達。休んで、傷の手当てをしてね。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Алонсо
		case "WildRose_Alonso_Final_1":
			dialog.text = "すごい血の海だったね……大丈夫、船長？";
			link.l1 = "あたしは大丈夫…ただ、メアリーと一緒に彼女の父親を殺さなきゃならなかったってこと以外はね…";
			link.l1.go = "WildRose_Alonso_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_Final_2":
			dialog.text = "見た感じ、あいつは本当にろくでなしだったみたいだね…";
			link.l1 = "「その通りだよ、」 " + npchar.name + "。だが、きちんと埋葬してやるべきだ――プロテスタント式でな。お前に直接やってほしい。誰にも墓の場所を知られてはならん。特にメアリーにはな。";
			link.l1.go = "WildRose_Alonso_Final_3";
		break;

		case "WildRose_Alonso_Final_3":
			dialog.text = "彼女に嫌な思い出を思い出させたくないのか？";
			link.l1 = "そして、無用な苦しみだ。他のみんなは船に戻して休ませてくれ。倒れた者たちも船に運んでくれ——マリーとあたしが戻ったら、海に葬ろう。\n今は、二人きりになりたいんだ。";
			link.l1.go = "WildRose_Alonso_Final_4";
		break;

		case "WildRose_Alonso_Final_4":
			dialog.text = "あたしがみんなに、あんたには手を出すなって言っとくよ。";
			link.l1 = "「ありがとう」 " + npchar.name + ".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
	}
}
