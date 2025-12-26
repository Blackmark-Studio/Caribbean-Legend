// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Fale, estou ouvindo";
			link.l1 = "Eu estava enganado. Adeus.";
			link.l1.go = "Exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Oficial, ouvi dizer que há um homem chamado Folke Deluc na sua prisão. Há algo que eu possa fazer para conseguir a libertação dele?";
                link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Oficial, sou eu de novo sobre o prisioneiro Folke Deluc. Comprei os direitos da dívida dele e quero que esse homem seja libertado e entregue a mim. Aqui estão os papéis da dívida dele, dê uma olhada.";
                link.l1.go = "Sharlie_3";
			}	
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Deluck"))
			{
				link.l1 = "Boa tarde, oficial. Gostaria de saber sobre o meu tripulante...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_DeluckSvoboda"))
			{
				link.l1 = "Aqui estão os papéis, agora solte meu homem.";
                link.l1.go = "Del_DeluckSvoboda";
			}
			//<-- Миниквест "Делюк"
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, aquele marinheiro? Ele pegou uma quantia considerável emprestada do nosso banqueiro, não devolveu, e ainda tentou fugir. Mas foi encontrado rapidamente. Desde então, está preso e vai ficar aqui até pagar a dívida.";
			link.l1 = "Hm. E como ele vai fazer isso enquanto estiver preso?";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Não me importo com isso, monsieur.";
			link.l1 = "Engraçado... E quanto essa pobre alma deve?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Não sei. Pergunte ao banqueiro e ele vai te dar os detalhes.";
			link.l1 = "Entendi. Obrigado pela informação, oficial.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskiper";
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", false);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Sharlie_3":
			Log_Info("You have given debt papers");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
			dialog.text = "Hm. Todos estão corretos. Você realmente quer que eu solte esse prisioneiro?";
			link.l1 = "Sim. Preciso que ele pague a dívida, e sei como ele pode fazer isso.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "Certo, não tenho motivo para te recusar. Deluc será trazido aqui em breve. Mas preciso te avisar, essa raposa vai fugir na primeira chance que tiver, então não crie ilusões sobre ele.";
			link.l1 = "Entendo, oficial. Agora quero levar meu devedor.";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Sim, claro. Sargento! Traga o prisioneiro! Folke Deluc, parece que agora ele tem um novo dono!";
			link.l1 = "...";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			DialogExit();
			// создаем штурмана
			sld = InitFolke("Folke", "Deluc");
			pchar.questTemp.Sharlie = "takeskiper";	
			ForceHeroAutolevel(sld);
			AddDialogExitQuestFunction("Del_Turma");
		break;
		//<-- Бремя гасконца
		
		//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
		case "Del_Deluck":
			DelLandQuestMark(npchar);
			dialog.text = "Ha! Digo que as fofocas sobre o seu apuro vão entreter Saint-Pierre por muito tempo. Mas não leve para o lado pessoal, Capitão. Está claro que você foi vítima do azar. Entre e não se preocupe: seu navegador não vai escapar desta conversa, ha ha!";
			link.l1 = "Hilário. Obrigado, oficial.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_prison");
		break;
		
		case "Del_DeluckSvoboda":
			dialog.text = "Entendido, Capitão. Vamos agir conforme combinado.";
			link.l1 = "...";
			link.l1.go = "Del_DeluckSvoboda_2";
			Log_Info("You have given debt papers");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
		break;
		
		case "Del_DeluckSvoboda_2":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			
			sld = CharacterFromID("Folke");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_10";
			
			AddDialogExitQuestFunction("Del_Turma");
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
