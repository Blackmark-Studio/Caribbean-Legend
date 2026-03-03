// Раймонд Бейкер - палач Сент-Джонса и возможный офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何か用か？";
			link.l1 = "いいえ、なんでもありません。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "baker":
			dialog.text = "ありがとうございます、船長！あなたがいなかったら、私はどうなっていたか想像もできません……";
			link.l1 = "想像できるよ。お前は飢え死にするか、ドミニカの野蛮人の腹の中で終わってたかもしれねえ。だが、 俺に恩を返すチャンスがあるぜ。";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "どうされましたか、船長？";
			link.l1 = "ある男についてもっと知りたいんだ。いわば、俺たちの共通の知り合いさ。実はお前さんのとても親しい友人だよ。 ブッチャー船長のことだ。そう、二十年前にお前さんが絞首刑にしたあの男さ。おいおい、どうした、 顔色が真っ青じゃねえか？ラムでも一杯やるか？";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "「まさか…彼に遣わされたのですか？」";
			link.l1 = "馬鹿な！奴が死んでいるのに、どうやって「奴に遣わされた」なんてことがあるんだ！ 俺が興味あるのはブッチャー本人じゃなくて、奴が残した物だ。手紙や書類、そういうものさ。もしかして、 奴のポケットから何か見つけたんじゃないか……待てよ！意味が分からないな。本気でブッチャーが生きてると思ってるのか？お前が自分で奴を処刑したじゃないか！";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			dialog.text = "くそっ！お前は何も分かっちゃいねえな。ってことは、やっぱり屠殺屋に送り込まれたわけじゃなかったのか……";
			link.l1 = "ほうほう。ますます面白くなってきたな。どうやらヘンリーがブッチャーを恐れていたのも無理はない、 それで心臓発作で死んじまったってわけか……ブッチャーは生きてるのか？";
			link.l1.go = "baker_4";
		break;
		
		case "baker_4":
			dialog.text = "あいつですよ、船長…。それに、奴らは俺を探しているんだ。";
			link.l1 = "レイモン、お前は馬鹿じゃないと聞いている。俺を騙そうなんて思うなよ。ここではどんな脅威からも安全だ。 知っていることを全部話せば、俺が何か助けてやる方法を考えてやる。もしかしたら、 俺たちには共通の敵がいるかもしれない。まずはブッチャーの話から始めよう。";
			link.l1.go = "baker_5";
		break;
		
		case "baker_5":
			dialog.text = "彼は生きているが、今は名前が違うんだ！処刑の夜に奴の部下が俺のところに来た。ジャックマンと、もう一人、 変なあだ名の男だった。確か「溺れた男」と呼ばれていたはずだ。";
			link.l1 = "死刑執行人だ。ヘンリー・ザ・ハングマン。";
			link.l1.go = "baker_6";
		break;
		
		case "baker_6":
			dialog.text = "そうだ！奴らは俺に単純な取引を持ちかけてきた――一番苦しい死に方をするか、船長を救うか、どちらかだってな。だから俺は、 暇な時に作った特製の道具を使って処刑を偽装するしかなかったんだ。ベルトや金具をこう組み合わせると、 体重をうまく分散できるんだよ。\nあとはそれを縄の秘密のフックに取り付けるだけさ。もちろん、「死体」役もちゃんと演じなきゃいけなかったけどな。 正直言って、ローレンスの演技は見事だったぜ。完璧にやってのけたが……一つだけ、あいつは小便を漏らすのだけは断固拒否したんだ、理由は……";
			link.l1 = "今、「ブッチャー」のことを「ローレンス」って呼んだのか？";
			link.l1.go = "baker_7";
		break;
		
		case "baker_7":
			dialog.text = "それが彼の本名です。ローレンス・ベルトロープと呼ばれているとあなたに言いましたね。 彼が一年前にカリブへ戻ってきてから、私はずっと不安でした。そして、危険な連中が私を探していると知ったときには……\n念のために当局への自白書まで書きました。怖くて提出できず、いつも身につけています。 共犯者だと思われるかもしれませんから。どうか、あなたの乗組員に加えてください。誓って、私は優秀な医師ですし、 きっとお役に立てます。";
			link.l1 = "いいだろう。それで、ブッチャーの…いや、ベルトロープの私物はどうなっている？トマス・ベルトロープと関係があるのか？";
			link.l1.go = "baker_8";
		break;
		
		case "baker_8":
			dialog.text = "さあな。ベルトロープ本人から特別にもらったものは何も残ってないんだ。でも、持ってるものは全部渡すよ。 好きにしてくれ。件に関する書類は全部この鞄の中だ。念のため全部取っておいて、いつも手元に置いてある。\nほら、見てくれ……これはブッチャー船長の伝説、これは俺の告白書……これはジョシュア・リードベーターの持ち物だったものだ……";
			link.l1 = "止まれ！リードビータ―？それは誰だ？";
			link.l1.go = "baker_9";
		break;
		
		case "baker_9":
			dialog.text = "おお！あの人は本当に特別な男だったよ。自らブッチャーを追い詰めた人物さ。人々は彼のことを「仮面の男」 と呼んで覚えている。ブッチャーが処刑された直後、彼も殺されたんだ。誰かがサメの歯で喉を切り裂いたんだよ！ 一太刀で終わった。生きている間は、きっとひどい苦しみを味わったに違いない。\nもし仮面の下の顔を見たら、肉の塊しかなかったんだ！彼が死んだとき、ポケットにはこの日誌のページが入っていた。 きっとジェシカ・ローズの著作の一部だろう。不気味な話さ！読んでみな、きっと色々と分かるはずだ。\nそしてこれがその歯そのものさ。文字が見えるかい？S.D.…何の意味かは分からないがな。それに血痕も少し残っている。";
			link.l1 = "もう十分だ！私はすべてをじっくり読んで考え直す必要がある。\nそれまでお前は私の乗客か船医としてここにいるんだ。\n安心していい、レイモン、私の船の上では安全だ。";
			link.l1.go = "baker_10";
		break;
		
		case "baker_10":
			DialogExit();
			sld = characterFromId("Baker_Cap");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
			//sld.ship.hp = 0;
			//sld.SinkTenPercent = true;
			bQuestDisableMapEnter = false;
			GiveItem2Character(pchar, "shark_teeth");
			GiveItem2Character(pchar, "letter_jess");
			GiveItem2Character(pchar, "letter_baker"); // показания бейкера
			ChangeItemDescribe("letter_baker", "itmdescr_letter_baker"); // Addon-2016 Jason
			AddQuestRecordInfo("Legend_CapBucher", "1");
			AddQuestRecordInfo("Letter_jess", "1");
			AddQuestRecord("Shadows", "5");
			pchar.questTemp.Saga.Shadows = "islatesoro";
			// в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Baker_officer";
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
		
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddCharacterExpToSkill(pchar, "Sailing", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Baker_officer":
			dialog.text = "「はい、船長？」";
			Link.l1 = "俺の命令を聞け！";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "キャプテン、少し動揺しているようですね。それに顔色も悪い…状況が違えば、私の秘薬をおすすめするところですが…";
				Link.l1 = "医学にも詳しくなったようだな、"+npchar.name+"。ありがとう、平気だ。だが今から踏み出す一歩は、他の状況なら決して選ばなかったかもしれない。";
				Link.l1.go = "SharlieEpilog_Baker_1";
				break;
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "レイモン、船について詳しい報告をしてくれ。";
			    Link.l11.go = "QMASTER_1";

			    // Warship. Автозакупка товара
				Link.l12 = "俺たちが寄港するたびに、ある品物を必ず仕入れてほしいんだ。";
				Link.l12.go = "QMASTER_2";
			}
			
			link.l2 = "たいしたことじゃない。解散！";
			link.l2.go = "exit";
			NextDiag.TempNode = "Baker_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
        case "QMASTER_1":
			dialog.Text = "さあ、船長、俺は医者であって会計係じゃねえんだ。昔は別の仕事もしてたが……まあ、それはいい。帳簿付けなんて本当に無理だ、悪いな。";
			Link.l1 = "よかろう、そうしよう。お前は俺の船医だ――俺の船に加わった時にそう約束したからな。";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "船長、正直に申し上げますと、私は交易の経験がほとんどございません。値切ったこともなければ、 相場を調べたこともありません。それに……もしよろしければ、私は船に残らせていただきたいのです。 あの商人たちの中には私のことを覚えている者もいるかもしれませんし、 気づかれたら仮面の男たちがすぐにやって来るでしょうから。\n";
			link.l1 = "つまり、自分の過去に怯えながら生き続けるつもりか……。\nよし、息を吐け、俺が自分でやる。";
			Link.l1.go = "exit";
        break;
		
		case "stay_follow":
            dialog.Text = "ご命令は？";
            Link.l1 = "ここに立て！";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "俺について来い、遅れるんじゃねえぞ！";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "火器の弾薬の種類を変更する。";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "弾薬の種類を選択：";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "態度が変わったぞ！";
            Link.l1 = "下がってよい。";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "態度が変わったぞ！";
            Link.l1 = "下がってよい。";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// Эпилог
		case "SharlieEpilog_Baker_1":
			dialog.text = "ふむ…何か見落としているようですね。これからの知らせにあなたが喜ぶと思っていたのですが。";
			link.l1 = "何の話だ？";
			link.l1.go = "SharlieEpilog_Baker_2";
		break;

		case "SharlieEpilog_Baker_2":
			dialog.text = "ゴホン…すみません。自分でも何があったのか…たぶん、日差しにやられたのでしょう。本当は、あなたに話したいことがあったのです、キャプテン。";
			link.l1 = "ほう？何の話だ？";
			link.l1.go = "SharlieEpilog_Baker_3";
		break;
		
		case "SharlieEpilog_Baker_3":
			dialog.text = "私はもう、これ以上果てしない海戦を続けるには歳を取りすぎました。間接的に関わっているとはいえ、です。少しばかりの蓄えもありますし、陸に上がって個人開業したいと思っています。反対されませんか？";
			link.l1 = "もちろん反対なんてしないさ、"+npchar.name+"。君のような有能な士官がいなくなるのは寂しいが、君の決断は理解し、尊重する。幸運を祈ってるよ。君ならすぐに評判の名医になるさ。";
			link.l1.go = "SharlieEpilog_Baker_nothing";
			link.l2 = "賢明な判断だ。もちろん私は何も言わないよ。君には追加で1ヶ月分の給料を渡すよう手配しよう——無駄にはならないはずだ。さて…あとはただ、新しい人生の幸運を祈るだけだな。";
			link.l2.go = "SharlieEpilog_Baker_salary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // только если есть жена
			{
				link.l3 = "はは、もちろん反対なんてしないよ、親愛なる"+npchar.name+"。今の私は、君の気持ちが痛いほど分かる。これを受け取ってくれ。3ヶ月分の給料だ。君のこれからがうまくいくよう願っている。";
				link.l3.go = "SharlieEpilog_Baker_salary_X3";
			}
		break;
		
		case "SharlieEpilog_Baker_nothing":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Baker_exit");
		break;
		
		case "SharlieEpilog_Baker_salary":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Baker_exit");
			//
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Baker_salary_X3":
			dialog.text = "ありがとうございます、キャプテン。あなたも奥様と一緒に、居心地の良い家を早めに探されたほうがいいでしょう。何しろ、船の揺れは腹の中のいくつかのプロセスに良くありませんからね…";
			link.l1 = "腹の中？何のことだ？船酔いのやつなんていないはずだが。";
			link.l1.go = "SharlieEpilog_Baker_salary_X3_2";
			//
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Baker_salary_X3_2":
			dialog.text = "ただの独り言です、キャプテン。お気になさらず。奥様を、そしてご自身を大切に。";
			link.l1 = "君も気をつけてな、"+npchar.name+"。落ち着いたら、サン＝ピエール教会のブノワ神父を通じて知らせてくれ。";
			link.l1.go = "SharlieEpilog_Baker_salary_X3_3";
		break;
		
		case "SharlieEpilog_Baker_salary_X3_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Baker_exit");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
