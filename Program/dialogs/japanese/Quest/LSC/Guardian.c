// диалог протекторов, солдат и мушкетеров кланов LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何の用だ、てめえ？";
			link.l1 = "いや、なんでもない。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- фразы гардов нарвалов --------------------------------------------
		// пост нарвалов на проход на Сан-Габриэль
		case "Narval_warning":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("野郎ども、気をつけろ、狂人がいるぞ！武器を取れ！","敵が来たぞ！武器を取れ！","ああ、この野郎！今から痛い目に遭わせてやるぜ！");
				link.l1 = "くそっ！";
				link.l1.go = "check_parol_fight";
				break;
			}
			ref location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "nrv_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "止まれ、相棒。ここから先はナーワルの縄張りだ、よそ者の立ち入りは禁止だぜ。招待状がなきゃ通れねえ。 合言葉は知ってるか？";
					link.l1 = "ああ。";
					link.l1.go = "Narval_warning_yes";
					link.l2 = "いいや。";
					link.l2.go = "Narval_warning_no";
				}
				else // если друг нарвалам
				{
					dialog.text = "「あ、あ、」 "+GetFullName(pchar)+"「やあ、友よ、ここを自由に歩いていいと聞いたぜ。ようこそ！」";
					link.l1 = "ありがとう、友よ！";
					link.l1.go = "exit";
				}
				location.nrv_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "合言葉を忘れてないだろうな……";
					link.l1 = "心配するな……";
					link.l1.go = "exit";
				}
				else // если друг нарвалам
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"！元気にしてるか？";
					link.l1 = "「元気だ、ありがとう！」";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Narval_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Narval_warning_yes":
			dialog.text = "じゃあ、あそこの強面にそれを言ってこい。あいつを騙そうなんて思うなよ、 うちの連中はマスケット銃を持ってるからな、どうすればいいか分かってるぜ。もし何か企んでるなら、 とっとと引き返した方が身のためだ。今すぐにな。警告はしたからな。";
			link.l1 = "わかったぜ、相棒。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_no":
			dialog.text = "なら、ここに用はないだろう。もちろん、死ぬつもりでもない限りな。あるいは冗談か？俺をからかってるのか？まあ、 どうでもいいさ。降りていけ、俺の仕事は警告することで止めることじゃねえ。合言葉を知らなきゃ戻ってこれねえぞ。";
			link.l1 = "わかったぜ、相棒。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "他に何が必要なんだ？「サン・ガブリエル」号に降りるか、とっとと失せろ！";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "申し訳ない。 "+pchar.name+"だが、俺は今、当番中だ。邪魔しないでくれ、友よ。さあ、行ってくれ！";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_parol":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("野郎ども、気をつけろ、あのイカれ野郎が来たぞ！武器を取れ！","敵が来たぞ！武器を取れ！","ああ、この野郎！今からたっぷり思い知らせてやるぜ！");
				link.l1 = "くそっ！";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "申し訳ない。 "+pchar.name+"、だが俺は今当番中だ。邪魔しないでくれ、友よ。さあ、行きな！";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol";
				break;
			}
			dialog.text = "その場から動くな！お前は俺たちの仲間じゃねえ！";
			link.l1 = "俺は立ってる、立ってるんだ。";	
			link.l1.go = "check_parol";
		break;
		
		case "check_parol":
			dialog.text = "合言葉をはっきり大きな声で言え。";
			sTotalTemp = sNrvParol;
			if (CheckAttribute(pchar, "questTemp.LSC.NParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_" + (281 + rand(11)));
				link.l1.go = "check_parol_wrong";
				link.l2 = StringFromKey("QuestsUtilite_" + (293 + rand(11)));
				link.l2.go = "check_parol_wrong";
				link.l3 = StringFromKey("QuestsUtilite_" + (305 + rand(11)));
				link.l3.go = "check_parol_wrong";
				link.l4 = StringFromKey("QuestsUtilite_" + (317 + rand(11)));
				link.l4.go = "check_parol_wrong";
				
				switch (rand(3))
				{
					case 0:
						link.l1 = sTotalTemp;
						link.l1.go = "check_parol_1";
					break;

					case 1:
						link.l2 = sTotalTemp;
						link.l2.go = "check_parol_1";
					break;

					case 2:
						link.l3 = sTotalTemp;
						link.l3.go = "check_parol_1";
					break;

					case 3:
						link.l4 = sTotalTemp;
						link.l4.go = "check_parol_1";
					break;
				}
			}
			else
			{
				link.l1 = "「合言葉だと？通してくれ、さもねえと……」";
				link.l1.go = "check_parol_wrong";
			}
		break;
		
		case "check_parol_1":
			dialog.text = "よし、進んでいいぞ。";
			link.l1 = "ありがとな、相棒……";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			pchar.questTemp.LSC.parol_nrv = "true";
		break;
		
		case "check_parol_wrong":
			dialog.text = "ふむ……おい、野郎ども！客が来たぜ！";
			link.l1 = "くそっ！";
			link.l1.go = "check_parol_fight";
		break;
		
		case "check_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Narval_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("野郎ども、気をつけろ、あの狂人が来たぞ！武器を取れ！\n","敵が来たぞ！武器を取れ！","ああ、この野郎！今から痛い目にあわせてやるぜ！");
				link.l1 = "くそっ！";
				link.l1.go = "check_parol_fight";
				break;
			}
			dialog.text = "進め！ここに立ち止まるな！";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
		break;
		
		// у резиденции
		case "Narval_residence":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("野郎ども、気をつけろ、あのイカれ野郎だ！武器を取れ！","敵が来たぞ！武器を取れ！","ああ、この野郎！今からたっぷり思い知らせてやるぜ！");
				link.l1 = "くそっ！";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // диалог от времени суток. лесник
			    {
					dialog.text = TimeGreeting()+", "+pchar.name+"！ボスに会いたければ、扉は開いてるぜ。";
					link.l1 = "……いいだろう……";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else
				{
                    dialog.text = TimeGreeting()+", "+pchar.name+"！親分に会いたいなら、今は寝てるぜ。朝になったらまた来な。";
					link.l1 = "……わかったよ……";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");	
                }					
				break;	
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "黒人の味方なんざ、ここに用はねえ。親分の直々の命令だ！";
				if (CheckAttribute(pchar, "questTemp.LSC.Donald_enter"))
				{
					link.l1 = "俺に会わなきゃならねえんだ。お前ら、本当に厄介なことになったな。俺は提督の正式な命令でここに来てるんだ。 だから、さっさとそのクソ扉を開けろ！\n";
					link.l1.go = "negotiations";
				}
				else
				{
				link.l1 = "俺もあいつに会いたいとは言えねえな……";
				link.l1.go = "exit";
				}
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "親分に会いたいのか？ふん、じゃあ、さっさと行けよ。";
			link.l1 = "「…させてくれてありがとう…」";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else
			{
            dialog.text = "親分に会いたいのか？今日はもう面会は終わりだ。朝になったらまた来な。";
			link.l1 = "……わかった……";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Narval_soldier":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("野郎ども、気をつけろ、あの狂人が来たぞ！武器を取れ！","敵が来たぞ！武器を取れ！","ああ、この野郎！今から痛い目に遭わせてやるぜ！");
				link.l1 = "くそっ！";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"！元気にしてるか？";
				link.l1 = "大丈夫だ、ありがとう……";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "聞けよ、相棒、今は話す気分じゃねえんだ。どっか行ってくれ…";
				link.l1 = "「いいだろう。」";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_soldier";
		break;
		
		case "negotiations":
			dialog.text = "ほうほう……落ち着けよ。最初から提督の使いだって言えばよかったんだ。見てみろ、ここにはいろんな奴らがうろついてるんだぜ……";
			link.l1 = "やっと通してくれるのか？ありがとな！";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			DialogExit();
			NextDiag.CurrentNode = "negotiations_2";
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false); // открыть вход к Дональду Гринспи
		break;
		
		case "negotiations_2":
			dialog.text = "進め、許可されているぞ…";
			link.l1 = "ああ、本当かい？信じられないな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_2";
		break;
		
//------------------------------------- фразы гардов ривадос --------------------------------------------
		// пост ривадос на проход на Фурию и Веласко
		case "Rivados_warning":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("おい、野郎ども、気をつけろ、凶暴なイカれ野郎がいるぞ！武器を取れ！","敵が来たぞ！武器を取れ！","ああ、このクソ野郎め！今からたっぷり思い知らせてやるぜ！");
				link.l1 = "くそっ！";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "rvd_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "止まれ！俺の後ろにある領地はリヴァドス族のものだ。招待なしのよそ者は通すわけにはいかねえ。合言葉は知ってるか？ ";
					link.l1 = "「ああ。」";
					link.l1.go = "Rivados_warning_yes";
					link.l2 = "いいや。";
					link.l2.go = "Rivados_warning_no";
				}
				else // если друг ривадос
				{
					dialog.text = "「ああ、」 "+GetFullName(pchar)+"！会えて嬉しいぜ！ここを自由に歩いていいって聞いたぞ。ようこそ！";
					link.l1 = "ありがとう、友よ！";
					link.l1.go = "exit";
				}
				location.rvd_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "合言葉を忘れてないだろうな……";
					link.l1 = "心配するな……";
					link.l1.go = "exit";
				}
				else // если друг ривадос
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"！元気にしてるか？";
					link.l1 = "大丈夫だ、ありがとう……";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_warning_yes":
			dialog.text = "行っていいぜ。こいつが合言葉を聞いてくるからな。俺たちを騙すつもりなら、今すぐ出て行ったほうが身のためだぜ。 警告はしたからな。";
			link.l1 = "わかったぜ、相棒。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_no":
			dialog.text = "ほほう！合言葉もなしに俺たちのところへ来るとは、あんた、よほど度胸があるか、ただの馬鹿かどっちかだな。 冗談で来たのか？まあ、行くがいいさ。俺は止めるためじゃなく、警告するためにここにいるんだ。 本当に合言葉を知らないなら、気をつけるんだな！";
			link.l1 = "わかったぜ、相棒。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "さて、何の用だ？さっさと行くか、消えろ！";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "申し訳ない "+pchar.name+"、でも俺は今当番中なんだ。エディがあんまり喋るなって言っててさ。";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_parol":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("野郎ども、気をつけろ、凶暴な狂人がいるぞ！武器を取れ！","敵が来たぞ！武器を取れ！","ああ、てめえは本当にイカれた野郎だな！今から痛い目に遭わせてやるぜ！");
				link.l1 = "くそっ！";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "申し訳ない、 "+pchar.name+"だが、今は当番なんだ。エディがあまり喋るなって言っててな。";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			dialog.text = "そこで止まれ！お前はリヴァドスじゃねえ！";
			link.l1 = "通してほしい。";	
			link.l1.go = "Rcheck_parol";
		break;
		
		case "Rcheck_parol":
			dialog.text = "では、合言葉をはっきり大きな声で言え。";
			sTotalTemp = sRvdParol;
			if (CheckAttribute(pchar, "questTemp.LSC.RParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_" + (281 + rand(11)));
				link.l1.go = "Rcheck_parol_wrong";

				link.l2 = StringFromKey("QuestsUtilite_" + (293 + rand(11)));
				link.l2.go = "Rcheck_parol_wrong";

				link.l3 = StringFromKey("QuestsUtilite_" + (305 + rand(11)));
				link.l3.go = "Rcheck_parol_wrong";

				link.l4 = StringFromKey("QuestsUtilite_" + (317 + rand(11)));
				link.l4.go = "Rcheck_parol_wrong";
				
				switch (rand(3))
				{
					case 0:
						link.l1 = sTotalTemp;
						link.l1.go = "Rcheck_parol_1";
					break;

					case 1:
						link.l2 = sTotalTemp;
						link.l2.go = "Rcheck_parol_1";
					break;

					case 2:
						link.l3 = sTotalTemp;
						link.l3.go = "Rcheck_parol_1";
					break;

					case 3:
						link.l4 = sTotalTemp;
						link.l4.go = "Rcheck_parol_1";
					break;
				}
			}
			else
			{
				link.l1 = "合言葉だと？通してくれ、さもないと……";
				link.l1.go = "Rcheck_parol_wrong";
			}
		break;
		
		case "Rcheck_parol_1":
			dialog.text = "その通りだ。先へ進め。";
			link.l1 = "ありがとな、相棒……";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			pchar.questTemp.LSC.parol_rvd = "true";
		break;
		
		case "Rcheck_parol_wrong":
			dialog.text = "ははは！客人が来たぜ！俺たちがどんな奴らか見せてやろうじゃねえか！";
			link.l1 = "くそっ！";
			link.l1.go = "Rcheck_parol_fight";
		break;
		
		case "Rcheck_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Rivados_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("野郎ども、気をつけろ、危ないイカれ野郎がいるぞ！武器を取れ！","敵が来たぞ！武器を取れ！","ああ、お前は本当にイカれた野郎だな！今から痛い目に遭わせてやるぜ！");
				link.l1 = "くそっ！";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			dialog.text = "ここに立ってないで、さっさと行け！";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
		break;
		
		// у резиденции
		case "Rivados_residence":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("野郎ども、気をつけろ、凶暴なイカれ野郎がいるぞ！武器を取れ！","敵が来たぞ！武器を取れ！","ああ、この病み野郎め！今からたっぷり教えてやるぜ！");
				link.l1 = "くそっ！";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
				{
				dialog.text = TimeGreeting()+", "+pchar.name+"！ドアは開いてるぜ、エディとチミセットに会いたきゃどうぞ。あいつら、あんたに会えて喜ぶだろうよ。";
				link.l1 = "……いいだろう……";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else // лесник - режим пропуска 
				{	
				dialog.text = TimeGreeting()+", "+pchar.name+"！エディとチミセットに会いたいなら、もう休んでるぜ。朝になったらまた来な。あいつらもきっと喜ぶさ。";
				link.l1 = "……わかった……";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "エディの船室にはナーワルの仲間が入る用はねえぞ！これはあいつの直々の命令だ。とっとと失せろ！";
				link.l1 = "俺もあいつに会いたくなかったんだよ……";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (GetCharacterIndex("Chimiset") == -1) // Чимисет убит
			{
				dialog.text = "エディの船室の中でお前がやることは何もねえ！それはあいつからの直々の命令だ。さっさと失せろ！";
				link.l1 = "俺もあいつには会いたくなかったんだよ……";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "エディに会いたいのか？まあいい、進めよ。あいつもお前のために少しは時間を割いてくれるだろう。";
			link.l1 = "「…させてくれてありがとう」";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else // лесник режим пропуска.
			{
            dialog.text = "エディに会いたいのか？今日はもう面会はできねえ、朝になったらまた来な。 そしたらエディが少しだけ時間を割いてくれるぜ。";
			link.l1 = "……わかった……";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Rivados_soldier":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("野郎ども、気をつけろ、狂暴なやつがいるぞ！武器を取れ！","敵が来たぞ！武器を取れ！","ああ、お前は本当にイカれた野郎だな！今から痛い目に遭わせてやるぜ！");
				link.l1 = "くそっ！";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"！元気にしてるか？";
				link.l1 = "大丈夫だ、ありがとう……";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "聞けよ、相棒、今は話す気分じゃねえんだ。どっか行ってくれ…";
				link.l1 = "「いいだろう。」";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_soldier";
		break;
//------------------------------------- фразы гардов пиратов --------------------------------------------	
		// у склада
		case "Shark_storage":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("おい、野郎ども、気をつけろ、武装した狂人がいるぞ！武器を取れ！","敵が来たぞ！武器を取れ！","ああ、この野郎！今からてめえのケツを蹴っ飛ばしてやるぜ！");
				link.l1 = "くそっ！";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "止まれ！ここは立入禁止区域だ！";
			link.l1 = "わかったよ、あんたの言う通りだ……";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_storage";
		break;
		
		// у резиденции
		case "Shark_residence":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("おい、野郎ども、気をつけろ、武装した狂人がいるぞ！武器を取れ！","敵が来たぞ！武器を取れ！","ああ、この野郎！今からてめえのケツを蹴っ飛ばしてやるぜ！");
				link.l1 = "くそっ！";
				link.l1.go = "shark_guard_fight";
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00)
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "止まれ！お前は俺たちの仲間じゃねえな……シャークが待ってるのか？それともただ島をうろついてるだけか？";
					link.l1 = "「サメ？スティーブ・ドドソン？」";
					link.l1.go = "first_talk_day";
				}
				else
				{
				dialog.text = "提督があんたを受け入れるぜ。さあ、進みな。";
				link.l1 = "ありがとう！";
				link.l1.go = "exit";
			}
			}
			else
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "どこへそんなに急いでるんだ？夜だぞ、見えねえのか！ それとも本気で提督がわざわざ起きてお前を迎えてくれるとでも思ってるのか？朝になってからまた来い。";
					link.l1 = "おっしゃる通りです。それで、どこで休めますか？";
					link.l1.go = "first_talk_night";
				}
			else
			{
				dialog.text = "もう遅いぞ、提督は今は会っていない。明日また来い。";
				link.l1 = "……いいだろう……";
				link.l1.go = "exit";
			}
			}
			NextDiag.TempNode = "Shark_residence";
		break;
		
		case "Shark_soldier":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("おい野郎ども、気をつけろ、武装した狂人がいるぞ！武器を取れ！","敵が来たぞ！武器を取れ！","ああ、この野郎！今からてめえのケツを蹴っ飛ばしてやるぜ！");
				link.l1 = "くそっ！";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "提督に話しているところを見られたら、機嫌を損ねるぜ。さっさと行け。";
			link.l1 = "……いいだろう……";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_soldier";
		break;
		
		case "first_talk_night":
			dialog.text = NPCStringReactionRepeat("酔ってるのか？引き返して橋を渡り、船を二隻通り過ぎたら、もう一つ橋がある。それを渡れば酒場に着く。 そこで寝るんだ。","俺を怒らせたいのか？今言ったことをやれって言っただろ。消えろ！","寝ろよ、酔っ払い面……","「消えろ！！」","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("ありがとうございます、旦那。実はもう少し礼儀正しくしてくれてもいいんじゃないか…","申し訳ない、忘れてしまった……","俺は酔っちゃいねえ！","「なんだって！？」",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "first_talk_day":
			dialog.text = "そんなに驚くなよ、坊主。スティーブ・シャークが俺たちの提督だってのは皆知ってるさ。あんた、あいつに何か用か？";
			link.l1 = "ああ、くそっ！俺はあいつに用があるんだ、しかも急ぎだぜ。";
			link.l1.go = "first_talk_day_1";
		break;
		
		case "first_talk_day_1":
			dialog.text = "「どんな用件だ？」";
			link.l1 = "このことはシャークにだけ内緒で話すつもりだ。俺はヤン・スヴェンソンのために働いているんだが、 あんたはあいつを知ってるか？";
			link.l1.go = "first_talk_day_2";
		break;
		
		case "first_talk_day_2":
			dialog.text = "森の悪魔だと？はっ！メインの半分はあの男を知ってるぜ。いいか、坊主、意地張るのはやめろ。事情を話すか、 俺が怒る前にとっとと消えな。シャークが「役立たずは放っておけ」って言ったから、俺はその通りにしてるだけだ。";
			link.l1 = "わかった。ほら、この手紙を見てみろ、フォレストデビルがシャークに宛てて書いたものだ。";
			link.l1.go = "first_talk_day_3";
		break;
		
		case "first_talk_day_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "（見ている）…まあいい。スティーブも面白がるだろうさ。さあ、行け。";
			link.l1 = "「へえ、そうかい？もし面倒でなけりゃ、その手紙を返してくれよ、頼むぜ。」";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "first_talk_day_5";
			else link.l1.go = "first_talk_day_4";
		break;
		
		case "first_talk_day_4":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
			LocatorReloadEnterDisable("LostShipsCity_town", "reload2", true); //закрываем кладовку со стороны моря
			pchar.quest.LSC_entry_pantry.over = "yes"; //снять прерывание на арест
			pchar.quest.LSC_findMary.over = "yes"; //снять прерывание на Мэри
			pchar.questTemp.LSC = "entrance"; //меняем флаг
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
			// закрываем вход к Мэри
			LocatorReloadEnterDisable("LostShipsCity_town", "reload60", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload61", true);
		break;
		
		case "first_talk_day_5":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
		break;
		
		case "shark_guard_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_SHARK");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
