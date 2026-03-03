#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	bool bLock = (CheckAttribute(pchar, "GenQuest.BrothelLock")) && (GetCharacterIndex("Mary") != -1);
	bool bLock1 = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) && (IsOfficer(characterFromId("Helena")));

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("町で警報が鳴ったぜ。みんなお前を探してる！俺だったら、ここで長居はしねえな。","町中の衛兵が総出であんたを探し回ってるんだぜ。俺はバカじゃねえし、あんたと話す気なんてさらさらねえよ！","逃げろよ、相棒、兵隊どもにミンチにされる前にな…"),LinkRandPhrase("何の用だ、このろくでなしめ！？町の衛兵はもうお前の尻を追ってるぜ。そう遠くへは逃げられねえぞ、海賊！","汚ねえ殺し屋め、俺の家から出ていけ！衛兵！","俺はお前なんか怖くねえぞ、この野郎！縄が待ってるんだ、そう遠くへは行けねえさ…"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("へっ、警報なんか気にしちゃいねえよ…","奴らが俺を捕まえられるわけがねえ。"),RandPhraseSimple("「黙れ、」 "+GetWorkTypeOfMan(npchar,"")+"、さもねえと、その汚ねえ舌を引っこ抜いてやるぞ。","「へっ、」 "+GetWorkTypeOfMan(npchar,"")+"、お前も海賊狩りをしたいのか？いいか、相棒、落ち着いていれば生き延びられるかもしれねえぞ…"));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"！いらっしゃい、 "+GetAddress_Form(NPChar)+" ロス・テケス鉱山の酒場へようこそ。飯も酒も女も、全部お手頃な値段だぜ！俺の名は "+GetFullName(npchar)+" そして、俺はいつでもあんたのためにいるぜ。";
				Link.l1 = "さて……俺は "+GetFullName(pchar)+"。お会いできて嬉しいぜ "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "ああ、俺の古い知り合いだな、船長 "+GetFullName(pchar)+"！会えて嬉しいぜ、じいさん！ラム酒に女か？";
				if (makeint(pchar.money) >= 5)
				{
					link.l1 = "ラムを注いでくれ。 "+npchar.name+".";
					link.l1.go = "drink";
				}
				link.l2 = "ちょっと寝たいんだ。空いてる部屋はあるか？";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("何か新しい知らせはあるか？","ここらで何か変わったことはあるか？","陸の上での暮らしはどうだい？");
				link.l3.go = "rumours_tavern";
				link.l4 = "いや、何もいらねえよ。 "+npchar.name+"。ちょっと挨拶しに寄っただけだ。";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "ああ、嬉しいわ！この町じゃ新しい顔は珍しいのよ。ラムを注いで、ちょっとおしゃべりでもどうかしら…";
			link.l1 = "ここは初めてなんだが、この入植地についてもう少し知りたいんだ。";
			link.l1.go = "info";
			if (makeint(pchar.money) >= 5)
			{
				link.l2 = "ラムを注いでくれ。 "+npchar.name+".";
				link.l2.go = "drink";
			}
			link.l3 = "ちょっと眠りたいんだ。空いてる部屋はあるか？";
			link.l3.go = "room";
		break;
		
		case "info":
			dialog.text = "面白い話なんてないさ。毎日同じ仕事だぜ――退屈と太陽と埃ばっかりだ。ここに住んでるのは兵隊と黒人、それにインディオだけだ。金に飢えた冒険者や盗賊も時々 見かけるぜ\nたまにあんたみたいな旦那や船長が奴隷を延べ棒に換えたり、貴金属を買いに来たりもする。 うちの商人はなかなか面白い奴でな、金や銀の塊だけじゃなく、半貴石なんかも売ってるんだ\n 特別な知識を持った奴なら、こういう小石が役に立つって言ってるぜ。だから店を覗いてみな。 鉱山そのものは山の奥深くにある。見学したけりゃ行ってもいいが、見張りを怒らせない方が身のためだぜ\n囚人と話すなよ、盗みなんてもってのほかだ。とにかく、この集落で一番いい場所は俺の酒場さ――この灼熱地獄から休める最高の場所だぜ！";
			link.l1 = "情報をありがとう！";			
			link.l1.go = "exit";
		break;
		
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 3)
			{
				dialog.text = "船長、もうやめておいた方がいいと思いますぜ。酒に酔って騒ぎを起こすなんて、神様もお許しになりません。 ここじゃそういうのには本当に厳しいんだ。あんたの権威でも助けにならねえぜ。";
				link.l1 = "ふむ……確かにそうだな、もう十分飲んだぜ。心配してくれてありがとな！";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -5);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "どういたしまして、船長。俺自慢のジャマイカ産黒ラムなら、一杯たったのエイト5枚だぜ！";
				link.l1 = RandPhraseSimple(LinkRandPhrase("よし、お前の健康と店の繁盛を祈って乾杯だ！","よし、海の連中に乾杯だ！","よし、お前の町の繁栄に乾杯だ！"),LinkRandPhrase("よし、運命の風に、幸運の突風に、みんながもっと気楽で裕福に生きられるように！","よし、どんな時でも俺たちの背中に追い風が吹くように！","よし、幸せと運と喜び、そして女たちに乾杯だ！"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
		break;
		
		case "room":
			if (CheckAttribute(pchar, "GenQuest.LosTequesSex"))
			{
				dialog.text = "旦那、部屋と女の子の代金はもういただいてますぜ。さあ、二階へどうぞ、あの娘はしばらく前からあんたを待ってるぜ。 ";
				link.l1 = "「よし。」";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "ああ、あるぜ。どれくらい滞在するつもりだ？";
			if(!isDay())
			{
				link.l1 = "朝までだ。";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "日が暮れるまでだ。";
				link.l1.go = "room_night";
				link.l2 = "次の朝まで。";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "十枚のエイトだぜ。部屋に女もどうだ？あの娘ならたった千ペソだぞ。";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "いや、女はいらねえ。ほら、部屋代だ。";
				link.l1.go = "room_day_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "ああ、部屋と女をもらうぜ。ほら、金だ。";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "あいにく、部屋代を払う余裕がねえんだ。";
			link.l3.go = "exit";
		break;

		case "room_day_next":
			dialog.text = "十枚のエイトだぜ。部屋に女もどうだ？あの娘ならたった千ペソだ。";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "いや、女はいらねえ。ほら、部屋代だ。";
				link.l1.go = "room_day_wait_next";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "よし。部屋と女をもらうぜ。ほら、金だ。";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "あいにく、部屋代を払う余裕がねえんだ。";
			link.l3.go = "exit";
		break;

		case "room_night":
			dialog.text = "十枚のエイト硬貨だぜ。部屋に女も呼ぶかい？あの娘ならたった千ペソだぞ。";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "いや、女はいらねえ。ほら、部屋代だ。";
				link.l1.go = "room_night_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "よし。部屋とあの娘を頼むぜ。金はここにある。";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_night";
				}
			}
			link.l3 = "あいにく、部屋代を払う余裕がないんだ。";
			link.l3.go = "exit";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -20);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "room_girl":
			AddMoneyToCharacter(pchar, -1010);
			dialog.text = "さあ、二階へどうぞ、旦那。あの娘が待ってるぜ。ごゆっくり！";
			link.l1 = "ありがとな、相棒……";
			link.l1.go = "room_girl_1";
		break;
		
		case "room_girl_1":
			DialogExit();
			pchar.GenQuest.CannotWait = true;
			pchar.GenQuest.LosTequesSex = "true";
			LocatorReloadEnterDisable("LosTeques_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("LosTeques_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			sld = GetCharacter(NPC_GenerateCharacter("MineFuckGirl" , "squaw_"+(rand(2)+1), "woman", "woman_B", 1, SPAIN, 1, true, "quest"));
			sld.dialog.FileName = "Tavern\LosTeques_Tavern.c";
			sld.dialog.currentnode = "MineFuckGirl";
			//sld.greeting = "";
			sld.name = GetIndianName(WOMAN);
			sld.lastname = "";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "LosTeques_tavern_upstairs", "goto", "goto1");
		break;
		
		case "MineFuckGirl":
			dialog.text = "どうした、白人の旦那。見るんじゃねえ "+npchar.name+" そんなふうに、 "+npchar.name+" 何でもできるし、あの売春宿の白人女よりもうまいんだぜ。ああ、旦那、あんたは本当にいい男だ……約束するよ、この女はあんたを長く愛し続けるからね。";
			link.l1 = "それはいいな、一番のインディアンのお守りを見せてくれ。お前を濡らすのに雨乞いなんて必要ねえぜ…";
			link.l1.go = "MineFuckGirl_sex";
		break;
		
		case "MineFuckGirl_sex":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("白昼堂々の強盗だと！！！ここで何が起きてるんだ！？待て、ちょっと待てよ、相棒…","おい、そこで何してやがる？！俺を盗もうってのか？こりゃ面倒なことになったな…","待て、てめえ、何してやがる！？やっぱり盗人だったか！ここが貴様の最後だ、クソ野郎……");
			link.l1 = LinkRandPhrase("「悪魔め！」","くそっ！","「ああ、くそっ」");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
