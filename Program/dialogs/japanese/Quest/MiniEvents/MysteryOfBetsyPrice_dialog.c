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
			dialog.text = "何の用だ？";
			link.l1 = "「何でもない。」";
			link.l1.go = "exit";
		break;

		case "Poorman_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "おい、美人さん、あんたのコレクションにぴったりの上等な飾り物はどうだい？本物の宝だぜ！ あんたにはみんなの羨望のまなざし、俺にはパンとラムを買うための小銭がちょっと、ってわけさ。";
			}
			else
			{
				dialog.text = "おい、船長、あんたの女に粋な贈り物はどうだ？本物の宝だぜ！あんたには彼女の熱い感謝、 俺にはパンとラムの一杯分の小銭ってわけさ。\n";
			}
			link.l1 = "「それで一時間後に兵隊が俺を捕まえに来て、盗みの罪で牢屋に放り込むってのか？どこで手に入れたんだ、 この浮浪者め？」";
			link.l1.go = "Poorman_2_fortune";
			link.l2 = "「上等な贈り物だと？それに、あんたみたいな宿無しがそんな物をどこで手に入れるんだ？」";
			link.l2.go = "Poorman_2_leadership";
			if (npchar.quest.meeting == "0") npchar.quest.meeting = "1";
		break;

		case "Poorman_2_fortune":
			dialog.text = ""+GetSexPhrase("船長、俺","I")+" この美しいカメオ付きのペンダントを見つけたんだ、誓って正直な話さ！もし嘘なら沈んじまってもいいぜ！ただそこに、 誰にも要られずに転がってたんだ。こんな美しいものを泥の中に放っておけるわけないだろ？";
			link.l1 = "よし。そこにあるものを見せてくれ。";
			link.l1.go = "Poorman_3";
			link.l2 = "あんたみたいな立派な旦那の言葉なんて誰が信じるんだ？もっと騙されやすい奴を探しな。";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Poorman_2_leadership":
			dialog.text = ""+GetSexPhrase("「船長、俺」","I")+" カメオ付きのこの美しいペンダントを見つけたんだ、正直な話だぜ！もし嘘なら沈んじまってもいい！ そこに誰にも要られずに転がってたんだよ。こんな美しいものを泥の中に放っておけるわけがねえだろ？";
			link.l1 = "よし。そいつを見せてみろ。";
			link.l1.go = "Poorman_3";
			link.l2 = "あんたみたいな立派な旦那の言葉を誰が信じるってんだ？もっと騙されやすい奴を探しな。";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Poorman_exit":
			DialogExit();
			AddDialogExitQuestFunction("TBP_PismoVDome");
		break;
		
		case "Poorman_3":
			dialog.text = "見てくれよ……なかなかいい物だろう！酒場の近く、灯りのある家の花壇で見つけたんだ。でも、あそこにはずっと誰もいなくて、 返す相手もいないんだよ。";
			link.l1 = "面白い小物だな。それで、いくら欲しいんだ？";
			link.l1.go = "Poorman_4";
		break;

		case "Poorman_4":
			dialog.text = "たった百ペソ"+GetSexPhrase("、船長","")+"…あんたみたいな奴にははした金だろうが、俺には一週間もパンの心配をせずに済む大金さ。見てくれよ――なんて美しいんだ！";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "「よし、これが百ペソだ。」";
				link.l1.go = "Poorman_5";
			}
			link.l2 = "俺は遠慮しておくぜ。他の奴に運を試してみな。";
			link.l2.go = "Poorman_exit";
		break;

		case "Poorman_5":
			dialog.text = "ありがとうございます。 "+GetAddress_Form(NPChar)+"！これで運も必ず味方してくれるはずだ！あんたはいい人だって、すぐに分かるぜ。";
			link.l1 = "...";
			link.l1.go = "Poorman_exit";
			GiveItem2Character(PChar, "jewelry24");
			pchar.questTemp.TBP_BuyKulon = true;
			pchar.questTemp.TBP_BuyKulonOtdatBetsy = true;
		break;
		
		case "Pirate_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "おおお、誰が俺たちのところに来たんだ？どうやらドアを間違えたわけじゃなさそうだな、お嬢ちゃん……さあ、入って入って！服を脱いで、くつろいでいけよ。";
				link.l1 = "ほうほう……ここにいるのは誰だ？お前ら、ベッツィにあの“やさしい”脅しの伝言を残した同じ悪党どもじゃねえか？";
			}
			else
			{
				dialog.text = "「な、なんだこのイカは！？ドアを間違えたのか、このヤギ頭め！ぶった斬られる前にとっとと失せろ！」";
				link.l1 = "ほうほう……ここにいるのは誰だ？お前ら、ベッツィにあの素敵な脅し文句を残していった間抜けどもじゃねえか？";
			}
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "ベッツィ？ベッツィなんざ、くたばっちまえ！それより面白ぇのは、お前がここで何してるかだぜ、お嬢ちゃん……せっかく来たんだ、慌てて帰ることはねぇさ。お前を楽しませる方法はいくらでもあるからな……";
			}
			else
			{
				dialog.text = "なんだと、ベッツィ？運を試すんじゃねえ、バカ野郎。自分の足でまだ出ていけるうちに、とっとと消えな。\nさもねえと、バラバラにしてバケツで運び出す羽目になるぜ！";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_2");
		break;

		case "BetsiPrice_1":
			dialog.text = "助けてくれ！助けて、頼む！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_3");
			locCameraFromToPos(1.40, 1.62, 1.14, false, 2.58, -0.30, -1.64);
		break;
		
		case "Pirate_3":
			dialog.text = "...";
			link.l1 = "ほら、あそこにいるぜ。お前は首までトラブルに浸かってるんだ、相棒。これが最後の過ちになりたくなけりゃ、 彼女をすぐに解放するんだな。";
			link.l1.go = "Pirate_4";
		break;

		case "Pirate_4":
			dialog.text = "ははっ！聞いたか、レジー？ "+GetSexPhrase("奴は","彼女は")+" 俺たちを脅すことさえしているんだ。 "+GetSexPhrase("なんて生意気なナメクジだ","なんて生意気なクズだ")+"。おい、見せてやろう "+GetSexPhrase("この成り上がり野郎の根性がどんな色か見てやろうぜ","この成り上がり者に本当の苦しみってやつを教えてやる")+".";
			link.l1 = "お前の葬式だぜ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_4");
		break;

		case "Pirate_5":
			if (!CharacterIsAlive("TBP_Bandit_1"))
			{
				dialog.text = "...";
				link.l1 = "さあ、その娘を放せ。さもないと、お前も仲間の隣で眠ることになるぜ。";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_HouseBetsi_6");
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Pirate_5";
			}
		break;

		case "BetsiPrice_2":
			dialog.text = "くそったれどもめ！俺が黙ってると思ったのか！？";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_2_1";
			sld = CharacterFromID("TBP_Bandit_2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("TBP_BetsiPrice"));
			CharacterTurnByChr(npchar, sld);
		break;

		case "BetsiPrice_2_1":
			dialog.text = "そしてお前……奴らの仲間じゃなさそうだな。お前は何者だ？";
			link.l1 = "Captain "+GetFullName(pchar)+"、お仕えいたします。";
			link.l1.go = "BetsiPrice_2_2";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "BetsiPrice_2_2":
			dialog.text = "つまり、俺の命はお前に借りができたってことか？";
			link.l1 = "そうみたいだな。しかし今はもっと大事なことがある――こいつらは何者だ、そしてお前は一体何に巻き込まれたんだ？";
			link.l1.go = "BetsiPrice_3";
		break;
		
		case "BetsiPrice_3":
			dialog.text = "こいつらは……重要なイギリスの役人に送り込まれた連中だ。かつては俺にとても近しい存在だった……だが今じゃ、見ての通り、俺の死を望んでやがる。";
			link.l1 = "お前の話がだんだん分かってきたぜ。あんたはあいつの愛人だったが、ある時からそれを利用しようと決めたんだな。 脅かしてやろうとした……家族に話すつもりだったのか？";
			link.l1.go = "BetsiPrice_4";
		break;

		case "BetsiPrice_4":
			dialog.text = "「意外と近いな」"+GetSexPhrase(" 真実へ、美男"," 真実へだよ、お嬢ちゃん")+"……そして同時に、それとはまったく違う場所でもあったのよ。もしそうだったら、私はもうとっくに死んでいたはずだわ。 ええ、私は彼の愛人だった。でも、家庭の揉め事を起こそうなんて思ったことは一度もなかったの\nすべてはもっと複雑だったのよ。ある日、彼が新しいおもちゃを見つけて、 私を手ぶらで捨てようと決めたことを知ったの。まるで不要品みたいに私を放り出すつもりだったのよ。でもね、 私は何も持たずに去るなんて性分じゃないの\nだから本当に価値のあるもの――彼の人生を破滅させる書類を手に入れて、新世界へ逃げたの。そして私は取引を持ちかけた。彼の秘密と引き換えに、 私の安全と十分な報酬を求めたのよ\nそれが私がまだ生きている理由――彼らはその書類を必要としている。そして私は、それがどこに隠されているかを急いで明かすつもりはなかったの。";
			link.l1 = "ふむ、お前は美しいだけじゃなく、まったく悪魔のように狡猾だな。大胆に勝負したが、正直に言おう――この勝負はもうお前の手を離れているぜ。まだ抜け出すチャンスがあるうちに、別の道を考えたほうがいいんじゃねえか？ ここで見つかったなら、他の場所に隠れても無駄だろう。遅かれ早かれ、お前の運も尽きるさ。";
			link.l1.go = "BetsiPrice_5";
		break;

		case "BetsiPrice_5":
			dialog.text = "何を言ってるんだ？ただあいつに書類を渡して、俺は手ぶらで帰れってのか？ここまで苦労してきたのに？";
			link.l1 = "お前も分かってるだろうが、奴らにとってお前は排除すべき厄介者でしかないんだ。 奴らは欲しいものを手に入れるまで絶対に止まらねえ。\nだが、まだ選択肢はある。あそこにいる間抜けに書類を渡せ。そいつがご主人様に届けて、 お前がもう諦めて全部終わらせたいと伝えさせるんだ。";
			link.l1.go = "BetsiPrice_6";
		break;

		case "BetsiPrice_6":
			dialog.text = "それが私の唯一のチャンスなら……わかったわ、覚悟はできてる。書類はずっと手元に持っていたの。片時も離れたくなくて、 コルセットに縫い込んでおいたのよ。ちょっと待ってて……";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_7";
		break;

		case "BetsiPrice_7":
			dialog.text = "ほら、持っていけ。これが俺の持っていた書類のすべてだ。\nあの化け物に別れの言葉をかけてくれないか？\nお前なら説得の仕方は分かってるだろう？";
			link.l1 = "奴はもう主な教訓を学んだと思うぜ。あとは何をすべきか、はっきり教えてやるだけだな。";
			link.l1.go = "exit";
			notification(StringFromKey("Neutral_15"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
			AddDialogExitQuestFunction("TBP_HouseBetsi_11");
		break;
		
		case "Pirate_6":
			dialog.text = "...";
			link.l1 = "立て。よく聞け、この野郎。お前が取りに来た書類だ。これを主人に持っていけ、そして伝えろ――もしベッツィにまた刺客を差し向けるなら、お前の仲間と同じ運命を辿ることになるとな。 彼女はもう二度とあいつの人生に関わらない――だから、もう追う理由はない。これは彼女自身が和解のために踏み出した一歩だと受け取れ。これで全て終わることを、 あいつが分別ある人間だと信じたいものだ。全部理解できたか、それとも頭に叩き込んでやらなきゃ分からねえか？";
			link.l1.go = "Pirate_7";
			notification(StringFromKey("Neutral_16"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
		break;

		case "Pirate_7":
			dialog.text = "「全て理解した」 "+GetAddress_Form(NPChar)+"...";
			link.l1 = "だったらさっさと出て行け。ここに居座るなんて考えるなよ――もう一度見かけたら、次は容赦しねえからな。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_12");
		break;

		case "BetsiPrice_8":
			dialog.text = "「さて、」 "+GetSexPhrase("俺の英雄","俺の怒り")+"……お礼を言うのも忘れてしまったようだ……興奮のせいだよ。捕虜になって、しかもこんな勇敢な者のおかげで自由を取り戻せるなんて、 そうそうあることじゃないからな\n "+GetSexPhrase("救助者","救助者")+"。ねえ、教えてくれない？困っている女性を助けるのがあんたの癖なのかしら、それとも私がものすごく運がいいだけ？";
			link.l1 = "何と言えばいいかな、ベッツィ、俺は派手な登場が好きでさ、それに\n "+GetSexPhrase("美しい女性たち","あらゆる冒険")+".";
			link.l1.go = "BetsiPrice_9";
		break;

		case "BetsiPrice_9":
			dialog.text = "私の名前はミランダ。ミランダ・ベルよ。姿を消す必要があった時、ベッツィという名を名乗った――新しい人生には新しい名前、わかるでしょ。ヨーロッパから逃げる時はあまりにも急いでいて、 ほんの少しのコインと宝石をいくつか掴んだだけ\n残りはきっと、私を追っていたあのろくでなしどもに渡ったんでしょうね。今じゃ豪華な宴や高価なドレスの代わりに、 町外れのみすぼらしい小屋と酒場の仕事よ。まさかいつか、 良い仲間とワインを味わう代わりにラムを給仕する日が来るなんて、思いもしなかったわ……";
			link.l1 = "これだけのことがあっても、お前はまるで運命を手中に収めているように見えるぜ。もしかすると、 それこそがお前の本当の才覚なのかもしれねえな。";
			link.l1.go = "BetsiPrice_10";
		break;

		case "BetsiPrice_10":
			dialog.text = ""+GetSexPhrase("お世辞だな。でもな、お前にはよく似合ってるぜ","お世辞だな")+"…こんなことがあった後だから、なんだか落ち着かないんだ。もしもう角のあたりで待ち伏せされてたらどうしよう？ 家まで送ってくれ、私の\n "+GetSexPhrase("救世主","救いの女神")+" 「もう少しの間だけ。」";
			link.l1 = "俺は物事を中途半端にするのは性に合わねえ。だから、奥さん、俺が力になるぜ。行こう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma");
		break;

		case "BetsiPrice_11":
			dialog.text = "着いたな。ところで、お前がどういう風の吹き回しであの家に来たのか、俺はまだ聞いてなかったぜ？";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulonOtdatBetsy") && pchar.questTemp.TBP_BuyKulonOtdatBetsy == true)
            {
			link.l2 = "偶然そこにいたわけじゃない。このペンダントが俺を導いたんだ。受け取ってくれ。\n酒場の主人はお前がいなくなったことで本気で動揺していて、何があったのか調べてくれと頼まれたんだ。\nまあ、断る選択肢なんてあったか？困っているご婦人を見捨てるなんて、船長の名折れだぜ。";
			link.l2.go = "BetsiPrice_12_otdal_kulon";
			}
			else
			{
			link.l1 = "俺がそこにいたのは偶然じゃねえ。酒場の主人があんたの失踪に本気で動揺してて、 何があったのか調べてくれって頼まれたんだ。さて、断る選択肢なんて俺にあったか？困ってるご婦人を見捨てるなんて、 船長の名折れだぜ。";
			link.l1.go = "BetsiPrice_12";
			}
		break;
		
		case "BetsiPrice_12":
			dialog.text = "ああ、それは本当に高潔ですね、+pchar.name+船長 "+pchar.name+"！でも、酒場の主人は俺のことより自分の儲けの方が気になってたに違いねえよ。残念だけど、 今日は中に招待できねえんだ――ちょっと休まなきゃな。地下室で過ごした時間で、俺が美しくなったわけでもねえしな。\nでも、もしもう一度会えなかったら――絶対に許さねえからな。だから明日、酒場に来いよ。お前に……プレゼントを用意しておくぜ。";
			link.l1 = "さて、これでまた寄る理由ができたな。じゃあな、ミ…ベッツィ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
		break;
		
		case "BetsiPrice_12_otdal_kulon":
			dialog.text = "ああ、それは本当に高貴ですね、船長 "+pchar.name+"！でも、酒場の主人は俺のことよりも自分の儲けの方が気になってたに違いねえよ。残念だけど、 今日は中に招待できねえんだ――ちょっと休まなきゃな。地下室で過ごした時間じゃ、俺が美しくなるわけもねえしな。だが、もしもう会えなかったら――絶対に許さねえからな。だから明日、酒場に来いよ。……お前に贈り物を用意しておくぜ。\n";
			link.l1 = "さて、これでまた立ち寄る理由が増えたな。じゃあな、ミ…ベッツィ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
			TakeItemFromCharacter(pchar, "jewelry24");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "TBP_Helena_1":
			dialog.text = "ほうほう……なんて甘い別れだ。そこのみすぼらしい女は誰だ？まるで一週間も地下室に閉じ込められてたみたいな格好じゃねえか。 それでもお前は目で食い尽くしてやがったんだろう、違うか、 "+pchar.name+"?";
			link.l1 = "お前が思ってるようなことじゃねえ。あの娘は困った状況に陥ってて、俺が助けてやっただけだ。それだけさ。";
			link.l1.go = "TBP_Helena_2";
		break;

		case "TBP_Helena_2":
			dialog.text = "「それで、もちろんお前は彼女の白馬の騎士になると決めたんだな？」";
			link.l1 = "誰かが危険な目に遭っている時、俺は傍観なんてできねえんだ。";
			link.l1.go = "TBP_Helena_3";
		break;

		case "TBP_Helena_3":
			dialog.text = "いいだろう。しかし次は、 "+pchar.name+"……もっと気をつけてくれ……そして俺に嫉妬する理由を作らないでくれよ。";
			link.l1 = "もちろんよ、あなた。ここを出ましょう、まだやることがたくさんあるわ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;

		case "TBP_Mary_1":
			dialog.text = "ほうほう……なんて甘い別れだ。そんなに気を遣って、優しい約束までして……しかもあんなに親しげに名前を呼んでやがる、いいじゃねえか。\n俺も何日か姿を消してみようかな、そしたらお前も同じくらい必死に俺を探してくれるのか？";
			link.l1 = "メアリー、お前が俺のお守りだって知ってるだろ。あいつは……ただトラブルに巻き込まれた娘にすぎねえんだ。";
			link.l1.go = "TBP_Mary_2";
		break;

		case "TBP_Mary_2":
			dialog.text = "ああ、もちろんだよ！ただの騎士を求める哀れな娘ってわけか！それにお前のその目つき――あれも礼儀からか？目で彼女を脱がせるところだったじゃねえか！";
			link.l1 = "メアリー、大げさだぜ！俺がどんな目でお前を見てるか、よく見てみろよ？違いが分かるだろ？それとも……近くで思い出させてやらなきゃいけねえか？";
			link.l1.go = "TBP_Mary_3";
		break;

		case "TBP_Mary_3":
			dialog.text = "「よし、」 "+pchar.name+"、今回はうまく切り抜けたな。しかし、またこんな場面を見かけたら……";
			link.l1 = "それなら、俺の心の中で一番で唯一の存在が誰か、もう一度思い出させてやらなきゃな。\nさあ、愛しい人、まだやることがたくさんあるんだぜ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;
		
		case "BetsiPrice_sex_1":

			switch (rand(1))
			{
				case 0:
					dialog.text = "んん……君がこんなに近くにいると、俺の頭の中でどんな考えが渦巻いてるか想像もつかないだろうな……そして、それを現実にしたくてたまらないんだ。";
					link.l1 = "だったら、考えてるだけじゃなくて……全部、俺に見せてみろよ。";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "ああ、わたくしの愛しい人"+GetSexPhrase("","")+"…君がそばにいると、自分を抑えるのがどれほど大変か、君には分からないだろう…";
					link.l1 = "では、この甘い拷問はもう十分だ……私のもとへ来て……";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_3");
		break;

		case "BetsiPrice_sex_2":
			switch (rand(1))
			{
				case 0:
					dialog.text = "「あっ、」 "+GetSexPhrase("私の愛しい船長","「愛しい人」 "+pchar.name+"")+"…俺はいまだにこの甘い狂気に囚われているんだ。";
					link.l1 = "この狂気は覚えておく価値があるかもしれねえ……いや、いつかまた繰り返すのも悪くねえな。";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "「ああ、」 "+pchar.name+"…俺が「すごかった」と言っても、調子に乗るんじゃねえぞ"+GetSexPhrase("、だろう？","……してくれるか？")+"?";
					link.l1 = "もう一度……今度は耳元でささやいてくれるって約束してくれるなら、いいわ。";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_7");
		break;

		
		
		
		
		
		
		
	}
}