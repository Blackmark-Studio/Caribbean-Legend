// Addon-2016 Jason, французские миниквесты (ФМК) Порт-о-Пренс
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
			link.l1 = "ああ、そうするさ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "officer":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "ここで一体何が起きているんだ、旦那方？戦いの音が聞こえたぞ。";
			link.l1 = "「おい、役人さん、女の悲鳴が聞こえてきて……」";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_2":
			dialog.text = "";
			link.l1 = ""+GetFullName(pchar)+"。船長 "+GetFullName(pchar)+".";
			link.l1.go = "officer_3";
		break;
		
		case "officer_3":
			dialog.text = "今のところは自由にしていいぞ、船長。ここで何が起きたかは分かっている。何か質問があれば呼び出すからな。";
			link.l1 = "「よし…」";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "ここで一体何が起きているんだ、旦那方？喧嘩の音が聞こえたぞ。";
			link.l1 = "ふう……役人さん、俺は酒場の女中に頼まれてここに来たんだ――誰かが殺されてるって言うから来てみたら、本当だった――あの二人の悪党がこのご立派な旦那を襲ったんだ。残念ながら、助けられなかったよ。 あの野郎どもがとどめを刺しやがった。";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			dialog.text = "ちくしょう……あいつはスペイン野郎じゃねえか！なんでここにいるんだ？ふん。それで、お前は何者だ、 "+GetAddress_Form(NPChar)+"?";
			link.l1 = ""+GetFullName(pchar)+"。船長 "+GetFullName(pchar)+".";
			link.l1.go = "officer_7";
		break;
		
		case "officer_7":
			dialog.text = "船長、今のところは自由にしていいぜ。あんたの証言は目撃者の話と合ってる。必要があればまた呼ぶからな。";
			link.l1 = "……よかろう……";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
		break;
		
		case "noble":
			dialog.text = "すべて説明させてください、役人殿！ 私はサントドミンゴから来たドン・ドミンゴ・オルティス・アルバラーテでございます。 若いご婦人のお招きでポルトープランスに参りました。お会いするまでの間、酒場に滞在しておりました。しかし、 二時間も経たぬうちに、二人の呪われた悪党どもが私の部屋に押し入ってきたのです。もしもあの時、 間一髪の助けがなければ\n "+GetSexPhrase("現れたこの親切な旦那","現れたこの美しいセニョリータ")+"、俺は本当にひどい目に遭っていただろう。";
			link.l1 = "ドン・ドミンゴ・オルティス・アルバラテ？スペイン人か？";
			link.l1.go = "noble_1";
		break;
		
		case "noble_1":
			dialog.text = "レイ・フェリペ本人と同じくらいスペイン人だぜ、はっ！それに、 俺の書類はちゃんと整ってるってことも言っておきたい。俺はエスパーニャの貴族であって、 汚ねえ海賊なんかじゃねえぞ！";
			link.l1 = "ドン・ドミンゴ、今回の不運な出来事につきまして心よりお詫び申し上げます！ どうかご一緒に衛兵詰所までお越しください、いくつか質問とワインをご用意しております。 すべてこちらで対処いたします。さて、あなたは…";
			link.l1.go = "noble_2";
		break;
		
		case "noble_2":
			DialogExit();
			sld = CharacterFromID("FMQP_off");
			sld.Dialog.currentnode = "officer_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "noble_3":
			PlaySound("Voice\English\LE\Domingo\Domingo_01.wav");
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" 「船長！」 "+UpperFirst(GetAddress_Form(NPChar))+" 船長！サンティアゴと聖母マリアに誓って、あなたは高貴な方だ。カスティーリャの真の息子は、 必ずその高貴さに報いるものだ！ここでの用事が済んだら、ぜひあなたにも報いたいと思う。どうか、 サントドミンゴの私のつましい家にお越しくだされ！街の門のすぐ近くだ。ご馳走を用意してお待ちしているぞ。\n "+GetSexPhrase("俺の親友","「俺の命の恩人」")+"！俺の名を覚えとけ、ドン・ドミンゴ・オルティス・アルバラーテだ！";
			link.l1 = "...";
			link.l1.go = "noble_4";
		break;
		
		case "noble_4":
			DialogExit();
			AddMapQuestMarkCity("santodomingo", true);
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "FMQP_AfterFightInTown");
		break;
		
		case "noble_5":
			dialog.text = "Captain "+pchar.lastname+"？！おお、マドレ・デ・ディオス！なんてこった！これは大虐殺じゃねえか！ここで何があったんだ、 "+GetSexPhrase("俺のいい友達","「俺の命の恩人」")+"「？こいつらは誰だ？」";
			link.l1 = "お会いできて嬉しいです、ドン・ドミンゴ。\nこいつらは……いや、今日はあなたに挨拶しに来たんだ。\nあそこにいる奴が見えるか？あれがウーゴ、あなたの召使いで、そいつは……";
			link.l1.go = "noble_6";
		break;
		
		case "noble_6":
			dialog.text = "うごっ？！ああ、騙されたんだな、船長！";
			link.l1 = "なるほどな、俺にはよくあることだぜ。三人の悪党があんたの家に押し入り、忠実な男ウーゴを殺した――上の階で彼の死体はもう見つけた――それからあんたを待ち伏せしようとしたんだ。俺が来たのは奴らの計画外だった。だが、 奴らは俺との対面を生き延びられなかったぜ。";
			link.l1.go = "noble_7";
		break;
		
		case "noble_7":
			dialog.text = "サンタ・マリア、オラ・プロ・ノビス！お前の剣さばきはトレドの剣術師範みたいだ！お前が味方でよかったぜ！ああ、 かわいそうなウーゴ！子供の頃から俺を育ててくれたのに、今や……マルディタス・カナージャスに殺されるなんて！";
			link.l1 = "ドン・ドミンゴ、どうやらまだ危険から抜け出せていないようだな。お前の部下のウーゴが何か知っていたらしい。 このメモを読んでみろ。テーブルの上で見つけたんだ。";
			link.l1.go = "noble_8";
		break;
		
		case "noble_8":
			ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
			RemoveItems(pchar, "letter_parol", 1);
			dialog.text = "渡してくれ……（読む）そんなはずは……ああ、なんてこった！信じられねえ！ルイスおじさん……でも……";
			link.l1 = "「誰がやったか、何か手がかりはあるか？」";
			link.l1.go = "noble_9";
		break;
		
		case "noble_9":
			dialog.text = "「ただ疑いだけだ……恐ろしい疑いがな」 "+GetSexPhrase("俺のいい友達","「俺の命の恩人」")+"「！どうして俺のおふくろの兄貴がそんなことをしやがったんだ？」";
			link.l1 = "俺にも事情を教えてくれないか？すまないな、ドン・ドミンゴ。でも俺の経験じゃ、 親族ってのは男にとって一番厄介な敵になることが多いんだよ……";
			link.l1.go = "noble_10";
		break;
		
		case "noble_10":
			dialog.text = "「そうだ、あんたの言う通りだ」 "+GetAddress_Form(NPChar)+"！全部話すよ！お前はもう二度も俺を助けてくれたし、今はお前だけが頼りになりそうだ！\nでも、こんなひどい場所はもう出ようぜ、気分が悪くなる。\nこの騒ぎについてアルカルデに知らせなきゃならねえし、ウーゴのこともきっと面倒見てくれるさ。\nそれより、地元のタベルナでワインでも飲んで、少し落ち着かないか？";
			link.l1 = "お前の方がよっぽど神経が参ってるみたいだな、案内してくれ、旦那！";
			link.l1.go = "noble_11";
		break;
		
		case "noble_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Santodomingo_tavern", "sit", "sit_base2", "FMQP_InSantoDomingoTavern");
		break;
		
		case "noble_12":
			LAi_SetSitType(pchar);
			dialog.text = "さて、友よ、俺の家族の歴史を……まあ、かいつまんで話させてもらうぜ。母のドーニャ・イサベラ・オルティスは、 父であるマルケス・リカルド・アルバラーテと結婚し、慣習に従って父の姓を名乗った。 母の兄であるルイス・オルティスは植民地の駐屯地司令官だったが、母の結婚後、 父の推薦でポルトベロ近くの砂糖プランテーションの管理人に任命されたんだ\nそれは広大で裕福なプランテーションで、本当に儲かる土地だった。数年前、両親が海で悲劇的な死を遂げた後、 俺は一人息子としてすべてを相続した。プランテーションも含めてな。叔父はそのまま管理人を続け、 俺は彼からの家賃で十分満足していた。支払いもいつもきっちりしてくれていたよ。";
			link.l1 = "「それで、自分のおじさんが…」";
			link.l1.go = "noble_13";
		break;
		
		case "noble_13":
			dialog.text = "ああ。今のところ、あいつはただの借り主だ。農園の持ち主は俺で、あいつじゃねえ。\nだがな！もし俺に何かあったら――農園はあいつのものになるぜ。";
			link.l1 = "なあ、ドミンゴ、俺はな、それよりずっとしょぼい賞金のために、親族を皆殺しにするような奴らを知ってるぜ。";
			link.l1.go = "noble_14";
		break;
		
		case "noble_14":
			dialog.text = "もっとまともな連中と付き合うべきだよ、カルロス。親愛なるウーゴが、最後の手紙で伯父の書類について触れていた……これは直接的な手がかりだわ。ああ、こんなこと信じたくない！でも……スペインに住んでいる従妹のマルガリータ・オルティスが、最近婚約したの。それが原因かしら、\n "+GetAddress_Form(NPChar)+" 船長か？";
			link.l1 = "可愛い甥っ子のために、うちの叔父貴が急に金を必要とするかもしれねえぞ……";
			link.l1.go = "noble_15";
		break;
		
		case "noble_15":
			dialog.text = "金だと？！もちろんだが……だが侯爵の称号も忘れるな！それがあれば、いとこは将来の夫にふさわしい相手になるんだ！イエス・クリスト！ 俺はなんて馬鹿だったんだ！";
			link.l1 = "その貴族の称号は、砂糖農園よりも価値があるぜ。";
			link.l1.go = "noble_16";
		break;
		
		case "noble_16":
			dialog.text = "ちょっと待て！今思い出したが、これが俺の命を狙われた最初の出来事じゃなかったんだ！数週間前、 通りで物乞いと遭遇したんだよ！酔っ払ったカナージャが俺に無礼を働きやがって、無視できなかったんだ。そいつ、 腕の立つ剣士だったぜ。剣を抜いてきて、俺が仕留める前にレイピアで俺を傷つけることまでやりやがった。";
			link.l1 = "「で、どうしてお前はポルトープランスの酒場にいるんだよ？若いセニョリータの話をしてたよな？」";
			link.l1.go = "noble_17";
		break;
		
		case "noble_17":
			dialog.text = "（顔を赤らめて）旦那…はい、船長、現場には若くて綺麗なセニョリータがいました…今になって、あれが罠の囮だったと分かりました。くそっ、どこもかしこもろくでなしばかりで、誰も信用できねえ！ かわいそうなウーゴ…もう死んじまった。";
			link.l1 = "どうにかしたほうがいいぞ、ドミンゴ。スペインに逃げるってのはどうだ？";
			link.l1.go = "noble_18";
		break;
		
		case "noble_18":
			dialog.text = "スペインへ？あの悪党に私のプランテーションを渡して行けと？船長、私はドミンゴ・オルティス・アルバラテ侯爵だぞ！ ";
			link.l1 = "しかし……";
			link.l1.go = "noble_19";
		break;
		
		case "noble_19":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"、お願いしてもよろしいでしょうか？ウーゴが死んでしまい、私のそばに信頼できる者が誰もいません。 あなたはすでに二度も私を救ってくれました！二度もです！私はあなたに大きな借りがありますし、 永遠に恩義を感じています。それなのに、さらにもう一つお願いをするとは厚かましいと思います。聖母マリアに誓って、 必ずあなたに報いると約束します！";
			if (startHeroType == 2)  
			{
				link.l1 = "「ご用件は何でしょうか」 "+npchar.name+"?";
				link.l1.go = "noble_20";
			}
			else
			{
				link.l1 = "よし、スペイン人にしてはいい奴だな。どうした、ドミンゴ？何か用か？";
				link.l1.go = "noble_20";
			}
			
		break;
		
		case "noble_20":
			dialog.text = "ポルトベロの俺のプランテーションへ行こうぜ！今、俺の叔父はカルタヘナにいるはずだ。 ウーゴが何か書類のことを言ってたから、ドン・ルイス・オルティスの帳簿や文書を調べてみよう！ あいつの汚い陰謀を暴く手がかりが見つかるかもしれねえ。ポルトベロまでは結構距離があるが、 航海の報酬はきっちり払うからな！\n";
			link.l1 = "この段階であなたを拒むなんて馬鹿げてるよ、ドン・ドミンゴ。もう引き返せないところまで来ちまったんだ。";
			link.l1.go = "noble_21";
		break;
		
		case "noble_21":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "神に感謝だ、助けてくれると信じてたぜ、相棒！ほら、 ポルトベロまでの航海の報酬としてこの二万ペソを受け取ってくれ。\nいつ出航する？カタヘナから叔父が戻る前に急がなきゃならねえ！";
			link.l1 = "じゃあ、ぐずぐずしてる暇はねえぜ。";
			if (startHeroType != 2 && CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 20 && GetNationRelation2MainCharacter(SPAIN) == RELATION_NEUTRAL) {link.l1.go = "noble_22";}
			else {link.l1.go = "noble_22x";}
		break;
		
		case "noble_22x":
			GiveNationLicence(HOLLAND, 20);
			dialog.text = "ほら、オランダ西インド会社の許可証だ。二十日間の有効期限があるから、ここにお前の名前を書き込んでおくぜ。よし、 できた。これでコスタ・ガルダとの面倒は避けられるはずだ。";
			link.l1 = "「素晴らしいぜ！」";
			link.l1.go = "noble_22";
		break;
		
		case "noble_22":
			dialog.text = "「今はお前の船に乗ってもいいのか、船長？」";
			link.l1 = "ありがたく思えよ、お前は名誉ある客人だぜ。\n風向きが良くなり次第、すぐに出航するからな。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_OnBoard");
			AddMapQuestMarkCity("portobello", true);
		break;
		
		case "noble_23":
			dialog.text = "さて、Carlos船長、ここまで来たな。\nこれから叔父の家を探して、中に何があるか見てみようぜ。";
			link.l1 = "ドン・ドミンゴ、衛兵と何か揉め事が起きそうか？";
			link.l1.go = "noble_24";
		break;
		
		case "noble_24":
			dialog.text = "いや……ただ……ふむ。ルイスが奴らを俺に敵対させた可能性もあるな。いずれにせよ、用心に越したことはねえ。必要な家を探そうぜ。";
			link.l1 = "もう知ってるだろ？お前のプランテーションさ。";
			link.l1.go = "noble_25";
		break;
		
		case "noble_25":
			dialog.text = "ふむ……正直に言うと、前回来たときはまだ八歳だったんだ。だが、できるだけ早くその埋め合わせをするつもりだぜ！";
			link.l1 = "なるほどな。じゃあ探し始めようぜ。あんたの叔父さんの家はここで一番でかいはずだ。";
			link.l1.go = "noble_26";
		break;
		
		case "noble_26":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("FMQ_Portpax", "7");
		break;
		
		case "noble_27":
			dialog.text = "ここには何があるんだ、 "+GetAddress_Form(NPChar)+"?";
			link.l1 = "見てください、ドン・ドミンゴ。帳簿の記録のようですね。これは面白いかもしれません。";
			link.l1.go = "noble_28";
		break;
		
		case "noble_28":
			ChangeItemDescribe("Almanac", "itmdescr_Almanac");
			RemoveItems(pchar, "Almanac", 1);
			dialog.text = "（読みながら）ふむ……そうだな。これを見てくれ……あいカランバ！十万ペソだ！それにもう十五万ペソ！それから……（ページをめくりながら）ルイスおじさん！";
			link.l1 = "何か面白いことでもあるか？";
			link.l1.go = "noble_29";
		break;
		
		case "noble_29":
			dialog.text = "何か面白いことでもあるのか！俺の親愛なる叔父は、俺に言っていた額の五倍もの収入があったんだ！泥棒め！横領野郎！ ";
			link.l1 = "驚きはしねえよ。時々ちゃんと現状を自分で確かめねえと、誰にも全面的な信頼なんて置けねえもんだぜ。 それが常識ってやつさ。";
			link.l1.go = "noble_30";
		break;
		
		case "noble_30":
			dialog.text = "常識なんて、庶民には通じるかもしれんが、俺の育ちじゃそんな紳士の裏切りなんて思いもよらなかった！さすがだな、 カルロス、いつも正しい！俺の叔父が俺から盗みを働いていたとは！クソッ！これは俺の責任だが、必ず償う。 このプランテーションは俺のものだし、叔父は今日限りで職を解かれた！あいつはもう誰でもない！ 必ずキールホールにしてやる！";
			link.l1 = "ドン・ドミンゴ……お前の叔父上がそんな決断に反対するんじゃねえか？";
			link.l1.go = "noble_31";
		break;
		
		case "noble_31":
			dialog.text = "あいつが同意しようがしまいが、俺は知ったこっちゃねえ！俺はマルケス・ドミンゴ・オルティス・アルバラーテだ、 ルイス・オルティスなんざただの小作人、それも元小作人にすぎねえ！それに奴は……";
			link.l1 = "落ち着け、旦那。あんたはここじゃ見かけない顔だし、俺はフランス人だがオランダの許可で航海してる身だ。 しかもスペインの海賊取り締まり隊とはいろいろあってな……。\nそれに、あんたの叔父さんはこの町をほとんど牛耳ってる。衛兵や地元の総督のことを考えてみろよ。 本当にあんたの味方をしてくれると思うか？";
			link.l1.go = "noble_32";
		break;
		
		case "noble_32":
			dialog.text = "お前の指摘は剣のように鋭いな……たしかに……いや、違う。スペイン兵が貴族に手を出すなんて、絶対にありえねえ！叔父上が俺に挑みたいなら、 かかってこいってんだ！";
			link.l1 = "それでも、俺は別の道を勧めるぜ。法廷に行ってみたらどうだ？";
			link.l1.go = "noble_33";
		break;
		
		case "noble_33":
			dialog.text = "ははっ！カルロス、その通りだ。ちゃんとした役人に話をしに行こう。おじが密輸業者との取引について、 詳細を手帳に書き残したのは失敗だったな。奴らから奴隷を格安で買っていたんだ。この帳簿は俺たちに大いに役立つぜ。 あの野郎が地下牢にぶち込まれてる間は、俺に手出しできるはずがねえ。行くぞ！ポルトベロへ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PrepareUncle");
		break;
		
		case "noble_34":
			//PlaySound("Voice\English\LE\Domingo\Domingo_04.wav");
			dialog.text = "こんなのは汚らわしくて無礼な嘘にすぎん！どうしてあいつが俺の両親の名誉をあんな下劣な口で汚せるんだ！くそっ、 必ず報いを受けさせてやる！剣を抜け、この人殺しめ！";
			link.l1 = "";
			link.l1.go = "noble_35";
		break;
		
		case "noble_35":
			DialogExit();
			sld = CharacterFromID("FMQP_Uncle");
			sld.Dialog.currentnode = "uncle_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noble_36":
			PlaySound("Voice\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "ルイスおじさんの魂はしかるべき場所――地獄にいるさ…… "+pchar.name+"、お前は俺の守護天使に送られてきたんだな！この悪党の言葉を信じなくて本当に良かったぜ。正直なところ、 俺はお前が俺をここに一人残してこのカナージャと戦わせるんじゃないかと心配してたんだ\nああ "+GetAddress_Form(NPChar)+"、俺も完璧じゃねえが、だがこれは……俺が自分の親を殺すために海賊を雇ったなんて、こんな汚い嘘を！俺にこんなことの罪を着せるなんて……これをだ！ふん、ざまあみろってやつだな。";
			link.l1 = "無事に着いてよかったな、ドン・ドミンゴ。これからどうする？スペインの法律に引っかかってなきゃいいが。";
			link.l1.go = "noble_37";
		break;
		
		case "noble_37":
			dialog.text = "法だと？ははっ！違うぜ、 "+pchar.name+"「俺はこの立派な帳簿を見せてやるぜ、叔父貴の密輸の全てが記されてるんだ。 俺の命を狙った何度もの企みも忘れるなよ；ついさっきの最後の未遂の後には証人も山ほどいるんだ。心配すんな、」\n "+GetAddress_Form(NPChar)+"。ここは俺の町だ、みんなに見せつけてやる時だぜ！";
			link.l1 = "慎重に動いてください、旦那。亡くなったおじ上よりも、あなたのことを良く思わせるのです。";
			link.l1.go = "noble_38";
		break;
		
		case "noble_38":
			dialog.text = "それが作戦だぜ、船長。でも俺に逆らう奴には容赦しねえからな。心から感謝を伝えさせてもらうぜ、 "+pchar.name+"！どうぞ、酒場に行って休んでくれ、一杯か二杯やってこい。俺も一緒に飲みたいが、あんたの言う通りだ。 そろそろ賢くなって自分でプランテーションを管理する時だな。明日またここに来てくれ、船長！";
			link.l1 = "承知しました、ドン・ドミンゴ。また明日お会いしましょう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PlantatonPause");
		break;
		
		case "noble_39":
			DelLandQuestMark(npchar);
			PlaySound("VOICE\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "「ああ、ここにいたのか」 "+GetAddress_Form(NPChar)+"!";
			link.l1 = "ご機嫌いかがですか、ドン・ドミンゴ？ご自分のプランテーションの調子はどうですか？";
			link.l1.go = "noble_40";
		break;
		
		case "noble_40":
			dialog.text = "プランテーションは素晴らしいが、金の方はそうもいかない――なんと、親愛なる叔父が全財産をカルタヘナの銀行に移していたんだ。 金を取り戻すには弁護士たちの時間がかなりかかりそうだ。でも大丈夫、何とかしてみせるさ。落ち込むなよ、船長、 君の高潔さ、誠実さ、友情に報いる約束は必ず守るからな！";
			link.l1 = "俺があんたの味方として戦ってた時、報酬のことなんて考えたこともなかったぜ、旦那…";
			link.l1.go = "noble_41";
		break;
		
		case "noble_41":
			dialog.text = "それは知っているぜ、船長。それだけであんたの人柄がよく分かるってもんだ！善行には報いが必要だろう。だから、 今は金がないが、俺のプランテーションからあんたの船に商品を積み込むよう命じるつもりだ。コーヒーだよ、 しかも大量にな。きっと大きな利益になるはずだぜ。";
			link.l1 = "おお！こりゃいいな……";
			link.l1.go = "noble_42";
		break;
		
		case "noble_42":
			dialog.text = "さらに、俺には大した価値はないが、あんたみたいな船乗りにはとても貴重な品がいくつかあるんだ。 上等な望遠鏡とお守りが三つだ。どうぞ受け取ってくれ、今から全部あんたのものだぜ。\n";
			link.l1 = "感謝だぜ！";
			link.l1.go = "noble_43";
		break;
		
		case "noble_43":
			Log_Info("You have received a good spyglass");
			Log_Info("You have received three amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "最後に、私の計り知れない感謝の印として、このレイピアを贈ろう。\nこの剣は長い間、私に仕えてくれた。今度は君のために、もっと役立ってくれるはずだ。\nこの剣を見て、良きスペイン人の友、ドミンゴ・アルバラーテ侯爵を思い出してくれ！";
			link.l1 = "本当にありがとうございます、旦那！まさかこんなことになるとは……";
			link.l1.go = "noble_44";
		break;
		
		case "noble_44":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "さて、残念だが、ここでお別れを言わねばならん。\nポルトベロへ行って総督に会い、それからカルタヘナへ向かうつもりだ……\n要するに、気楽な暮らしは終わりだ。これからは大人として生きる時が来たってわけさ。";
			link.l1 = "ふうん、今はずいぶん賢くなったじゃねえか……";
			link.l1.go = "noble_45";
		break;
		
		case "noble_45":
			dialog.text = "「それは本当だ。楽しかったぜ。」 "+GetAddress_Form(NPChar)+"！たまには俺のところに遊びに来いよ。航海の無事を祈ってるぜ！";
			link.l1 = "ドン・ドミンゴ、あんたのプランテーション経営もうまくいくといいな！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_ReceiveReward");
		break;
		
		case "noble_46":
			PlaySound("Voice\English\YoungMan02.wav");
			dialog.text = "ええ、遅れちまったな、旦那！残念だが、俺の年老いた叔父貴はもう書類をきれいさっぱり片付けちまったよ。 誰かがサントドミンゴのことを教えやがって、用心したらしい……だが、これで終わりにするつもりはねえ！叔父貴を訴えるためにポルトベロの総督に会いに行くぜ。 もうあいつに俺の財産を好き勝手されるのはごめんだ。";
			link.l1 = "いい判断だ。";
			link.l1.go = "noble_47";
		break;
		
		case "noble_47":
			dialog.text = "ありがとう、船長！楽しかったぜ！感謝の印として俺のレイピアを贈るよ。こいつは俺によく仕えてくれたが、 今度はお前の役に立ってくれるだろう。これを見て、スペインの良き友——ドミンゴ・アルバラーテ侯爵を思い出してくれ！";
			link.l1 = "本当にありがとうございます、旦那！まさかこんなことになるとは……";
			link.l1.go = "noble_48";
		break;
		
		case "noble_48":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			dialog.text = "さて、残念だが、そろそろお別れしなきゃならねえ。\n俺はポルトベロへ行くつもりだ。\nお気楽な日々も終わりだ、大人として生きる時が来たってわけさ。\n海での幸運を祈ってるぜ！";
			link.l1 = "ドン・ドミンゴ、叔父さんとのこと、幸運を祈るぜ！きっとお前が勝つと信じてるぞ！";
			link.l1.go = "noble_49";
		break;
		
		case "noble_49":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 40.0);
			pchar.questTemp.FMQP = "fail";
			AddQuestRecord("FMQ_Portpax", "13");
			CloseQuestHeader("FMQ_Portpax");
			sld = &Locations[FindLocation("PortoBello_Plantation")];
			sld.soldiers = true;
		break;
		
		case "uncle":
			PlaySound("Voice\English\OliverTrast02.wav");
			if (pchar.sex == "woman") { dialog.text = "ちょうどいい時に着いたようだな。俺の手に負えない甥っ子と、その新しい恋人、船長 "+GetFullName(pchar)+"「……ああ、ああ、」 "+GetSexPhrase("若造","お嬢さん")+"、驚くなよ――お前のことをちょっと調べさせてもらったんだ。"; }
			else { dialog.text = "ちょうどいい時に着いたようだな。俺の手のかかる甥っ子と、その守護天使である船長よ\n "+GetFullName(pchar)+"「……ああ、ああ、」 "+GetSexPhrase("若造","お嬢さん")+"、驚くなよ――お前についてちょっと調べさせてもらったんだ。"; }
			link.l1 = "ルイス・オルティスか？";
			link.l1.go = "uncle_1";
		break;
		
		case "uncle_1":
			dialog.text = "その通りだ、船長。しかし他のことは全部間違っている。他人の家族の問題に首を突っ込むべきじゃねえ。 お前が守ってる相手がどんな奴か、全然分かってねえんだ。俺の放蕩甥っ子ドミンゴはどうしようもないろくでなしで、 どこの酒場や売春宿にも顔を出す常連、見かけた女は片っ端から寝ようとするか、少なくとも口説こうとする。 家賃は毎月俺が払ってやってるのに、あいつは数日で使い果たして、いつももっともっととせがんでくる。 何度も何度もだ。あいつの恥知らずな振る舞いが、母親――つまり俺の妹――を狂わせちまったんだ。\n噂で聞いたが、あの悪党はイギリスの私掠船を雇って指示し、リカルド・アルバラーテ侯爵の船を沈めさせたらしい。 その船には立派な侯爵と、俺の大切な妹も乗っていた。ドミンゴは家の金が欲しくて、殺しまでやるような奴だ……残念ながら、こいつを絞首台に送るだけの証拠を掘り出すことはできなかった。";
			link.l1 = "";
			link.l1.go = "uncle_2";
		break;
		
		case "uncle_2":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_34";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "uncle_3":
			if (pchar.sex == "woman") { dialog.text = "「私の可愛い甥っ子は、いつも通り自分の世界に浸っているな。騒がしくて、剣がぶつかる音やグラスの鳴る音ばかりで、 中身はほとんどない。\nあんたが彼のどこに惹かれるのか、旦那、私には分からんよ、彼は……」"; }
			else { dialog.text = "わたくしの可愛い甥は、いつも通り自分の世界に浸っておりますわ。騒がしいこと、 剣のぶつかる音やグラスの鳴る音ばかりで、中身はほとんどありませんの。どうしてあなたが、 あんな価値のない小僧を助けようと思ったのか、わたくしには理解できませんわ……"; }
			link.l1 = "俺の理解だと、甥っ子に対する証拠を掘り出せなかったから、今度は刺客を送り込んだってわけか。\n普通に訴訟でも十分だったんじゃねえか。";
			link.l1.go = "uncle_4";
		break;
		
		case "uncle_4":
			dialog.text = "嘘をつくな。ここにいるドミンゴは、数え切れないほど敵を作ってきたんだぜ。捨てられた恋人や寝取られた旦那どもが、 あいつの後ろには山ほどいる。どうやって今まで生き延びてきたのか不思議なくらいだ！\nあいつに聞いてみろよ、今までいくつの結婚式をぶち壊した？何人の怒った婚約者を傷つけたり殺したりしたんだ？";
			link.l1 = "彼の召使ウーゴ……";
			link.l1.go = "uncle_5";
		break;
		
		case "uncle_5":
			dialog.text = "ああ、ウーゴ！奴は一番の悪党だ！ウーゴは自分の放蕩主人を心から慕っていた。主人の悪事なんて、 ウーゴにとっちゃ子供のいたずらみたいなもんさ。覚えておけ、 "+GetSexPhrase("若造","お嬢さん")+"「家業は家族だけのものだ。他人が首を突っ込んだり詮索したりすれば、痛い目を見ることになるぜ。」";
			link.l1 = "今度は俺を脅すつもりか。";
			link.l1.go = "uncle_6";
		break;
		
		case "uncle_6":
			int icpy = GetOfficersQuantity(pchar);
			iTotalTemp = 10000+10000*icpy;
			dialog.text = "警告だ。聞け、船長： "+GetSexPhrase("やりすぎだが、 ","")+"俺はお前を敵だとは思っちゃいねえ――ただ道を誤った奴だと見てるだけだ。だから提案がある。引き返して立ち去れ。血を流したくねえんだ。\n家族の揉め事はお前抜きで片付けるぜ。 "+GetSexPhrase("甥に関わる費用については、俺がすべて補償する用意があるぜ：","楽にしてやるために、俺はお前に金を払う用意があるぜ：")+" "+FindRussianMoneyString(iTotalTemp)+" 現金だ。受け取ってさっさとここを忘れろ。さもないと、俺の護衛たちがお前を殺すだけだぞ。";
			link.l1 = "「家族が一番」ってのが俺の口癖さ。じゃあ俺には関係ねえな、金を渡して「ブエン・カミーノ」だ。";
			link.l1.go = "uncle_7";
			link.l2 = "お前の話は自分のプランテーションの肥料よりも臭うぜ。ドン・ドミンゴは聖人じゃねえかもしれねえが、 あんたは悪魔だ、旦那！";
			link.l2.go = "uncle_8";
		break;
		
		case "uncle_7":
			AddMoneyToCharacter(pchar, iTotalTemp);
			dialog.text = "あんたが分別のある男だって分かってたぜ。金を持ってさっさと行きな、カピタン。\n今後は他人の汚い下着を漁るのはやめとけよ――誰も感謝なんかしねえからな。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_UncleExit");
		break;
		
		case "uncle_8":
			if (pchar.sex == "woman") {dialog.text = "なるほどな。お前は俺の甥っ子とそっくりだ――愚かで向こう見ずな娘だな。あいつにはぴったりの相手だ。二人まとめて痛い目に遭わせてやるぞ！";}
			else {dialog.text = "なるほどな。お前も俺の甥っ子と同じだな――愚かで思い上がったガキめ！両方まとめて痛い目にあわせてやるぜ！";}
			link.l1.go = "exit";
			AddDialogExitQuest("FMQP_UncleFight");
		break;
		
		case "ugo":
			pchar.quest.FMQP_SantoDomingoOver.over = "yes";
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = TimeGreeting()+" "+GetAddress_Form(NPChar)+"。どういたしましょうか？";
			link.l1 = "ごきげんよう。失礼しますが、ここはドミンゴ・アルバラテ旦那のお宅でしょうか？";
			link.l1.go = "ugo_1";
		break;
		
		case "ugo_1":
			dialog.text = "ああ、ここがアルバラーテ家だ。質素だが居心地は悪くねえ。俺の名はウーゴ、若旦那に仕えてる。あんた、 あの方に用があって来たのか？";
			link.l1 = "ああ、旦那。ドン・ドミンゴが少し前に俺を自分の屋敷に招いてくれたんだ。説得力がすごかったぜ。 会わせてもらえるか？";
			link.l1.go = "ugo_2";
		break;
		
		case "ugo_2":
			dialog.text = "ああ、親愛なる "+GetSexPhrase("旦那","お嬢さん")+"「ドン・ドミンゴは今家におりません。正直なところ、あのやんちゃ坊主――いや、失礼、若い旦那がどこにいるのか私も知りたいくらいでして……。それで、彼に何かご用でしょうか？」";
			link.l1 = "そうだな……偶然ドン・ドミンゴを助けたんだ。ポルトープランスの酒場で、あいつは二人の悪党に襲われていた。 俺は旦那のご主人が自分を守るのを手伝ったんだよ、あの……なんて呼んでたっけな……マルディータ・カナージャとかいう連中からな。 ドン・ドミンゴは調査が終わったらここに来てくれと俺を招待してくれた。もうすべて片付いていると思ってたから、 家で会えるものだと期待してたんだ。";
			link.l1.go = "ugo_3";
		break;
		
		case "ugo_3":
			dialog.text = "マドレ・デ・ディオス！なんて恐ろしい話をしているんだ！すぐに司令官に会わなきゃ――ドン・ドミンゴが今まさに直面している危険について警告しないと！ "+UpperFirst(GetAddress_Form(NPChar))+"、お前は行かなくちゃならねえし、俺も急がなきゃな！";
			link.l1 = "落ち着け、ウーゴ。坊ちゃんは無事だ。書類もちゃんと揃ってるって本人が言ってたし、もう解放されるはずだったんだ。 だから俺がここに来たんだよ。すぐに会えるはずだぜ。";
			link.l1.go = "ugo_4";
		break;
		
		case "ugo_4":
			dialog.text = "おお！どうしてそんなことを！？あの世間知らずの坊やが――しかもカエル食いのフランス野郎どもの手に！？命を狙う盗賊どもまでいるってのに？いや、 絶対に司令官に会わねばならん！ "+UpperFirst(GetAddress_Form(NPChar))+"、どうぞ行ってください！";
			link.l1 = "わかった、わかった、そんなに急かすなよ。もう行くぜ。";
			link.l1.go = "ugo_exit";
			link.l2 = "旦那、なんでそんなに緊張してるんだ？もう言っただろう、あんたのご主人には危険はないって。ここにいさせてくれ、 ドミンゴ旦那が来るのを待ちたいんだ。長旅でくたくたなんだよ、あんたのもてなしにあずかれるとありがたい。 冷たい水と、潮風で渇いた喉を流せる熱い風呂が欲しいね。\nそれが済んだら、あんたは地元の守備隊に行って好きにすればいいさ。";
			link.l2.go = "ugo_5";
		break;
		
		case "ugo_exit":
			DialogExit();
			LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "houseSp4", "FMQP_SDMFail");
		break;
		
		case "ugo_5":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"「今すぐこの家を出て行け！」";
			link.l1 = "ウーゴ、召使いが紳士のお客様にこんな口の利き方をしていいとは到底思えませんわ。ドン・ドミンゴも、 自分の命を救った方に対してこんな扱いをするのをお許しになるとは思えません！";
			link.l1.go = "ugo_6";
		break;
		
		case "ugo_6":
			dialog.text = "「ほう、そうか？（上に向かって叫ぶ）おい野郎ども、降りてこい、問題発生だ！」";
			link.l1 = "なんだと！？";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_SantoDomingoFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
