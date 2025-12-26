void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold, NextMonth;
	string attrL, sStr, Month;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "何かご用ですか？";
			link.l1 = "いいえ、何もありません。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// диалоги в ПУ
		case "SharlieEpilog_Pikar_1":
			dialog.text = "おや、誰かと思えば！ "+GetTitle(NPChar,true)+" "+pchar.lastname+" この目で見たぞ！";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				link.l1 = ""+npchar.name+"！まさかお前に会うなんて思ってもみなかったぜ…正直、まだ生きてるとも思わなかったからな！";
				link.l1.go = "SharlieEpilog_Pikar_2";
			}
			else
			{
				link.l1 = "信じられない……ハンサム？でも……どうして？";
				link.l1.go = "SharlieEpilog_PikarResurrected_1";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\LE\Rocur\Rocur_03.wav");
		break;
		
		case "SharlieEpilog_Pikar_2":
			if (IsStateTitle())
			  {
				dialog.text = "ははは！まあ、心配することはなかったんだよ。見ての通り、俺は元気にやってるさ。ちょっと自分へのご褒美に、 きれいな船を手に入れたんだ。\nでも君は……どうしてこんなことになったんだい、友よ？";
			  }
			  else 
			  {
				dialog.text = "ははは！まあ、心配することはなかったんだよ。見ての通り、俺は元気にやってるぜ。ちょっと“きれいな”小船を自分へのご褒美にしたんだ。で、君は……どうしてここに来たんだい、友よ？\n";
			  }
			link.l1 = "ここじゃない。酒場へ行こう――用事は後回しでいい。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_1":
			dialog.text = "しっ……そんなに大声を出さなくていいだろ。あの美少年はもういないさ、王子様と同じようにな。そうじゃねえか？";
			link.l1 = "「でも、私はこの目で見たんだ……」";
			link.l1.go = "SharlieEpilog_PikarResurrected_2";
		break;

		case "SharlieEpilog_PikarResurrected_2":
			dialog.text = "どうやって俺がやられたかって？そんなに単純ならよかったんだがな、旦那。信じてくれよ。";
			link.l1 = "酒場へ行こう。全部話してくれ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_Captain_1":
			dialog.text = "...";
			link.l1 = "それで、お前が新しいピナス船『"+GetShipName("Ulysse")+"「？」";
			link.l1.go = "SharlieEpilog_Captain_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\z_arest_02.wav");
		break;
		
		case "SharlieEpilog_Captain_2":
			dialog.text = "私。 "+GetFullName(npchar)+"そんなに知りたがるとはね。で、あなたは誰だ？";
			link.l1 = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"、それと、この船をあなたから買いたいのです。";
			link.l1.go = "SharlieEpilog_Captain_3";
		break;
		
		case "SharlieEpilog_Captain_3":
			dialog.text = "もちろん、もちろん、あなたのことは聞いているよ。この船を狙う連中はやっと振り切ったと思っていたんだが。 残念だけど、君をがっかりさせることになりそうだね。 "+GetTitle(NPChar,true)+" - '"+GetShipName("Ulysse")+"「』は今や俺のものだ、そしてもうすぐあの船でボルドーへ向かうぜ。 最初の取引から失敗するために商売を始めたわけじゃねえからな。不運はごめんだぜ。」";
			link.l1 = "ボルドーから来たのか？面白いな……もしかすると、君に儲かる話があるかもしれない。ラム酒を飲みながら話さないか？";
			link.l1.go = "SharlieEpilog_Captain_4";
		break;
		
		case "SharlieEpilog_Captain_4":
			dialog.text = "ラムやいい話を断るなんて、俺の性分じゃねえ。行こうぜ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		// диалоги в таверне
		case "SharlieEpilog_Pikar_5":
			if (IsStateTitle())
			  {
				dialog.text = "それでは、君に。 "+GetTitle(npchar,false)+" "+pchar.lastname+"……お前みたいな奴がいつまでもTiraxの使い走りなんてやってるわけがないと思ってたぜ。\nだが、まさかこんな大物になるとはな……本当に驚かせてくれるじゃねえか、くそっ。";
				link.l1 = "ははっ。よく言うぜ。で、今度は商人になるつもりか？";
			  }
			  else 
			  {
				dialog.text = "再会を祝して！また会う予感がしていたよ。";
				link.l1 = "ははは。彼女に乾杯だ！それで、商人になる決心をしたのか？";
			  }
			
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;

		case "SharlieEpilog_Pikar_6":
			dialog.text = "まあ、一生をほんのわずかなドゥブロンのために命がけで過ごすわけにもいかないさ。\nうまく袖の下を渡して、余計な口をつぐませれば――ほら、俺はもう盗賊でも海賊でもなく、立派な商人ってわけだ。";
			link.l1 = "さて、これは意外な展開だな。これじゃあ、今まさに新米ピナス船長に提案しようとしていたことを、 どうやって君に持ちかければいいのかわからなくなってしまったよ。"+GetShipName("Ulysse")+"「。」";
			link.l1.go = "SharlieEpilog_Pikar_7";
		break;

		case "SharlieEpilog_Pikar_7":
			dialog.text = "もう、はっきり言っちゃいなよ。あたしたち、ずっと前から知り合いでしょ？";
			link.l1 = "あのね……私がカリブに来たのは、あなたが買い取ったあのピナス船に乗ってきたのよ。競売に出されるって聞いて、 どうしても手に入れて、フランスまで自分で帆走して帰りたかったの。";
			link.l1.go = "SharlieEpilog_Pikar_8";
		break;

		case "SharlieEpilog_Pikar_8":
			dialog.text = "ハハハハハ！待って……アハハハハハ……";
			link.l1 = "それで、何がおかしいんだ？";
			link.l1.go = "SharlieEpilog_Pikar_9";
		break;

		case "SharlieEpilog_Pikar_9":
			dialog.text = "俺が競売で勝った途端に、こざっぱりした若造が近づいてきやがったんだ——身なりのいい坊ちゃんさ——自分と荷物をボルドーまで運んでくれって、きれいな金額を提示してきやがった。しかもただの金額じゃねえ——まるごと一袋分のコインだぜ。";
			link.l1 = "そうなのか？ははは。本当に面白いな。で、どうしたんだ？承諾したのか？";
			link.l1.go = "SharlieEpilog_Pikar_10";
		break;

		case "SharlieEpilog_Pikar_10":
			dialog.text = ""+pchar.name+"まあ、大西洋を渡るだけで山ほどの金を断るほど俺は馬鹿じゃねえよ。\nでしょ？数ヶ月は堅パンかじって塩漬け肉を噛みしめる羽目になるけどさ。\nでもさ、俺なんてもっと安い報酬で命張ったことだってあるんだぜ。\nだからもちろん、乗ったよ。";
			link.l1 = "その場合、同じ取引を提案しよう。私をボルドーまで連れて行ってくれれば、同じだけの金貨を渡す。";
			link.l1.go = "SharlieEpilog_Pikar_11";
		break;

		case "SharlieEpilog_Pikar_11":
			dialog.text = "乗客になる覚悟はできてるか？\nルールは知ってるだろ――船には船長が一人だけ。\nそして俺の船では、その船長は俺だ。";
			link.l1 = "なぜだ？少し息をついて、人生について考えてみるさ。もしかしたら本当に落ち着いて、 そろそろこの落ち着かない心に終止符を打つべきかもな。今はまだ想像しにくいが、案外悪くないのかもしれねえ。\nなんたって、お前でさえ戦いから身を引くことにしたんだからな。";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Pikar_12_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Pikar_12";
			}
		break;
		
		case "SharlieEpilog_Pikar_12_wife":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				dialog.text = "ああ、もし俺にもお前みたいな美しい妻がいたら、きっと海をやめてどこか静かな場所で落ち着くかもしれねえな――家を建てて、ちょっとワインでも商うんだ。今ならそれもできるさ――お前がスペイン野郎どもの手から俺を救い出してくれてから、無駄にしてる時間なんて一秒もねえよ。";
			}
			else
			{
				dialog.text = "ああ、もし俺にもお前のような美しい奥さんがいたら、きっと自分も海を離れて、 どこか静かな場所で腰を落ち着けていただろうな。家を建てて、少しワインの取引でもしてさ。\nそれにあのプランターの未亡人の遺産もあるんだろう？もう十分すぎる暮らしができるじゃねえか。";
			}
			link.l1 = "「妻か！くそっ、」 "+npchar.name+"、まだ彼女にはそのことを話していません。";
			link.l1.go = "SharlieEpilog_Pikar_13_wife";
		break;
		
		case "SharlieEpilog_Pikar_13_wife":
			dialog.text = "そんなのは後でいくらでもできるだろう。俺は自分のオンボロ船をちゃんと整備しなきゃならねえんだ。 用事が片付いたら、さっさとこっちに来いよ。出航前に盛大な宴を開こうぜ。";
			link.l1 = "そうこなくっちゃ！心配しないで、すぐに順番が来るからね。";
			link.l1.go = "SharlieEpilog_Pikar_14_wife";
		break;
		
		case "SharlieEpilog_Pikar_14_wife":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_1");}
			else {AddQuestRecord("SharlieEpilog", "11_5");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_12":
			dialog.text = "ああ、もし俺に妻がいたら、海を離れてどこか静かな場所で腰を落ち着けていたかもしれねえな――家を建てて、ちょっとワインでも売ったりしてさ。\nでも今は……海こそが俺の家なんだ。";
			link.l1 = "「俺の自分の農園で作ったワインだ、ははっ！ボルドー産さ。」 "+npchar.name+"ああ、あの娘たちは本当に目の保養だよな！もしかしたら、そこで恋人ができるかもしれないぜ――恋の手ほどきもなかなかのもんだ。なあ、思ったんだけどさ、 これから数か月はお前の船乗りたちの顔しか見られねえんだろ？出航前に地元の娼館で盛大に宴でも開くべきじゃねえか。 ";
			link.l1.go = "SharlieEpilog_Pikar_13";
		break;
		
		case "SharlieEpilog_Pikar_13":
			dialog.text = "そしてあんた、旦那、何を差し出せばいいかちゃんと分かってるじゃねえか。自分の用事が片付いたら、 さっさとここに戻ってこいよ。そしたら一緒に娼館へ行こうぜ――約束だ。";
			link.l1 = "よし、それじゃあ、時間を無駄にしないで始めよう！";
			link.l1.go = "SharlieEpilog_Pikar_14";
		break;
		
		case "SharlieEpilog_Pikar_14":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_2");}
			else {AddQuestRecord("SharlieEpilog", "11_6");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_3":
			dialog.text = "自由のために！";
			link.l1 = "そしてジャン、お前にも！死の淵からの帰還に乾杯だ！まだ信じられないよ。どうやって？";
			link.l1.go = "SharlieEpilog_PikarResurrected_4";
		break;

		case "SharlieEpilog_PikarResurrected_4":
			dialog.text = "俺は戦場から引きずり出された――生きているのがやっとで、頭の先から足の先まで血まみれだった。兵舎に放り込まれ、 まるで死肉のようにそのまま見捨てられたんだ。奴隷の中に、ちょっと頭の切れる奴がいてな――モコって名前だ。あいつが俺を助けてくれた。自分のシャツを裂いて傷を縛り、水まで飲ませてくれたんだ。";
			link.l1 = "「つまり、あれだけのことをしておいて、スペイン人たちはお前を生かしておいたってことか？」";
			link.l1.go = "SharlieEpilog_PikarResurrected_5";
		break;

		case "SharlieEpilog_PikarResurrected_5":
			dialog.text = "ご覧の通りさ。しかし、あいつらが親切心でやったわけじゃねえ。復讐が目的だった――尋問、拷問。焼かれ、殴られ、切られた。目玉を焼き潰すと脅されたぜ――まったく、俺への深い愛情の表れだよな。だがな、誰かが「海賊どもが俺の仇討ちを企んでて、もうナイフを研いでる」 って噂を流したんだ。プランテーションの旦那は神経質にビクビクし始めてな。兄弟たちが押しかけてくるのを待たずに、 慌ててカンペチェの自分の領地に逃げちまった。俺とモコ、それに他の連中も一緒に連れて行って、 証人を残さないようにしたのさ。残りの連中には「俺は死んだ」って伝えられて――それで全部終わりだ。";
			link.l1 = "それでどうなったの？どうやって脱出したの？それに、一体どうしてここにいるの？";
			link.l1.go = "SharlieEpilog_PikarResurrected_6";
		break;

		case "SharlieEpilog_PikarResurrected_6":
			dialog.text = "運だよ、相棒。盲目で、汚い運だ。俺はプランテーションに送られて——拷問は続いた。あの野郎は俺の苦しみを一秒一秒味わおうとしたが、日が経つごとに弱っていって……ついには熱病でくたばった。それからは、もう誰も俺のことなんか気にしなかった。家畜みたいに畑に追い立てられ、 鞭で打たれる機会を絶対に逃さなかったんだ。";
			link.l1 = "俺にはまだ、どうやってあそこから抜け出せたのか分からねえんだが？";
			link.l1.go = "SharlieEpilog_PikarResurrected_7";
		break;

		case "SharlieEpilog_PikarResurrected_7":
			dialog.text = "クリストファー・ミングスのことを聞いたことがあるか？";
			link.l1 = "アロンソが何か言ってたな…カンペチェ襲撃のことだ！あの時はスペイン野郎どもにひどい目を見せてやったんだよな。じゃあ、 あいつらがあんたを解放したのか？";
			link.l1.go = "SharlieEpilog_PikarResurrected_8";
		break;

		case "SharlieEpilog_PikarResurrected_8":
			dialog.text = "正確には違う。俺たち自身で脱出したんだ。衛兵たちがイギリスのバッカニアどもと戦っている間に、 モコと俺は兵舎の屋根から抜け道を見つけて反乱を起こした。そんで、 あの死んだクソ野郎のプランターの女房の武器庫と財宝を奪ったんだ。";
			link.l1 = "財務官の金庫だって？！そりゃ意外だな。";
			link.l1.go = "SharlieEpilog_PikarResurrected_9";
		break;

		case "SharlieEpilog_PikarResurrected_9":
			dialog.text = "俺たちは迷う暇なんてなかった――武器と物資を持ってジャングルへ突っ込んだんだ。二日間、密林をかき分けて進み続け、 ついにカン・ペチ族の村にたどり着いた。そこのシャーマンはスペイン人に従うふりをしていたが、 実際はあまり好いていなかった。モコはすぐに彼と意気投合し、俺たちは武器の半分と、 今後どんな戦争が起きても手を貸すという約束を条件に、村に受け入れてもらった。そうして俺は、 一年半もそこで暮らすことになったんだ。";
			link.l1 = "ジャン、お前はもう昔のお前じゃねえ。これからは「ラッキー」だ。";
			link.l1.go = "SharlieEpilog_PikarResurrected_10";
		break;

		case "SharlieEpilog_PikarResurrected_10":
			dialog.text = "ははは。気にしないさ。で、その後、フランス人の宣教師が俺たちのバタビルにやって来たんだ。すぐに気づいたよ――これが手錠なしでここを抜け出すチャンスだってな。俺たちは護衛を買収して――あっという間にトルトゥーガへ向けて出航したんだ。\nそれからは、もう死神とかくれんぼするのは十分だって思ったんだろうな。昔の稼業はきっぱりやめて……運よく、自分の船を手に入れたってわけさ。"+GetShipName("Ulysse")+"'。\n"+"それでお前は？どうしてこんなことになったんだ？俺は昔から、 お前みたいな大胆な奴がいつまでもティラックスの使いっ走りで終わるはずがねえと思ってたさ。だが、 まさかこんな大物になるとはな……本当にお前には驚かされっぱなしだぜ、くそっ。";
			link.l1 = "ははっ。どの口が言うんだよ。で、商人になるって決めたのか？";
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;
		
		case "SharlieEpilog_Captain_5":
			dialog.text = "「海の者たちに！」";
			link.l1 = "「そして幸運の女神に！」";
			link.l1.go = "SharlieEpilog_Captain_6";
		break;

		case "SharlieEpilog_Captain_6":
			dialog.text = "でしょ？じゃあ、本題に入ろう。あたしに何を提案したいの？";
			link.l1 = "ボルドーへ向かうんだね……実は、私もそこへ行くところなんだ。";
			link.l1.go = "SharlieEpilog_Captain_7";
		break;

		case "SharlieEpilog_Captain_7":
			dialog.text = "俺に乗船してほしいのか？俺の知る限り、お前は自分の船を持っているはずだ。もしかすると艦隊まであるかもしれねえ。 それなのに、他人の船に乗ることを選んだんだな。違うか？";
			link.l1 = "そうだよ。最近の出来事で、そろそろ錨を下ろして落ち着く時期かなって考えるようになったんだ……あなたの船でただの乗客として過ごせば、新しい生活のリズムに慣れられるかどうか分かると思うんだ。";
			link.l1.go = "SharlieEpilog_Captain_8";
		break;

		case "SharlieEpilog_Captain_8":
			dialog.text = "ふむ……命を危険にさらすのが馬鹿らしくなったのか？その気持ち、よく分かるよ。俺自身も……まあ、いいさ。お前のための席は船にあるし、お前の連れも全員乗せてやる。旅費はすでに、ある若い伊達男が払ってる――しかも急ぎの分もな。だから貨物は積まない。さて、支払いの話だが……\n";
			link.l1 = "ご心配なく、船長。私はあなたの雇い主と同じくらい気前がいいですし、同額を支払う用意がありますよ。";
			link.l1.go = "SharlieEpilog_Captain_9";
		break;

		case "SharlieEpilog_Captain_9":
			dialog.text = "素晴らしい！それで、取引成立ということかな？";
			link.l1 = "取引成立だ！それは一杯やる価値があるぜ！";
			link.l1.go = "SharlieEpilog_Captain_10";
		break;

		case "SharlieEpilog_Captain_10":
			dialog.text = "ああ、いいラムだな……船を整備して必要な物資を揃えるのに二週間はかかるぜ。\nそれが終わったら、出航できる。";
			link.l1 = "それじゃあ、また二週間後にここで会おう。\nでは、また今度だな、船長。";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Captain_11_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Captain_11";
			}
		break;
		
		case "SharlieEpilog_Captain_11_wife":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_3");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Captain_11":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_4");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "さて、友よ、全部片付いたか？この鶏小屋に本当の楽しみ方ってやつを見せてやろうぜ！";
				link.l1 = "「まだだ」 "+npchar.name+"、まだ片付けなければならないことがいくつか残っています。";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "船長、乗船の準備はできていますか？";
				link.l1 = "ああ、友よ、まだ片付けなければならないことがあるんだ。";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_Pikar_WaitInTavern";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				// только если знаком с Пикаром и поговорил с женой
				link.l2 = "おい、宿屋の旦那！みんなに酒を振る舞え、俺のおごりだ！安物じゃなくて、一番いい酒を持ってこいよ！";
				link.l2.go = "SharlieEpilog_Pikar_WaitInTavern_2";
			}
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern_2":
			dialog.text = "...";
			link.l1 = "俺たちに、友よ。塩っぽい風に、果てしない海に、そして永遠に呼びかけてくる、決して手の届かない地平線に――…";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_FrameInSea":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_FrameInSea");
		break;
		
		case "SharlieEpilog_Mary_1":
			dialog.text = "...";
			link.l1 = ""+npchar.name+"「ねえ、あなた、父のことについて話したいの。」";
			link.l1.go = "SharlieEpilog_Mary_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_2":
			dialog.text = "どうしたの、あなた？彼は無事だといいけど、でしょ？";
			link.l1 = "まあ、期待したほど順調ではありません。彼があまり時間を残されていないと思われる理由があり、 私に会えないまま最後の旅路に出るかもしれないという思いに、深く悩んでいるのです。";
			link.l1.go = "SharlieEpilog_Mary_3";
		break;

		case "SharlieEpilog_Mary_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "わかっているよ、愛しい人、わかっている……でも、それが人生さ。君に父上を会わせたかった。彼に、僕がどれほど素晴らしい妻を持っているか見せて、 僕たちに祝福をもらいたかったんだ。";
			link.l1.go = "SharlieEpilog_Mary_4";
		break;

		case "SharlieEpilog_Mary_4":
			dialog.text = "もし彼に気に入られなかったらどうしよう、でしょ？あたし、貴族の生まれじゃないんだよ…";
			link.l1 = "「馬鹿な、」 "+npchar.name+"、どうしてあなたを気に入らないことがあるの？あなたは素晴らしい人よ！私の心を射止めたなら、 きっと彼の心も掴めるわ。";
			link.l1.go = "SharlieEpilog_Mary_5";
		break;

		case "SharlieEpilog_Mary_5":
			dialog.text = "本当にそう思うの、あなた？それなら、できるだけ早くお父様のところへ行かなくちゃ。";
			link.l1 = "まさにそのつもりだ。俺たちの船も見つけておいた。二週間後に出航するぞ。";
			link.l1.go = "SharlieEpilog_Mary_6";
		break;

		case "SharlieEpilog_Mary_6":
			dialog.text = "船か？俺たちの船じゃないのか？";
			link.l1 = "いいえ、あなた。私たちはピナス船『"+GetShipName("Ulysse")+"「……私はこの船でカリブに来た――そしてこの船で去るのです。」";
			link.l1.go = "SharlieEpilog_Mary_7";
		break;

		case "SharlieEpilog_Mary_7":
			dialog.text = "それであなたは船長じゃなくなるの？";
			link.l1 = "遅かれ早かれ、この役目はいずれ手放さなければならなかっただろう。\n一時的なものだと願いたい。\nそれでも、自分の未来がどうなるかを少しでも感じておくのは悪くない。";
			link.l1.go = "SharlieEpilog_Mary_8";
		break;

		case "SharlieEpilog_Mary_8":
			dialog.text = "それで、私たちの士官たちはどうするの？全員を連れて行くわけにはいかないし、 ここであなたを待ってくれるとも思えないわ。";
			link.l1 = "ええと……そうですね、あなたの言う通りですわ。皆一人ひとりと話して、おそらくは本当にお別れを言わなければなりませんの。 これまで一緒に乗り越えてきたことを思うと、簡単にはいきませんけれど。";
			link.l1.go = "SharlieEpilog_Mary_9";
		break;
			
		case "SharlieEpilog_Mary_9":
			dialog.text = "酒場でちょっとした送別会でも開くかい？";
			link.l1 = "私もそのことを考えていたわ、あなた。ねえ……あなたの言う通りかもしれないわ。本当にいい考えよ。";
			link.l1.go = "exit";
			link.l2 = "それはいい考えじゃないと思う。盛大なお別れはやめておこう……この方がみんなのためにもなるはずだ。\n親しい友人だけを招待するのはどうかな……";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		case "SharlieEpilog_Helena_1":
			dialog.text = "...";
			link.l1 = "あなた、父のことについてお話ししたいの。";
			link.l1.go = "SharlieEpilog_Helena_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_2":
			dialog.text = "「もちろん」 "+pchar.name+"。無事だといいんだけど？";
			link.l1 = "正確には違うわ。父はしばらく前から病気で、もうすぐその病に負けてしまうかもしれないの…父はとても勇敢に耐えているけれど、本当に父を悩ませているのは、 もう二度と私に会えないかもしれないという思いだけなの。私は父に会いに行きたい…そしてあなたを紹介したいの。私たちの結婚に祝福をもらいたいのよ。";
			link.l1.go = "SharlieEpilog_Helena_3";
		break;

		case "SharlieEpilog_Helena_3":
			dialog.text = "お会いできるのを楽しみにしているわ、あなた。いつ出航するの？";
			link.l1 = "二週間後だ。しかし、それだけじゃない。自分たちの船では航海しないんだ。 ピナス船が俺たちを旧世界まで運んでくれる。 "+GetShipName("Ulysse")+"「―かつて私をここへ連れてきた、まさにその人です。」";
			link.l1.go = "SharlieEpilog_Helena_4";
		break;

		case "SharlieEpilog_Helena_4":
			dialog.text = ""+pchar.name+"「だが、長い航海の前に船を替えるのは縁起が悪いんだ。」";
			link.l1 = "船を変えるつもりはありませんわ、あなた。私たちは乗客になるのです。";
			link.l1.go = "SharlieEpilog_Helena_5";
		break;

		case "SharlieEpilog_Helena_5":
			dialog.text = "でも…あなた、わたくしにはわかりませんわ…";
			link.l1 = "「そうするしかないんだ」 "+npchar.name+"……いずれは船長を退く時が来るだろう。その時、自分がどんな気持ちになるのか、前もって知っておきたいんだ。";
			link.l1.go = "SharlieEpilog_Helena_6";
		break;

		case "SharlieEpilog_Helena_6":
			dialog.text = "それがあなたの決断なら……でも、私たちの士官たちはどうするの？全員を連れて行くことはできないわ。それに、 彼らがここであなたを待ちたいと思うかどうかも疑問よ。\n";
			link.l1 = "ええと……そうですね。皆と一人ずつ話さなければなりませんし、おそらくこれが本当の別れになるでしょう。 今まで一緒に乗り越えてきたことを思うと、簡単にはいきませんが。";
			link.l1.go = "SharlieEpilog_Helena_7";
		break;
			
		case "SharlieEpilog_Helena_7":
			dialog.text = "酒場でちょっとした送別会でも開こうか？";
			link.l1 = "私も同じことを考えていましたわ、あなた。ねえ……まさにそれを実行しましょう。ほんとうに良い考えですわ。";
			link.l1.go = "exit";
			link.l2 = "それはいい考えじゃないと思う。盛大なお別れはやめておこう……この方がみんなのためにもなるはずだ。\n親しい友人だけ招待するのはどうかな……";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		// Диалог с Алонсо в таверне Сен-Пьера
		case "SharlieEpilog_AlonsoInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				dialog.text = "船長……もう宿屋の主人と話してきたよ。最高の酒を用意してくれてる。いつ始める？";
				link.l1 = "今すぐだ！おい、宿屋の旦那！みんなに酒を振る舞え、俺のおごりだ！";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_1";
			}
			else
			{
				dialog.text = "船長、「ユリシーズ」のことをどうやって知ったのか教えてくれるって約束したよね。";
				link.l1 = "覚えてる、覚えてるぜ。おい、宿屋の旦那！この卓に一番上等なラムを持ってこい。";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_3";
			}
			link.l2 = "「早すぎる」 "+npchar.name+"。まだ急ぎの用事が残っております。";
			link.l2.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_AlonsoInTavern";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_1":
			dialog.text = "...";
			link.l1 = "さて、友よ、他の連中も呼んでくれ――サン・ピエールに本物の海の野郎どもがどう祝うか見せてやろうぜ！";
			link.l1.go = "SharlieEpilog_AlonsoInTavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_AlonsoInTavern_2":
			dialog.text = "ははっ！船長、信じられないだろうけど、もう呼んじゃったよ！";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_FrameInSea";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_3":
			dialog.text = "...";
			link.l1 = "「我らに」 "+npchar.name+"「運命の女神に、そして我らの帆を満たす風に！」";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		// На пинасе Улисс
		case "SharlieEpilog_Alonso_1":
			dialog.text = "とんでもない騒ぎを起こしちまったな、船長。ははは。酒場が完全にぶっ壊れずに済んだのは、 宿屋の主人が隠してたわずかなラム酒のおかげみたいだぜ。";
			link.l1 = "「思い出させないでくれ」 "+npchar.name+"、やっと少しだけ気分が良くなってきたところです。";
			link.l1.go = "SharlieEpilog_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "SharlieEpilog_Alonso_2":
			dialog.text = "かしこまりました、旦那 "+pchar.lastname+"。ははは。しかし、少なくともマルティニークは王侯貴族のようなやり方で後にしたな。あそこでのお前の出発の話は、 長い間語り継がれるだろう。";
			link.l1 = "宿屋の主人を小舟に乗せて、ル・フランソワまで酒を買いに行かせたのは、さすがにやりすぎだったかもしれないな。";
			link.l1.go = "SharlieEpilog_Alonso_2_1";
		break;
		
		case "SharlieEpilog_Alonso_2_1":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2)
				{
					dialog.text = "ハハハ。あいつのことは心配するな。この数日で自分のプランテーションを買えるほどの金を稼いだんだ――もしかしたら爵位まで手に入るかもしれないぞ。";
				}
			else
				{
					dialog.text = "ハハハ。あいつのことは心配いらないさ。ここ数日でプランテーションを買えるほどの金と、 それに見合う称号まで手に入れたんだ。ただ、君が誰とも士官たちと話さなかったのは残念だな。みんな、 きっと寂しがるよ。\n";
				}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;
		
		case "SharlieEpilog_Alonso_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
				{
					sld = CharacterFromID("Helena");
					locCameraFromToPos(-8.97, 6.39, -12.78, true, -8.54, 4.94, -13.90);
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
				{
					sld = CharacterFromID("Mary");
					locCameraFromToPos(-3.62, 4.03, 2.30, true, -4.98, 2.62, 3.26);
					// locCameraFromToPos(-4.13, 4.23, 2.55, true, -5.71, 2.54, 3.58);
				}
				dialog.text = "そうみたいだ、 "+sld.name+" 「夜の半分もいなくなったこと、まだ怒っているのよ。」";
			}
			else
			{
				dialog.text = "「それであの商人の件……さすがにやりすぎでしたよ、船長。」";
			}
			link.l1 = "ちくしょう、なんでジャンと俺はあの地元の店をうろついちまったんだ……";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;
		
		case "SharlieEpilog_Alonso_4":
			dialog.text = "「それで、どうやって捕まらずに済んだんだ？本当に笑い話になっただろうな―」 "+GetTitle(PChar,true)+" ワインの瓶を数本盗もうとして捕まった。";
			link.l1 = "「おかしいと思っているのか」 "+npchar.name+"、しかも半分も覚えていないんだ。こんなに飲んだのは……いや、実は一度もなかったな。";
			link.l1.go = "SharlieEpilog_Alonso_5";
			locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
		break;
		
		case "SharlieEpilog_Alonso_5":
			dialog.text = "さて、それじゃあ、いいスタートに乾杯だよ、船長。ははっ。すごく楽しかった、でしょ？またやりたいな。で、 いつ戻るって言ってたっけ？\n";
			link.l1 = "俺たちの荷物を確認してきてくれないか？全部持ってきたか？俺は後で降りるよ――今は船倉の空気は体に良くないからな。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_UlysseInSea_8");
		break;
		
		// диалог с Алонсо у горы золота
		case "SharlieEpilog_Alonso_11": // этап 1
			dialog.text = "...";
			link.l1 = "見てくれよ……船は本当にひどいやられようだな。";
			link.l1.go = "SharlieEpilog_Alonso_12";
			SharlieEpilog_GoldInTheDeck_1_1();
		break;
		
		case "SharlieEpilog_Alonso_12":
			dialog.text = "ここに金貨が山ほどあるぜ、船長！";
			link.l1 = "なるほど "+npchar.name+"。これをすぐに全部箱に隠しておこう、乗組員たちに見られる前にな。あいつらにこんな誘惑は必要ねえ。";
			link.l1.go = "SharlieEpilog_Alonso_13";
		break;
		
		case "SharlieEpilog_Alonso_13":
			dialog.text = "いいえ、抗えない……";
			link.l1 = "何だって？";
			link.l1.go = "exit";
			locCameraFromToPos(-1.28, 7.70, -10.26, true, 0.74, 5.42, -9.49);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_2");
		break;
			
		case "SharlieEpilog_Alonso_21": // этап 2
			dialog.text = "...";
			link.l1 = "おい、どうしたんだ？";
			link.l1.go = "SharlieEpilog_Alonso_22";
			// SharlieEpilog_GoldInTheDeck_6();
		break;
		
		case "SharlieEpilog_Alonso_22":
			dialog.text = "...";
			link.l1 = "さあ、起きろ。こんな時に寝てるなんて……";
			link.l1.go = "SharlieEpilog_Alonso_23";
		break;
		
		case "SharlieEpilog_Alonso_23":
			dialog.text = "一緒に来いよ、船長。";
			link.l1 = "起きろ、ふざけてないで。";
			link.l1.go = "SharlieEpilog_Alonso_24";
		break;
		
		case "SharlieEpilog_Alonso_24":
			dialog.text = "落ち着いて。感じればいいんだ。";
			link.l1 = "でしょ？好きにしなよ。さあ、どいて。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_7");
		break;
		
		case "SharlieEpilog_Alonso_31": // этап 3
			dialog.text = "ずっとこれをやってみたかったんだ……";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_32";
			SharlieEpilog_GoldInTheDeck_10();
		break;
		
		case "SharlieEpilog_Alonso_32":
			dialog.text = "素晴らしい気分だろう、船長？";
			link.l1 = "ははは。可愛い兄上の様子を見にカリブまで来ただけのつもりだったのに、こんなことになるとはな。 父上もまさかこんな展開になるとは思っていなかっただろう。はは！";
			link.l1.go = "SharlieEpilog_Alonso_33";
		break;
		
		case "SharlieEpilog_Alonso_33":
			dialog.text = "Sir "+GetTitle(NPChar,false)+" "+pchar.lastname+"…ははっ！お前が最初にこの諸島に来たとき、どんな奴だったか覚えてるか？";
			link.l1 = "もちろん覚えているさ。ははは。今デッキを闊歩しているあの伊達男と同じくらい、 かつての俺も気取っていたなんて信じられねえよな。この忌々しいカリブの海で、本当にいろんなことがあった……陰謀、不死者、ククルカン兄弟……";
			link.l1.go = "SharlieEpilog_Alonso_34";
		break;
		
		case "SharlieEpilog_Alonso_34":
			dialog.text = "運がいいな、船長。そんな大金を手に入れて、しかも生きて帰ってこれるなんて……誰もができることじゃねえぜ。";
			link.l1 = "うん、でしょ？もうダラダラしてるのはやめようよ。誰かに本当に見つかったら困るでしょ？";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_11");
		break;
		
		// диалоги в катсцене с брашпилем
		case "SharlieEpilog_windlass_1":
			dialog.text = "...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "聞いてくれ、相棒。この船のウィンドラスの安全装置は気に入らないんだ。あまりにも頼りにならない。 誰かがうっかり外してしまうかもしれないぞ。";
			}
			else
			{
				link.l1 = "聞いてください、船長。この船のウィンドラスの安全装置は気に入りません。あまりにも信用できなくて、 誰かがうっかり外してしまうかもしれません。";
			}
			link.l1.go = "SharlieEpilog_windlass_2";
			locCameraFromToPos(-7.57, 9.68, -21.21, true, -9.79, 7.76, -20.01);
		break;
		
		case "SharlieEpilog_windlass_2":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "「もう、やめてよ」 "+pchar.name+"…船の上では、誰もが知っていることだ…";
			}
			else
			{
				dialog.text = "もう、やめてよ船長。誰がそんなこと考えるっていうの…";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_windlass_3");
		break;
		
		case "SharlieEpilog_windlass_3": // диалог Пикара и дворянина
			dialog.text = "おい、この間抜け……一体何をしてやがるんだ？自分の不器用な足を突っ込むなって、誰にも教わらなかったのか？";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_4";
			locCameraFromToPos(-10.28, 9.94, -22.90, true, -9.29, 7.86, -21.36);
			NPCsLookEachOther("SharlieEpilog_Pikar", "SharlieEpilog_Bernard_Clone");
			CharacterTurnByChr(pchar, CharacterFromID("SharlieEpilog_Bernard_Clone"));
		break;
		
		case "SharlieEpilog_windlass_4":
			dialog.text = "...";
			link.l1 = "落ち着け、調子に乗るな！私は貴族だぞ、こんなことは許せない……";
			link.l1.go = "SharlieEpilog_windlass_5";
		break;
		
		case "SharlieEpilog_windlass_5":
			dialog.text = "俺の船じゃ、お前はただの部外者だ。ここじゃ俺の船員たちの方がよっぽど権利があるんだぜ。 だから大人しく黙って隅っこにいろ。さもなきゃ、俺が直々に海に放り込んでやるからな。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_6";
		break;
		
		case "SharlieEpilog_windlass_6": // диалог Пикара и Шарля
			dialog.text = "...";
			link.l1 = "ははは。まるで自分自身を外から見ているようだったな。";
			link.l1.go = "SharlieEpilog_windlass_7";
			SharlieEpilog_windlass_9_1();
		break;
		
		case "SharlieEpilog_windlass_7":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "何の話をしているんだ？";
				link.l1 = "でしょ、別にかまわないよ、 "+npchar.name+"「そんなにうちの乗客に厳しくするなよ。まだ全部初めてなんだ。俺たちだって、 一日でベテランの海の男になったわけじゃねえだろう？」";
			}
			else
			{
				dialog.text = "何の話をしているんだ？";
				link.l1 = "「気にするな」 "+npchar.name+"。それに、乗客のことをあまり厳しく見ないでやってくれ。あいつにとっては何もかも初めてなんだ。俺たちだって、 もともと海の荒くれ者として生まれたわけじゃねえからな。";
			}
			link.l1.go = "SharlieEpilog_windlass_8";
		break;
		
		case "SharlieEpilog_windlass_8":
			dialog.text = "あいつの才能じゃ、水夫になるよりキャプスタンに絡まる方がよっぽど現実的だぜ。そんなこと思いつくなんてな……";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "誰にも分からん、誰にも分からんさ。俺がこの諸島にやって来た時も、相変わらず無邪気で好奇心旺盛、 そして傲慢な若造だったよ。";
			}
			else
			{
				link.l1 = "誰にも分からないさ。俺が最初にこの諸島に来た時も、同じように無邪気で好奇心旺盛、そして傲慢な若造だったよ。";
			}
			link.l1.go = "SharlieEpilog_windlass_9";
		break;
		
		case "SharlieEpilog_windlass_9":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "ああ、そうだよ、なんて比べ方だよ、でしょ？\n"+"待て\n"+"つまり自分を彼に重ねて見ているのか？ははは。じゃあ、お前が面倒を見てやれよ。俺が子守をするつもりはねえからな。 ";
				link.l1 = "俺があいつを見張っておくぜ。少なくとも、お前が奴の皮を剥ぐまではな。だが、錨の代金はきっちり払わせるべきだ。";
			}
			else
			{
				dialog.text = "つまり自分を彼に重ねたのか？はは。まあいいさ、船長、これからはあんたの責任だぜ。 俺が子守をするつもりはねえからな。";
				link.l1 = "俺があいつを見張っておくよ。少なくとも、お前が生きたまま皮を剥ぎ終えるまではな。\nだが、錨のことは――ちゃんと代金を払わせろよ。";
			}
			link.l1.go = "SharlieEpilog_windlass_10";
		break;
		
		case "SharlieEpilog_windlass_10":
			dialog.text = "錨を下ろせ。\n風を待て。\n進路を維持しろ。";
			link.l1 = "...";
			link.l1.go = "exit";
			SharlieEpilog_windlass_10();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_1");
		break;
		
		// диалоги Старшего матроса и Алонсо		
		case "SharlieEpilog_AlonsoTrollingHighSailor_2": // Алонсо
			dialog.text = "";
			link.l1 = "錨を上げろ。\n風をつかめ。\n北東に針路を取れ。";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_3";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_3": // Старший матрос
			dialog.text = "";
			link.l1 = "錨を上げろ！ジブを下ろせ――風を捕まえるぞ。さあ、仕事にかかれ…";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_4";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_4": // Алонсо
			dialog.text = "";
			link.l1 = "何をしているんだ？";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_5";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_5": // Старший матрос
			dialog.text = "";
			link.l1 = "何をしているんだ？";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_6";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_6": // Алонсо
			dialog.text = "";
			link.l1 = "だめ、何をしているの！？";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_7";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_7": // Старший матрос
			dialog.text = "";
			link.l1 = "ううっ……何してるんだ？年長の水夫が船長の命令を繰り返してるぞ。";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_8";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_8": // Алонсо
			dialog.text = "";
			link.l1 = "だから、年長の水夫はただ彼らの後について繰り返すだけだ。";
			link.l1.go = "exit";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_2");
		break;
		
		// Шарль ругает Алонсо
		case "SharlieEpilog_AlonsoTrollingHighSailor_9":
			dialog.text = "...";
			link.l1 = "下がれ、Alonso。俺たちはただの乗客だ。忘れたのか？";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_10";
			locCameraFromToPos(-8.00, 4.49, -1.91, true, -9.97, 2.64, -1.90);
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_10":
			dialog.text = "えへん……悪いな、船長。つい我慢できなかったんだ\nでも、やってよかったよ。まるで昔に戻ったみたいだったからな。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_5");
		break;
		
		// Диалог Шарля с Пикаром о всяком (можно попасть в Поместье де Монпе)
		case "SharlieEpilog_PikarOnUliss":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"「……私に何かご用でしょうか？」";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A"))
				{
					link.l1 = "さて、友よ、調子はどうだ？";
					link.l1.go = "SharlieEpilog_PikarOnUliss_A_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_B"))
				{
					if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
					{
						link.l2 = "「認めて、」 "+npchar.name+"「お前はティラックスから離れると決めた時から、すでに商人になるつもりだったんじゃないか？」";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
					else
					{
						link.l2 = "「認めなさい、」 "+npchar.name+"「その頃から、もう商人になろうと考えていたのか、あのプランテーションで？」";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_C"))
				{
					link.l3 = "はっきり覚えているのは、使者が私に話しかけようとしたことだ。\nだが、どうしても何の用だったか思い出せないんだ。\n君は何か知っているか？";
					link.l3.go = "SharlieEpilog_PikarOnUliss_C_1";
				}
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_E"))
				{
					link.l1 = "船長、ボルドーに行ったことはありますか？";
					link.l1.go = "SharlieEpilog_PikarOnUliss_E_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_F"))
				{
					link.l2 = "船長、正直に言うと、どうやってマルティニークを出たのかほとんど覚えていません。 誰かから大事な手紙を受け取るはずだったのですが、結局受け取っていないようです。\nこの件について誰かあなたに話しましたか？";
					link.l2.go = "SharlieEpilog_PikarOnUliss_F_1";
				}
			}
			link.l4 = "そよ風が吹いてきたようだな。出航の時間だ。（海へ出る）";
			link.l4.go = "SharlieEpilog_PikarOnUliss_D_1";
			link.l5 = "まだ何もない。行ってくる。";
			link.l5.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_A_1":
			dialog.text = "ははは……これ以上元気なことはないさ！活力も健康も満ちあふれてるぜ。";
			link.l1 = "本当か？まるでサメに噛み砕かれたみたいな顔してるぜ。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_A = true;
		break;

		case "SharlieEpilog_PikarOnUliss_A_2":
			dialog.text = "よく言うよ。お前こそ、まるで叩かれた犬みたいな顔してるじゃないか。";
			link.l1 = "私も同じ気持ちだよ。ははっ。くそ、いつどうやって出航したのかさえ覚えてないや。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_3";
		break;

		case "SharlieEpilog_PikarOnUliss_A_3":
			dialog.text = "ああ、素晴らしい宴だったな。だが、とんでもなく金がかかった。俺の馬鹿どもがもう少しで売春宿を燃やしかけてな、 醜聞を揉み消すために大金を払わされたんだ。だから今じゃ、あいつらは一生俺に借りができたってわけさ。\nそれで、乗客の気分はどうだ？退屈でまだ遠吠えなんかしてないだろうな？";
			link.l1 = "自分の運命がもう自分の手の中にはないような気がする。\nそれでも同時に、不思議な安堵感を覚えるんだ。\nまるで肩から大砲の弾の箱を降ろしたかのように。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_4";
		break;

		case "SharlieEpilog_PikarOnUliss_A_4":
			dialog.text = "ははは。じゃあ、もし退屈したら、俺の部下として迎えてやるぜ。";
			link.l1 = "それはとてもご親切ですが、お断りしなくてはなりません。\nカリブ中のラム酒を集めても、私たちの宴には足りませんから。";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_1":
			if (IsStateTitle()) 
			{
				dialog.text = "正確には違うぜ、相棒。時々そんな考えが頭をよぎったことはあったが、特に気にしちゃいなかった。 だが二度目にその思いが戻ってきたのは、タイラックスの忠犬どもが跡形もなく消えちまったって噂を聞いた時だ。 クレーバーも、ハゲも、あの臭い年寄り犬レプラコーンまで、全員だ。\nそれにお前が成し遂げた数々の話を耳にした時、ついに俺ももう十分だと思った。 いつまでも小銭のために命を張り続けるわけにはいかねえからな。\n今じゃ、粉まみれの野郎どもに頭を下げる必要もないくらい金は手に入れた。だが海を捨てる覚悟は……まだできちゃいなかった。だから新しい稼業を選んだのさ。";
			} 
			else 
			{
				dialog.text = "正確には違うな、友よ。時々そんな考えが頭をよぎったことはあったが、特に気に留めてはいなかった。だが、 ある噂を耳にしたときにまた思い出したんだ――タイラックスの忠実な犬どもが、跡形もなく消えちまったって話さ。クレーバーも、ハゲも、 あの臭い年寄りレプラコーンまで、全員だ。\nそれに敵の砲弾で、一度の戦いで二度も脳天を吹き飛ばされかけてな、ついに「もうたくさんだ」と思った。 いつまでも金のために命を張り続けるわけにはいかねえ。\nもう十分な金は手に入れた。カツラをかぶった野郎どもに頭を下げて生きる必要はねえさ。だが、海を捨てる覚悟は……まだできちゃいなかった。だから、新しいことに挑戦してみることにしたんだ。";
			}
			link.l1 = "クリーバー、ハゲ、レプラコーン……あいつらがどこへ消えたか知ってるか？";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_B = true;
		break;

		case "SharlieEpilog_PikarOnUliss_B_2":
			dialog.text = "いいや、知らないよ。正直言って――あんな奴らがどこへ行こうが俺にはどうでもいいぜ。地獄に落ちようが知ったこっちゃねえ。";
			link.l1 = "だいたいそのあたりに私が送り出しました。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_3";
		break;

		case "SharlieEpilog_PikarOnUliss_B_3":
			dialog.text = "奴らの乗組員を全滅させたのはお前だったのか？こりゃ驚いたぜ！それでマーカスはそのことを許してくれたのか？";
			link.l1 = "彼はそのことを知らない。そしておそらく、これからも決して知ることはないだろう。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_4";
		break;

		case "SharlieEpilog_PikarOnUliss_B_4":
			dialog.text = "くそっ、俺はちょうどいいタイミングであいつらから抜け出したんだ、はは。お前だって、 俺の首を見逃さなかっただろうな\nだが一つだけ分からねえ――お前は一体何のためにこんなことをしたんだ？";
			link.l1 = "お前の言った通りだ――あいつらは金のためなら仲間同士で首を絞め合い、誰でも裏切るし殺す連中だ。 俺たちは南メインのどこかの地下牢に誘い込まれて、「莫大な財宝がある」なんて話を聞かされた。 すべては綿密に仕組まれた罠だったのに、あの馬鹿どもは何の疑いもなく餌に食いついたんだ。 戦利品を平等に分けるどころか、「分け合う意味なんてない」と思ったらしく、 俺を始末して全部自分たちのものにしようとしたのさ。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_5";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_5":
			dialog.text = "そいつらはやり遂げられなかった、絶対に無理だったな、はは！\nちょっと待て、そもそもあの罠を仕掛けたのは誰だ？";
			if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l1 = "スペインの民間の復讐者、ゾロとかいう奴がカルタヘナの復讐を狙っていたんだ。\nあの虐殺を生き延びた者は、永遠に地下牢で朽ち果てるはずだった――すべての出口は封鎖されていた。\nだが、あの野郎は運が悪かったな――俺の部下が奴を出し抜いたんだ。";
			}
			else
			{
				link.l1 = "あるゾロという、スペインの民衆の復讐者がいた――カルタヘナの仇討ちを求めてな。\nあの地獄の虐殺を生き延びた者は、永遠に地下牢に閉じ込められる運命だった――すべての出口は固く封じられていた。\n俺はなんとか脱出できた。だが、その代償はあまりにも大きかった。";
			}
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_6";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_6":
			dialog.text = "少なくとも生きて帰ってこれたんだな。で、自分の命と引き換えになりかけたあの金もちゃんと持ち帰ったんだろう？";
			link.l1 = "そこには金なんてなかった。ただの金メッキの鉛だったんだ……";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_7";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_7":
			dialog.text = "...";
			link.l1 = "あれこれあって、私はティラックスを離れることにしたんだ。\nこのことを話すのは君が初めてだよ。まあ、私の士官たちは別だけどね。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_8";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_8":
			dialog.text = "「だから言っただろ」とはあまり言いたくないが……警告はしておいたぞ。";
			link.l1 = "引き際をわきまえるのは、昔から私の得意分野ではありませんの。だから、 あなたが少し教えてくださらなくてはなりませんわ。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_9";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_9":
			dialog.text = "俺のこと知ってるだろう――旨いラムが二杯もあれば、俺の金貨の隠し場所だって教えちまうぜ、へっへっ。";
			link.l1 = "まあ、俺からそんな気前のいいことは期待するなよ、ははは。自分の物資でなんとかしろよな。";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_C_1":
			dialog.text = "その通りだ。あいつは君に何通か手紙を渡そうとした――ベンとか、あるいはベネディクトとかいうやつからのな。でも君は「ベンなんて知らない」と言い放って、 これ以上俺たちの楽しみを邪魔するなら酒場から叩き出すぞと脅したんだ。";
			link.l1 = "くそっ……これはブノワ院長からの手紙だったようだな。大事な手紙だ。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_C = true;
		break;

		case "SharlieEpilog_PikarOnUliss_C_2":
			dialog.text = "さて、それなら俺が預かっておいて正解だったな。へっへっ。あの若造が選んだ相手は間違ってなかったって、 なんとなく感じてたんだ。ほら、受け取れ。";
			link.l1 = "本当に助けてくれたよ、 "+npchar.name+"、ありがとうございます。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_3";
		break;

		case "SharlieEpilog_PikarOnUliss_C_3":
			dialog.text = "「ありがとう」一回じゃ足りねえぜ、友よ。俺に一杯奢ってもらうぞ――しかもただの酒じゃなくて、ボルドーで一番旨い酒だ。";
			link.l1 = "飲み物はやるよ、この乞食め。うちのラムはカリブのラムにはかなわねえが、ワインなら……お前が今まで味わったことのねえ代物だぜ。";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_E_1":
			dialog.text = "「そんなこと、一度もなかった…」";
			link.l1 = "羨ましいな。私ももう一度初めての気持ちでボルドーを見てみたいものです。\n君はきっとラム酒のほうが好きだろうが、市庁舎の近くで開かれるワイン市にはぜひ行ってみてほしい。\nカリブの愛好家たちは、我々のクラレットに大金を払うだろう。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_E = true;
		break;

		case "SharlieEpilog_PikarOnUliss_E_2":
			dialog.text = "助言ありがとうございます。少しお尋ねしてもよろしいでしょうか？";
			link.l1 = "「もちろん。」";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_3";
		break;

		case "SharlieEpilog_PikarOnUliss_E_3":
			dialog.text = "長年も舵を握ってきたのに、今は乗客になった気分はどう？もう新しい役割には慣れたのかしら？";
			link.l1 = "ふむ……自分の運命をもう自分で操れないような気がしてならない。しかし同時に、妙な安堵感もある。 まるで肩に担いでいた砲弾の箱を下ろしたような気分だ。結論を出すには、まだ早すぎるだろうな。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_4";
		break;

		case "SharlieEpilog_PikarOnUliss_E_4":
			dialog.text = "この忌々しい凪に巻き込まれたせいで、手持ち無沙汰になるほど時間はたっぷりあるぞ。";
			link.l1 = "良き仲間と共にいれば、穏やかな海も苦にはならないものです。それに正直に申しますと、船長、 私は仲間運に恵まれておりますわ。";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_F_1":
			dialog.text = "ああ、使いの者が来ていたよ。どこかの修道院長が寄越したんだ。君にこの手紙を渡すのを、つい忘れてばかりいた。 ほら、受け取ってくれ。";
			link.l1 = "素晴らしいです。本当に助かりました、船長。ありがとうございます。";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_F = true;
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A")){dialog.text = "「その通りだ。」";}
			else {dialog.text = "「その通りだ。」";}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_D_2";
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_2":
			dialog.text = "右舷前方から風だ！前帆からミズン帆まで全部張れ！全速前進だ！";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InEstateDeMonpe";
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(CharacterFromID("SharlieEpilog_Pikar"), "quest", "quest10");
		break;
		
		case "SharlieEpilog_InEstateDeMonpe":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe");
		break;
		
		//Матрос 1 на верхней палубе
		case "SharlieEpilog_Sailor_1":
			dialog.text = "「見事な刃だ」 "+GetTitle(NPChar,true)+"。見せていただけますか？";
			link.l1 = "また今度にしよう。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_1";
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer05.wav");
		break;
		
		//Матрос 2 на верхней палубе
		case "SharlieEpilog_Sailor_2":
			dialog.text = "その砂時計はいつ鳴るんだ？舌を噛み切りそうだぜ。";
			link.l1 = "我慢しろ、水夫。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-07.wav");
		break;
		
		//Матрос 3 на орудийной палубе
		case "SharlieEpilog_Sailor_3":
			dialog.text = "あのネズミが走っていくのを見たか？あんなにでかいのは生まれて初めて見たぜ！";
			link.l1 = "「さて……」";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_3";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-04.wav");
		break;
		
		//Матрос 4 на орудийной палубе
		case "SharlieEpilog_Sailor_4":
			dialog.text = "これからどうすればいいんだ、旦那？酔っ払いすぎて、どうやってこの船に乗ったのかさえ覚えてないんだ。 俺は水夫じゃねえ……それに、故郷には妻と子供が二人いるんだよ。";
			link.l1 = "もう少し酒を控えておけばよかったな。今さら遅い――これからは水夫になるしかねえぞ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_4";
			PlaySound("Voice\" + LanguageGetLanguage() + "\Ransack_2.wav");
		break;
		
		//Старший матрос
		case "SharlieEpilog_HighSailor_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"。私どもの船にご乗船いただき光栄でございます。";
			link.l1 = "あなたはとても礼儀正しいですね、先輩水夫旦那。長年の海の荒くれ者にしては、礼儀はあまり見かけない資質です。 しかし、乗組員を困らせるのはやめましょう――ここは国王陛下の宮廷ではありませんから。私のことはただ「船長」と呼んでください。";
			link.l1.go = "SharlieEpilog_HighSailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;

		case "SharlieEpilog_HighSailor_2":
			dialog.text = "まあ、俺が水夫になってからは、まだそんなに経ってねえんだ。前はルヴァスール旦那の書記をやってたんだよ。だが、 あの人が…ええと…排除されて、新しい総督がやって来た。ルネ・ド・ボワデュフル・ド・レストル旦那がどんな悪党かって話は、 ある界隈ですぐに広まったさ。そこで気づいたんだ――もうまともな仕事なんて見つからねえってな。みんな、俺が全部知ってて黙ってたって思うだろうからな。";
			link.l1 = "「そうではなかったか？」";
			link.l1.go = "SharlieEpilog_HighSailor_3";
		break;

		case "SharlieEpilog_HighSailor_3":
			dialog.text = "もちろん違うよ。他人のことに首を突っ込む癖なんて、俺にはなかったさ。それに、 ルヴァスールは好奇心を厳しく罰したからな。";
			link.l1 = "それは簡単に信じられるよ。";
			link.l1.go = "SharlieEpilog_HighSailor_4";
		break;

		case "SharlieEpilog_HighSailor_4":
			dialog.text = "だから、あいつの件が片付いた後、俺は見つけた最初の海賊船に水夫として乗り込んだんだ。\nそして不思議なことに、俺はすぐに順応して変わっていった。 あの冷酷な殺し屋どもからも一目置かれるようになったんだ。\nでも、あいつらのやっていたことは……どうしても俺には合わなかった。\nそうして、俺はここにたどり着いたってわけさ。";
			link.l1 = "それで、私がルヴァスールの運命に関わっていたことを知っていたのか？";
			link.l1.go = "SharlieEpilog_HighSailor_5";
		break;

		case "SharlieEpilog_HighSailor_5":
			dialog.text = "もちろんです、船長。そして、あなたがあの化け物をこの世から消してくれて本当に嬉しいです。同時に、 あなたは私をあの息苦しい小部屋から救い出してくれました。私の人生をまったく新しい光で見せてくれたのです。";
			link.l1 = "世の中って本当に狭いものだな……";
			link.l1.go = "SharlieEpilog_HighSailor_6";
		break;

		case "SharlieEpilog_HighSailor_6":
			dialog.text = "矛盾して聞こえるかもしれませんが、世界は広大であると同時に、実に小さいものです。";
			link.l1 = "おかしいな。そんなこと、考えたこともなかったよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
		break;
		
		case "SharlieEpilog_HighSailor_7":
			dialog.text = "Captain "+pchar.lastname+"…素晴らしい夜じゃないか？";
			link.l1 = "そうかもしれませんね。あとは穏やかな北西の風が吹いてくれれば、さらに最高でしょう。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;
		
		//Диалог с боцманом Моко
		case "SharlieEpilog_Moko_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Captain "+pchar.lastname+"...";
				link.l1 = "実は……いや、やっぱりいいや。覚えてるよ！君の名前はモコだろ。 丸ごと一樽のラム酒を一気に飲み干したのは君じゃなかったか？";
				link.l1.go = "SharlieEpilog_Moko_2";
			}
			else
			{
				dialog.text = "……何のご用ですか、旦那？";
				link.l1 = "お前みたいな大男にはそうそう会えねえよ。名前は何だ？";
				link.l1.go = "SharlieEpilog_Moko_4";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Kapitani Korabley-07.wav");
		break;

		case "SharlieEpilog_Moko_2":
			dialog.text = "俺は……それから二日後にやっと目を覚ましたんだ。";
			link.l1 = "お前の立場なら、他の誰もが数時間ももたなかっただろう。飲む時みたいに戦うなら、 ジャンはお前みたいな甲板長がいて本当に運がいいぜ。";
			link.l1.go = "SharlieEpilog_Moko_3";
		break;

		case "SharlieEpilog_Moko_3":
			dialog.text = "ちょうど私の船長に恵まれたように、運が良かったわ。\n彼のおかげで、私は自由を手に入れたの。\nそして、あなたにも感謝してる。もしあなたがジャンを助けてくれなかったら、 私は今でもプランテーションで朽ち果てていたでしょ？";
			link.l1 = "まさに大冒険だったな。\nそして、思ったよりも良い結末になって本当に嬉しいよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_4":
			dialog.text = ""+npchar.name+"。俺はこの船の甲板長だ。";
			link.l1 = "ははっ、お前に逆らう奴なんて見てみたいもんだぜ。船長の下で仕えて長いのか？";
			link.l1.go = "SharlieEpilog_Moko_5";
		break;

		case "SharlieEpilog_Moko_5":
			dialog.text = "数年になる。俺はあいつに大きな借りがあるんだ。あいつがいなければ、俺は……で腐っていただろうな……";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Moko_6";
		break;

		case "SharlieEpilog_Moko_6":
			dialog.text = "...";
			link.l1 = "「プランテーションでのことか？」";
			link.l1.go = "SharlieEpilog_Moko_7";
		break;

		case "SharlieEpilog_Moko_7":
			dialog.text = "...";
			link.l1 = "「さあ、」 "+npchar.name+"もちろん、何も話さなくてもいいんだが、まだ気づいてないなら言っておくぜ、 俺はあのカツラをかぶった貴族どもとは違うんだ。船長があんたを助け出したのか？";
			link.l1.go = "SharlieEpilog_Moko_8";
		break;

		case "SharlieEpilog_Moko_8":
			dialog.text = "俺たちは一緒に逃げ出したんだ。マラカイボのプランテーションからさ。ジャンがいなけりゃ、絶対に無理だったぜ。 そっからずっと、俺はあいつの乗組員だ。最初は水夫、今じゃ――俺が甲板長さ。";
			link.l1 = "船長が奴隷だったのか？全然想像もできなかったぜ。まあ、俺にも隠してる過去がいくつかあるけどな。 スペイン野郎の支配からよく逃げられたもんだ、嬉しいぜ。 "+npchar.name+"「……それで、水夫になった気分はどうだ？」";
			link.l1.go = "SharlieEpilog_Moko_9";
		break;

		case "SharlieEpilog_Moko_9":
			dialog.text = "今まで本当に生きていた気がしない。今や海こそが俺の居場所だ。";
			link.l1 = "ここは君の気持ちがよくわかるよ、友よ。誰よりもね。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_repeat":
			dialog.text = "Captain "+pchar.lastname+"「……どうなさいましたか？」";
			link.l1 = "「ありがとう」 "+npchar.name+"「今は何も必要ありません。」";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		//Диалог с дворянином Бернардом
		case "SharlieEpilog_Bernard_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"！この船で少なくとも一人は分別のある顔を見られて本当に嬉しいですわ。この……水夫たち……まるで野蛮人ですの。";
			link.l1 = "俺があんたの立場なら、他人の船でそんな口はきかねえな。どうやってカリブに来たか知らねえが、 ここじゃやり方が違うんだぜ。乗組員にはちゃんと敬意を払った方が身のためだぞ。";
			link.l1.go = "SharlieEpilog_Bernard_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;

		case "SharlieEpilog_Bernard_2":
			dialog.text = "「敬意？あいつらに？奴らは野蛮人だ！私は貴族だぞ。」 "+GetTitle(NPChar,true)+"…私は秩序に慣れているし、仕える者がいるのが当然で…文明というものにも！もし私に逆らう者がいれば――父上が…";
			link.l1 = "お前の父親には、お前が道中で熱病で死んだと伝えてやるさ。どうせ証明のしようもねえだろうよ。";
			link.l1.go = "SharlieEpilog_Bernard_3";
		break;

		case "SharlieEpilog_Bernard_3":
			dialog.text = "あのフォックス大佐め！全部あいつのせいだ！あの娘のために、俺は大西洋を渡り、自分の快適な暮らしを捨てて、 あの冷たい視線や、あのひどい食事、そして……この終わりなき揺れまで耐えてきたんだ！それなのに今じゃ、他人の船で航海してるなんて！";
			link.l1 = "フォックス大佐……";
			link.l1.go = "SharlieEpilog_Bernard_4";
		break;

		case "SharlieEpilog_Bernard_4":
			dialog.text = "「彼と面識がありますか、」 "+GetTitle(NPChar,true)+"?";
			link.l1 = "ゴホン…彼のことは聞いたことがある。";
			link.l1.go = "SharlieEpilog_Bernard_5";
		break;

		case "SharlieEpilog_Bernard_5":
			dialog.text = "そうか、それなら特に見逃したものはないな。あの男はまさに盲目的な軍人の頑固さと偏見の権化だ。";
			link.l1 = "彼は兵士だ……";
			link.l1.go = "SharlieEpilog_Bernard_6";
		break;

		case "SharlieEpilog_Bernard_6":
			dialog.text = "まさにその通り！それがすべてを物語っているんだ。\n娘さんとの面会をお願いしに行ったとき、彼がどうしたか知ってるか？わかるか？\n一言も発さずに、俺を追い出したんだよ！";
			link.l1 = "でも、引かなかったよね、でしょ？";
			link.l1.go = "SharlieEpilog_Bernard_7";
		break;

		case "SharlieEpilog_Bernard_7":
			dialog.text = "もちろんだ！面会を求めて一週間も費やしたんだぞ！頭を下げて頼み込んだ！挙句の果てには……衛兵を買収しようとまでしたんだ！結局、招待もなしにこっそり入り込むことに成功したんだ。 ただ話がしたかっただけなんだ！";
			link.l1 = "彼はそのことをあまり喜んでいなかったと思う。";
			link.l1.go = "SharlieEpilog_Bernard_8";
		break;

		case "SharlieEpilog_Bernard_8":
			dialog.text = "私に会えて嬉しい？ああ、父さんは本当に大騒ぎしたんだよ！私は追い出されて、屋敷に近づくのも禁止されて、 父さんの船も没収されてさ、挙句の果てにはイギリス人船長全員に私を乗せるなってお達しまで出たんだ！ 仕方なくマルティニークでフランス船を探す羽目になったよ……悪夢だったよ。";
			link.l1 = "どうやら本気で怒らせてしまったようだな。";
			link.l1.go = "SharlieEpilog_Bernard_9";
		break;

		case "SharlieEpilog_Bernard_9":
			dialog.text = "彼はいつも私に反対していた。彼のお気に入りの言葉は「士官の娘は士官の妻になるものだ」だった。あなた、 "+GetTitle(NPChar,true)+"、彼はもっとふさわしい結婚相手だと考えていた。";
			link.l1 = "もしかすると、今回は他にも理由があったのかもしれない……";
			link.l1.go = "SharlieEpilog_Bernard_10";
		break;

		case "SharlieEpilog_Bernard_10":
			dialog.text = "...";
			link.l1 = "それで、あなたはここに愛しい人に会いに来たのですね。";
			link.l1.go = "SharlieEpilog_Bernard_11";
		break;

		case "SharlieEpilog_Bernard_11":
			dialog.text = "そうだ。彼女がヨーロッパを離れてから、一通も手紙を受け取っていないんだ。 きっと彼女の父親が郵便を途中で止めているに違いない。彼女が僕のことを忘れるはずがない！もちろん、 彼女は僕に対して控えめだった…いや、冷たかったくらいだ…でも、僕のことを人生から消し去ったなんて信じられない。";
			link.l1 = "お悔やみ申し上げます、旦那。心の傷は肉体の傷よりも遥かに癒えるのが遅いものです。しかし……おや？なぜあなた、イギリス人がボルドーへ向かっているのですか？";
			link.l1.go = "SharlieEpilog_Bernard_12";
		break;

		case "SharlieEpilog_Bernard_12":
			dialog.text = "恥をかいて帰るつもりはないよ。事が落ち着くまでボルドーの伯父のところに滞在しなきゃならないな。\nそれにしても、伯父の屋敷はうちよりずっと広くて優雅だし、召使いたちもずっとよく訓練されているんだ。";
			link.l1 = "まあ、これは最悪の結果ってわけじゃないだろう。\n新しい恋人だって見つかるかもしれないぞ。ボルドーには若くて美しい娘がたくさんいるんだ、信じてくれ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
		break;
		
		case "SharlieEpilog_Bernard_repeat":
			dialog.text = "「いつになったら、ついに到着するのかしら」 "+GetTitle(NPChar,true)+"？私、このような……紳士たちに囲まれて耐えがたいほど苦しんでおりますわ。今すぐお風呂に入らなくてはなりませんの。";
			link.l1 = "残念だが、これから二ヶ月の間は彼女のことを夢見るしかできないよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;
		
		//Диалог с Книппелем на корабле Улисс
		case "SharlieEpilog_Knippel_1":
			dialog.text = "この凪め、呪ってやる。チェーンショットでもぶち込んでやりたいぜ。";
			link.l1 = "「文句を言うな」 "+npchar.name+"「そのうち、風は必ず吹くさ。」";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "「それまで私はどうすればいいんだ、旦那？大砲の点検すらできやしない……何しろ、他人の船の上なんだからな。」";
			link.l1 = "少しはリラックスしてみてください。いつも働いてばかりじゃなくてもいいんですよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		case "SharlieEpilog_Knippel_repeat":
			dialog.text = "ちくしょう、無風か……";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		//Диалог с Лонгвэем на корабле Улисс
		case "SharlieEpilog_Longway_1":
			dialog.text = "悪くない船ですね、船長。あなたもそう思いますか？";
			link.l1 = "「メイフェンよりもさらに上か？」";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = "For "+npchar.name+" メイフェン号より優れた船なんてない。この船ほど風上ぎりぎりを帆走できる船は、もう現れないわ。";
			link.l1 = "「落ち着いて」 "+npchar.name+"、冗談だよ。もちろん、梅鳳は別格さ。でもユリシーズも立派な船だ。堅実だよ。";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = ""+npchar.name+" 舵を握ること。自分の手に船が応えてくる感覚を味わうこと……";
			link.l1 = "あいにくだが、友よ、この船は他の誰かのものだ。向こうにいる大男に試合を申し込んでみたらどうだ？ お互いにいい刺激になるさ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		case "SharlieEpilog_Longway_repeat":
			dialog.text = "「追い風なら、どれくらい速く進めるんだ？」";
			link.l1 = "「はっきりとは言えません」 "+npchar.name+"。彼らの航海士に聞いたほうがいいぞ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		//Диалог с Тонзагом на корабле Улисс
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "ここにいる水夫長の巨漢を見たか？片手でココナッツを潰せるって話だぞ。";
			link.l1 = "ははは。どうやらあいつのこと、ちょっと怖がってるんじゃねえか？";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "そんなこと気にする必要ある？大きさが全てじゃないよ。もっと大きいのも扱ったことあるんだから。";
			link.l1 = "それなら、あいつに拳で勝負を挑んだらどうだ？一対一で――正々堂々とな。";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "ううっ……";
			link.l1 = "少し顔色が悪くなったな。ははは。まあ、嫌なら仕方ないさ。あんたのもう若くない骨をいたわってやろう。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		case "SharlieEpilog_Tonzag_repeat":
			dialog.text = "この海域には魚があふれていて、船ですくい上げられるほどだが、こいつら怠け者どもは網を投げることすらしやしねえ。 ";
			link.l1 = "あいつらの甲板長に話してこい。お前のそのコメント、きっと気に入るぜ、へっへっ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		//Диалог с Тичингиту, охраняющим золото
		case "SharlieEpilog_Tichingitu_21":
			dialog.text = "金は無事です、船長 "+pchar.name+"。Tichingituがしっかり彼を守ってくれるだろう。";
			link.l1 = "ありがとう、友よ。まもなくアロンソが君の代わりを務めるだろう。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tichingitu_21";
		break;
		
		//Диалог с Книппелем, охраняющим золото
		case "SharlieEpilog_Knippel_21":
			dialog.text = "ぶったまげたぜ、旦那、このボロ船には俺が今まで見たこともねえほどネズミがいるじゃねえか。";
			link.l1 = "船は手入れもされずに長い間港に放置されていた。\n新しい乗組員たちがすぐにそれらを片付けるだろう。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_21";
		break;
		
		//Диалог с Лонгвэем, охраняющим золото
		case "SharlieEpilog_Longway_21":
			dialog.text = "ロングウェイが鎖の音を聞いた。\n船長、錨を下ろしたのか？";
			link.l1 = "ヒューズを飛ばしたのは我々の乗客だった。\n今のところ風はまだとても弱いが、長くは続かないといいんだがな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_21";
		break;
		
		//Диалог с Тонзагом, охраняющим золото
		case "SharlieEpilog_Tonzag_21":
			dialog.text = "ああ、くそ……今は強いラム酒を一杯やりたいもんだぜ。";
			link.l1 = "夕食はもうすぐできるから、頑張ってくれ。アロンソが代わりにやってくれるぞ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_21";
		break;
		
		//Диалог с Мэри перед походом в каюту
		case "SharlieEpilog_Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+"、愛しい人、気分はいかがですか？";
			link.l1.go = "SharlieEpilog_Mary_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_12":
			dialog.text = "...";
			link.l1 = "おいでよ、ダーリン。僕がちょっとワインを買いに店へ行っただけで、本当に怒ってるのかい？";
			link.l1.go = "SharlieEpilog_Mary_13";
		break;

		case "SharlieEpilog_Mary_13":
			dialog.text = "ワインを買いに店へ行ってたのかい？せめて一言くらい言ってくれてもいいじゃない！ あんたが娼館にでも行ってたんじゃないかって、どうやって分かれっていうのよ――女と一緒に……それとも全員まとめて！？";
			link.l1 = "「愛しい人よ、私が本当にそんな危険を冒すと思いますか？私はこの群島で一番美しくて賢くて、 しかも猛烈に嫉妬深い妻を持っているのですよ。そんな私が、 安っぽい波止場の女たちなんかに時間を無駄にすると本気で思っているのですか？」";
			link.l1.go = "SharlieEpilog_Mary_14";
		break;

		case "SharlieEpilog_Mary_14":
			dialog.text = "せめて一言くらい声をかけてくれてもよかったでしょ！あたし、そこに座ってたんだから…";
			link.l1 = "約束するよ、次は話すだけじゃなくて、一緒に連れて行くからね。\nでも今は……急に気になっちゃったんだ、船長室の家具がちゃんとしてるかどうか。特にベッドがね。\n確かめに行こうか？";
			link.l1.go = "SharlieEpilog_Mary_15";
		break;

		case "SharlieEpilog_Mary_15":
			dialog.text = ""+pchar.name+"……もし誰かが入ってきたらどうするの？\nふふ……今はもっと欲しくなっちゃったわ。";
			link.l1 = "それなら、一瞬たりとも無駄にしないでおこう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Элен перед походом в каюту
		case "SharlieEpilog_Helena_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+"、私の愛しい人、気分はいかがですか？";
			link.l1.go = "SharlieEpilog_Helena_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_12":
			dialog.text = "...";
			link.l1 = "おいでよ、ダーリン。僕がちょっとワインを買いに店へ行っただけで、本当に怒ってるのかい？";
			link.l1.go = "SharlieEpilog_Helena_13";
		break;

		case "SharlieEpilog_Helena_13":
			dialog.text = "私も連れて行ってくれてもよかったのに。もしかして、 あなたのちっぽけな悪友たちより私の方が役に立たないとでも思ってるの？";
			link.l1 = "あなたなら簡単に彼らを凌駕すると思いますわ。\nでも、そのときはワインのことなんて頭から消えてしまうでしょうね。";
			link.l1.go = "SharlieEpilog_Helena_14";
		break;

		case "SharlieEpilog_Helena_14":
			dialog.text = "それで、何についてだ？";
			link.l1 = "あの時その場であなたとこっそり抜け出すことについて……今もその考えが頭から離れないの。";
			link.l1.go = "SharlieEpilog_Helena_15";
		break;

		case "SharlieEpilog_Helena_15":
			dialog.text = "そうなの？それで、具体的にどこに好奇の目から隠れるつもりなの？";
			link.l1 = "船長室にて。彼のベッドの頑丈さを試してみるべきだと思うわ。";
			link.l1.go = "SharlieEpilog_Helena_16";
		break;

		case "SharlieEpilog_Helena_16":
			dialog.text = "ははっ。もし船長に見つかったらどうする？\nでも……そのことを考えるだけで、胸がドキドキしちゃうよ。";
			link.l1 = "それじゃあ、時間を無駄にしないで行こう！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Мэри в каюте
		case "SharlieEpilog_Mary_21":
			dialog.text = "素晴らしかったわ、私の船長…\nあなたにお知らせがあるの。";
			link.l1 = "「知らせかい？全部聞かせてくれ。」";
			link.l1.go = "SharlieEpilog_Mary_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Mary_22":
			dialog.text = ""+pchar.name+"…子どもができるの。私、妊娠してるんだよ、でしょ？";
			link.l1 = "私の愛しい人……本当なの？";
			link.l1.go = "SharlieEpilog_Mary_23";
		break;

		case "SharlieEpilog_Mary_23":
			dialog.text = "「あなたは父親になるのよ」 "+pchar.name+"!";
			link.l1 = ""+npchar.name+"…これは信じられない！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Mary_31":
			dialog.text = "「あなたは幸せですか、私の愛しい人？」";
			link.l1 = "幸せかって？冗談だろ？くそっ、俺は世界一幸せな男だぜ！でも…どうしてもっと早く教えてくれなかったんだ？";
			link.l1.go = "SharlieEpilog_Mary_32";
		break;

		case "SharlieEpilog_Mary_32":
			dialog.text = "出発を遅らせるの？私は本当にあなたのお父様にお会いしたいのですわ。 "+pchar.name+".";
			link.l1 = ""+npchar.name+"…愛してる！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		//Диалог с Элен в каюте
		case "SharlieEpilog_Helena_21":
			dialog.text = "あなたはいつも通り最高だったわ、ダーリン。あなたに知らせたいことがあるの。";
			link.l1 = "「知らせかい？聞かせてくれ。」";
			link.l1.go = "SharlieEpilog_Helena_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Helena_22":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+"「モンペ騎士、あなたは父親になるのです。」";
			link.l1 = "「それは…本当なの？」";
			link.l1.go = "SharlieEpilog_Helena_23";
		break;

		case "SharlieEpilog_Helena_23":
			dialog.text = "私が背負うこの名と同じくらい確かなことだ "+npchar.name+"……半年も経たないうちに、私たちの子供が生まれるわ――小さなムッシュ・ド・モール……それとも、マドモワゼルかしら。";
			link.l1 = "エレーヌ……これは信じられません！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Helena_31":
			dialog.text = "...";
			link.l1 = "「だから俺たちの出航祝いに一緒に飲まなかったのか！でも…どうして先に言ってくれなかったんだ？」";
			link.l1.go = "SharlieEpilog_Helena_32";
		break;

		case "SharlieEpilog_Helena_32":
			dialog.text = "あなたが危険を冒さずに諸島に留まると決めてしまうのではないかと心配していました。\nあなたにはお父様の願いを叶えてほしかったのです。そして……私自身も、ぜひお父様にお会いしたいのです。";
			link.l1 = ""+npchar.name+"……愛してる！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		// Диалог с Пикаром
		case "SharlieEpilog_PikarInCabin_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "ほうほう……で、ここで何をしているんだ？小さなガスコーニュ人でも作ってるのか？";
				link.l1 = "ハハハ！俺に息子ができるんだ、 "+npchar.name+"「！俺、父親になるんだ！」";
				link.l1.go = "SharlieEpilog_PikarInCabin_1_1";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"「……船長の許可もなく船長室を使うなんて、いくらあなたほどの身分でもやりすぎじゃありませんか？」";
				link.l1 = "申し訳ありません、船長。でもちゃんとした理由があるんです！私、父親になるんですよ！";
				link.l1.go = "SharlieEpilog_PikarInCabin_12";
			}
			SharlieEpilog_PikarInCabin_camera_2();
		break;
		
		case "SharlieEpilog_PikarInCabin_1_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_2":
			dialog.text = "「あるいは娘も！」";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_2_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_2_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_3", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_3":
			dialog.text = "俺に隠してたのか、この野郎！？俺はお前のこと友だちだと思ってたのによ！";
			link.l1 = "俺も今知ったばかりだ！信じられるか？俺がだぜ！俺、父親になるんだ！";
			link.l1.go = "SharlieEpilog_PikarInCabin_4";
		break;

		case "SharlieEpilog_PikarInCabin_4":
			dialog.text = "ははは！本当に嬉しそうだな、相棒！こんな君を見るのは初めてだぜ\nさて、二人でゆっくり話してくれ。俺は祝砲の準備に取りかかる。準備ができて号令をかける時は教えてくれよ。";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;

		case "SharlieEpilog_PikarInCabin_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				sld = CharacterFromID("Mary");
			}
			dialog.text = "はは……信じてくれ、君がここに来た理由はなんとなく察していたよ。";
			link.l1 = "いいえ、もちろん違うよ！ "+sld.name+" 私、妊娠したの！男の子を産むのよ！";
			link.l1.go = "SharlieEpilog_PikarInCabin_12_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_12_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_13":
			dialog.text = "「あるいは娘も！」";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_13_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_13_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_14", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_14":
			dialog.text = "ええと……心からお祝い申し上げます！\n祝砲は私が手配します――全ての大砲で盛大にやりますので、ご命令の準備ができたらお知らせください。\nそれまでは……船室をご自由にお使いください。";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;
		
		// Диалог с Пикаром после интима с женой
		case "SharlieEpilog_PikarZalp_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "ええと……父上……すぐにまた跡継ぎを作るおつもりですかな？";
				link.l1 = "ははっ！俺に任せりゃ、一度に一ダースでもぶっ放してやるぜ！さあ、相棒、全砲門で一斉射撃といこうじゃねえか？";
				link.l1.go = "SharlieEpilog_PikarZalp_2";
				link.l2 = "残念ながら、そう簡単にはいかないんだ、友よ。だが、俺たちは最善を尽くしたぜ。";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"...";
				link.l1 = "さて、船長、全砲門で一斉射撃をお見舞いしますか？";
				link.l1.go = "SharlieEpilog_PikarZalp_3";
				link.l2 = "「今はだめだ。」";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_PikarZalp_1";
		break;
		
		case "SharlieEpilog_PikarZalp_2":
			dialog.text = "乗組員たちはあなたの命令を待っているだけです！号令をかけてください、 "+GetTitle(NPChar,true)+".";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_3":
			dialog.text = "乗組員は準備万端です。命令を出してください。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_final":
			dialog.text = "...";
			link.l1 = "砲手たち！全砲門発射！撃て！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_ZalpInSea");
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(pchar, "quest", "quest10");
			CharacterTurnToLoc(npchar, "quest", "quest10");
		break;
		
		// Диалог с отцом в поместье де Монпе
		case "SharlieEpilog_HenriDeMonper_1":
			NextMonth = GetDataMonth() + 2;
			if (NextMonth == 13) NextMonth = 1;
			else if (NextMonth == 14) NextMonth = 2;
			Month = XI_ConvertString("MonthVoc_" + NextMonth);
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"…なんと嬉しいことか、息子よ！";
			if (GetDataMonth() >= 4 && GetDataMonth() <= 10)
			{
				link.l1 = "父上……まさかまた家に戻ってくるなんて……雪がどんなものだったか、ほとんど忘れかけていました。ここはまるで何も変わっていないように感じます……";
			}
			else
			{
				link.l1 = "父上……また家に戻ってきたなんて信じられません……この日を祝うかのように、雪まで降ってきたようですね。 "+month+"……ここはまったく何も変わっていないな……";
			}
			link.l1.go = "SharlieEpilog_HenriDeMonper_2";
			locCameraFromToPos(-8.76, 7.86, 0.75, true, -7.41, 6.11, 0.18);
			Achievment_Set("ach_CL_202");
		break;
		
		case "SharlieEpilog_HenriDeMonper_2":
			dialog.text = "お前には同じことは言えねえな！その立ち振る舞い、歩き方、その傷跡\n"+"いいえ、今私の前に立っているのは、かつて私が遠い地へ送り出した甘やかされた少年ではもうありません。";
			link.l1 = "カリブではすぐに大人になりますよ、お父様。でも、その話はまた後でゆっくりしましょう。\nさて、ご健康はいかがですか？こうして正装で私の前に立っていらっしゃるということは、 ご病気も快方に向かわれたのでしょうか？";
			link.l1.go = "SharlieEpilog_HenriDeMonper_3";
		break;
		
		case "SharlieEpilog_HenriDeMonper_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				dialog.text = "「ああ、」 "+pchar.name+"、彼女はますます私の首にしがみついた。しかし、私は本当に愛する息子を普段着で迎えてよいのだろうか？私にとって、 今日は特別な日なのですわ、 "+pchar.name+"\n"+"どうやら私に紹介したい人がいるようですね。";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_10");
			}
			else
			{
				dialog.text = "「ああ、」 "+pchar.name+"、年月を重ねるごとに彼女の支配はますます強まっている。しかし、私は本当に愛する息子に普段着で会えるだろうか？ 私にとって今日は特別な日なのだ、 "+pchar.name+"\n"+"一人では来なかったようだな\n"+"旅の後でお腹が空いているだろう？シュザンヌが君の好みに合わせてガチョウの肝を用意してくれたぞ！\n"+"テーブルに来てくれ――その途中で私たちを紹介してくれよ！";
				link.l1 = "正直に言うと、屋敷に近づいた時からその香りを感じていたよ！";
				link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "...";
			link.l1 = "父上、私の妻を紹介させていただきます―― "+sld.name+" "+pchar.lastname+". "+sld.name+"、こちらが私の父、シュヴァリエです "+GetCharacterName("Henri")+" "+GetCharacterName("ド・モンペール")+".";
			link.l1.go = "SharlieEpilog_HenriDeMonper_5";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
				dialog.text = ""+pchar.name+"、本当に感激しております！あなたの花嫁は、こちらで見慣れた甘やかされた社交界のご令嬢方とはまるで違いますね。 船の扱いも、私の息子の心を操るのと同じくらい見事だと申し上げてもよろしいでしょう。";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_1";
				CharacterTurnByChr(npchar, sld);
			}
			else
			{
				sld = CharacterFromID("Mary");
				dialog.text = "お会いできて大変光栄でございます、奥様。私の息子の趣味は素晴らしいと自信を持って申し上げます！";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_1";
				CharacterTurnByChr(npchar, sld);
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2":
			dialog.text = "お褒めいただき光栄ですわ、シュヴァリエ！おっしゃる通り、どんな荒れ狂う嵐の中でも舵を取ることはできますの。 でも、あなたのご子息の心については――操縦する必要はありませんわ。私たちは目指すものも志も、一つに結ばれておりますの。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_2_1";
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_3":
			dialog.text = "ベノワ院長はあなたのことを賢く勇敢な若い女性だと評していました――どうやら誇張ではなかったようですね。私は嬉しく思います、 "+pchar.name+" 私はあなたに、ただの妻ではなく、心の伴侶を見つけました\n"+"旅の後でお腹が空いているでしょう。シュザンヌがあなたの好みに合わせてガチョウのレバーを用意してくれましたよ！\n"+"それでは皆さん、ご一緒にテーブルにつきましょう！\n道中で、もっとお互いを知り合えるといいですね。";
			link.l1 = "認めざるを得ません、屋敷に近づいた時からその香りを感じていましたよ！";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2":
			dialog.text = "お会いできて光栄ですわ、シュヴァリエ！ "+pchar.name+" あなたのことはたくさん聞いてたよ、そしてまさにこんな人だって想像してたんだ、でしょ！";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_2_1";
			CharacterTurnByChr(pchar, npchar);
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_3":
			sld = CharacterFromID("Mary");
			dialog.text = ""+pchar.name+"、私は感激しております！あなたの花嫁はサロンの白粉まみれのご婦人方とはまるで違います――それこそが本当の価値ですわ\n"+"あなたは甘やかされた気まぐれなユリよりも、美しいバラを選んだと思います。";
			link.l1 = "ワイルドローズ号ですよ、お父様…… "+sld.name+"  - 本当に宝物だよ。きっと君も彼女のことをもっと知れば、私に同意してくれるはずさ。";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_4";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_4":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "ты познакомишь меня с остальными";
			else sStr = "ты представишь меня нашему гостю";
			dialog.text = "それでは、この瞬間を引き延ばすのはやめましょう！旅の後でお腹も空いているでしょう。 シュザンヌがあなたのお好み通りにガチョウのレバーを用意してくれましたよ！\n"+"皆、席につけ！そして向かう途中で、私は願っている "+sStr+"";
			link.l1 = "認めざるを得ませんが、屋敷に近づいた時からその香りを感じていましたよ！";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			CharacterTurnByChr(CharacterFromID("HenriDeMonper"), pchar);
		break;
		
		case "SharlieEpilog_HenriDeMonper_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_14");
		break;
		
		case "SharlieEpilog_HenriDeMonper_7":
			dialog.text = "...";
			link.l1 = "あなた、ぜひこれを食べてみてちょうだい――うちの家伝のレシピで作ったガチョウの肝は、他のどんな料理とも比べものにならないのよ！ 祖父の代から伝わっているの。地中海のどこかの国から贈られたものなのですわ。";
			link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_15");
		break;
		
		// диалог на ужине в поместье де Монпе
		case "SharlieEpilog_InKitchenDeMonpe":
			dialog.text = "";
			link.l1 = "宴の始まりに暗い話をするのは本意ではありませんが、家族として、私たちは先人たちを忘れてはなりません。\n皆さん、グラスをミシェルのために掲げてください。\n主が彼の魂に安らぎを与えてくださいますように。";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_2":
			dialog.text = "";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "добрых друзей";
				else sStr = "соратника";
				dialog.text = "";
				link.l1 = "「あなたに聞きたいことが山ほどあります」 "+pchar.name+"…だがまず、奥方にお言葉をいただいてからにしよう\n "+sStr+"。どうか、シャルルとどのように出会ったのか教えてください。";
			}
			else
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "твоих добрых друзей";
				else sStr = "твоего друга";
				dialog.text = "";
				link.l1 = "あなたに聞きたいことが山ほどあります。 "+pchar.name+"…しかし、その前に一言言わせてください "+sStr+"。どうか教えてください、あなたはどうやってシャルルと出会ったのですか？";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		// if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
		
		case "SharlieEpilog_InKitchenDeMonpe_4":
			dialog.text = "";
			link.l1 = "私もあなたと同じくらいこれを聞くのが楽しみだよ！";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "私の命は死の危険にさらされていた…… "+pchar.name+"本物の紳士みたいに、何も悪いことは起こさせなかったよ！私を守ってくれて、あの悪党どもをやっつけてくれたんだ、 でしょ！";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = ""+pchar.name+" イギリスの悪党の手から私を奪い返してくれたのよ、あいつは…私を誘拐しようとしたの。もしあなたがあと一時間でも遅れていたら、私たちは決して出会えなかったでしょ？";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5_1":
			dialog.text = "";
			link.l1 = "彼が本物の貴族として行動することを、私は決して疑いませんでした。\n名誉は我が家にとって、ただの言葉以上のものです。\n私はお前を誇りに思うぞ、息子よ。";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = ""+sld.name+" 白い顔の奴の家に忍び込んで食い物を探す。白い顔の奴に見つかる "+sld.name+" - そして投獄された。船長 "+pchar.name+" 来て助けて "+sld.name+" 牢獄から。それ以来 "+sld.name+" 船長に仕える "+pchar.name+" 「そして最期の息まで誠実でいるわ。」";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6_1":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = "息子がただの貴族であるだけでなく、思いやりのある人間でもあると知って、私の心は温かくなる。\n彼のそばにあなたのような忠実な友がいることを嬉しく思う。 "+sld.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "その船長はかつて仕事を求めて私の家にやって来た。私は彼に任務を与え、彼は見事にやり遂げた。親分は彼を気に入り、 どんどん自分の仕事に引き込んでいったが、私は監視役として彼の船に送られた……そしてあの旦那が、こっそり錨を上げて、俺の髭めがけて砲弾をぶちかまし、 船長には一言も告げずに諸島を出て行きやがった。自分でかき回した厄介事の中に、船長を一人残してな。 俺は船長に自分の力を貸すと申し出た。リチャードが船長にひどい仕打ちをしたってのに――尻めがけて砲弾をぶち込んだってのに――船長は俺を追い返さなかったんだ。";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "ロングウェイと善良な船長は同じ男に仕えていた。しかし、その男はロングウェイを裏切った。 だからロングウェイは決めた――二度とあの男には仕えないと。善良な船長は俺を自分の船に士官として迎え入れ、 ロングウェイのために多くのことをしてくれたんだ。";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "初めて出会ったのは、ブリッジタウンの酒場だった： "+pchar.name+" 彼は自分の信じる大義を探していて、私は信頼できる腕を求めていた。\nあの出会いはほんの始まりに過ぎなかった――やがて、私たちの運命を結びつける出来事が次々と起こった。\n私は彼の部下となり、今では迷いなく彼を友と呼べる。命を懸けても惜しくない男だ。";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7_2":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "状況の裏にいる人間を見抜くのは、稀有な才能だ。\nつまり、私の息子もなかなか分別があるということだな。";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "私の息子がただの冷酷な兵士ではなく、仲間を思いやる本当の指導者になったことを嬉しく思う。";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "そんな言葉を聞けるのは滅多にないことだ。\n息子が腕の立つ船乗りであるだけでなく、本当の友でもあるという何よりの証拠だろうな。";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8":
			dialog.text = "";
			link.l1 = "ボルドーで出会ったんだ。キャプテンは乗客として俺たちの船に乗り込み、マルティニークまで送り届けた。それ以来――ここに送られるまでずっと、俺は彼の乗組員の代表として声を上げ、そして見守ってきたんだ\n "+GetFullName(pchar)+" 一歩一歩、彼は今の自分になっていった。";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8_1":
			dialog.text = "";
			link.l1 = "なるほど、あなたはあの手に負えない若造だった頃のシャルルを知っていたのですね、 私が家を出るように強く言ったあの時の。\n旦那、あなたと私には語り合うことがたくさんありそうですな。";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_9";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_9":
			dialog.text = "";
			link.l1 = "「あなた」 "+pchar.name+"、あなたは長く輝かしい道のりを歩んできましたね……野兎の毛皮を求めて荒野に踏み出したのに、結局はライオンと戦い、その皮を肩に担いで凱旋したのです。\n今ほど我が家や領地の行く末に安心できる時はありません。";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_10";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_10":
			dialog.text = "";
			link.l1 = "一刻も早く我が家の家督をお前に引き継ぎたいと思っている。\n仕事は山ほどあるが、主ご自身がきっとお前を見守ってくださると信じている。\nお前は託された遺産を守るだけでなく、de Montpe家の名誉と財産をさらに高めてくれるだろう。";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_11";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_11": //выбор Шарля
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = "私があなたの息子であり後継者であることは、この上ない名誉でございます。家の責任は喜んで全て引き受けます。 妻もきっと私の大きな支えとなってくれると確信しております。この名にさらなる栄光をもたらすため、 できる限りのことを尽くすとお約束いたします……そして、我が家の繁栄への第一歩は、子の誕生でございます！";
				link.l1.go = "SharlieEpilog_ChooseEstate_HaveWife_1";
			}
			else
			{
				link.l1 = "私があなたの息子であり後継者であることは、私にとって大変な名誉でございます。\n喜んで我が家のすべての責任を引き受け、家名にさらなる栄光をもたらすために全力を尽くすことをお約束いたします。";
				link.l1.go = "SharlieEpilog_ChooseEstate_Single_1";
			}
			link.l2 = "父上、私の新世界での年月は私を変えました。もうヨーロッパのこの穏やかな生活には馴染めそうにありません。";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_HaveWife_1";
			}
			else
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_Single_1";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		// --> Выбрал остаться в поместье с женой
		case "SharlieEpilog_ChooseEstate_HaveWife_1":
			dialog.text = "";
			link.l1 = ""+pchar.name+"……まさか……";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_HaveWife_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "「はい、お父様。」 "+sld.name+" 妊娠している。";
			link.l1.go = "SharlieEpilog_HaveWife_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_13":
			dialog.text = "";
			link.l1 = "これは本当に素晴らしい知らせだ、我が息子よ！主が私の祈りを聞き届けてくださったのだ！ ここにいる皆も証人となってくれ。新たな命の誕生を祝して、我が領地でこれまでにない盛大な舞踏会を開こう！さあ、 杯を掲げよう――後継者に乾杯！";
			link.l1.go = "SharlieEpilog_HaveWife_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_HaveWife_14":
			dialog.text = "";
			link.l1 = "「あるいは、女相続人かも！」";
			link.l1.go = "SharlieEpilog_HaveWife_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_15":
			dialog.text = "";
			link.l1 = "我が家の物語の新たな章に乾杯！";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_16":
			dialog.text = "";
			link.l1 = "未来の戦士、あるいは良き娘に乾杯！";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_HaveWife_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "「新生児の健やかな成長を祝して！」";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "あなたたちを巡り合わせた巡り合わせに乾杯！";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "ご家族の明るい未来に乾杯！";
			}
			link.l1.go = "SharlieEpilog_HaveWife_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_HaveWife_18":
			dialog.text = "";
			link.l1 = "未来のアロンソ・ド・モール、あるいは小さなアロンシータ・ド・モールに乾杯！";
			link.l1.go = "SharlieEpilog_HaveWife_19";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_HaveWife_19":
			dialog.text = "";
			link.l1 = "あははは！";
			link.l1.go = "SharlieEpilog_HaveWife_20";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_20":
			dialog.text = "";
			link.l1 = "「ははっ！」";
			link.l1.go = "SharlieEpilog_HaveWife_21";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_21":
			dialog.text = "";
			link.l1 = "「ハハハ！」";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_toast":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_toast");
		break;
		// <-- Выбрал остаться в поместье с женой
		
		// --> Выбрал остаться в поместье будучи холостяком
		case "SharlieEpilog_ChooseEstate_Single_1":
			dialog.text = "";
			link.l1 = "私があなたの息子であり後継者であることは、この上ない名誉でございます。\n喜んで我が家のすべての責任を引き受け、家名にさらなる栄光をもたらすために、 できる限りのことを尽くすことをお約束いたします。";
			link.l1.go = "SharlieEpilog_ChooseEstate_Single_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_ChooseEstate_Single_2":
			dialog.text = "";
			link.l1 = "「教えてくれ、 "+pchar.name+"、私のイヴォンヌとの結婚の提案について考えてくれましたか？";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_13":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_ChooseCaribbean"))
			{
				link.l1 = "認めますよ、お父様……イヴォンヌは私の心に本当に近い存在ではありませんでした。でも新世界には素晴らしい女性がたくさんいます。 約束します――運命の人に出会ったら、私は迷わず行動します。";
			}
			else
			{
				link.l1 = "認めますよ、お父様……イヴォンヌは私の心に近い存在ではありませんでした。でも、フランスには素晴らしい女性がたくさんいます。 約束します――本当にふさわしい人に出会ったら、私は迷わず行動します。";
			}
			link.l1.go = "SharlieEpilog_Single_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_14":
			dialog.text = "";
			link.l1 = "お前の心意気が気に入ったぞ、我が息子よ。さあ、杯を掲げよう——お前に、お前の功績に、そして立派な帰郷に乾杯だ！";
			link.l1.go = "SharlieEpilog_Single_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_15":
			dialog.text = "";
			link.l1 = "「新世界で生き抜くには欠かせない、本当の友に乾杯！」";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_Single_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_16":
			dialog.text = "";
			link.l1 = "「シャルル船長とその大きな心に乾杯！」";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_Single_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "船長の鉄の意志に乾杯！";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "「我らが船長の知恵に乾杯！」";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "「忠誠と大義に乾杯！」";
			}
			link.l1.go = "SharlieEpilog_Single_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_Single_18":
			dialog.text = "";
			link.l1 = "「いつも無傷で切り抜けることだ！」";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		// <-- Выбрал остаться в поместье будучи холостяком
		
		// Шарль губернатор разговаривает с зелёным капитаном
		case "SharlieEpilog_GreenCaptain":
			dialog.text = "";
			link.l1 = "かなりしつこく面会を求めていたと聞いている。\nそれで、マルティニーク総督に何の用だ？";
			link.l1.go = "SharlieEpilog_GreenCaptain_1";
			locCameraFromToPos(-1.80, 3.84, -9.08, true, -2.38, 2.21, -7.33);
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer_common_2.wav");
		break;
		
		case "SharlieEpilog_GreenCaptain_1":
			dialog.text = "フランス王家の利益に仕えることについて話したい。";
			link.l1 = "ああ、君には持ち前の機転と海戦の腕前が問われる任務があるんだ、でしょ？準備はできてる？ 自分を証明してみせてくれる？";
			link.l1.go = "SharlieEpilog_GreenCaptain_2";
		break;

		case "SharlieEpilog_GreenCaptain_2":
			dialog.text = "閣下、これからの任務の内容について詳しくご説明いただけますか？";
			link.l1 = "もちろんだ。スペインの連絡船『サンタ・エスペランサ』を見つけて乗り込み、 船長室で見つけた書類をすべて私のところに持ってきてほしい。 その船は約十二日後にトリニダード付近を通過する予定だ。";
			link.l1.go = "SharlieEpilog_GreenCaptain_3";
		break;

		case "SharlieEpilog_GreenCaptain_3":
			dialog.text = "でしょ？この仕事、引き受けるよ。どんな書類を探せばいいの？";
			link.l1 = "郵便のやり取りだ。その中には、私にとって非常に重要な書類も含まれている。\nだが、書類を一つ一つ確認する必要はない、そのまま全部まとめて持ってきてくれればいい。\nこの仕事の報酬として、君に一万五千ペソ支払おう……\nでは、結果を持って私の邸宅まで来てくれるのを待っているよ。";
			link.l1.go = "SharlieEpilog_GreenCaptain_4";
		break;

		case "SharlieEpilog_GreenCaptain_4":
			dialog.text = "「お待たせすることはないと思います、閣下。」";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_5");
		break;
		
		//Шарль разговаривает с комендантом форта
		case "SharlieEpilog_KomendantFort":
			dialog.text = "閣下……ご報告してもよろしいでしょうか？";
			link.l1 = "「報告せよ」 "+GetAddress_Form(NPChar)+" "+npchar.lastname+".";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) link.l1.go = "SharlieEpilog_KomendantFort_1";
			else link.l1.go = "SharlieEpilog_KomendantFort_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\military02.wav");
		break;
		
		case "SharlieEpilog_KomendantFort_1":
			dialog.text = "「ゴホン……」";
			link.l1 = "遠慮なく話してくれ。私の妻には隠し事などない。";
			link.l1.go = "SharlieEpilog_KomendantFort_2";
		break;
		
		case "SharlieEpilog_KomendantFort_2":
			dialog.text = "諜報報告：ウィレムスタッドから艦隊が出航した。艦隊を率いるのは二等戦列艦『ゴウデン・リュー』、 まさに海の怪物だ。艦隊は二百五十門以上の大砲と千五百人を超える兵士を擁している。標的はサン＝ピエールだ。";
			link.l1 = "ふむ……つまり、準備する時間はほとんどないということか。";
			link.l1.go = "SharlieEpilog_KomendantFort_3";
		break;

		case "SharlieEpilog_KomendantFort_3":
			dialog.text = "ご命令は何でしょうか、総督？";
			link.l1 = "幾隻かの船が停泊地に停めてあり、敵の背後を突く準備ができている……";
			link.l1.go = "SharlieEpilog_KomendantFort_4";
		break;

		case "SharlieEpilog_KomendantFort_4":
			dialog.text = "両側から攻撃するつもりか？";
			link.l1 = "その通りだ。砦が敵の砲火を引きつける。夜になったら、私の指揮下にある戦隊が海から攻撃を仕掛ける。 敵の注意を分散させた後、港から松ヤニと板を積んだ火船を送り込む。やつらの艦隊は木っ端微塵になるだろう。";
			link.l1.go = "SharlieEpilog_KomendantFort_5";
		break;

		case "SharlieEpilog_KomendantFort_5":
			dialog.text = "素晴らしいご計画でございます、公爵様！準備開始の命令を出しましょうか？";
			link.l1 = "始めよう。主が我らと共にあらんことを。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_11");
		break;
		
		// Стражник вызывает Алонсо
		case "SharlieEpilog_Guard":
			dialog.text = "";
			link.l1 = "護衛たち、アロンソを呼べ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoArrive");
		break;
		
		//Шарль разговаривает с Алонсо после коменданта
		case "SharlieEpilog_Alonso35":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")))
			{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
				dialog.text = "「総督、旦那…」";
				link.l1 = ""+npchar.name+"、オランダ艦隊は今にも到着して包囲を開始するだろう。私の命令を聞け。フィリップを連れて "+sld.name+"、すぐにそれらを修道院長のところへ連れて行け。彼に全ての女、子供、年寄りを集めさせ、安全を確保させろ。";
				link.l1.go = "SharlieEpilog_Alonso36_Wife";
				break;
			}
			dialog.text = "「総督、旦那…」";
			link.l1 = ""+npchar.name+"、オランダ艦隊が今にも到着して街を包囲するだろう。修道院長に、すべての女、子供、 老人を集めて安全を確保するよう伝えてくれ。\nお前には火船の指揮を任せるつもりだ。詳細は追って伝える。まず何よりも民間人の保護が最優先だ。";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;

		case "SharlieEpilog_Alonso36_Wife":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "そうは思わない "+sld.name+" 他の女たちと一緒にいることに同意するだろう。退屈で死にそうなのだ。";
			link.l1 = "ふむ……それなら、彼女に戦いの準備をさせろ。お前もぼんやりしてはいられないぞ――火船の指揮を任せる。詳しいことは後で話す。今は――私の息子を頼む。";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;
		
		case "SharlieEpilog_Alonso37":
			dialog.text = "光栄です！進めてもよろしいでしょうか？";
			link.l1 = "許可する。進め。私たちには一秒一秒が大事だ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_13");
		break;
		// --> Выбрал отправиться назад на Карибы с женой
		case "SharlieEpilog_ChooseCaribbean_HaveWife_1":
			dialog.text = "";
			link.l1 = "そうか……まあ、君がそう言うだろうとは思っていたよ――もっと違う返事を期待していたけれどね。だが、君の選択を尊重するし、これ以上説得しようとは思わないよ。";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_2":
			dialog.text = "";
			link.l1 = "私があなたを失望させてしまったことは分かっています。ですが、これまでのすべてを覆すような知らせがあるんです。";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_3":
			dialog.text = "";
			link.l1 = "お話をうかがいましょう。";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "私はここに少なくとも一年は滞在するつもりです。 "+sld.name+" 彼女の体調では、揺れるのは絶対に無理だ。";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_5";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_5":
			dialog.text = "";
			link.l1 = ""+pchar.name+"……まさか……";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		// <-- Выбрал отправиться назад на Карибы с женой
		
		// --> Выбрал отправиться назад на Карибы один
		case "SharlieEpilog_ChooseCaribbean_Single_1":
			dialog.text = "";
			link.l1 = "さて……正直に言うと、あなたがそう言うだろうとは思っていました――でも、違う答えを期待していたのも事実です。それでも、あなたの選択を尊重しますし、 これ以上説得しようとはしません。ですが、教えてください、\n "+pchar.name+"「それで、イヴォンヌとの結婚の申し出について考えてくれたか？」";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		// <-- Выбрал отправиться назад на Карибы один
		
		//Диалог Шарль и Мишеля на Рифе Скелета
		case "SharlieEpilog_Mishelle_1":
			dialog.text = "我慢できなかったんだな？";
			link.l1 = "あなた！？これは夢なのか？";
			link.l1.go = "SharlieEpilog_Mishelle_2";
			SharlieEpilog_OnReefs_6();
			PlaySound("Voice\" + LanguageGetLanguage() + "\sharlie\mishelle-04.wav");
		break;

		case "SharlieEpilog_Mishelle_2":
			dialog.text = "安易な利益への渇望、権力、無敵という幻想……兄上よ、そのうちどれがあなたを滅ぼしたのですか？すべての白人の心を曇らせるものが、 あなたの心も曇らせたのですか？";
			link.l1 = "出て行け！お前はただの幽霊だ！ここにいる資格はない！";
			link.l1.go = "SharlieEpilog_Mishelle_3";
		break;

		case "SharlieEpilog_Mishelle_3":
			dialog.text = "まだ分からないのか？Spectra sunt memoria peccatorum――亡霊とは罪人の記憶だ。お前こそが幽霊……欲と盲目的な虚栄心に呑み込まれたカリブの伝説の男だ。金のために、何人殺してきた？ "+pchar.name+"?";
			link.l1 = "さて、親愛なる兄上よ、もう一度あなたを殺すことになっても私は構わない！自業自得ですわ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_OnReefs_9");
		break;
		
		
		
		
		
	}
}