// полковник Фокс - бравый командир морской пехоты 'морские лисы'.
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
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyReward"))
			{
				dialog.text = "ご用件は何ですか、旦那？ああ…まさか！お待ちください！あなたは、 ルヴァスールの手下どもの汚い手から私の娘を救ってくださったフランスの船長ではありませんか！ ";
				link.l1 = "キャサリンがすでに私のことをあなたに話したようですね……";
				link.l1.go = "terrapin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Usurer") && !CheckAttribute(npchar, "quest.utensil"))
			{
				dialog.text = "何のご用ですか、旦那？";
				link.l1 = "ごきげんよう、大佐。少々「特別」な用件で参りました。少しお時間をいただけませんか？";
				link.l1.go = "guardoftruth";
				break;
			}
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "eng_reward")
			{
				dialog.text = "私の記憶が正しければ、あなたは "+GetSexPhrase("船長","女船長")+" シント・マールテンで私の部下たちの任務遂行を手伝った者は誰だ？ "+TimeGreeting()+"!";
				link.l1 = TimeGreeting()+"「はい、大佐。それは私でございます。」";
				link.l1.go = "FMQN";
				break;
			}
			dialog.text = "何の御用ですか、旦那？";
			link.l1 = "「何もありません、大佐。これで失礼いたします。」";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guardoftruth":
			dialog.text = "ここまで来たんだ、さっさと言えよ……";
			link.l1 = "最近、オランダの海賊ローリー・ザ・キャップの指揮するスクーナー船に乗り込んで、 船長をここセントジョンズに連れてきたのですね。";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "船長だと？ああ、笑わせるな！こんな犯罪者のクズに、この名誉ある称号を呼ぶ資格などない。俺が捕まえたのは、 くそったれな海賊だ、狼どもの頭目で、イギリスの商人や交易商を襲い、殺してきた奴だ。 そいつとその手下どもにはふさわしい報いを与えてやった――セントジョンズ中の者が桟橋での絞首刑を見届けたのさ！";
			link.l1 = "今となってはこの悪党を問い詰めることはできそうにありませんね……大佐、もしかしてお力を貸していただけませんか？その海賊は自分の物ではない金の香炉を持っていました。 彼の所持品の中に、それらしき物は見つかりましたか？";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "いいえ、そいつを調べたが、あの悪党は何も持っていなかった。それに、持ち物はきっと全部、 正直な商人たちから奪ったものだろう！\nそれから、あなたが気にしている件だが……うーん、いや、それも見つかっていない。そもそも、香炉なんてものが海賊船にあるはずがないだろう？ 本当にあいつらの中に神父がいたと思うのか？";
			link.l1 = "いいえ、持っていません。ローリー・ザ・キャップがウィレムスタッドの高利貸しからそれを買ったんだが、 その高利貸しも別の海賊から手に入れたらしい。香炉は立派で高価な品で、私は本来の持ち主に返そうとしているんです。 ローリーはカササギのようにそれに目をつけていたんでしょうね。";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "実のところ、ロリーの船に乗り込んで拿捕した時、船倉は空っぽで、 ドゥブロンが入った小さな箱がいくつかあっただけだ。ガラクタばかりで、貴重品もなければ金の香炉もなかった。 海賊に似つかわしくない品なら、私も覚えているはずだ。\nあの忌々しい海賊がドミニカに財産を隠したのではないかと疑っている。我々も上陸して辺りを探したが、 何も見つからなかった。ただ、島に長く留まったり奥地まで探索したりはしなかった。あそこは野蛮人が多すぎるからな。 ";
			link.l1 = "ふむ……あの海賊は盗んだ品々と一緒に香炉をドミニカのどこかに隠したのかもしれませんね……残念です。\n処刑の前にその海賊を尋問しましたか？";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "俺はやったさ……でもあいつは俺の顔を見て笑い出したんだ。\nだが、あいつの隠し財産なんて本当はどうでもよかった。ローリー・ザ・キャップは絞首刑になった、 それが一番大事なことだ。";
			link.l1 = "なるほど。お話とお時間、ありがとうございました、大佐。ごきげんよう……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("GuardOT_Fox_DlgExit");
		break;
		
		case "terrapin":
			dialog.text = "何度もだ、船長！フランス人からこのような名誉ある勇敢な行いが見られるとは思わなかった。 軍人としても父親としても、あなたに感謝している。この世で私にとって娘ほど大切なものはないのだ…";
			link.l1 = "お力になれて嬉しく思いますし、やがて私の行いがフランス人へのあなたのお気持ちを変えることを願っております。";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "見知らぬイギリス娘のために命を賭けるほど高潔で寛大な紳士であるあなた様のご臨席は、 私のあなた方同胞への感情を大いに和らげることでしょう！";
			link.l1 = "どの国のネズミどもにも、正直者はいるものですよ、大佐……";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "そして、あなたはそれを証明した！報酬が待っているぞ、船長。もちろん、娘の命は何物にも代えがたいが、 ジョナサン・フォックスは必ず借りを返すと誓う！君は真の兵士だ、だから私からの贈り物も兵士への贈り物だ。さあ、 見てみなさい。\nこれはブランダーバス、優れた海軍用マスケットで、片手でも使える。特別なボルトを装填すれば、 どんな頑丈な胸甲も貫通できる。さらに散弾も撃てるし、頑丈な造りだから釘を詰めて撃つこともできる。さあ、 受け取ってくれ、これは君のものだ。";
			link.l1 = "兵士にとってこれほど素晴らしい贈り物はありません、ありがとうございます、Colonel殿！";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			Log_Info("You have received a blunderbuss");
			Log_Info("You have received 10 arrows");
			Log_Info("You have received 10 charges of nails");
			Log_Info("You have received instructions for creating the harpoon arrows");
			Log_Info("You have received instructions for creating the charge of nails");
			GiveItem2Character(pchar, "pistol8");
			TakeNItems(pchar, "harpoon", 10);
			TakeNItems(pchar, "GunEchin", 10);
			GiveItem2Character(pchar, "recipe_harpoon"); 
			GiveItem2Character(pchar, "recipe_GunEchin"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "さらに、少量の弾薬とその製造方法の説明書もお渡しします。その力を最大限に活用しないのはもったいないですからね！ ";
			link.l1 = "ありがとうございます、大佐。こんな贈り物はありがたく頂戴しますが、 私がキャサリンを助けたのは報酬のためではないことを知っておいていただきたいのです。無防備な娘が危険に遭うのを、 どうしても見過ごせなかっただけです。";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "それは承知している、船長。それはあなたの名誉を二重に高めることだ。カトリーヌは本当にあなたに感銘を受けた、 彼女に良い印象を与えるのは簡単なことではないのだ。改めて、彼女を救ってくれたことに感謝する。我々 はあなたに借りができた！";
			link.l1 = "さて、贈り物をありがとう、大佐。キャサリンによろしく伝えてくれ、 次は父親の言うことを聞いてくれるといいんだがな。";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "承知しました、船長！ごきげんよう、道中ご無事で！";
			link.l1 = "ごきげんよう、大佐。";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Terrapin_KathyReward");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
			ChangeCharacterNationReputation(pchar, ENGLAND, 20);
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "報告書は読ませてもらった。あなたの行動は非常に高く評価されている、ゆえに報酬を与えねばならぬ。 遠征の功績として三万ペソ、兵士としての勇気には武器を。\nこの剣と火縄銃を受け取りなさい。今やすべてあなたのものだ！";
			link.l1 = "ありがとうございます、旦那。";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "もちろんでございます、船長。あなたはまた、イギリス植民地や当局、そして私個人からの愛と敬意も受けておられます。 私の部下を見捨てず、任務を助けてくださったことに感謝いたします！";
			link.l1 = "喜んでございます、大佐……";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "それでは、失礼します―他にも用事がございますので。ご武運を、船長。 "+pchar.lastname+".";
			link.l1 = "「ごきげんよう」 "+GetAddress_Form(NPChar)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
