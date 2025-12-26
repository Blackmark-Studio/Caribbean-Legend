// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsun?","Ne bilmek istersiniz?"),"Ne istiyorsun, "+GetAddress_Form(NPChar)+"?","Bu üçüncü kez bana sormaya çalışıyorsun...","Senden bıktım, defol git!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Üzgünüm, fikrimi değiştirdim.","Önemli değil, kusura bakmayın."),"Unuttum, özür dilerim...","Üçüncü seferde olacak galiba, ha? Affedersin...","Affedersin, affedersin! O zaman ben kendim çıkayım...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Bak, Miguel Dichoso'nun komutasındaki bir fırkateyn Nisan 1654'te buralardaydı, ama sonra ortadan kayboldu. Gemisi hakkında bana daha fazla bir şey söyleyebilir misin? Belki başına ne geldiğini ya da nereye gittiğini görmüşsündür? Bir şey hatırlıyor musun?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Oh-ho... Evet, Señor, o gerçekten görülmeye değerdi! Böyle şeyler unutulmaz, ha!";
			link.l1 = "Ne olduğunu anlatabilir misin?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Señor Dichoso'nun fırkateyni San Jose limanında demir attı. Her şeyi gayet iyi görebildim, evet. Sana söyleyeyim, harika bir fırkateyndi, tam bir şaheserdi, kanayan kalbim üzerine yemin ederim! Mürettebatı hızından övgüyle bahsediyordu, on altı knot hıza ulaşabiliyormuş! Burada bir gün geçirdiler, sonra doğruca Tobago adasına yelken açtılar. Sonra, inanmazsın, onlar ufukta kaybolur kaybolmaz havada tuhaf şeyler olmaya başladı. O zamanlar günlerce hava açıktı, tek bir bulut yoktu! Ama bu korkunç fırtına birdenbire çıktı. Sanki bizzat Neptün bizi ziyarete gelmiş gibiydi! Fenerimin tepesine çıkıp ışığı yakmaya gittim, ama sonra onu gördüm... Santa Quiteria! Dev dalgaların üzerinde yükseliyordu, yanında kocaman bir hortum vardı! Fırkateyn fenerimin önünden bir kıvılcım gibi geçti ve sonra fırtına tarafından kuzeybatıya sürüklendi! O günden beri Santa Quiteria'yı gören olmadı. Sadece bir saat sonra rüzgar, yağmur, bulutlar kayboldu ve güneş parlıyordu, fırtınadan eser yoktu! Böyle bir şey hiç görmemiştim! Gerçi o gün körfezimden o kadar çok kehribar topladım ki...";
			link.l1 = "Yani fırtına fırkateyni tekrar Karayip Denizi'ne mi sürükledi?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Oldu bile! Ta ötelerde, Martinique tarafına. Dichoso'nun o fırtınadan sağ çıkabildiğini sanmıyorum, ama elinden geleni yapıyordu! Fırkateyn batmıyordu, ama Santa Quiteria şimdiye kadar mercanların arasında denizin dibinde olmalı... Aslında, Dichoso ve fırkateyni hakkında bana soran ilk kişi sen değilsin.";
			link.l1 = "Gerçekten mi? Miguel ile başka kim ilgileniyordu?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "İspanyol filosundan öyle havalı bir kaptan, hem de! Kendini tanıttı... ah... şimdi unuttum... Ha! Señor Diego. Adı Diego'ydu ama soyadı... de Montagna mıydı, de Montoya mıydı. Öyle bir şeydi işte. Tıpkı senin gibi beni dikkatle dinledi, teşekkür etti ve gitti. O günden beri bir daha görmedim onu.";
			if (sti(Pchar.money) >= 5000)
			{
				link.l1 = "Anladım. Hikayeniz için çok teşekkür ederim, bana gerçekten yardımcı oldunuz. Lütfen minnettarlığımın karşılığı olarak bu paraları kabul edin. Hoşça kalın.";
				AddMoneyToCharacter(pchar, -5000);
				AddCharacterExpToSkill(pchar, "Leadership", 250);
			}
			else
			{
				link.l1 = "Anladım. Hikayeniz için çok teşekkür ederim, bana gerçekten çok yardımcı oldunuz. Hoşça kalın.";
			}
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			AddQuestRecord("Guardoftruth", "41");
			pchar.questTemp.Guardoftruth.Trinidad = "mayak";
			pchar.quest.GuardOT_setDiego.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setDiego.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setDiego.function = "GuardOT_SetDiegoOnMayak";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
