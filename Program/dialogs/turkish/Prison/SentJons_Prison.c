// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Konuş, dinliyorum";
			link.l1 = "Yanılmışım. Hoşça kal.";
			link.l1.go = "Exit";
			
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaZalog"))
			{
				link.l1 = "Geçenlerde şehrin askerlerinden biri Charlie Knippel'i tutuklayıp gözaltına aldı. Hâlâ burada mı?"; 
				link.l1.go = "DTSG_AntiguaZalog_2";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов
		case "DTSG_AntiguaZalog_2":
			dialog.text = "Evet, doğru, ama neden soruyorsun?";
			link.l1 = "Şu mesele var ki, Charlie benim subaylarımdan biri. Neyle suçlandığını öğrenmek istiyorum. Onu götüren askerler bana hiçbir şey söylemedi."; 
			link.l1.go = "DTSG_AntiguaZalog_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaZalog_3":
			dialog.text = "Doğru. Bu, herkesin bildiği bir şey değil. Ne yazık ki, sizin için bile öyle. Bu bir devlet sırrı, efendim.";
			link.l1 = "Yani, kefalet seçeneği yok anladığım kadarıyla?"; 
			link.l1.go = "DTSG_AntiguaZalog_4";
		break;
		
		case "DTSG_AntiguaZalog_4":
			dialog.text = "Kesinlikle. Değerli bir tayfanı kaybetmenin ne kadar can sıkıcı olduğunu anlıyorum, ama ne sen ne de ben bu konuda bir şey yapamayız. Gerçekten üzgünüm, Kaptan.";
			link.l1 = "Kefalet yok anladım. O halde... tazminat teklif edeyim? Hem de cömertçe. Sizin ve tüm adamlarınız için, kimse dışarıda kalmasın."; 
			link.l1.go = "DTSG_AntiguaZalog_5";
		break;
		
		case "DTSG_AntiguaZalog_5":
			dialog.text = "Rüşvet mi? Cesurca, Kaptan, ama ne kadar para verirseniz verin, Charlie'yi serbest bıraktığımızı öğrenenlerin gazabından bizi hiçbir şey kurtaramaz.";
			link.l1 = "Belki... Ama en azından onunla konuşabilir miyim?"; 
			link.l1.go = "DTSG_AntiguaZalog_6";
		break;
		
		case "DTSG_AntiguaZalog_6":
			dialog.text = "Neden olmasın? Onu kurtarmak ya da kaçmasına yardım etmek için hiçbir şey yapamazsın, o yüzden... buyur. Hücrelerden birinde.";
			link.l1 = "Ha, ya bana neyle suçlandığını ve senin bu kadar önemsediğin o devlet sırrını açıklarsa, Memur Bey?"; 
			link.l1.go = "DTSG_AntiguaZalog_7";
		break;
		
		case "DTSG_AntiguaZalog_7":
			dialog.text = "Bundan endişelenmiyorum. Nedenini anlarsın. Hadi git, fikrimi değiştirmeden önce eski subayınla konuş.";
			link.l1 = "Teşekkür ederim."; 
			link.l1.go = "DTSG_AntiguaZalog_8";
		break;
		
		case "DTSG_AntiguaZalog_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaZalog");
			pchar.questTemp.jailCanMove = true;
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto9");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Killer", "sold_eng_10", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Killer";
			LAi_SetStayType(sld);
			sld.talker = 5;
			GiveItem2Character(sld, "blade_14");
			EquipCharacterbyItem(sld, "blade_14");
			GiveItem2Character(sld, "pistol4");
			EquipCharacterbyItem(sld, "pistol4");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload12");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			LAi_SetImmortal(sld, true);
		break;
		
		case "DTSG_AntiguaTrevoga_2":
			dialog.text = "Gerek yok, Kaptan. Dediğim gibi, seni de o aptal Charlie'nin yanına, aynı hücreye atacaklardı. Ama birincisi, Vali tutuklanmaya direnmemeni takdir etti, ikincisi ise, sarayın camlarını neredeyse kıracak kadar bağıran tefeciyle yapılan son görüşmeden hiç memnun kalmadı...";
			link.l1 = "Benim tutuklanmamı mı istedi?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaTrevoga_3":
			dialog.text = "O sormadı - emretti. Ve Ekselansları'na bir şey empoze edilmesinden hiç hoşlanmaz. Bu yüzden o tefeci kapı dışarı edildi.";
			link.l1 = "Çok komik. Şimdi..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_4";
		break;
		
		case "DTSG_AntiguaTrevoga_4":
			dialog.text = "Şimdi aynısını yapmanızı tavsiye ederim, Kaptan de Maure. Ve cevap alamayacağınız soruları sormayın.";
			link.l1 = "Charlie Knippel olmadan buradan ayrılmam."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H1";
			link.l2 = "Lütfen, efendim, Charlie Knippel ile konuşmama izin verin. Ya da en azından ne olduğunu öğreneyim..."; 
			link.l2.go = "DTSG_AntiguaTrevoga_Ch1";
		break;
		
		case "DTSG_AntiguaTrevoga_H1":
			dialog.text = "O halde, ona katıl. Ama bir hücrede değil, öteki dünyada.";
			link.l1 = "Demek ki, öldü..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H2";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_H2":
			dialog.text = "Gerçekten keskinsiniz, Kaptan. Ama şunu bilin ki size bunu kimin ve neden yaptığını asla söylemeyeceğim.";
			link.l1 = "Öyle mi?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_H3";
		break;
		
		case "DTSG_AntiguaTrevoga_H3":
			dialog.text = "Aynen öyle. Ve şimdi sabrımı sınama – yoksa bir İngiliz askerini öldürdüğün için seni hücreye attırırım.";
			link.l1 = "Senin hücrelerinden pek az kişinin çıktığını düşünürsek, orada olmak istemem. Sana iyi günler dilemiyorum."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_Ch1":
			dialog.text = "Charlie Knippel hiç kimseyle konuşmaz. Belki sadece Yaratıcı ile...";
			link.l1 = "Öldü mü?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_Ch2";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_Ch2":
			dialog.text = "Cezası infaz edildi. Sana ayrıntı veremem. Ve umarım ısrar etmezsin - bu senin için kötü sonuçlanabilir. Sadece bir hücreyle de kalmaz. Anlaşıldı mı, Kaptan de Mor?";
			link.l1 = "Gayet açık. Hoşça kal."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaTrevoga");
			AddQuestRecord("DTSG", "10");
			CloseQuestHeader("DTSG");
			ChangeCharacterComplexReputation(pchar, "authority", -10);
			AddCrewMorale(Pchar, -30);
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
