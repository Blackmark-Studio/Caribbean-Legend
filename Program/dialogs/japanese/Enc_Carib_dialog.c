void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "First time":
			dialog.text = "おめでとう！これはバグだ。ジェイソンに連絡して、どこでどうやって見つけたか伝えてくれ。じゃあな！";
			link.l1 = "すぐにやるぜ！";
			link.l1.go = "exit";
			Diag.TempNode = "First time";
		break;

		case "exit_fight":
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_peace":
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}	
			ChangeIndianRelation(1.00);
		break;
		
		// военные индеи - карибы
		case "war_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				dialog.text = LinkRandPhrase("海の息子よ、ようこそ！お前のことは聞いているぜ。俺たちの土地を自由に歩いていいぞ。",""+npchar.name+" 蒼白い顔の兄弟よ、歓迎するぞ。お前が我々の客として来てくれて嬉しい。","「勇敢な色白の戦士よ、挨拶するぞ！」 "+npchar.name+" インディアンの友人に会えて嬉しい。安らかに行きなさい！");
				link.l1 = RandPhraseSimple("「やあ、赤い肌の兄弟よ！狩りがうまくいくよう祈ってるぜ！」","ごきげんよう、勇敢な戦士よ！神々があなたとご家族を祝福されますように！");
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = RandPhraseSimple("赤い肌の兄弟よ、興味がありそうなものがあるんだ。取引しないか？","勇敢な戦士よ、面白い品を売ってやれるぜ。取引するかい？");
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("止まれ、色白野郎！何の権利があって俺の土地を歩いているんだ？","止まれ、白人！ここは俺の祖先の土地であり、俺の土地だ！","止まれ、色白野郎！ここは俺の土地だ、お前の居場所じゃねえ");
				link.l1 = RandPhraseSimple("「お前の土地だと？消え失せろ、この赤ら顔のクズ野郎！」","あいつを見ろよ――しゃべる猿じゃねえか！さっさと失せろ！");
				link.l1.go = "war_indian_1";
				link.l2 = RandPhraseSimple("俺は和平のために来たんだ、赤い肌の戦士よ。無駄に争うべきじゃねえ。","俺はお前やお前の土地の敵じゃねえ、戦士よ。平和のために来たんだ。");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/3)) > hrand(80)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2";
				link.l3 = RandPhraseSimple("俺は取引に来たんだ、戦うためじゃねえ。","俺はインディアンとは戦わねえ。取引するんだ。");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/6)+makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE)/6)) > hrand(90)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2";
			}
		break;
		
		case "war_indian_1":
			dialog.text = RandPhraseSimple("生まれてきたことを後悔させてやるぜ、この色白の野郎……お前の心臓をえぐり出して火で焼いてやる！","石でも食わせてやるぜ、この青白い犬野郎！死を乞いながらひざまずくお前を、俺たちは笑って見ててやるぜ、 この白い雑種め！");
			link.l1 = RandPhraseSimple("まだその汚ねえ口を閉じられねえのか、この化け物め！てめえが這い出てきたジャングルに叩き返してやるぜ！","俺様を脅すつもりか、このクズ野郎が！？よし、てめえは今すぐ木に登り直しやがれ！");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_2_1":
			dialog.text = RandPhraseSimple("お前の声は誠実だと聞いた。この日は斧をお前に向けたりはしねえ。平和のうちに行け、色白の奴。","青白い顔の者はめったに平和をもたらさぬが、お前の目を見れば嘘は言っていないと分かる。さあ、行け。");
			link.l1 = RandPhraseSimple("賢明な判断だな、戦士よ。幸運を祈るぞ。","理解し合えて嬉しいぞ、戦士よ。");
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_2_2":
			dialog.text = RandPhraseSimple("嘘をつくな、色白の野郎め！インディアンを殺しに来たんだろう！\n戦う覚悟はできてるか、色白野郎！？","お前はインディアンを殺す。白人の舌は嘘つきの舌だ。俺はそれを切り取って火で焼いてやる！");
			link.l1 = RandPhraseSimple("まあ、相棒、だったら俺を責めるなよ。神のみぞ知るが、俺は避けようとしたんだぜ…","「望んだのはお前だろう、戦士。」");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = "取引か？俺たちは白人の武器が必要だ。あの青白い顔の者どもの片手で使う火の武器だ！ それと引き換えに俺たちの品を渡すぜ！火の武器、取引できるか？";
				link.l1 = "ふむ。あるぜ。それで、見返りに何をくれるんだ？";
				link.l1.go = "war_indian_trade";
				link.l2 = "この野郎め！それで俺のピストルで植民者たちを撃つつもりか？そんなことはさせねえ！そしてお前らジャッカルども、 今ここで全員ぶった斬ってやる……";
				link.l2.go = "exit_fight";
			}
			else
			{
				dialog.text = "お前は俺たちの欲しいものを持っていないな、色白野郎……お前は俺たちの戦利品になるんだ！";
				link.l1 = "やれるもんならやってみろよ、かかし野郎……";
				link.l1.go = "exit_fight";
			}
		break;
		
		case "war_indian_3_2":
			dialog.text = RandPhraseSimple("俺たちは白い顔の犬どもとは取引しねえ。殺して奪うだけだ！","俺たちは汚ねえミスキートやアラワクじゃねえ、白顔どもと取引なんかしねえ！あいつらを殺して戦利品を奪うのさ！");
			link.l1 = RandPhraseSimple("なら、俺から奪ってみろ、このろくでなし！","まずは俺のサーベルを奪ってみろ、このクズ野郎！");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_trade":
			iGun = 1;
			dialog.text = "お前が持ち物を見せてくれりゃ、俺たちがいくら出すか言うぜ。";
			for (i=6; i>=1; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol"+i) > 0)
				{
					sLink = "l"+iGun;
					link.(sLink) = "Offer "+XI_ConvertString("pistol"+i)+".";
					link.(sLink).go = "gun_"+i;
					iGun++;				
				}
			}
		break;
		
		case "gun_1":
			npchar.quest.gun = "pistol1";
			if (hrand(1) == 0)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(1)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(9)+14);
				iTotalTemp = hrand(2)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "おう！それに対して俺たちが払ってやるぜ "+sText+".";
			link.l1 = "「取引成立だ！」";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "いや。ありえねえ。";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_2":
			npchar.quest.gun = "pistol2";
			if (hrand(3) < 2)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(3)+1);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "おう！なかなかの武器じゃねえか……それに見合うもんをやるぜ "+sText+".";
			link.l1 = "「取引成立だ！」";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "いや。ありえねえ。";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_3":
			npchar.quest.gun = "pistol3";
			if (hrand(5) < 3)
			{
				qty = rand(1)+2;
				npchar.quest.item = "jewelry5"+qty;
				iTotalTemp = hrand(6)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful pearl";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(2)+2);
				iTotalTemp = hrand(2)+5;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  this beautiful stone";
			}
			dialog.text = "おうよ！すげえ武器だぜ！たくさんの敵をぶっ殺せる！それと引き換えにお前にやる "+sText+".";
			link.l1 = "「取引成立だ！」";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "いや。ありえねえ。";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_4":
			npchar.quest.gun = "pistol4";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(10)+qty*30;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "obereg_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "おう！すげえ武器じゃねえか……それと引き換えにこれをやるぜ "+sText+".";
			link.l1 = "「取引成立だ！」";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "いや。ありえねえ。";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_5":
			npchar.quest.gun = "pistol5";
			if (hrand(7) < 7)
			{
				if (hrand(10) < 8)
				{
					npchar.quest.item = "jewelry7";
					iTotalTemp = 2+hrand(1);
				}
				else
				{
					npchar.quest.item = "jewelry8";
					iTotalTemp = hrand(4)+10;
				}
				qty = hrand(1)+1;
				npchar.quest.item = "jewelry"+(qty+6);
				if (qty == 1) iTotalTemp = 2;
				else iTotalTemp = hrand(5)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful and precious petrified tar";
			}
			else
			{
				npchar.quest.item = "indian_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "おう！美しくて強力な武器だな！こいつで何人もの敵を倒したぜ！その武器と引き換えに渡すぞ "+sText+".";
			link.l1 = "「取引成立だ！」";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "いや。ありえねえ。";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_6":
			npchar.quest.gun = "pistol6";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(8)+qty*20;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "amulet_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "おう！いい武器じゃねえか……その礼はちゃんとするぜ "+sText+".";
			link.l1 = "「取引成立だ！」";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "いや。ありえねえ。";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "war_indian_trade_agree":
			ChangeIndianRelation(1.00);
			npchar.quest.count = sti(npchar.quest.count)+1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			Log_Info("You have given "+XI_ConvertString(npchar.quest.gun)+"");
			Log_Info("You have received "+XI_ConvertString(npchar.quest.item)+" in amount of "+FindRussianQtyString(iTotalTemp)+"");
			PlaySound("interface\important_item.wav");
			if (sti(npchar.quest.count) > 3+hrand(2));
			{
				dialog.text = "よし。これがあんたの品だ。もう取引はしねえ。後でまた来な。もっといい火薬武器を持ってくりゃ、もっと渡してやる。 さあ、行け！";
				link.l1 = "さらばだ、赤き肌の戦士よ。";
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = "よし。これがあんたの品だ。もっと火薬武器を取引したいのか？";
				if (CheckCaribGuns())
				{
					link.l1 = "持ってるぜ。買うか？";
					link.l1.go = "war_indian_trade";
				}
				link.l2 = "いいや。次はもっと持ってくる。";
				link.l2.go = "war_indian_trade_exit";
			}
		break;
		
		case "war_indian_trade_exit":
			dialog.text = "持ってこい。もっといい火薬武器を持ってきたら、もっと払ってやるぜ。さあ、行け！";
			link.l1 = "じゃあな、戦士よ……";
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_trade_bad":
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for(i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}	
			}
			else
			{
				dialog.text = "「だったら全部タダでもらうぜ、色白野郎！」";
				link.l1 = "試してみてもいいぜ…";
				link.l1.go = "exit_fight";
			}
		break;
		
		// мирные индеи - мискито
		case "peace_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase("よう、白人よ。俺たちのジャングルで何の用だ？","俺たちのジャングルはとても危険だぜ。ここで何してるんだ？","「何の用だ、勇敢な白人よ？」");
			link.l1 = RandPhraseSimple("俺はただ通りかかっただけだぜ、赤い肌の友よ。この道は俺たち二人が通るには十分な広さがあると思うが？","よう、ジャングルの息子よ！俺は用事で来ただけだ、インディアンとは戦わねえ。");
			link.l1.go = "peace_indian_1";
			link.l2 = RandPhraseSimple("「なんでお前に教えなきゃなんねえんだ？自分の道を行け、余計なことに首を突っ込むな！」","自分の道を行け、赤い肌の者よ。俺はお前と話している暇はねえ。");
			link.l2.go = "peace_indian_2";
		break;
		
		case "peace_indian_1":
			dialog.text = RandPhraseSimple("我々は平和な民だ。白人と敵対してはいない。行くがよい、だが我々の土地では気をつけるのだぞ！","インディアンの蒼白い顔の友人に会えて嬉しいぞ。安らかに行け、海の息子よ！");
			link.l1 = RandPhraseSimple("お前にも幸運を、森の息子よ……","さらばだ、赤い肌の友よ。");
			link.l1.go = "exit_peace";
		break;
		
		case "peace_indian_2":
			dialog.text = RandPhraseSimple("俺たちは平和な狩人だ。だが、この土地でそんな口をきく白人どもは許さねえぞ！","俺たちは白人とは戦わねえ。だが、白人が俺たちを侮辱すりゃ、先祖から教わった通りに応えるだけだ！");
			link.l1 = RandPhraseSimple("まだその汚ねえ口を閉じられねえのか、この化粧したカカシめ！てめえが這い出てきたジャングルに叩き返してやるぜ！","俺に脅しをかけるつもりか、このクズ野郎！？今すぐてめえが降りてきた木に這い上がるんだな！");
			link.l1.go = "exit_fight";
		break;
	}
}
