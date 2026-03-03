// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Bana bu soruyu kısa bir süre önce de sormuştunuz...","Evet, dur tahmin edeyim... Yine aynı şeyleri mi dolaşıyorsun?","Dinle, burada finans işlerini ben yürütüyorum, sorulara cevap vermem...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Doğru tahmin ettiniz, üzgünüm...","Anladım...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Sinistra Длинные тени старых грехов	
			if (CheckAttribute(pchar, "questTemp.DTSG_KnippelDolg"))
			{
				link.l1 = "Borçlularınızdan biriyle ilgili sizinle konuşmak istiyorum.";
				link.l1.go = "DTSG_KnippelDolg";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов	
		case "DTSG_KnippelDolg":
			DeleteAttribute(pchar, "questTemp.DTSG_KnippelDolg");
			dialog.text = "Hangisi?";
			if (sti(pchar.reputation.nobility) > 50)
			{
				link.l1 = "(Onur) Kesinlikle Charlie Knippel.";
				link.l1.go = "DTSG_KnippelDolg_VD_2";
			}
			else
			{
				link.l2 = "(Onur) Bana bu kadar sakin konuşmaya nasıl cüret ediyorsun. Adamımın peşine ödül avcılarını sen gönderdin.";
				link.l2.go = "DTSG_KnippelDolg_2";
			}
		break;
		
		case "DTSG_KnippelDolg_VD_2":
			dialog.text = "Charlie mi? Ama artık benim borçlum değil. Borcu çoktan ödendi, efendim.";
			link.l1 = "Gerçekten mi? Eğer sır değilse, kim tarafından?";
			link.l1.go = "DTSG_KnippelDolg_VD_3";
		break;
		
		case "DTSG_KnippelDolg_VD_3":
			dialog.text = "It's not. By his captain, Richard Fleetwood. A true gentleman; everyone should have friends like him.";
			link.l1 = "Bakın, artık Charlie'nin kaptanıyım. Bay Fleetwood... onu bana devretti. Sözünü tutup size ödeme yaptığını bilmek güzel.";
			link.l1.go = "DTSG_KnippelDolg_VD_4";
		break;
		
		case "DTSG_KnippelDolg_VD_4":
			dialog.text = "Demek bu yüzden soruyorsun.";
			link.l1 = "Sadece bu da değil. Charlie'yi iyi tanıyorsun, değil mi? Tutuklandı ve daha önce de paralı askerler peşine gönderildi. Nedenini biliyor musun? Sonuçta, seninle iş yapanlar oldukça... çeşitli insanlar.";
			link.l1.go = "DTSG_KnippelDolg_VD_5";
		break;
		
		case "DTSG_KnippelDolg_VD_5":
			dialog.text = "Charlie tutuklandı mı? Beni şaşırttınız efendim, bundan hiç haberim yoktu. Onun... düşmanları olduğundan da. O, Tanrı'dan korkan iyi bir adamdı...";
			link.l1 = "Buna itiraz edemem. Neyse, yine de teşekkürler. Umarım komutan kefaletimi kabul eder.";
			link.l1.go = "DTSG_KnippelDolg_VD_6";
		break;
		
		case "DTSG_KnippelDolg_VD_6":
			dialog.text = " Kefalet için paraya ihtiyacınız olursa tekrar bana gelmekten çekinmeyin – size iyi şartlar sunarım. ";
			link.l1 = "Ha-ha, ciddi misiniz? Bir tefeci her zaman tefecidir. Kefaleti kendim ödeyebilirim. Hoşça kalın.";
			link.l1.go = "DTSG_KnippelDolg_VD_7";
		break;
		
		case "DTSG_KnippelDolg_VD_7":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			AddQuestRecord("DTSG", "11");
			pchar.questTemp.DTSG_AntiguaZalog = true;
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		
		case "DTSG_KnippelDolg_2":
			dialog.text = "Ödül avcıları mı? Adamının peşinde mi? Neden bahsediyorsun?..";
			link.l1 = "İnkar etme. En iyisi itiraf et, meseleyi centilmenler gibi halledelim. Ama numara yaparsan, işi zor yoldan çözmek zorunda kalırım.";
			link.l1.go = "DTSG_KnippelDolg_3";
		break;
		
		case "DTSG_KnippelDolg_3":
			dialog.text = "Y-yanılıyorsunuz!.. Muhafız!!! Beni öldürmekle tehdit ediyor!";
			link.l1 = "Allah kahretsin ya...";
			link.l1.go = "DTSG_KnippelDolg_4";
		break;
		
		case "DTSG_KnippelDolg_4":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaStrazhBank_1", "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, false, "soldier"));
			GiveItem2Character(sld, "blade_10");
			EquipCharacterByItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterByItem(sld, "pistol1");
			ChangeCharacterAddressGroup(sld, "SentJons_bank", "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_AntiguaStrazhBank";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			LAi_SetHP(sld, 140+MOD_SKILL_ENEMY_RATE*10, 140+MOD_SKILL_ENEMY_RATE*10);
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
