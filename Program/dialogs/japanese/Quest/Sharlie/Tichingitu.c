// Тичингиту - индеец-офицер
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
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何の用だ？";
			link.l1 = "「何でもない。」";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "何の用だ、色白の顔よ？ティチンギトゥはお前に話すことなどない。";
			link.l1 = "お前の名前はティチンギトゥか？ふむ。聞け、戦士よ、俺はお前を眺めに来たわけじゃねえ。質問しに来たんだ。 なぜあのデブの家に侵入した？";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "何も言わないのか？賢くないな。盗みや他の罪でお前は絞首刑になるぞ。なぜそんなことをしたのか話せば、 もしかしたら助けてやれるかもしれない。";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "ティチンギトゥは、たくさんの道を通り、大きな海を越え、広大な森や沼地から白い顔の者たちの町へやって来た。\nティチンギトゥは疲れていて、食べ物が欲しかった。\nティチンギトゥは飢えで死にそうだった。\n誰もティチンギトゥを助けようとしなかった。\n彼らは「出て行け、赤い肌の犬め」と叫んだ。\n酒場の主人は、インディアンを汚い犬のように追い出した。\nティチンギトゥは食べたかった。";
			link.l1 = "くそっ、だがなんでお前は……自分の森からこの入植地に来たんだ？";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "ティチンギトゥは先住民の部族から追放された。\nティチンギトゥは部族のシャーマンと喧嘩し、シャーマンは酋長に告げ口し、ティチンギトゥに呪いをかけた。\nティチンギトゥは部族を去り、故郷から遥か遠くへ行った。\nティチンギトゥには家もなく、武器もなく、何も持っていない。";
			link.l1 = "それはまさに不運というものだ。どうして自分の仲間と争ったんだ？";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "部族のシャーマンは邪悪な男だ。奴は「悪霊が妻の体に取り憑いた」と言った。だから妻は死ななければならなかった。 だが、妻はただ病気だっただけで、霊など取り憑いていなかった。ティチンギトゥは妻を治そうとしたが、 シャーマンが妻を殺した。ティチンギトゥはシャーマンに立ち向かったが、みんながティチンギトゥに背を向けたので、 ティチンギトゥは去っていった。";
			link.l1 = "妻を助けようとしたのか？それで村を追い出されたのか？";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "ああ、色白の顔よ。ティチンギトゥには選択肢がないんだ。盗むか、飢え死にするかしかない……";
			link.l1 = "ふむ、なんということだ……飢えた男がわずかな金を盗んだだけで絞首刑とは……ティチンギトゥ、君を助けてみるよ。君が忍び込んだあの大男、ファデイのことは知っている。何かできるかもしれない……司令官に話をしに行こう。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			AddDialogExitQuestFunction("Tichingitu_DlgExit_1");
		break;
		
		case "Tichingitu_wait":
			dialog.text = "ティチンギトゥは待つ。インディアンは死を恐れない。シャーマンがティチンギトゥに呪いをかけた、 ティチンギトゥは死なねばならぬ。";
			link.l1 = "まだ全てが失われたわけじゃない。俺が助けてみせる……";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			dialog.text = "ティチンギトゥは待っている。インディアンは死を恐れない。シャーマンがティチンギトゥを呪った、 ティチンギトゥは死なねばならぬ。";
			link.l1 = "悲観的になることはない。お前の投獄は終わったんだ。俺が解放する手助けをしたんだぞ。";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			dialog.text = "白顔の冗談か？ティチンギトゥは自由なのか？";
			link.l1 = "いや、冗談じゃない。もうすぐお前の牢屋が開けられて、外に出られるぞ。\n俺について来い、牢獄から案内してやる。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tichingitu_DlgExit_2");
		break;
		
		case "Tichingitu_9":
			dialog.text = "";
			link.l1 = "また自由の身になったな。さあ、ティチンギトゥ、もう盗みはするなよ、これ以上厄介ごとを起こすんじゃないぞ！ インディアンの村を探して、自分の仲間と一緒に暮らした方がいい。きっと受け入れてくれるはずだ。";
			link.l1.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "ティチンギトゥは行かない。ご主人様がティチンギトゥの命を救ってくれた。ティチンギトゥはここに残る。 ティチンギトゥの命はご主人様のものだ。";
			link.l1 = "は？何を言ってるんだ？どんな主人だ、どんな人生だって？俺の言ってることが分からねえのか？お前は自由だ！行け！";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "インディアンには借りがある、白い旦那。ティチンギトゥは誠実に、真心でお仕えする。 ティチンギトゥは戦い方を知っている。旦那のために戦場で死ぬ覚悟だ。ここに残る。";
			link.l1 = "おお、主よ！くそっ……俺は一体どんな主人なんだ、ティチンギトゥ？俺はお前を助けたが、お前を奴隷にするためじゃねえんだぞ。";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "ティチンギトゥ、奴隷じゃない。ティチンギトゥ、自由なインディアンだ。ティチンギトゥ、あんたに仕えたい。 ティチンギトゥ、戦い方知ってる、どんな犬でもご主人様に近づく前に死ぬ。ティチンギトゥ、 マスケットの手入れも装填もできる。ティチンギトゥ、マスケット撃てる。";
			link.l1 = "ただし…ティチンギトゥ、お前のその考えも悪くないな。俺には忠実な奴が必要だし、お前も悪い男には見えねえ。それに、 火縄銃の扱いも知ってるだろう。それにしても、お前一人で何をするつもりだ？どうせまた何か盗んで、 次こそは間違いなく絞首刑だ…よし、ここにいていいぜ。ただし覚えておけ、俺と一緒にいれば平穏な人生なんて望めねえからな。\n";
			link.l1.go = "Tichingitu_13";
			link.l2 = "よし、もういい。安らかに行け、赤い肌の兄弟よ。お前の神々が見守ってくれるようにな！";
			link.l2.go = "Tichingitu_exit";
		break;
		
		case "Tichingitu_exit":
			DialogExit();
			AddDialogExitQuestFunction("Tichingitu_DlgExit_3");
		break;
		
		case "Tichingitu_13":
			dialog.text = "ティチンギトゥは何も恐れない、白い旦那。ティチンギトゥはあなたに仕えることが嬉しい。 ティチンギトゥは最後の一息まで忠実だ。";
			link.l1 = "よし。ティチンギトゥ、乗組員へようこそ！";
			link.l1.go = "Tichingitu_hire";
		break;
		
		case "Tichingitu_hire":
			DialogExit();
			AddDialogExitQuestFunction("Tichingitu_Hire");
		break;
		
	//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Tichingitu_officer":
			dialog.text = "ティチンギトゥはあなたの話を聞いているぞ、船長 "+pchar.name+"!";
			// Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = ""+npchar.name+" はキャプテン "+pchar.name+" の目に戸惑いを見ている。";
				Link.l1 = "君はいつだって私の心を見透かしているな、友よ。実は私は故郷、ヨーロッパへ帰らねばならない。難しい決断だったが、他人の船で旅立つことにした。乗客としてな。";
				Link.l1.go = "SharlieEpilog_Tichingitu_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "ティチンギトゥ、私はこれからタイアサルという古いインディオの村へ向かうつもりだ。正直に言うが、 これはとても危険で、しかも普通じゃない旅なんだ――転送の偶像を使うんだよ。君は……一緒に来てくれるか？";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "ティチンギトゥ、船の詳細な報告をしてくれ。";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "私たちが寄港するたびに、ある品物を必ず購入してほしい。";
				Link.l12.go = "QMASTER_2";
			}

			Link.l1 = "俺の命令を聞け！";
            Link.l1.go = "stay_follow";
			link.l2 = "今のところ何もない。楽にしてくれ！";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "船の報告？ティチンギトゥには報告はありません、旦那。武器と服だけです。 ティチンギトゥはどこからも報告を受け取っていません。";
			Link.l1 = "わかったよ、どうでもいいさ。";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "旦那、ティチンギトゥはあんたがいないと植民地には絶対に足を踏み入れないんだ。\nティチンギトゥが店に入ると、みんなまた盗人だと思う。\nそれで、牢屋行きさ。";
			link.l1 = "ああ、たぶんお前の言う通りだな。もうあの牢屋の話はごめんだぜ。それに、お前が会計係だなんて誰も信じやしねえよ。 ";
			link.l1.go = "exit";
		break;
		
		case "stay_follow":
            dialog.Text = "ご命令は何でしょうか？";
            Link.l1 = "「ここで止まれ！」";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "俺について来い、遅れるんじゃねえぞ！";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "火器の弾薬の種類を変更する必要がある。";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "マスケット銃の弾薬の種類を変更しろ。";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "戦闘用の主武器を変更しろ。";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "標的から距離を取ってほしい。";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "弾薬の種類を選んでください：";
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
		
		case "SetMusketBullets":
			Dialog.Text = "弾薬の種類を選択してください：";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "戦闘開始時にあなたが使うのは：";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "計画変更だ！";
            Link.l1 = "楽にしろ。";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "計画変更だ！";
            Link.l1 = "楽にしてくれ。";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "どれくらいだ、船長？ティチンギトゥに何ヤードか教えてくれ。ただし二十ヤードを超えないようにな。";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "船長、ティチンギトゥをお許しください、ですがあなたのおっしゃることが分かりません。";
				link.l1 = "申し訳ない、私のミスだ……";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "ティチンギトゥはじっとして動かない。船長、それでいいのか？";
				link.l1 = "「はい、まさにその通りです。」";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "ティチンギトゥは標的から二十ヤード以上離れることができない。\nそれ以上離れると外してしまうのだ。";
				link.l1 = "よし、二十ヤード離れていろ。";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "ティチンギトゥはすべて理解している。\nティチンギトゥはあなたが言う役目を引き受ける。";
			link.l1 = "「よし。」";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "ティチンギトゥの人生は、長い間、私の船長の人生そのものになった。\nインディアンは、船長がティチンギトゥのためにしてくれたことを決して忘れない。\nティチンギトゥは、船長がどこへ行けと言おうと、何も問わず、ためらいもせず、ついていく。";
			link.l1 = "ありがとう、友よ！";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "いつ出発するんだ？";
			link.l1 = "少し後になるだろう。今は旅の準備をしなければならないな。";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "21");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "白人に百ドゥブロン払って出ていけば、自由に仕事を終えられるってわけだ。";
			link.l1 = "「もしまた捕まったらどうするんだ？」";
			link.l1.go = "tonzag_jailed_1";
			locCameraFromToPos(-16.78, 1.88, -1.70, true, -5.00, -6.10, -20.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "我々は千ドゥブロン支払う。";
			link.l1 = "皮肉屋だが、とても洞察力がある。";
			link.l1.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "グアドループはもっとひどい。";
			link.l1 = "どういうことだ？";
			link.l1.go = "tonzag_jailed_3";
		break;
		
		case "tonzag_jailed_3":
			dialog.text = "あそこではティチンギトゥ一人だけを吊るそうとしている。こっちじゃ何人も吊るすつもりらしい。 そんなに悪くはねえな。";
			link.l1 = "そりゃあ、まったく皮肉じゃねえか！";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "至近距離で撃たれた。船長、あの爺さんはまだ強い、急げば助けられるぞ。";
			link.l1 = "...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
			AddDialogExitQuestFunction("Tonzag_JailFear");
		break;
		
		case "tonzag_dead":
			dialog.text = "白人は容赦しねえ。俺の仲間もたくさんやられた、船長。だが、お前の仲間はもっと多いぜ。";
			link.l1 = "あれはお前の部族か？";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "「俺の……俺の分だ。」";
			link.l1 = "頑張れよ、友よ。";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
	// Тичингиту говорит о том, что нужно спасти Делюка
		case "Del_Deluck":
			dialog.text = "「また40ドゥブロンか？」";
			link.l1 = "え？またデリュクの釈放金を俺が払うのかって聞いてるのか？";
			link.l1.go = "Del_Deluck_1";
		break;
		
		case "Del_Deluck_1":
			dialog.text = "「はい。」";
			link.l1 = "私もよく分からないな……君はどう思う？";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "彼を保釈してやるべきだ。";
			link.l1 = "それは立派だな。仲間を見捨てないってわけか？";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "あるいは、あいつを見捨てろ。弱い奴はジャングルのジャガーに任せておけ。";
			link.l1 = "誰だ？";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			dialog.text = "大きな猫。";
			link.l1 = "ティチンギトゥ、君の言っていることがよく分からないんだ。とにかく、この状況で俺はどうすればいいのか教えてくれ。 ";
			link.l1.go = "Del_Deluck_5";
		break;
		
		case "Del_Deluck_5":
			dialog.text = "自分の頭で考えろ。";
			link.l1 = "とても助かった！";
			link.l1.go = "Del_Deluck_6";
		break;
		
		case "Del_Deluck_6":
			DialogExit();
			AddQuestRecord("FolkeDeluc", "2");
			ReturnOfficer_Tichingitu();
		break;
		
		// Эпилог
		case "SharlieEpilog_Tichingitu_1":
			dialog.text = "キャプテン "+pchar.name+"、"+npchar.name+" を連れていかないのか？";
			link.l1 = "君は私の友だ、"+npchar.name+"。もちろん一緒に旅に出ようと誘いたい。でも理解してほしい——旧世界の人々は先住民を見慣れていない。君を指差し、私の奴隷だと思い込み、それ相応の扱いをするだろう。";
			link.l1.go = "SharlieEpilog_Tichingitu_2";
		break;

		case "SharlieEpilog_Tichingitu_2":
			dialog.text = ""+npchar.name+" は気にしない。"+npchar.name+" は白人がインディアンを軽蔑していると知っている。そして "+pchar.name+" キャプテンに、約束通り——最後の息までついていく。";
			link.l1 = "すべての者がインディアンを軽蔑しているわけじゃない。ただ、大多数は警戒心を抱く。それが自分たちの信仰を異質なものから守る手段なんだ。ともかく、私は誰にも君を侮辱させないし、奴隷扱いなんてさせない。君の部族の誰もヨーロッパを見たことがないはずだ——あの呪われたシャーマンでさえ、夢の中でも想像すらできなかったろう。";
			link.l1.go = "SharlieEpilog_Tichingitu_3";
		break;

		case "SharlieEpilog_Tichingitu_3":
			dialog.text = "マスコギ族のインディアンは船乗りじゃない。ヨーロッパに行くなんて無理だ。私は聞いたことがある——大きなカヌーで行っても満月二つ分かかると。";
			link.l1 = "そうだ、"+npchar.name+"。しかも、それは風が順調だった場合の話だ。簡単な旅じゃない。出航は2週間後だ…君が一緒に来てくれるのが嬉しい。出発に合わせて、酒場でささやかな宴を開くつもりだ。君は火の水が苦手だって知ってるけど、それでも君が来てくれたら嬉しいよ。";
			link.l1.go = "SharlieEpilog_Tichingitu_4";
		break;
		
		case "SharlieEpilog_Tichingitu_4":
			dialog.text = ""+npchar.name+"、行く。でも…祝いの襲撃の方がいいか？";
			link.l1 = "ハハハ。今回はやめておこう、友よ——そういう場じゃない。始まる時に声をかけるよ。今は行かねばならない——やるべきことがあるんだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Tichingitu = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
