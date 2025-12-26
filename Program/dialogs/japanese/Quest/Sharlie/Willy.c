// Вильям Патерсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何かご用ですか？";
			link.l1 = "いいえ、何もありません。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "catoche":
			dialog.text = "こんにちは、旦那。くそっ、やっぱりこの辺の軍事騒動を引き起こしたのはあんただったのか！？";
			link.l1 = TimeGreeting()+"、旦那。そうだ、上陸したのは俺の船だ。で、何の用だ？お前は誰だ？イギリス人か？";
			link.l1.go = "catoche_1";
		break;
		
		case "catoche_1":
			dialog.text = "スコットランド人だ、旦那。イギリス海軍の船長ウィリアム・パターソンだ、 こっちは俺の副長で右腕のアーチボルド・カルフーン。実はな、ジャングルの中にスペインの砦があるんだ。俺の任務は、 その呪われた野郎どもを、イギリス領に危険なほど近く建てられたその砦から追い出すことだ。\n最近、突撃を試みたが、あいつらは損害を受けても持ちこたえやがった。俺は援軍を求めて出たんだが……";
			link.l1 = "今はもうその必要はない。お前の未完の仕事は俺が片付けた。ジャングルの砦はもぬけの殻だ。 スペインの司令官ディエゴ・デ・モントヤは死んだし、奴の艦隊も全滅したぞ。";
			link.l1.go = "catoche_2";
		break;
		
		case "catoche_2":
			dialog.text = "これは一体どんな自警行為だ？イギリス領でこんな軍事行動を起こす動機は何なんだ？";
			link.l1 = "念のため言っておくが、パターソン船長、ここはベリーズじゃないぞ。どこのイギリス領だって？この騒ぎは全部、 ドン・ディエゴ・デ・モントヤが俺と俺の船を襲うという無謀な決断をしたせいで始まったんだ。";
			link.l1.go = "catoche_3";
		break;
		
		case "catoche_3":
			dialog.text = "えへん……で、ドン・ディエゴがあんたを襲った理由は何だったんだ、船長？";
			link.l1 = "奴と俺は長年の因縁があるんだ…あいつが率いていた艦隊がサン・ピエールを襲撃したあの日からさ。\nその少し後、俺が直接手を下してあの艦隊を壊滅させたんだ。";
			link.l1.go = "catoche_4";
		break;
		
		case "catoche_4":
			dialog.text = "くそっ！あの年老いたカバジェロは生かしておく必要があったのに！ なぜジャングルに軍事基地を設けたのか尋問するつもりだったんだ。理由もなくそんなことをするはずがない……";
			link.l1 = "申し訳ありませんが、今は彼から何も聞き出せません。\nいずれにせよ、砦には守備隊の負傷兵がいるかもしれません。彼らが話してくれる可能性はありますか？";
			link.l1.go = "catoche_5";
		break;
		
		case "catoche_5":
			dialog.text = "兵士たちめ……ああ、頑固な連中なんて役に立たねえ！\nドン・ディエゴの死体はどこだ？あいつ、重要な書類を持ってたかもしれねえだろうが！";
			link.l1 = "ドン・ディエゴは武器庫の砦の敷地に置いてきた。\nどうしても彼が必要なら、そこで見つけられるはずだ。\n逃げ出せるとは思えないよ。";
			link.l1.go = "catoche_6";
		break;
		
		case "catoche_6":
			dialog.text = "ええ…誰が他人のことに首を突っ込めって言ったんだよ…お前のせいで頭が痛くなってきたじゃねえか…";
			link.l1 = "船長、なぜ私を叱責なさるのか理解できません。私はあなたの仕事をこなし、自分の部下を戦いに送り、 自らの命も危険にさらしましたが、それでもご不満なのですね。今やるべきことは、 任務の成功とあなたの一切の成果をポートロイヤルに報告するだけです。 あなたの栄光に対して私が手柄を主張するつもりはありませんので、ご安心ください。";
			link.l1.go = "catoche_7";
		break;
		
		case "catoche_7":
			dialog.text = "手柄を主張するだと？栄光って何のことだ！？全然わかってねえな……はあ、もういい。じゃあな、旦那。";
			link.l1 = "あなたにも幸運を祈るよ！";
			link.l1.go = "catoche_8";
		break;
		
		case "catoche_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "GuardOT_OpenCatocheDoor", 10.0);
			sld = CharacterFromID("Archy");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 7.0);
			AddQuestRecord("Guardoftruth", "57");
		break;
		
		case "isladevieques":
			PlaySound("Voice\English\sharlie\Willie Paterson.wav");
			dialog.text = "おい、噂話は本当だったな。お前、猫みたいに九つの命があるってよ！ "+TimeGreeting()+"、ド・モール様。あまりお元気がなさそうですね……";
			link.l1 = TimeGreeting()+"パターソンさん、あなたとアーチボルド殿は見事に芝居を打って、私をまんまと騙しましたね。くそっ、皆め……まったく気づきませんでしたよ……";
			link.l1.go = "isladevieques_1";
		break;
		
		case "isladevieques_1":
			dialog.text = "おい、聖地の門前で汚い言葉を使うなよ。予想できなかったのか？光栄だな、 群島で最も名高い策士の一人を欺けたんだからな。日記のアイデア、見事だったろう？\nお前を人目につかない場所におびき寄せる必要があったんだ。公然と殺せば大騒ぎになる、 お前はフィリップ・ド・ポワンシーの親しい友人だろ？これからお前は跡形もなく消える。 そして誰にも真相はわからないさ。";
			link.l1 = "「じゃあ、キャルフーンが俺に話したことは……全部嘘だったのか？」";
			link.l1.go = "isladevieques_2";
		break;
		
		case "isladevieques_2":
			dialog.text = "とんでもありません。本当にこの場所で哀れなアーチボルドを見つけたのです。ただし、彼は回顧録など書いていません。 あなたが彼の部屋で見つけた日記は、私が頼んで、特別にあなたのために書かせたものです、ド・モール旦那。\nカポ・カトーチェでお会いしてから、ずっとあなたを見張っていました。ドン・ディエゴの死体から「二つの姿」 の地図を奪ったのは、あなたでしょう？否定しないでください、私にはわかっているのです。";
			link.l1 = "お前も「真実の守護者」について知っているのか？";
			link.l1.go = "isladevieques_3";
		break;
		
		case "isladevieques_3":
			dialog.text = "馬鹿げた質問だな。当然知ってるさ。それに、お前が酋長の爪も持ってることも分かってる。だが、 すぐにそれらの品を返してもらうぜ。お前の物じゃねえからな。";
			link.l1 = "お前がドン・ディエゴみたいにふらふらしてなくて嬉しいぜ。率直さと正直さはありがたい。俺の理解では、 お前が持ってるんだろう、道しるべのコンパスとアロー？";
			link.l1.go = "isladevieques_4";
		break;
		
		case "isladevieques_4":
			dialog.text = "ハッハッハ！まあ、最後まで正直にいこうじゃねえか…旦那、本気で信じてるのかい？俺があんたやドン・ディエゴみたいな間抜けで、 そんな貴重な品を持ち歩いてると思ってるのか？コンパスはジャマイカにあるんだぜ、しかもポートロイヤルじゃなくて、 誰も探そうなんて思わねえ場所に、しっかり鍵をかけてな。だが、その情報はあんたには必要ねえよ。";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.OfficerKill"))
			{
				link.l1 = "私の理解では、もう俺を埋めたつもりか、パターソン旦那？猫にはあと一つ命が残ってると宣言してやるぜ！\n俺の士官たちはどこだ？";
				link.l1.go = "isladevieques_5_1";
			}
			else
			{
				link.l1 = "私の理解では、もう俺のことを埋めたつもりか、パターソン旦那？だがな、 猫にはまだ一つ命が残ってるってことを宣言させてもらうぜ！..";
				link.l1.go = "isladevieques_5_2";
			}
		break;
		
		case "isladevieques_5_1":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.GirlKill"))
			{
				dialog.text = "お前の女のことで心配か、船長？お前の女はあそこ、茂みに頭に穴を開けて転がってるぜ。 お前のために道を作ってくれたんだ、すぐにお前もあいつの後を追うことになるさ。いやあ、 あの娘はなかなかの美人だったぜ！一度だけじゃなく、何度も抱いたんだろうな？";
				link.l1 = "あの野郎め！その仕打ち、絶対に許さねえぞ、クソ野郎が！？";
				link.l1.go = "isladevieques_6";
			}
			else
			{
				dialog.text = "「お前の部下たちが道を切り開いてくれたぞ、ド・モール旦那。あいつらはあそこの茂みに転がっている。 すぐにお前も仲間入りだ。」";
				link.l1 = "それはどうかな！";
				link.l1.go = "isladevieques_6";
			}
		break;
		
		case "isladevieques_5_2":
			dialog.text = "本当にお前の最後にしてやるぜ。";
			link.l1 = "それはどうかな！";
			link.l1.go = "isladevieques_6";
		break;
		
		case "isladevieques_6":
			dialog.text = "笑わせてくれるな。一人で一隊に立ち向かうってか！\nまあ、もうおしゃべりは終わりだ……銃を構えろ！撃て！";
			link.l1 = "...";
			link.l1.go = "isladevieques_7";
		break;
		
		case "isladevieques_7":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться patch-8
			LAi_ActorRunToLocation(npchar, "quest", "teleport", "IslaDeVieques_HouseEntrance", "quest", "mushketer", "GuardOT_WillyGetReady", 10.0);
			for(i=1; i<=5; i++)
			{
				sld = CharacterFromID("GuardOT_willymushketer_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_WillyMushketerDie");
			DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
