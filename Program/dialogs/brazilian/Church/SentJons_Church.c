// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas, "+GetSexPhrase("meu filho","minha filha")+"?","Pode perguntar, estou ouvindo..."),"Estou ouvindo, pode falar. "+GetSexPhrase("meu filho","minha filha")+"...","Pela terceira vez, "+GetSexPhrase("meu filho","minha filha")+", peça o que precisar.","Um clérigo tem muito trabalho e você está me distraindo, "+GetSexPhrase("meu filho","minha filha")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Agora não, padre..."),"Não tenho nada a dizer, me desculpe.","Vou perguntar, mas depois. Me perdoe, padre.","Com licença, padre...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_pastor"))
			{
				link.l1 = "Santo Padre, gostaria de falar sobre a filha de Thomas Morrison.";
                link.l1.go = "dwh_pastor_1";
			}
			if (CheckAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi"))
			{
				link.l1 = "Santo Padre, Thomas me pediu para lhe dizer que aceita o caminho do arrependimento, vai se dedicar às boas ações e vai providenciar um novo sino para a paróquia – custe o que custar.";
                link.l1.go = "dwh_pastor_VD_5";
			}
			// <-- Тёмные воды исцеления
		break;

		// --> Тёмные воды исцеления
		case "dwh_pastor_1":
			dialog.text = "Fale, meu filho, estou ouvindo.";
			link.l1 = "Eu sei que você é contra a cigana ajudar a garota. Mas como pode obrigar um pai a rejeitar até a menor chance de salvar sua filha? Os métodos dela podem ser questionáveis, mas ela tem conhecimentos que podem ajudar.";
			link.l1.go = "dwh_pastor_2";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_2":
			dialog.text = "Meu filho, só o Senhor pode curar a menina. A fé no Seu plano é o que nos sustenta nas provações. Se Thomas orar com devoção, seguir a palavra de Deus e for generoso com a igreja, o Senhor ouvirá suas preces e mostrará misericórdia.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Confiável) Mas até você deve admitir, o Senhor age através das pessoas. E se a cigana for apenas um instrumento da vontade Dele? E se o plano Dele for tão profundo que nós, simples mortais, não conseguimos compreender? O Senhor age de maneiras misteriosas, não é mesmo?";
				link.l1.go = "dwh_pastor_VD_1";
				Notification_Perk(true, "Trustworthy");
			}
			else
			{
				link.l1 = "Você está obrigando um pai a ver sua filha definhar, em vez de deixá-lo tentar salvá-la. Isso é misericordioso?";
				link.l1.go = "dwh_pastor_bez_VD_1";
				Notification_Perk(false, "Trustworthy");
			}
		break;

		case "dwh_pastor_VD_1":
			dialog.text = "Suas palavras são sábias, Capitão. Mas ainda assim, não posso permitir que a heresia se infiltre no coração do nosso rebanho e abale a fé de um dos seus filhos mais devotos.";
			link.l1 = "Nada abalaria mais a fé dele do que perder a filha. Mas se você permitir que ele use todos os meios, até mesmo os considerados pecaminosos, a fé dele vai se fortalecer, não enfraquecer.";
			link.l1.go = "dwh_pastor_VD_2";
		break;

		case "dwh_pastor_VD_2":
			dialog.text = "Mas... que tipo de exemplo isso daria para o resto da congregação?";
			link.l1 = "Um exemplo de que a igreja não pune cegamente, mas orienta e conduz ao verdadeiro arrependimento. As Escrituras não nos ensinam que o arrependimento sincero e as boas ações podem redimir o pecado? Uma doação generosa à igreja pode ser o primeiro passo para a redenção.";
			link.l1.go = "dwh_pastor_VD_3";
		break;

		case "dwh_pastor_VD_3":
			dialog.text = "Talvez você esteja certo, Capitão. Estou disposto a dar essa chance ao Thomas. Mas saiba disto—se ele se desviar do caminho correto e perder a fé, você também será responsável! Quanto às doações—a igreja não precisa de riquezas, temos o que é necessário. Exceto... o sino foi danificado durante o ataque espanhol...";
			link.l1 = "Vou passar suas palavras para Thomas. Obrigado pelo seu tempo, Santo Padre. Que o Senhor o proteja.";
			link.l1.go = "dwh_pastor_VD_4";
		break;

		case "dwh_pastor_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_11";
		break;

		case "dwh_pastor_bez_VD_1":
			dialog.text = "Isso não é falta de coração, Capitão, isso é fé. Não abandonamos o destino da moça, entregamos nas mãos do Senhor. Se Thomas rezar, acreditar e esperar com humildade, tenho certeza de que o Senhor ouvirá nossas preces e irá curá-la.";
			link.l1 = "Sabe, até os nobres da ilha, incluindo o governador, já recorreram aos serviços da cigana. E nenhum deles foi excomungado. Então por que você é tão rigoroso com o Thomas?";
			link.l1.go = "dwh_pastor_bez_VD_2";
		break;

		case "dwh_pastor_bez_VD_2":
			dialog.text = "Claro que eu sei, meu filho. Mas são almas perdidas, ainda não tocadas pela verdadeira luz do Senhor. Thomas é um pilar do nosso rebanho, um dos melhores. Permitir que o mal abale sua fé colocaria toda a igreja em risco, e eu não posso permitir um pecado tão grave.";
			link.l1 = "Então você se recusa a dar nem uma pequena chance? Isso é mesmo justo?";
			link.l1.go = "dwh_pastor_bez_VD_3";
		break;

		case "dwh_pastor_bez_VD_3":
			dialog.text = "O que você chama de salvação pode muito bem levar à ruína. Falo por experiência própria. Uma vez, contra a minha vontade, uma curandeira como ela tratou minha sobrinha. Uma menina pequena, ela morreu em agonia. E só o Senhor sabe se sua alma foi condenada por aqueles rituais. Não tente me convencer—é inútil.";
			link.l1 = "Muito bem. Se essa é sua decisão final, não vou discutir. Que o Senhor te proteja.";
			link.l1.go = "dwh_pastor_bez_VD_4";
		break;

		case "dwh_pastor_bez_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			
			AddQuestRecord("DWH", "4");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetCitizenType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_6";
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto23");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			LAi_CharacterEnableDialog(sld);
		break;

		case "dwh_pastor_VD_5":
			dialog.text = "Excelente, meu filho. Um novo sino será símbolo de sua devoção ao Senhor e à igreja. Deixe que ele faça o que for preciso, mas lembre-o—o olhar do Todo-Poderoso vigia cada ato, e nada escapa à Sua vontade.";
			link.l1 = "Assim seja, Santo Padre. Adeus.";
			link.l1.go = "dwh_pastor_VD_6";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_VD_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_15";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "barmen", "bar1");
			DelLandQuestMark(sld);
			LAi_RemoveLoginTime(sld);
		break;
		// <-- Тёмные воды исцеления
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
