import { Module } from '@nestjs/common';
import { UnoEngine } from './uno.engine';
import { UnoGateway } from './uno.gateway';
import { UnoService } from './uno.service';

@Module({
  providers: [UnoGateway, UnoService, UnoEngine],
})
export class UnoModule {}