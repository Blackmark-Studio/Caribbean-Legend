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
			dialog.text = "Ne istiyorsun, söyle bakalım?";
			link.l1 = "Hayır, bir şey değil.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- фразы гардов нарвалов --------------------------------------------
		// пост нарвалов на проход на Сан-Габриэль
		case "Narval_warning":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Çocuklar, dikkat edin, burada bir deli var! Silah başına!","Düşman burada! Silah başına!","Ah, seni alçak! Şimdi sana gününü göstereceğiz!");
				link.l1 = "Siktir!";
				link.l1.go = "check_parol_fight";
				break;
			}
			ref location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "nrv_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Dur dostum. İlerisi Narval bölgesi, yabancılara giriş yasak. Sadece davetle geçebilirsin. Parolayı biliyor musun?";
					link.l1 = "Evet.";
					link.l1.go = "Narval_warning_yes";
					link.l2 = "Hayır.";
					link.l2.go = "Narval_warning_no";
				}
				else // если друг нарвалам
				{
					dialog.text = "A-ah, "+GetFullName(pchar)+"! Merhaba, dostum, burada özgürce dolaşabileceğin söylendi bize. Hoş geldin!";
					link.l1 = "Teşekkür ederim, dostum!";
					link.l1.go = "exit";
				}
				location.nrv_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Umarım parolayı unutmadın...";
					link.l1 = "Endişelenme...";
					link.l1.go = "exit";
				}
				else // если друг нарвалам
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! Nasılsın?";
					link.l1 = "İyiyim, sağ ol!";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Narval_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Narval_warning_yes":
			dialog.text = "O zaman git ve bunu oradaki kabadayıya söyle. Sakın onu kandırmaya kalkma, tüfekli adamlarımız ne yapacaklarını iyi bilir. Eğer bir numara çevirmeyi düşünüyorsan, en iyisi şimdi dönüp gitmek. Uyardım seni.";
			link.l1 = "Pekala, dostum. Anladım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_no":
			dialog.text = "O zaman burada işin yok, tabii hayatına son vermek istemiyorsan. Yoksa şaka mı yapıyorsun, ha? Benimle dalga mı geçiyorsun? Aslında umurumda değil. Aşağı in, benim görevim uyarmak, durdurmak değil. Parolayı bilmiyorsan geri dönemezsin.";
			link.l1 = "Pekala, dostum. Anladım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "Daha ne istiyorsun? Ya 'San Gabriel'e in ya da kaybol!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Üzgünüm, "+pchar.name+", ama görev başındayım. Beni rahatsız etme, dostum. Yoluna devam et!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_parol":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Çocuklar, dikkat edin, o deli geliyor! Silah başına!","Düşman burada! Silah başına!","Ah, seni alçak! Şimdi sana gününü göstereceğiz!");
				link.l1 = "Lanet olsun!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "Üzgünüm, "+pchar.name+", ama görev başındayım. Beni rahatsız etme, dostum. Yoluna devam et!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol";
				break;
			}
			dialog.text = "Olduğun yerde kal! Sen bizden biri değilsin!";
			link.l1 = "Ayakta duruyorum, duruyorum.";	
			link.l1.go = "check_parol";
		break;
		
		case "check_parol":
			dialog.text = "Parolayı söyle, açık ve net bir şekilde.";
			sTotalTemp = sNrvParol;
			if (CheckAttribute(pchar, "questTemp.LSC.NParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_"+(281+rand(11)));
				link.l1.go = "check_parol_wrong";
				link.l2 = StringFromKey("QuestsUtilite_"+(293+rand(11)));
				link.l2.go = "check_parol_wrong";
				link.l3 = StringFromKey("QuestsUtilite_"+(305+rand(11)));
				link.l3.go = "check_parol_wrong";
				link.l4 = StringFromKey("QuestsUtilite_"+(317+rand(11)));
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
				link.l1 = "Ne parolü? Bırak geçeyim, yoksa...";
				link.l1.go = "check_parol_wrong";
			}
		break;
		
		case "check_parol_1":
			dialog.text = "Pekala, devam edebilirsin.";
			link.l1 = "Sağ ol, dostum...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			pchar.questTemp.LSC.parol_nrv = "true";
		break;
		
		case "check_parol_wrong":
			dialog.text = "Hm... Çocuklar! Misafirimiz var!";
			link.l1 = "Lanet olsun!";
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
				dialog.text = LinkRandPhrase("Çocuklar, dikkat edin, o deli orada! Silah başına!","Düşman burada! Silah başına!","Ah, seni alçak! Şimdi sana gününü göstereceğiz!");
				link.l1 = "Lanet olsun!";
				link.l1.go = "check_parol_fight";
				break;
			}
			dialog.text = "Yoluna devam et! Burada durma!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
		break;
		
		// у резиденции
		case "Narval_residence":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Çocuklar, dikkatli olun, o deli orada! Silahlara!","Düşman burada! Silah başına!","Ah, seni alçak! Şimdi sana haddini bildireceğiz!");
				link.l1 = "Lanet olsun!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // диалог от времени суток. лесник
			    {
					dialog.text = TimeGreeting()+", "+pchar.name+"! Kapı açık, patronu görmek istersen içeri girebilirsin.";
					link.l1 = "Peki...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else
				{
                    dialog.text = TimeGreeting()+", "+pchar.name+"! Patronu görmek istiyorsan, şu an uyuyor. Sabah tekrar gel.";
					link.l1 = "Peki...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");	
                }					
				break;	
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Siyahların dostlarının burada işi yok. Patronun doğrudan emri!";
				if (CheckAttribute(pchar, "questTemp.LSC.Donald_enter"))
				{
					link.l1 = "Beni görmek zorunda kalacak. Başınız gerçekten büyük belada, arkadaşlar. Buraya amiralin resmi emriyle geldim. O yüzden şu lanet kapıyı açın!";
					link.l1.go = "negotiations";
				}
				else
				{
				link.l1 = "Onu görmek istediğimi de söyleyemem...";
				link.l1.go = "exit";
				}
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Patronu mu görmek istiyorsun? Hm, peki, o zaman yoluna devam et.";
			link.l1 = "Bana izin verdiğin için teşekkür ederim...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else
			{
            dialog.text = "Patronu mu görmek istiyorsun? Bugün ziyaret yok. Sabah tekrar gel.";
			link.l1 = "Pekala...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Narval_soldier":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Çocuklar, dikkat edin, o deli orada! Silah başına!","Düşman burada! Silah başına!","Ah, seni alçak! Şimdi sana gününü göstereceğiz!");
				link.l1 = "Siktir!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Nasılsın?";
				link.l1 = "İyiyim, sağ ol...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Dinle dostum, konuşacak havamda değilim. Yola devam et...";
				link.l1 = "Pekâlâ.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_soldier";
		break;
		
		case "negotiations":
			dialog.text = "Pekâlâ, pekâlâ... Sakin ol. Baştan amiralden geldiğini söyleseydin ya. Bak, burada her türlü insan dolaşıyor...";
			link.l1 = "Sonunda beni geçirecek misin? Teşekkürler!";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			DialogExit();
			NextDiag.CurrentNode = "negotiations_2";
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false); // открыть вход к Дональду Гринспи
		break;
		
		case "negotiations_2":
			dialog.text = "Yoluna devam et, buna izinlisin...";
			link.l1 = "Gerçekten mi? İnanamıyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_2";
		break;
		
//------------------------------------- фразы гардов ривадос --------------------------------------------
		// пост ривадос на проход на Фурию и Веласко
		case "Rivados_warning":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Çocuklar, dikkatli olun, saldırgan bir psikopat var! Silahlara!","Düşman burada! Silah başına!","Ah, seni pislik herif! Şimdi sana gününü göstereceğiz!");
				link.l1 = "Lanet olsun!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "rvd_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Dur! Arkamdaki topraklar Rivados klanına ait, ve senin gibi yabancılar davet olmadan geçemez. Parolayı biliyor musun?";
					link.l1 = "Evet.";
					link.l1.go = "Rivados_warning_yes";
					link.l2 = "Hayır.";
					link.l2.go = "Rivados_warning_no";
				}
				else // если друг ривадос
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Seni gördüğümüze sevindik! Burada özgürce dolaşabileceğin söylendi bize. Hoş geldin!";
					link.l1 = "Teşekkür ederim, dostum!";
					link.l1.go = "exit";
				}
				location.rvd_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Umarım parolayı unutmadın...";
					link.l1 = "Endişelenme...";
					link.l1.go = "exit";
				}
				else // если друг ривадос
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! Nasılsın?";
					link.l1 = "İyiyim, teşekkürler...";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_warning_yes":
			dialog.text = "Gidebilirsin o zaman. Bu delikanlı senden bir parola isteyecek. Bizi kandırmak gibi bir niyetin varsa, şimdi gitmen en iyisi. Seni uyardım.";
			link.l1 = "Pekâlâ, dostum. Anladım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_no":
			dialog.text = "Ho-ho! Eğer bizi bir parola olmadan ziyaret etmeye geliyorsan, ya çok cesursun ya da çok delisin. Yoksa şaka mı yapıyorsun? Hadi bakalım. Benim işim uyarmak, durdurmak değil. Gerçekten parolayı bilmiyorsan dikkatli ol!";
			link.l1 = "Pekâlâ, dostum. Anladım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Ne istiyorsun? Yürü git ya da kaybol!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Üzgünüm, "+pchar.name+", ama nöbetteyim. Eddie fazla konuşmamı istemiyor.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_parol":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Çocuklar, dikkatli olun, saldırgan bir deli var! Silah başına!","Düşman burada! Silah başına!","Ah, sen tam bir pisliksin! Şimdi sana haddini bildireceğiz!");
				link.l1 = "Lanet olsun!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Üzgünüm, "+pchar.name+", ama nöbetteyim. Eddie fazla konuşmamı istemiyor.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			dialog.text = "Olduğun yerde kal! Sen Rivados değilsin!";
			link.l1 = "Geçmek istiyorum.";	
			link.l1.go = "Rcheck_parol";
		break;
		
		case "Rcheck_parol":
			dialog.text = "O zaman bir parola söyle ve yüksek sesle, net bir şekilde söyle.";
			sTotalTemp = sRvdParol;
			if (CheckAttribute(pchar, "questTemp.LSC.RParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_"+(281+rand(11)));
				link.l1.go = "Rcheck_parol_wrong";

				link.l2 = StringFromKey("QuestsUtilite_"+(293+rand(11)));
				link.l2.go = "Rcheck_parol_wrong";

				link.l3 = StringFromKey("QuestsUtilite_"+(305+rand(11)));
				link.l3.go = "Rcheck_parol_wrong";

				link.l4 = StringFromKey("QuestsUtilite_"+(317+rand(11)));
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
				link.l1 = "Ne şifresi? Beni geçir, yoksa...";
				link.l1.go = "Rcheck_parol_wrong";
			}
		break;
		
		case "Rcheck_parol_1":
			dialog.text = "Doğru. Devam et.";
			link.l1 = "Sağ ol, dostum...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			pchar.questTemp.LSC.parol_rvd = "true";
		break;
		
		case "Rcheck_parol_wrong":
			dialog.text = "Ha-ha! Burada bir misafirimiz var! Ona kim olduğumuzu gösterelim!";
			link.l1 = "Lanet olsun!";
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
				dialog.text = LinkRandPhrase("Çocuklar, dikkatli olun, saldırgan bir psikopat var! Silah başına!","Düşman burada! Silah başına!","Ah, sen tam bir pisliksin! Şimdi sana iyi bir ders vereceğiz!");
				link.l1 = "Lanet olsun!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			dialog.text = "Burada durma, yoluna devam et!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
		break;
		
		// у резиденции
		case "Rivados_residence":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Çocuklar, dikkatli olun, saldırgan bir psikopat var! Silah başına!","Düşman burada! Silah başına!","Ah, seni pislik herif! Şimdi sana gününü göstereceğiz!");
				link.l1 = "Siktir!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
				{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Kapı açık, Eddie ve Chimiset'i görmek istersen içeri girebilirsin. Seni gördüklerine sevineceklerdir.";
				link.l1 = "Peki...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else // лесник - режим пропуска 
				{	
				dialog.text = TimeGreeting()+", "+pchar.name+"! Eddie ve Chimiset'i görmek istiyorsan, onlar çoktan dinlenmeye çekildiler. Sabah tekrar gel, seni gördüklerine sevinecekler.";
				link.l1 = "Peki...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Narval dostlarının Eddie'nin kamarasında yapacak hiçbir şeyi yok! Bu onun kesin emri. Kaybol!";
				link.l1 = "Ben de onu görmek istememiştim...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (GetCharacterIndex("Chimiset") == -1) // Чимисет убит
			{
				dialog.text = "Eddie'nin kamarasında yapacak hiçbir işin yok! Bu onun doğrudan emri. Kaybol!";
				link.l1 = "Ben de onu görmek istememiştim...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Eddie'yi görmek mi istiyorsun? Peki, devam et, sanırım senin için bir dakikasını ayırır.";
			link.l1 = "Bana izin verdiğin için teşekkür ederim...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else // лесник режим пропуска.
			{
            dialog.text = "Eddie'yi mi görmek istiyorsun? Bugün artık ziyaretçi kabul etmiyoruz, sabah tekrar gel, o zaman seninle bir dakika görüşür.";
			link.l1 = "Pekala...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Rivados_soldier":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Çocuklar, dikkatli olun, saldırgan bir deli var! Silah başına!","Düşman burada! Silah başına!","Ah, sen tam bir pisliksin! Şimdi sana gününü göstereceğiz!");
				link.l1 = "Lanet olsun!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Nasılsın?";
				link.l1 = "İyiyim, sağ ol...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Dinle dostum, konuşacak havamda değilim. Yola devam et...";
				link.l1 = "Pekâlâ.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_soldier";
		break;
//------------------------------------- фразы гардов пиратов --------------------------------------------	
		// у склада
		case "Shark_storage":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Çocuklar, dikkatli olun, silahlı bir deli var! Silah başına!","Düşman burada! Silah başına!","Ah, seni alçak! Şimdi senin kıçını tekmeleyeceğiz!");
				link.l1 = "Lanet olsun!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Dur! Burası yasak bir bölge!";
			link.l1 = "Peki, dediğin gibi olsun...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_storage";
		break;
		
		// у резиденции
		case "Shark_residence":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Çocuklar, dikkatli olun, silahlı bir deli var! Silah başına!","Düşman burada! Silah başına!","Ah, seni alçak! Şimdi kıçını tekmeleyeceğiz!");
				link.l1 = "Lanet olsun!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00)
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Dur! Bizden biri değilsin... Köpekbalığı seni mi bekliyor, yoksa öylece amaçsızca mı dolaşıyorsun?";
					link.l1 = "Köpekbalığı mı? Steve Dodson?";
					link.l1.go = "first_talk_day";
				}
				else
				{
				dialog.text = "Amiral seni kabul edecek. Devam et.";
				link.l1 = "Teşekkürler!";
				link.l1.go = "exit";
			}
			}
			else
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Nereye böyle acele ediyorsun? Gece oldu, görmüyor musun! Yoksa gerçekten amiralin seni karşılamak için uyanacağını mı sandın? Sabah gel.";
					link.l1 = "Dediğiniz gibi. Peki, nerede dinlenebilirim?";
					link.l1.go = "first_talk_night";
				}
			else
			{
				dialog.text = "Geç oldu, amiral şu anda kimseyi kabul etmiyor. Yarın tekrar gel.";
				link.l1 = "Peki...";
				link.l1.go = "exit";
			}
			}
			NextDiag.TempNode = "Shark_residence";
		break;
		
		case "Shark_soldier":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Çocuklar, dikkat edin, silahlı bir deli var! Silah başına!","Düşman burada! Silah başına!","Ah, seni alçak! Şimdi senin kıçını tekmeleyeceğiz!");
				link.l1 = "Lanet olsun!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Amiral beni konuşurken görürse hoşuna gitmez. Yola devam et.";
			link.l1 = "Pekâlâ...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_soldier";
		break;
		
		case "first_talk_night":
			dialog.text = NPCStringReactionRepeat("Sarhoş musun? Geri dön ve köprüyü geç, iki geminin yanından geçtikten sonra başka bir köprü göreceksin, o seni meyhaneye götürecek. Orada uyu.","Beni sinirlendirmeye mi çalışıyorsun? Ne yapman gerektiğini az önce söyledim. Kaybol!","Git biraz uyu, sarhoş surat...","Defol!!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Teşekkür ederim, efendim. Aslında biraz daha nazik olabilirdiniz...","Üzgünüm, unuttum...","Ben sarhoş değilim!","Ne?!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "first_talk_day":
			dialog.text = "Bu kadar şaşırma, delikanlı. Herkes Steve Shark'ın bizim amiralimiz olduğunu bilir. Onunla bir işin mi var?";
			link.l1 = "Evet, kahretsin! Onunla işim var ve bu acil.";
			link.l1.go = "first_talk_day_1";
		break;
		
		case "first_talk_day_1":
			dialog.text = "Ne tür bir iş?";
			link.l1 = "Bunu sadece Köpekbalığı'na özel olarak anlatacağım. Jan Svenson için çalışıyorum, onu tanıyor musun?";
			link.l1.go = "first_talk_day_2";
		break;
		
		case "first_talk_day_2":
			dialog.text = "Orman Şeytanı mı? Ha! Ana karanın yarısı o adamı tanır. Dinle evlat, inat etme. Ya kendini açıkla ya da ben sinirlenmeden kaybol. Köpekbalığı, işe yaramazlardan uzak durmamı söyledi, ben de emrine uyuyorum.";
			link.l1 = "Peki. Bak, işte bu mektuba bir göz at, Orman Şeytanı tarafından Köpekbalığı'na yazılmış.";
			link.l1.go = "first_talk_day_3";
		break;
		
		case "first_talk_day_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(bakıyor)... Peki. Sanırım Steve bunu ilginç bulacaktır. Devam et.";
			link.l1 = "Gerçekten mi? Eğer zahmet olmazsa, mektubu geri verir misin lütfen.";
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
